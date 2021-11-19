from datetime import datetime

import requests
import json
import matplotlib.pyplot as plt

# ================================ Motion retrieval ==========================================

ae1 = "Motion"
cnt1 = "node1"

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
uri_ae1 = uri_cse + "/" + ae1
uri_cnt1 = uri_ae1 + "/" + cnt1

uri_req1 = uri_cnt1 + "/?rcn=4"

headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}

response1 = requests.get(uri_req1, headers=headers)
res1 = json.loads(response1.text)
# print(res)

cins1 = res1["m2m:cnt"]["m2m:cin"]

x1 = []
y1 = []

for cin in cins1:
    dt = datetime.strptime(cin["ct"], '%Y%m%dT%H%M%S')
    x1.append(dt)
    y1.append(float(cin["con"]))



plt.plot(x1, y1)
plt.xlabel("time")
plt.ylabel("Motion")

plt.gcf().autofmt_xdate()
plt.show()
plt.savefig('motion.jpg')

# ===================================== Distance retrieval ==========================================

ae2 = "Distance"
cnt2 = "node2"

uri_ae2 = uri_cse + "/" + ae2
uri_cnt2 = uri_ae2 + "/" + cnt2

uri_req2 = uri_cnt2 + "/?rcn=4"

headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}

response2 = requests.get(uri_req2, headers=headers)
res2 = json.loads(response2.text)
# print(res)

cins2 = res2["m2m:cnt"]["m2m:cin"]

x2 = []
y2 = []

for cin in cins2:
    dt = datetime.strptime(cin["ct"], '%Y%m%dT%H%M%S')
    x2.append(dt)
    y2.append(float(cin["con"]))



plt.plot(x2, y2)
plt.xlabel("time")
plt.ylabel("Distance")

plt.gcf().autofmt_xdate()
plt.show()
plt.savefig('distance.jpg')

# ===================================== temperature retrieval ===============================

ae3 = "Temperature"
cnt3 = "node3"

uri_ae3 = uri_cse + "/" + ae3
uri_cnt3 = uri_ae3 + "/" + cnt3

uri_req3 = uri_cnt3 + "/?rcn=4"

headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}

response3 = requests.get(uri_req3, headers=headers)
res3 = json.loads(response3.text)
# print(res)

cins3 = res3["m2m:cnt"]["m2m:cin"]

x3 = []
y3 = []

for cin in cins3:
    dt = datetime.strptime(cin["ct"], '%Y%m%dT%H%M%S')
    x3.append(dt)
    y3.append(float(cin["con"]))



plt.plot(x3, y3)
plt.xlabel("time")
plt.ylabel("Distance")

plt.gcf().autofmt_xdate()
plt.show()
plt.savefig('temperature.jpg')

# ================================= humidity retrieval =======================================

ae4 = "Humidity"
cnt4 = "node4"

uri_ae4 = uri_cse + "/" + ae4
uri_cnt4 = uri_ae3 + "/" + cnt4

uri_req4 = uri_cnt4 + "/?rcn=4"

headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}

response4 = requests.get(uri_req4, headers=headers)
res4 = json.loads(response4.text)
# print(res)

cins4 = res4["m2m:cnt"]["m2m:cin"]

x4 = []
y4 = []

for cin in cins4:
    dt = datetime.strptime(cin["ct"], '%Y%m%dT%H%M%S')
    x4.append(dt)
    y4.append(float(cin["con"]))



plt.plot(x4, y4)
plt.xlabel("time")
plt.ylabel("Humidity")

plt.gcf().autofmt_xdate()
plt.show()
plt.savefig('humidity.jpg')



