from flask import Flask
from flask import jsonify
from flask import request

from mysql.connector import connect

from datetime import datetime


app = Flask(__name__)


@app.route('/users', methods=['GET'])
def getUsers():
    db = connect(host="localhost", user="root", passwd="root", database="cash_app_db")
    cursor = db.cursor(buffered=True)

    users_query = "SELECT * FROM user"
    cursor.execute(users_query)
    users = cursor.fetchall()

    for user in users:
        print(user)

    cursor.close()
    db.close()
    return jsonify(users)


@app.route('/login', methods=['POST'])
def login():
    db = connect(host="localhost", user="root", passwd="root", database = "cash_app_db")
    cursor = db.cursor(buffered=True)


    request_data = request.get_json()

    email = request_data['email']
    password = request_data['password']

    user_query = "SELECT * FROM user WHERE email = %s"
    cursor.execute(user_query, (email, ))

    user = cursor.fetchone()
    cursor.close()
    db.close()

    if user == None:
        return "User with given email has no account registered", 404
    else:        
        if user[2] != password:
            return "Wrong password", 401
        else:
            return jsonify({'id': user[0]}), 200


@app.route('/register', methods=['POST'])
def register():
    db = connect(host="localhost", user="root", passwd="root", database = "cash_app_db")
    cursor = db.cursor(buffered=True)


    request_data = request.get_json()

    email = request_data['email']
    password = request_data['password']
    first_name = request_data['first_name']
    last_name = request_data['last_name']

    user_query = "SELECT * FROM user WHERE email = %s"
    cursor.execute(user_query, (email, ))

    user = cursor.fetchone()

    if user != None:
        cursor.close()
        db.close()
        return "User with given email already has an account", 409
    
    else:
        register_query = "INSERT INTO user(email, password, first_name, last_name) VALUES(%s,%s,%s,%s)"
        cursor.execute(register_query, (email, password, first_name, last_name))
        userId = cursor.lastrowid
        db.commit()
        cursor.close()
        db.close()
        return jsonify({"id": userId}), 201


@app.route('/transactions', methods=['GET'])
def getUserTransactions():
    db = connect(host="localhost", user="root", passwd="root", database="cash_app_db")
    cursor = db.cursor(buffered=True)

    args = dict(request.args)

    user_id = args['user_id']

    userTransactionsQuery = "SELECT * FROM transaction t JOIN category c ON t.category_id = c.id WHERE t.user_id = %s ORDER BY t.date DESC"
    cursor.execute(userTransactionsQuery, (user_id,))
    userTransactions = cursor.fetchall()

    cursor.close()
    db.close()

    userTransactionsList = []

    for transaction in userTransactions:
        transactionDict = {}
        transactionDict['id'] = transaction[0]
        transactionDict['amount'] = transaction[1]
        transactionDict['date'] = transaction[2]
        transactionDict['user_id'] = transaction[3]
        transactionDict['category_id'] = transaction[4]
        transactionDict['category_name'] = transaction[6]
        userTransactionsList.append(transactionDict)
    
    return jsonify(userTransactionsList)


@app.route('/transactions', methods=['POST'])
def addUserTransaction():
    db = connect(host="localhost", user="root", passwd="root", database = "cash_app_db")
    cursor = db.cursor(buffered=True)


    request_data = request.get_json()

    amount = request_data['amount']
    # date = request_data['date']
    userId = request_data['user_id']
    categoryId = request_data['category_id']
   
    query = "INSERT INTO transaction(amount, user_id, category_id) VALUES(%s, %s, %s)"
    cursor.execute(query, (amount, userId, categoryId))
    transactionId = cursor.lastrowid

    db.commit()
    cursor.close()
    db.close()

    return jsonify({"id": transactionId}), 201


