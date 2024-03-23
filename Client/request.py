from typing import Dict, List
import requests
from time import sleep
import json


class client():
    def __init__(self, IP, schema, timeout = 5):
        self.IP = IP
        self.timeout = timeout
        f = open(schema)
        dictionaries = json.load(f)
        for x in dictionaries:
            name = x.get('name')
            method = x.get('type')
            endpt = x.get('endpoint')
            parameters = x.get('parameters')

            self.load(name, method, endpt, parameters)

        f.close()
        pass

    callback = {}
    def load(self,name,method,endpt,parameters):
        
        if method == "get":
            fn = lambda **kwargs: self.get(endpt, kwargs, parameters)

        elif method == "post":
            fn = lambda **kwargs: self.post(endpt, kwargs, parameters)

        self.callback[name] = fn

        pass
        

    def get(self, endpoint, kwargs, parameters=None):
        req = "http://" + self.IP + endpoint

        params = None
        if parameters is not None:
            params = {}
            for param in parameters:
                params[param] = kwargs[param]
        
        res = requests.get(req,
                           timeout=self.timeout,
                           params=params)
        response = float(res.text)

        return response
    
    def post(self, endpoint, kwargs, parameters=None):
        req = "http://" + self.IP + endpoint

        params = None
        if parameters is not None:
            params = {}
            for param in parameters:
                params[param] = kwargs[param]

        requests.post(req,
                    timeout=self.timeout,
                    params=params)

        return None
    

    def __call__(self, fn: str, **kwargs):
        return self.callback[fn](**kwargs)

exp = client("0.0.0.0",'requests.json')
print(exp("set_dac_delay", channel = 0))

