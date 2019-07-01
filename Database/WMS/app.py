# -*- coding: UTF-8 -*-
from flask import Flask, render_template, request
import pymysql
import json
import datetime, time
import string


# 使用python自带的json，将数据转换为json数据时，datetime格式的数据报错
# 重写构造json类，遇到日期特殊处理，其余的用内置的就行。
class DateEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime.datetime):
            return obj.strftime('%Y-%m-%d %H:%M:%S')
        elif isinstance(obj, datetime.date):
            return obj.strftime("%Y-%m-%d")
        else:
            return json.JSONEncoder.default(self, obj)


db = pymysql.connect("localhost", "root", "89667431", "Depot", charset='utf8')
cursor = db.cursor()
app = Flask(__name__)

ByDepotID = '0'
ByDepotName = '1'
ByClientID = '2'
ByClientName = '3'
BySupplierID = '4'
BySupplierName = '5'
ByGoodsID = '6'
ByGoodsName = '7'
ByStatus = '8'
ByWorkerID = '9'
ByWorkerName = '10'
ByWorkerSex = '11'
ByWorkerAge = '12'
ByWorkerType = '13'


def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass

    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass

    return False


@app.route("/login")
def login():
    UserName = request.args.get('ID')
    UserType = request.args.get('Type')
    if UserName == "":
        return json.dumps({'code': 1, 'data': {}})
    if UserType == "":
        return json.dumps({'code': 2, 'data': {}})
    sql = "select * from Worker where ID = '%s' and WorkerType = '%s'" % (UserName, UserType)
    try:
        count = cursor.execute(sql)
        if count == 0:
            return json.dumps({'code': 3, 'data': {}}, ensure_ascii=False)
        result = cursor.fetchone()

        return json.dumps(
            {'code': 0, 'data': {'ID': result[0], 'PWD': result[1], 'Name': result[2], 'Sex': result[3],
                                 'Age': result[4], 'Tel': result[5], 'WorkerType': result[6]}}, ensure_ascii=False)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetStorage")
def GetStorage():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    SS = request.args.get('SS')
    EE = request.args.get('EE')
    sql = ""
    if Kind == None or Info == None:
        sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
              "from storage,Supplier,depot,worker a,Goods " \
              "where storage.DepotID = depot.ID and " \
              "storage.SupplierID = Supplier.ID and " \
              "storage.PurchaseID = a.ID and " \
              "storage.GoodsID = Goods.ID and " \
              "storage.Date between '%s' and '%s' ;" % (SS, EE)
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "storage.DepotID = %d and " \
                  "storage.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByDepotName:
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "Depot.Name  Like '%%%s%%' and " \
                  "storage.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == BySupplierID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "storage.SupplierID = %d and " \
                  "storage.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == BySupplierName:
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "Supplier.Name  Like '%%%s%%' and " \
                  "storage.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "storage.GoodsID = %d and " \
                  "storage.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByGoodsName:
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "Goods.Name Like '%%%s%%' and " \
                  "storage.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByStatus:
            sql = "select storage.*,Depot.Name,Supplier.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from storage,Supplier,depot,worker a,Goods " \
                  "where storage.DepotID = depot.ID and " \
                  "storage.SupplierID = Supplier.ID and " \
                  "storage.PurchaseID = a.ID and " \
                  "storage.GoodsID = Goods.ID and " \
                  "storage.Status = '%s' and " \
                  "storage.Date between '%s' and '%s' ;" % (Info, SS, EE)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'DepotID': result[1], 'DepotName': result[10], 'GoodsID': result[2],
                       'GoodsName': result[13], 'Price': result[3], 'Count': result[4],
                       'SupplierID': result[5], 'SupplierName': result[11], 'Date': result[6], 'Status': result[8],
                       'PurchaseID': result[7], 'PurchaseName': result[12], 'ReviewID': result[9], 'Detail': result[14]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetDelivery")
