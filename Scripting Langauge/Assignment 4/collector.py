from urllib import request
import sys 
import time

#data field
url = sys.argv[1] + "/stats"
wait = int(sys.argv[3])
outputFile = "record.tsv" 

#Setup time to stop
oneHour = 3600
startTime = time.time()

#Keep reading the stats of website and record to file
with open("record.tsv", "w") as file:
    while True:
        if (startTime == oneHour):
            break
        req = request.urlopen(url)
        data = req.read().decode('utf-8').split("\n")
        for line in data[:4]:
            store = line.split(": ")[1]
            file.write(store + "\t")
        file.write("\n")
        time.sleep(wait)