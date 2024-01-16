from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

data = {"status": 0,
        "timer": 0,
        "mode": ""}


@app.route('/')
def hello_world():
    global data
    return render_template('base.html')


@app.route('/send_data', methods=['POST'])
def send_data():
    global data
    data = request.json
    return jsonify(data)


@app.route('/get_status', methods=['GET'])
def get_status():
    global data
    return data['status']


@app.route('/get_timer', methods=['GET'])
def get_timer():
    global data
    return data['timer']


@app.route('/get_mode', methods=['GET'])
def get_mode():
    global data
    return data['mode']


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
