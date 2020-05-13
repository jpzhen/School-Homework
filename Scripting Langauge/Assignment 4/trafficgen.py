import sys
import time
import random
from urllib import error
from urllib import request

# Store cmd line args
url = sys.argv[1]
rps = int(sys.argv[2])
jitter = float(sys.argv[3])

#calculate the range with the jitter

#continue hit the server with different probabilities of requets
while True:
    jitRps = random.randint(int(rps * (1 - jitter)), int(rps * (1 + jitter)))
    start = time.time()
    for i in range(jitRps):
        chance = random.randint(0, 100)
        try:
            if chance in range(0,25):
                request.urlopen(url + '/garabge', timeout= 10000) #404
            elif chance in range(26, 51):
                request.urlopen(url + '/fail', timeout= 10000) #500
            else:
                request.urlopen(url, timeout= 10000) #200
        except error.HTTPError:
            continue
    time.sleep(1)