@app.route("/transactions", methods=['DELETE'])
def deleteUserTransaction():
    db = connect(host="localhost", user="root", passwd="root", database="cash_app_db")
    cursor = db.cursor(buffered=True)

    args = dict(request.args)

    id = int(args['id'])

    deleteTransactionQuery = "DELETE FROM transaction WHERE id = %s"
    cursor.execute(deleteTransactionQuery, (id,))

    db.commit()
    cursor.close()
    db.close()
    
    return jsonify({"success": "Transaction removed successfully"}), 200


@app.route('/categories', methods=['POST'])
def addCategory():
    db = connect(host="localhost", user="root", passwd="root", database = "cash_app_db")
    cursor = db.cursor(buffered=True)

    request_data = request.get_json()

    name = request_data['name']
   
    query = "INSERT INTO category(name) VALUES(%s)"
    cursor.execute(query, (name,))
    categoryId = cursor.lastrowid

    db.commit()
    cursor.close()
    db.close()

    return jsonify(categoryId)


@app.route('/categories', methods=['GET'])
def getCategories():
    db = connect(host="localhost", user="root", passwd="root", database="cash_app_db")
    cursor = db.cursor(buffered=True)

    args = dict(request.args)

    if 'name' in args:
        name = args['name']
        categoriesQuery = "SELECT * FROM category WHERE name = %s"
        cursor.execute(categoriesQuery, (name,))
    else:
        categoriesQuery = "SELECT * FROM category"
        cursor.execute(categoriesQuery)

    categories = cursor.fetchall()

    cursor.close()
    db.close()

    categoriesList = []

    for category in categories:
        categoryDict = {}
        categoryDict['id'] = category[0]
        categoryDict['name'] = category[1]
        categoriesList.append(categoryDict)
    
    return jsonify(categoriesList), 200


@app.route('/categories')




@app.route('/tracks', methods=['GET'])
def getTracks():
    db = connect(host="localhost", user="root", passwd="root", database = "cash_app_db")
    cursor = db.cursor(buffered=True)


    args = dict(request.args)

    if 'difficulty' in args:
        difficulty_name = args['difficulty']
        difficulty_query = "SELECT id FROM difficulty WHERE name = %s"
        cursor.execute(difficulty_query, (difficulty_name, ))
        difficulty_id = cursor.fetchone()

        tracks_query = "SELECT * FROM track WHERE difficulty_id = %s"
        cursor.execute(tracks_query, difficulty_id)
    else:
        tracks_query = "SELECT * FROM track"
        cursor.execute(tracks_query)


    tracks = cursor.fetchall()
    cursor.close()
    db.close()

    tracks_array = []

    for track in tracks:
        track_dict = {}
        track_dict['id'] = track[0]
        track_dict['name'] = track[1]
        track_dict['length'] = track[2]
        track_dict['description'] = track[3]
        track_dict['difficulty_id'] = track[4]
        track_dict['localization_id'] = track[5]

        track_dict['difficulty_name'] = getDifficultyNameById(track[4])
        track_dict['localization_name'] = getLocalizationNameById(track[5])

        tracks_array.append(track_dict)

    return jsonify(tracks_array)


@app.route('/tracks/<trackId>', methods=['GET'])
def getTrackById(trackId):
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    args = dict(request.args)

    track_query = "SELECT * FROM track WHERE id = %s"
    cursor.execute(track_query, (trackId, ))
    track = cursor.fetchone()
    cursor.close()
    db.close()
    
    track_dict = {}
    track_dict['id'] = track[0]
    track_dict['name'] = track[1]
    track_dict['length'] = track[2]
    track_dict['description'] = track[3]
    track_dict['difficulty_id'] = track[4]
    track_dict['localization_id'] = track[5]

    track_dict['difficulty_name'] = getDifficultyNameById(track[4])
    track_dict['localization_name'] = getLocalizationNameById(track[5])

    return jsonify(track_dict)


