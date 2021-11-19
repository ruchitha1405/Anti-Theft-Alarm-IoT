from onem2m import *

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"

# ========================== room for PIR sensor =====================================

ae1 = "Motion"
cnt1 = "node1"

create_ae(uri_cse, ae1)

uri_ae1 = uri_cse + "/" + ae1
create_cnt(uri_ae1, cnt1)

uri_cnt1 = uri_ae1 + "/" + cnt1
create_data_cin(uri_cnt1, "random_value")

# ========================== room for HC-SR04 sensor ===================================

ae2 = "Distance"
cnt2 = "node2"

create_ae(uri_cse, ae2)

uri_ae2 = uri_cse + "/" + ae2
create_cnt(uri_ae2, cnt2)

uri_cnt2 = uri_ae2 + "/" + cnt2
create_data_cin(uri_cnt2, "random_value")

# =========================== room for temperature =====================================

ae3 = "Temperature"
cnt3 = "node3"

create_ae(uri_cse, ae3)

uri_ae3 = uri_cse + "/" + ae3
create_cnt(uri_ae3, cnt3)

uri_cnt3 = uri_ae3 + "/" + cnt3
create_data_cin(uri_cnt3, "random_value")

# =========================== room for humidity =====================================

ae4 = "Humidity"
cnt4 = "node4"

create_ae(uri_cse, ae4)

uri_ae4 = uri_cse + "/" + ae4
create_cnt(uri_ae4, cnt4)

uri_cnt4 = uri_ae4 + "/" + cnt4
create_data_cin(uri_cnt4, "random_value")

