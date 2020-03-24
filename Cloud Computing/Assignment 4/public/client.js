console.log("Client-side code running");

// Hanldes the Load button. Once clicked, load data from URL into my blob then from blob into Table
const loadButton = document.getElementById("loadButt");
loadButton.addEventListener("click", function(e) {
  console.log("button was clicked");
  fetch("/load", { method: "GET" })
    .then(response => {
      return response.text();
    })
    .then(response => {
        let lines = response.split('\n');
        let ul = document.createElement('ul');
        document.getElementById('queryOut').appendChild(ul);
        for (let i = 0; i < lines.length - 1; i++) {
            let partElement = lines[i].split(" ");
            let elementText = partElement[0] + partElement[1] + '\'s data has been loaded';
            let li = document.createElement('li');
            ul.appendChild(li);
            li.innerHTML += elementText;
        }
    });
});

// Handles the Clear button. Once clicked, delete all data in Blob and Table
const clearButton = document.getElementById("clearButt");
clearButton.addEventListener("click", function(e) {
  console.log("button was clicked");
  fetch("/clear", { method: "GET" })
    .then(response => {
      return response.text();
    })
    .then(response => {
        document.getElementById('queryOut').innerHTML = response;
    });
});

// Handles the Query button. Query Table Storage for information
const queryButton = document.getElementById("queryButt");
const firstText = document.getElementById('firstName');
const lastText = document.getElementById('lastName');
queryButton.addEventListener("click", function(e) {
    let serverEndpoint = '';
    if (firstText && firstText.value && lastText && lastText.value) {
        serverEndpoint = '/query?firstName=' + firstText.value + '&lastName=' + lastText.value;
        hitServer(serverEndpoint);
    } else if (firstText && firstText.value) {
        serverEndpoint = '/query?firstName=' + firstText.value;
        hitServer(serverEndpoint);
    } else if (lastText && lastText.value) {
        serverEndpoint = '/query?lastName=' + lastText.value;
        hitServer(serverEndpoint);
    } else {
        console.log("No input");
    }
});

// Helper Function for query button
function hitServer(endpoint) {
    console.log(endpoint);
    fetch(endpoint, { method: "GET" })
        .then(response => {
            return response.text();
        })
        .then(data => {
            let outputList = data.replace(/{|}|"|\[|\]/g,"");
            outputList = outputList.replace(/:/g, ' = ')
            outputList = outputList.replace(/,/g, ', ')
            outputList = outputList.replace(/lastName/g, '*lastName')
            let messlist = outputList.split('*');

            let ul = document.createElement('ul');
            document.getElementById('queryOut').appendChild(ul);
            console.log(messlist);
            messlist.forEach(line => {
                let li = document.createElement('li');
                ul.appendChild(li);
                li.innerHTML += line;
            })

        });
}