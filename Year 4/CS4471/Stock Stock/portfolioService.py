from flask import Flask, jsonify, request
from cloudant.client import Cloudant

app = Flask(__name__)

# Cloudant credentials (replace with your actual credentials)
API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

client = Cloudant.iam(API_USER, API_KEY, connect=True)
database = client["portfolio"]

@app.route('/user_stocks', methods=['GET'])
def get_user_stocks():
    user_id = request.args.get('user_id')

    if not user_id:
        return jsonify({"error": "User ID is required"}), 400

    try:
        for document in database:
            if document.get('_id') == user_id:
                stocks = []
                for stock_info in document.get('stocks', []):
                    stock_symbol = stock_info.get('stock')
                    shares = stock_info.get('shares')
                    stocks.append({"stock": stock_symbol, "shares": shares})
                return jsonify(stocks)
        return jsonify({"error": "User not found"}), 404
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True, port=5002)