def GetDelivery():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    SS = request.args.get('SS')
    EE = request.args.get('EE')
    sql = ""
    if Kind == None or Info == None:
        sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
              "from Delivery,client,depot,worker a,Goods " \
              "where Delivery.DepotID = depot.ID and " \
              "Delivery.ClientID = client.ID and " \
              "Delivery.SellerID = a.ID and " \
              "Delivery.GoodsID = Goods.ID and " \
              "Delivery.Date between '%s' and '%s' ;" % (SS, EE)
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.DepotID = %d and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByDepotName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Depot.Name  Like '%%%s%%' and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByClientID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.ClientID = %d and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByClientName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "client.Name  Like '%%%s%%' and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.GoodsID = %d and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByGoodsName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Goods.Name Like '%%%s%%' and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByStatus:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.Status = '%s' and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'DepotID': result[1], 'DepotName': result[10], 'GoodsID': result[2],
                       'GoodsName': result[13], 'Price': result[3], 'Count': result[4],
                       'ClientID': result[5], 'ClientName': result[11], 'Date': result[6], 'Status': result[8],
                       'SellerID': result[7], 'SellerName': result[12], 'ReviewID': result[9], 'Detail': result[14]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetLackOfGoods")
def GetLackOfGoods():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    SS = request.args.get('SS')
    EE = request.args.get('EE')
    sql = ""
    if Kind == None or Info == None:
        sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
              "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
              "where Delivery.DepotID = depot.ID and " \
              "Delivery.ClientID = client.ID and " \
              "Delivery.SellerID = a.ID and " \
              "Delivery.GoodsID = Goods.ID and " \
              "LackOfGoods.ID = Delivery.ID and " \
              "Delivery.Date between '%s' and '%s' ;" % (SS, EE)
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.DepotID = %d and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByDepotName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Depot.Name  Like '%%%s%%' and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByClientID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.ClientID = %d and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByClientName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "client.Name  Like '%%%s%%' and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
        elif Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Delivery.GoodsID = %d and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (int(Info), SS, EE)
        elif Kind == ByGoodsName:
            sql = "select Delivery.*,Depot.Name,Client.Name,a.Name,Goods.Name,Goods.Introduction " \
                  "from Delivery,client,depot,worker a,Goods,LackOfGoods " \
                  "where Delivery.DepotID = depot.ID and " \
                  "Delivery.ClientID = client.ID and " \
                  "Delivery.SellerID = a.ID and " \
                  "Delivery.GoodsID = Goods.ID and " \
                  "Goods.Name Like '%%%s%%' and " \
                  "LackOfGoods.ID = Delivery.ID and " \
                  "Delivery.Date between '%s' and '%s' ;" % (Info, SS, EE)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'DepotID': result[1], 'DepotName': result[10], 'GoodsID': result[2],
                       'GoodsName': result[13], 'Price': result[3], 'Count': result[4],
                       'ClientID': result[5], 'ClientName': result[11], 'Date': result[6], 'Status': result[8],
                       'SellerID': result[7], 'SellerName': result[12], 'ReviewID': result[9], 'Detail': result[14]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetInventory")
def GetInventory():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""
    if Kind == None or Info == None:
        sql = "select Inventory.*,Depot.Name DepotName,Goods.Name GoodsName,Goods.Introduction Detail " \
              "from Inventory,depot,Goods " \
              "where Inventory.DepotID = depot.ID and " \
              "Inventory.GoodsID = Goods.ID"
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Inventory.*,Depot.Name DepotName,Goods.Name GoodsName,Goods.Introduction Detail " \
                  "from Inventory,depot,Goods " \
                  "where Inventory.DepotID = depot.ID and " \
                  "Inventory.GoodsID = Goods.ID and " \
                  "Inventory.DepotID = %d " % (int(Info))
        elif Kind == ByDepotName:
            sql = "select Inventory.*,Depot.Name DepotName,Goods.Name GoodsName,Goods.Introduction Detail " \
                  "from Inventory,depot,Goods " \
                  "where Inventory.DepotID = depot.ID and " \
                  "Inventory.GoodsID = Goods.ID and " \
                  "Depot.Name Like '%%%s%%' " % (Info)
        elif Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select Inventory.*,Depot.Name DepotName,Goods.Name GoodsName,Goods.Introduction Detail " \
                  "from Inventory,depot,Goods " \
                  "where Inventory.DepotID = depot.ID and " \
                  "Inventory.GoodsID = Goods.ID and " \
                  "Inventory.GoodsID = %d " % (int(Info))
        elif Kind == ByGoodsName:
            sql = "select Inventory.*,Depot.Name DepotName,Goods.Name GoodsName,Goods.Introduction Detail " \
                  "from Inventory,depot,Goods " \
                  "where Inventory.DepotID = depot.ID and " \
                  "Inventory.GoodsID = Goods.ID and " \
                  "Goods.Name  Like '%%%s%%' " % (Info)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'DepotID': result[2], 'DepotName': result[3], 'GoodsID': result[0], 'GoodsName': result[4],
                       'Inventory': result[1], 'GoodsDetail': result[5]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetOutOfStock")
