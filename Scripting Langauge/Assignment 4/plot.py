import matplotlib.pyplot as graph 
import sys
from datetime import datetime

#default values
fileName = sys.argv[1]
dt = 60

#if user provides a flag
if (len(sys.argv) > 2) and sys.argv[2] == "--delta_t" :
    dt = int(sys.argv[3])
else:
    print("incorrect argv")
    sys.exit()

#find the time interval of data from collector.py
timeJump = []
with open(fileName) as file:
    for i, line in enumerate(file):
        if(i > 1):
            break
        lineList = line.split()
        timeJump.append(int(lineList[0]))
        print(i)
interval = dt // (timeJump[1] - timeJump[0])

#get all the values basied on the interval 
timeList = []
list200 = []
list404 = []
list500 = []
with open(fileName) as file:
    for i, line in enumerate(file):
        if( (i % interval) == 0):
            lineList = line.split()
            timeList.append(int(lineList[0]))
            list500.append(int(lineList[1]))
            list200.append(int(lineList[2]))
            list404.append(int(lineList[3]))

#getting the change per each interval
timeline = []
new200 = []
new404 = []
new500 = []
for i in range(1, len(list200)):
    new200.append(list200[i] - list200[i-1])
    new404.append(list404[i] - list404[i-1])
    new500.append(list500[i] - list500[i-1])
    timeline.append(timeList[i])

#setting the timeline for the graph
for i, time in enumerate(timeline):
    date = datetime.fromtimestamp(int(time))
    timeline[i] = str(date.hour) + ":" + str(date.minute)

#plot the graph using pyplot
fig = graph.figure()
graph.plot(timeline, new200, label = '200s')
graph.plot(timeline, new404, label = '404s')
graph.plot(timeline, new500, label = '500s')
graph.ylabel("RPS(%d minute rate)" % (dt // 60))
graph.xlabel('Time')
graph.legend()
graph.title("Time Server Requests Over an Hour")

fig.savefig('graph.jpg')
graph.show()