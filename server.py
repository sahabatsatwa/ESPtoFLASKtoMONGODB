from flask import Flask, request
import pymongo
from bson.json_util import dumps
from datetime import datetime as dtm


connection_url = 'mongodb://cobadatabase:proyek123@cluster0-shard-00-00.sxr4g.gcp.mongodb.net:27017,cluster0-shard-00-01.sxr4g.gcp.mongodb.net:27017,cluster0-shard-00-02.sxr4g.gcp.mongodb.net:27017/Example?ssl=true&replicaSet=atlas-u07olz-shard-0&authSource=admin&retryWrites=true&w=majority'
app = Flask(__name__)
client = pymongo.MongoClient(connection_url)

database = client.get_database('Example')
Suhu = database.suhu

@app.route("/info", methods = ['GET'])
def get_all_contact():
    data = Suhu.find({})
    return dumps(data)

@app.route('/input/suhu', methods = ['POST'])
def post():
    sekarang = dtm.now()
    tgl = dtm.strftime(sekarang, '%d-%b-%Y/%H:%M:%S')
    _json = request.json
    data={'suhu_tubuh': _json, 'waktu': tgl}
    Suhu.insert(data)
#    _suhu = _json['suhu_tubuh']
#    Suhu.insert({'suhu_tubuh': _suhu, 'waktu': tgl})
    print(request.data,tgl)
    return str(data) + "\nBerhasil input data ke Database ..."

app.run(host='0.0.0.0', port= 6969)