def GetOutOfStock():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""

    if Kind == None or Info == None:
        sql = "select * from OutOfStock"
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from OutOfStock where DepotID = %d " % (int(Info))
        elif Kind == ByDepotName:
            sql = "select * from OutOfStock where DepotName  Like '%%%s%%' " % (Info)
        elif Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from OutOfStock where GoodsID = %d " % (int(Info))
        elif Kind == ByGoodsName:
            sql = "select * from OutOfStock where GoodsName  Like '%%%s%%' " % (Info)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'DepotID': result[2], 'DepotName': result[4], 'GoodsID': result[0], 'GoodsName': result[3],
                       'Inventory': result[1], 'MinInventory': result[5], 'Detail': result[6]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetDepot")
def GetDepot():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""

    if Kind == None or Info == None:
        sql = "select * from Depot"
    else:
        if Kind == ByDepotID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Depot where ID = %d " % (int(Info))
        elif Kind == ByDepotName:
            sql = "select * from Depot where Name  Like '%%%s%%' " % (Info)

    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'Name': result[1], 'City': result[2],'Tel':result[3]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetGoods")
def GetGoods():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""

    if Kind == None or Info == None:
        sql = "select * from Goods"
    else:
        if Kind == ByGoodsID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Goods where ID = %d " % (int(Info))
        elif Kind == ByGoodsName:
            sql = "select * from Goods where Name  Like '%%%s%%' " % (Info)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'Name': result[1], 'Introduction': result[2], 'MinInventory': result[3]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetWorker")
def GetWorker():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""

    if Kind == None or Info == None:
        sql = "select * from Worker"
    else:
        if Kind == ByWorkerID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Worker where ID = %d " % (int(Info))
        elif Kind == ByWorkerName:
            sql = "select * from Worker where Name Like '%%%s%%' " % (Info)
        elif Kind == ByWorkerSex:
            sql = "select * from Worker where Sex = '%s' " % (Info)
        elif Kind == ByWorkerType:
            sql = "select * from Worker where WorkerType = '%s' " % (Info)
        elif Kind == ByWorkerAge:
            Age = Info.split('-')
            num = len(Age)
            begin = ""
            end = ""
            if num == 1:
                begin = Age[0]
                end = 200
            elif num == 2:
                if Age[0] == "":
                    begin = 0
                    end = Age[1]
                elif Age[1] == "":
                    begin = Age[0]
                    end = 200
                else:
                    begin = Age[0]
                    end = Age[1]

            if is_number(begin) == False or is_number(end) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Worker where Age between %d and %d " % (int(begin), int(end))
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'Name': result[2], 'Sex': result[3], 'Age': result[4], 'Tel': result[5],
                       'Type': result[6]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetClient")
def GetClient():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')

    sql = ""
    if Kind == None or Info == None:
        sql = "select * from Client"
    else:
        if Kind == ByClientID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Client where ID = %d " % (int(Info))
        elif Kind == ByClientName:
            sql = "select * from Client where Name Like '%%%s%%' " % (Info)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'Name': result[1], 'City': result[2], 'Tel': result[3]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


@app.route("/GetSupplier")
def GetSupplier():
    Kind = request.args.get('Kind')
    Info = request.args.get('Info')
    sql = ""

    if Kind == None or Info == None:
        sql = "select * from Supplier"
    else:
        if Kind == BySupplierID:
            if is_number(Info) == False:
                return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
            sql = "select * from Supplier where ID = %d " % (int(Info))
        elif Kind == BySupplierName:
            s = "\x25"
            sql = "select * from Supplier where Name Like '%%%s%%' " % (Info)
    try:
        count = cursor.execute(sql)
        if (count == 0):
            return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)
        results = cursor.fetchall()
        text = []
        for result in results:
            content = {'ID': result[0], 'Name': result[1], 'City': result[2], 'Tel': result[3]}
            text.append(content)
        return json.dumps({'code': 0, 'data': text}, ensure_ascii=False, cls=DateEncoder)
    except:
        print("Error: unable to fecth data")
        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False, cls=DateEncoder)