@app.route('/run', methods=['GET'])
def getUserRunsOnTrack():
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    args = dict(request.args)

    trackId = args['trackId']
    userId = args['userId']

    run_query = "SELECT * FROM run WHERE track_id = %s AND user_id = %s"
    cursor.execute(run_query, (trackId, userId))
    
    runs = cursor.fetchall()
    cursor.close()
    db.close()
    runs_array = []

    if runs == None:
        return jsonify("You have no runs on this track yet or track doesn't exist")

    for run in runs:
        run_dict = {}
        run_dict['id'] = run[0]
        run_dict['userId'] = run[1]
        run_dict['trackId'] = run[2]
        run_dict['time'] = run[3]
        run_dict['date'] = run[4]

        user = getUserDataById(run[1])
        run_dict['userEmail'] = user[0]
        run_dict['userFirstName'] = user[1]
        run_dict['userLastName'] = user[2]

        runs_array.append(run_dict)

    return jsonify(runs_array)


@app.route('/run', methods=['POST'])
def addUserRunToTrack():
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    request_data = request.get_json()
    print(request_data)

    trackId = request_data['track_id']
    userId = request_data['user_id']
    time = request_data['time']

   
    query = "INSERT INTO run(user_id, track_id, time) VALUES(%s, %s, %s)"
    cursor.execute(query, (userId, trackId, time))

    db.commit()
    cursor.close()
    db.close()

    return request_data


@app.route('/latest-run', methods=['GET'])
def getLatestUserRunOnTrack():
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    args = dict(request.args)

    trackId = args['trackId']
    userId = args['userId']

    run_query = "SELECT * FROM run WHERE track_id = %s AND user_id = %s ORDER BY date DESC LIMIT 1"
    cursor.execute(run_query, (trackId, userId))
    
    run = cursor.fetchone()
    cursor.close()
    db.close()

    if run == None:
        return jsonify("You have no runs on this track yet or track doesn't exist"), 401

    run_dict = {}
    run_dict['id'] = run[0]
    run_dict['userId'] = run[1]
    run_dict['trackId'] = run[2]
    run_dict['time'] = run[3]
    run_dict['date'] = run[4]


    return jsonify(run_dict)


@app.route('/record', methods=['GET'])
def getTrackRecord():
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    args = dict(request.args)

    trackId = args['trackId']
    userId = args['userId']
    record_query = "SELECT * FROM run WHERE track_id = %s AND user_id = %s ORDER BY time, date DESC LIMIT 1"
    cursor.execute(record_query, (trackId, userId))
    
    record = cursor.fetchone()
    cursor.close()
    db.close()
    if record == None:
        return jsonify("This track has no runs yet"), 401
    else:
        record_dict = {}
        record_dict['id'] = record[0]
        record_dict['userId'] = record[1]
        record_dict['trackId'] = record[2]
        record_dict['time'] = record[3]
        record_dict['date'] = record[4]

        return jsonify(record_dict)
    







def getDifficultyNameById(id):
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    difficulty_query = "SELECT name FROM difficulty WHERE id = %s"
    cursor.execute(difficulty_query, (id, ))
    difficulty_name = cursor.fetchone()
    cursor.close()
    db.close()

    return difficulty_name[0]


def getLocalizationNameById(id):
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    localization_query = "SELECT name FROM localization WHERE id = %s"
    cursor.execute(localization_query, (id, ))
    localization_name = cursor.fetchone()
    cursor.close()
    db.close()

    return localization_name[0]


def getUserDataById(id):
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    user_query = "SELECT email, first_name, last_name FROM user WHERE id = %s"
    cursor.execute(user_query, (id, ))
    user = cursor.fetchone()
    cursor.close()
    db.close()

    return user


def checkIfTrackHasARecordSet(trackId):
    db = connect(host="localhost", user="root", passwd="", database = "jogging_app_db")
    cursor = db.cursor(buffered=True)


    record_query = "SELECT * FROM record WHERE track_id = %s"
    cursor.execute(record_query, (trackId, ))
    result = cursor.fetchone()
    cursor.close()
    db.close()
    if result == None:
        return False
    return True



if __name__ == "__main__":
    app.run(port=5000)

