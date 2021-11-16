

# coding=utf-8

import requests
import json
import time




# ====================================================
# Register an AE


def create_ae(uri_cse, ae_name, labels="", fmt_ex="json"):
    """
        Method description:
        Registers an application entity(AE) to the OneM2M framework/tree
        under the specified CSE

        Parameters:
        uri_cse : [str] URI of parent CSE
        ae_name : [str] name of the AE
        labels : [str] labels for the AE
        fmt_ex : [str] payload format
    """

    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/{};ty=2    '.format(fmt_ex)}

    payload = {
        "m2m:ae": {
            "rn": "{}".format(ae_name),
            "api": "Application ID",
            "rr": "false",

        }
    }

    response = requests.post(uri_cse, json=payload, headers=headers)
    print('Return code : {}'.format(response.status_code))
    print('Return Content : {}'.format(response.text))

# ====================================================

# ====================================================
# Create a DESCRIPTOR/DATA CNT (based on cnt_name passed)


def create_cnt(uri_ae, cnt_name="", fmt_ex="json"):
    """
        Method description:
        Creates a container(CON) in the OneM2M framework/tree
        under the specified AE

        Parameters:
        uri_ae : [str] URI for the parent AE
        cnt_name : [str] name of the container (DESCRIPTOR/DATA)
        fmt_ex : [str] payload format
    """

    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/{};ty=3'.format(fmt_ex)}

    payload = {
        "m2m:cnt": {
            "rn": "{}".format(cnt_name),
            "mni": 120,
        }
    }

    response = requests.post(uri_ae, json=payload, headers=headers)
    print('Return code : {}'.format(response.status_code))
    print('Return Content : {}'.format(response.text))


# ====================================================

# ====================================================
# Create a DESCRIPTOR CIN


def create_descriptor_cin(uri_con, fmt_ex="json"):
    """
        Method description:
        Creates a descriptor content instance(desc_CIN) in the OneM2M framework/tree
        under the specified DESCRIPTOR CON

        This holds the detailed description for an specific AE

        Parameters:
        uri_con : [str] URI for the parent DESCRIPTOR CON
        fmt_ex : [str] payload format
    """

    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/{};ty=4'.format(fmt_ex)}

    data = {
        "m2m:cin": {
            "con": {
                "obj": {
                    "str": [{"@name": "type", "@val": "Temperature_Sensor"},
                            {"@name": "location", "@val": "Home"},
                            {"@name": "appId", "@val": "DHT"}],
                    "op": {
                        "@name": "getValue",
                        "@href": "/in-cse/in-name/DHT/DATA/la",
                        "@in": "obix:Nil",
                        "@out": "obix:Nil",
                        "@is": "retrieve"
                    }
                }
            }
        }
    }

    response = requests.post(uri_con, json=data, headers=headers)
    print('Return code : {}'.format(response.status_code))
    print('Return Content : {}'.format(response.text))
# ====================================================

# ====================================================


# Create a DATA CIN
def create_data_cin(uri_cnt, value, fmt_ex="json"):
    """
        Method description:
        Creates a data content instance(data_CIN) in the OneM2M framework/tree
        under the specified DATA CON

        Parameters:
        uri_cnt : [str] URI for the parent DATA CON
        fmt_ex : [str] payload format (json/XML)
    """

    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/{};ty=4'.format(fmt_ex)}

    payload = {
        "m2m:cin": {
            "con": "{}".format(value)
        }
    }

    response = requests.post(uri_cnt, json=payload, headers=headers)
    print('Return code : {}'.format(response.status_code))
    print('Return Content : {}'.format(response.text))

# ====================================================

# ====================================================


def get_data(uri, format="json"):
    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/json'}
# works with /la only with containerInstances as m2m:cin is only in that 
    response = requests.get(uri, headers=headers)
    # print('Return code : {}'.format(response.status_code))
    # print('Return Content : {}'.format(response.text))
    _resp = json.loads(response.text)
    return response.status_code, _resp["m2m:cin"]["con"]

# ====================================================


def discovery(uri, format="json"):
    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/json'}

    #response = requests.get(uri, headers=headers)
    response = requests.get(uri+"?fu=1&rty=3&drt=2", headers=headers)
    # print('Return code : {}'.format(response.status_code))
    # print('Return Content : {}'.format(response.text))
    _resp = json.loads(response.text)
    return response.status_code, _resp["m2m:uril"]

# ====================================================


def get_filtered_uri(uri, filter=""):
    _, filtered_uri = discovery(uri)
    # _, filtered_uri = discovery(server+cse+"?fu=1&"+filter)
    filtered_uri_list = filtered_uri.split(" ")
    # print(filtered_uri_list)
    return filtered_uri_list


def create_group_ae(cse_uri, group_name, uri_list):
    # uri_list = [cse_uri+x.split("/")[-1]+"/DATA"]
    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/json;ty=9'
    }

    payload = {
        "m2m:grp":
            {
                "rn": group_name,
                "mt": 3,
                "mid": uri_list,
                "mnm": 10
            }
    }

    response = requests.post(cse_uri, json=payload, headers=headers)
    print('Return code : {}'.format(response.status_code))
    print('Return Content : {}'.format(response.text))


def get_data_group(group_name):
    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/json'
    }

    group_uri = server+cse+group_name+"/fopt/la"
    response = requests.get(group_uri, headers=headers)
    # print('Return code : {}'.format(response.status_code))
    #print('Return Content : {}'.format(response.text))
    _resp = json.loads(response.text)
    return response.status_code, _resp

# ====================================================
# Delete an AE


def delete_ae(uri, data_format="json"):

    headers = {
        'X-M2M-Origin': 'admin:admin',
        'Content-type': 'application/{}'.format(data_format)}

    response = requests.delete(uri, headers=headers)
    print('Return code : {}'.format(response.status_code))
    #print('Return Content : {}'.format(response.text))
    return
# ====================================================