def HandleLackOfGoods(GoodsID, DepotID):
    try:
        # 查找是否有可处理的缺货单
        sql = "select Delivery.* " \
              "from LackOfGoods,Delivery,Inventory " \
              "where LackOfGoods.ID = Delivery.ID and " \
              "Inventory.GoodsID = Delivery.GoodsID and " \
              "Inventory.DepotID = Delivery.DepotID and " \
              "Delivery.GoodsID = %d and " \
              "Delivery.DepotID = %d " \
              "order by Delivery.Date asc" % (int(GoodsID), int(DepotID))
        count = cursor.execute(sql)
        if (count != 0):
            results = cursor.fetchall()
            for result in results:
                ID = result[0]
                sql1 = "Delete from LackOfGoods where ID = %d" % (int(ID))
                sql2 = "update Inventory set Inventory = Inventory - %f where GoodsID = %d and DepotID= %d and Inventory >= %f" % (
                    float(result[4]), int(GoodsID), int(DepotID), float(result[4]))
                count2 = cursor.execute(sql2)
                if count2 != 0:
                    cursor.execute(sql1)
                    db.commit()
                else:
                    break
    except:
        db.rollback()


@app.route("/UpdateStatus")
def UpdateStatus():
    ID = request.args.get('ID')
    table = request.args.get('table')
    ReviewID = request.args.get('ReviewID')
    now = time.strftime("%Y-%m-%d %H:%M:%S")
    DepotID = request.args.get('DepotID')
    GoodsID = request.args.get('GoodsID')
    Count = request.args.get('Count')

    if (ID == "" or table == "" or ReviewID == ""):
        return json.dumps({'code': 1, 'data': {}})

    sql = ""
    sql1 = ""
    sql2 = ""
    if table == '0':
        sql = "update Storage set ReviewID = '%s',Status = %d,Date = '%s' where ID = %d" % (ReviewID, 1, now, int(ID))
        sql1 = "update Inventory set Inventory = Inventory + %f where GoodsID = %d and DepotID= %d" % (
            float(Count), int(GoodsID), int(DepotID))
        sql2 = "insert into Inventory(GoodsID,Inventory,DepotID) values (%d,%f,%d)" % (
            int(GoodsID), float(Count), int(DepotID))
    elif table == '1':
        sql = "update Delivery set ReviewID = '%s',Status = %d,Date = '%s' where ID = %d" % (ReviewID, 1, now, int(ID))
        sql1 = "update Inventory set Inventory = Inventory - %f where GoodsID = %d and DepotID= %d and Inventory>=%f" % (
            float(Count), int(GoodsID), int(DepotID), float(Count))
        sql2 = "insert into LackOfGoods values (%d)" % (int(ID))
    try:
        # 执行update语句
        cursor.execute(sql)
        db.commit()
        try:
            count = cursor.execute(sql1)
            if (count == 0):
                if (table == '0'):  # 插入新的库存
                    try:
                        cursor.execute(sql2)
                        db.commit()
                        # 处理缺货单
                        HandleLackOfGoods(GoodsID, DepotID)
                        return json.dumps({'code': 0, 'data': {}}, ensure_ascii=False)
                    except:
                        db.rollback()
                elif (table == '1'):  # 更新缺货单
                    try:
                        cursor.execute(sql2)
                        db.commit()
                        return json.dumps({'code': 2, 'data': {}}, ensure_ascii=False)
                    except:
                        return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False)
            else:
                db.commit()
                if table == '0':
                    HandleLackOfGoods(GoodsID, DepotID)
                return json.dumps({'code': 0, 'data': {}}, ensure_ascii=False)
        except:
            db.rollback()
    except:
        db.rollback()
    return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False)


