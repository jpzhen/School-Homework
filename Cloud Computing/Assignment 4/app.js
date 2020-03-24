const express = require('express');
const app = express();
const fetch = require('node-fetch');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const azure = require('azure-storage');
const AZURE_STORAGE_CONNECTION_STRING = 'your azure connection string';

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// serve files from the public directory
app.use(express.static('public'));

// start the express web server listening on 8080
var port = normalizePort(process.env.PORT || '8081');
app.listen(port, () => {
    console.log('listening on 8081');
});

// Workers variables to communicate with Azure Storage
let tableClient = azure.createTableService(AZURE_STORAGE_CONNECTION_STRING);
let blobClient = azure.createBlobService(AZURE_STORAGE_CONNECTION_STRING);

// serve the homepage
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/public/index.html');
});

// Reponse to the Query Button
app.get('/query', (req, res) => {
    let reqObj = Object.keys(req.query);
    let reqArr = [];
    let tableQ = new azure.TableQuery();
    if (reqObj.length == '2') {
        reqObj.forEach(k => {
            reqArr.push(req.query[k]);
        });
        console.log(reqArr[0] + " " + reqArr[1]);
        tableQ = new azure.TableQuery().where('firstName == ? and lastName == ?', reqArr[0], reqArr[1]);
    } else if (reqObj.length == '1') {
        let objKey = reqObj[0].toString()
        let value = req.query[objKey];
        if (reqObj[0].toString() == 'lastName') {
            tableQ = new azure.TableQuery().where('lastName == ?', value);
        } else {
            tableQ = new azure.TableQuery().where('firstName == ?', value);
        }
    } else {
        res.send('Incorrect query parameter(s)');
    }
    tableClient.queryEntities('prog4table', tableQ, null, (error, result, response) => {
        if (!error) {
            let resEntries = result.entries;
            let outputArr = [];
            if (resEntries.length != 0) {
                resEntries.forEach(entry => {
                    let outputs = {};
                    Object.keys(entry).forEach(k => {
                        if (k !== ".metadata" && k !== 'PartitionKey' && k !== 'RowKey' && k !== 'Timestamp') {
                            let prop = Object.getOwnPropertyDescriptor(entry, k);
                            if (prop) {
                                outputs[k] = prop.value["_"];
                            }
                        }
                    })
                    outputArr.push(outputs);
                })
                res.send(outputArr);
            } else {
                res.send('No data found');
            }
        } else {
            res.send("No data found");
        }
    })
});

// Response to the Load Button
app.get('/load', (req, res) => {
    // Fetch from given url
    let blobUrl = '';
    fetch('https://s3-us-west-2.amazonaws.com/css490/input.txt', { method: 'GET'}) 
    .then(urlResponse1 => {
        return urlResponse1.text();
    }).then(urlResponse2 => {
        blobUrl = queryBlob(urlResponse2);
        console.log(blobUrl);
    });

    // Fetch from my azure blob storage
    setTimeout(() => {
    fetch(blobUrl, { method: 'GET' }).then(blobResponse1 => {
            return blobResponse1.text();
    }).then(blobResponse2 => {
        let sortedData = sortData(blobResponse2);
        entryBuilder(sortedData);
        res.send(sortedData);
    });
    }, 3000);
});

// Response to the Clear Button
app.get('/clear', async (req, res) => {
    tableClient.deleteTable('prog4table', (error, response) => {
        if (error) {
            console.log("ERROR AT DELETING TABLE");
        }
    });
    blobClient.deleteBlob('program4inputs', 'textblob.txt', (error, response) => {
        if (!error) {
            res.status(200).send('Success all data deleted');
        } else {
            console.log(response);
            res.status(404).send('No data to delete');
            return;
        }
    });
});

// Add to blob storage
function queryBlob(uploadInputs) {
    blobClient.createBlockBlobFromText('program4inputs', 'textblob.txt', uploadInputs, { contentSettings: { contentType: 'text/plain' } },function(error, result, response) {
        if (!error) {
        // file uploaded
        console.log('load successful');
        }
    });
    let url = blobClient.getUrl('program4inputs') + '/textblob.txt';
    return url;
}

// Add entries to table
function queryTable(uploadInput) {
    tableClient.createTableIfNotExists('prog4table', (error, result, response) => {
        if (!error) {
            console.log('table exist!');
            tableClient.insertEntity('prog4table', uploadInput, (error, result, response) => {
            if (!error) {
                console.log('success add entry');
            } else {
                console.log(response);
            }
        });
        } else {
            console.log(response);
        }
    });
}

//Create an entry that can be used to insert onto table storage
function entryBuilder(inputData) {
    let entGen = azure.TableUtilities.entityGenerator;
    console.log(inputData);
    let lines = inputData.split('\n');
    for (let i = 0; i < lines.length - 1; i++) {
        let lineArr = lines[i].split(' ');
        let jsonObj = {
            PartitionKey: entGen.String(lineArr[0] + lineArr[1]),
            RowKey: entGen.String(i.toString())
        };
        for (let j = 0; j < lineArr.length; j++) {
            if (lineArr[j].includes('=')) {
                let keyvalue = lineArr[j].split('=');
                if (keyvalue[0] != null && keyvalue[1] != null) {
                    jsonObj[keyvalue[0]] = entGen.String(keyvalue[1]);
                }
                else if (lineArr[0] != null) {
                    jsonObj[keyvalue[0]] = entGen.String('');
                }
            } else if (j == 0) {
                jsonObj['lastName'] = entGen.String(lineArr[j]);
            } else if (j == 1) {
                jsonObj['firstName'] = entGen.String(lineArr[j]);
            }
        }
        queryTable(jsonObj);
    }
}

// Elimnates extra spaces
function sortData(inputData) {
    let lines = inputData.split('\n');
    let newString = '';
    for (let i = 0; i < lines.length - 1; i++)  {
        let newline = lines[i].replace(/\s+/g, ' ').trim();
        newString += newline + '\n';
    }
    console.log(newString);
    return newString;
}

function normalizePort(val) {
    var port = parseInt(val, 10);

    if (isNaN(port)) {
        // named pipe
        return val;
    }

    if (port >= 0) {
        // port number
        return port;
    }
    return false;
}
