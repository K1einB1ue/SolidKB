import json


with open("./tmp.json",'r') as load_file:
    load_dict = json.load(load_file)
    print(load_dict)