@app.route("/Update")
def Update():
    ID = request.args.get('ID')
    table = request.args.get('table')
    DepotID = request.args.get('DepotID')
    GoodsID = request.args.get('GoodsID')
    Price = request.args.get('Price')
    Count = request.args.get('Count')
    SupplierID = request.args.get('SupplierID')
    now = time.strftime("%Y-%m-%d %H:%M:%S")

    Name = request.args.get('Name')
    City = request.args.get('City')
    Tel = request.args.get('Tel')

    if (ID == "" or table == "" or DepotID == "" or GoodsID == "" or Price == "" or Count == "" or SupplierID == ""):
        return json.dumps({'code': 1, 'data': {}})

    sql = ""
    if table == '0':
        sql = "update Storage set DepotID = %d,GoodsID = %d,Price = %f,Count = %f,SupplierID = %d,Date = '%s'  " \
              " where ID = %d" % (int(DepotID), int(GoodsID), float(Price), float(Count), int(SupplierID), now, int(ID))
    elif table == '1':
        sql = "update Delivery set DepotID = %d,GoodsID = %d,Price = %f,Count = %f,ClientID = %d,Date = '%s'  " \
              " where ID = %d" % (int(DepotID), int(GoodsID), float(Price), float(Count), int(SupplierID), now, int(ID))
    elif table == '5':
        sql = "update Depot set Name = '%s',City = '%s',Tel = '%s' where ID = %d"%(Name,City,Tel,int(ID))
    elif table == '6':
        sql = "update Goods set Name = '%s',Introduction = '%s',MinInventory = '%s' where ID = %d"%(Name,City,Tel,int(ID))
    elif table == '8':
        sql = "update Client set Name = '%s',City = '%s',Tel = '%s' where ID = %d"%(Name,City,Tel,int(ID))
    elif table == '9':
        sql = "update Supplier set Name = '%s',City = '%s',Tel = '%s' where ID = %d"%(Name,City,Tel,int(ID))
    try:
        cursor.execute(sql)
        db.commit()
        return json.dumps({'code': 0, 'data': {}}, ensure_ascii=False)
    except:
        db.rollback()
    return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False)


@app.route("/Insert")
def Insert():
    table = request.args.get('table')
    DepotID = request.args.get('DepotID')
    GoodsID = request.args.get('GoodsID')
    Price = request.args.get('Price')
    Count = request.args.get('Count')
    ClientID = request.args.get('ClientID')
    WorkerID = request.args.get('WorkerID')
    now = time.strftime("%Y-%m-%d %H:%M:%S")

    Name = request.args.get('Name')
    City = request.args.get('City')
    Tel = request.args.get('Tel')

    if ( table == "" or DepotID == "" or GoodsID == "" or Price == "" or Count == "" or ClientID == "" or WorkerID == ""):
        return json.dumps({'code': 1, 'data': {}})

    sql = ""
    if table == '0':
        sql = "insert into Storage(DepotID,GoodsID,Price,Count,SupplierID,Date,PurchaseID,Status,ReviewID) " \
              "values (%d,%d,%f,%f,%d,'%s','%s',%d,null)" % (
                  int(DepotID), int(GoodsID), float(Price), float(Count), int(ClientID), now, WorkerID, 0)
    elif table == '1':
        sql = "insert into Delivery(DepotID,GoodsID,Price,Count,ClientID,Date,SellerID,Status,ReviewID) " \
              "values (%d,%d,%f,%f,%d,'%s','%s',%d,null)" % (
                  int(DepotID), int(GoodsID), float(Price), float(Count), int(ClientID), now, WorkerID, 0)
    elif table == '5':
        sql = "insert into Depot(Name,City,Tel) values('%s','%s','%s')"%(Name,City,Tel)
    elif table == '6':
        sql = "insert into Goods(Name,Introduction,MinInventory) values('%s','%s','%s')"%(Name,City,Tel)
    elif table == '8':
        sql = "insert into Client(Name,City,Tel) values('%s','%s','%s')"%(Name,City,Tel)
    elif table == '9':
        sql = "insert into Supplier(Name,City,Tel) values('%s','%s','%s')"%(Name,City,Tel)
    try:
        cursor.execute(sql)
        db.commit()
        return json.dumps({'code': 0, 'data': {}}, ensure_ascii=False)
    except:
        db.rollback()
    return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False)


@app.route("/Delete")
def Delete():
    table = request.args.get('table')
    ID = request.args.get('ID')

    if (table == "" or ID == ""):
        return json.dumps({'code': 1, 'data': {}})

    sql = "delete from %s where ID = %d" % (table, int(ID))
    try:
        cursor.execute(sql)
        db.commit()
        return json.dumps({'code': 0, 'data': {}}, ensure_ascii=False)
    except:
        db.rollback()
    return json.dumps({'code': 1, 'data': {}}, ensure_ascii=False)


if __name__ == "__main__":
    app.run(debug=True, host='127.0.0.1', port=8888)
