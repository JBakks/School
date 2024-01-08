from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QLineEdit, QPushButton, QListWidget, QWidget, QListWidgetItem, QMessageBox
from PyQt5.uic import loadUi
from cloudant.client import Cloudant
import requests
from virtualHelper import totalBuy, totalSell, totalStocks

class VirtualTrading(QMainWindow):
    def __init__(self):
        super(VirtualTrading, self).__init__()
        loadUi('virtualTrade.ui', self)
        self.setWindowTitle("Portfolio")


        # data.create_document({"_id": "test", "username": "test", "stocks": [{"stock": "APPL", "shares": 6}, {"stock": "GAE", "shares": 12}]})

        self.searchButton.clicked.connect(self.stock_search)
        self.buyButton.clicked.connect(self.on_buy_clicked)
        self.sellButton.clicked.connect(self.on_sell_clicked)

        self.stock_data = {

        }

        self.load_user_stock_data()
        self.populate_stock_list()
        self.update_current_currency()

        total_price = self.calculate_portfolio_total()
        self.totalPrice.setText(f"{total_price:.2f}" if total_price is not None else "0.00")

    def update_current_currency(self):
        from loginManagement import LoginApp
        # Set the URL to fetch the user's currency data
        username = LoginApp.username  # Replace with the actual username
        currency_url = f"https://virtualtrading.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/virtual/get/{username}"

        # Make an HTTP GET request to the URL
        response = requests.get(currency_url)

        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            # Parse the JSON data from the response
            currency_data = response.json()

            # Extract the current currency value
            current_currency = currency_data.get("currency", 0.0)

            # Update the label in the UI
            self.currentCurrency.setText(f"{current_currency}")
        else:
            # Print an error message if the request was not successful
            print(f"Failed to fetch current currency. Status code: {response.status_code}")

    def load_user_stock_data(self):
        from loginManagement import LoginApp

        # Set the URL to fetch user stock data
        username = LoginApp.username
        url = f"https://virtualtrading.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/virtual/get/{username}"

        # Make an HTTP GET request to the URL
        response = requests.get(url)

        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            # Parse the JSON data from the response
            user_data = response.json()

            # Extract the stock information from the user_data dictionary
            stocks_data = user_data.get("stocks", [])  # Use "stocks" and handle the case where it's a list

            # Iterate through the user's stocks and update the stock data
            for stock_info in stocks_data:
                stock_symbol = stock_info.get("stock", "")  # Extract stock symbol, adjust as needed
                buy_transactions = stock_info.get("buy", [])

                # Calculate the total number of shares from buy transactions
                shares = sum(transaction.get("share", transaction.get("shares", 0)) for transaction in buy_transactions)

                stock_price = buy_transactions[0].get("amount", 100.0) if buy_transactions else 100.0  # Placeholder value

                # Update the stock data in the class attribute
                self.stock_data[stock_symbol] = {'price': stock_price, 'shares': shares}

            # Extract the user's currency
            user_currency = user_data.get("currency", None)

            # If the user doesn't have a currency in the response, set it to 2500
            if user_currency is None:
                user_currency = 2500
                # Also, update the database with the initial currency
                data.create_document({"_id": username, "username": username, "currency": user_currency, "stocks": []})

            # Update the current currency in the UI
            self.currentCurrency.setText(f"{user_currency}")

        else:
            # Print an error message if the request was not successful
            print(f"Failed to fetch user stock data. Status code: {response.status_code}")


    def populate_stock_list(self):
        self.stockList.clear()

        for symbol, data in self.stock_data.items():
            price = data['price']
            shares = data['shares']
            item = QListWidgetItem(f"{symbol}: ${price:.2f} shares: {shares}")
            self.stockList.addItem(item)

    def on_search_clicked(self):
        stock_symbol = self.search_line_edit.text()

    def on_buy_clicked(self):
            from loginManagement import LoginApp

            self.API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
            self.API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

            client = Cloudant.iam(self.API_USER, self.API_KEY, connect=True)
            data = client["virtualcurrency"]

            # Implement code to buy stocks
            stock_symbol = self.stockToFind.text().upper()  # Use the correct field from your UI
            num_shares_str = self.numShares.text()

            # Check if the user entered a valid number of shares
            if not num_shares_str.isdigit() or int(num_shares_str) <= 0:
                QMessageBox.information(self, "Alert", "Please enter a valid number of shares.", QMessageBox.Ok)
                return

            num_shares = int(num_shares_str)

            # Get the price from the label
            price_str = self.price.text()
            company_name = self.company.text()

            if price_str == "None" or company_name == "None":
                QMessageBox.information(self, "Alert", "Stock information is not available. Please search for a valid stock.", QMessageBox.Ok)
                return

            price = float(price_str)

            # Check if the user has enough currency to make the purchase
            current_currency_str = self.currentCurrency.text()
            current_currency = float(current_currency_str)

            total_cost = num_shares * price

            if total_cost > current_currency:
                QMessageBox.information(self, "Alert", "Insufficient currency to buy the specified number of shares.", QMessageBox.Ok)
                return

            # Update the model or add the purchased stock to the data
            if stock_symbol in self.stock_data:
                self.stock_data[stock_symbol]['shares'] += num_shares
            else:
                # Handle the case when the stock is not in the initial data
                self.stock_data[stock_symbol] = {'price': price, 'shares': num_shares}

            # Update the database
            username = "test"  # You may need to get the username from your application
            user_data = {"_id": LoginApp.username, "username": LoginApp.username, "stocks": []}

            # Check if the user already exists in the database
            if LoginApp.username in data:
                existing_user = True
                user_doc = data[LoginApp.username]
                print(data[LoginApp.username])
            else:
                existing_user = False

            if existing_user:
                # User exists, update the stocks list
                existing_user_stocks = user_doc.get("stocks", [])
                stock_exists = False
                for user_stock in existing_user_stocks:
                    if user_stock["stock"] == stock_symbol:
                        user_stock["shares"] += num_shares
                        stock_exists = True
                        user_stock["buy"].append({"share": num_shares, "amount": price, "date": "current_date"})  # Add transaction
                        break

                if not stock_exists:
                    existing_user_stocks.append({"stock": stock_symbol, "shares": num_shares, "buy": [{"share": num_shares, "amount": price, "date": "current_date"}]})

                user_data["stocks"] = existing_user_stocks
                user_doc["currency"] -= total_cost  # Deduct the total cost from the user's currency
                user_doc.save()
            else:
                # User doesn't exist, create a new document
                user_data["stocks"] = [{"stock": stock_symbol, "shares": num_shares, "buy": [{"share": num_shares, "amount": price, "date": "current_date"}]}]
                user_data["currency"] = 2500  # Set the initial currency value if creating a new user
                data.create_document(user_data)

            # Update the displayed list in the UI
            self.populate_stock_list()

            # Update the current currency in the UI
            self.update_current_currency()

            # Clear the search line edit and numShares line edit
            self.stockToFind.clear()
            self.numShares.clear()

            # Clear the labels
            self.price.clear()
            self.company.clear()

            # Optionally, update the total price as well
            total_price = self.calculate_portfolio_total()
            self.totalPrice.setText(f"{total_price:.2f}" if total_price is not None else "0.00")



    def on_sell_clicked(self):
        from loginManagement import LoginApp

        self.API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
        self.API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

        client = Cloudant.iam(self.API_USER, self.API_KEY, connect=True)
        data = client["virtualcurrency"]

        # Get the selected item from the list view
        selected_item = self.stockList.currentItem()
        if not selected_item:
            QMessageBox.information(self, "Alert", "Please select a stock to sell.", QMessageBox.Ok)
            return

        # Extract stock information from the selected item
        selected_text = selected_item.text()
        parts = selected_text.split(':')
        stock_symbol = parts[0].strip()

        # Check if the user entered a valid number of shares
        num_shares_str = self.sharesToSell.text()
        if not num_shares_str.isdigit() or int(num_shares_str) <= 0:
            QMessageBox.information(self, "Alert", "Please enter a valid number of shares.", QMessageBox.Ok)
            return

        num_shares = int(num_shares_str)

        # Check if the stock exists in the user's portfolio
        if stock_symbol not in self.stock_data:
            QMessageBox.information(self, "Alert", "Stock not found in your portfolio.", QMessageBox.Ok)
            return

        # Check if the user has enough shares to sell
        if self.stock_data[stock_symbol]['shares'] < num_shares:
            QMessageBox.information(self, "Alert", "Insufficient shares to sell.", QMessageBox.Ok)
            return

        # Get the current price from the stock_data dictionary
        price = self.stock_data[stock_symbol]['price']

        # Fetch the user document from the database
        username = LoginApp.username
        if username in data:
            user_doc = data[username]
        else:
            QMessageBox.information(self, "Alert", "User not found in the database.", QMessageBox.Ok)
            return

        # Calculate the total value of the sold stocks using the totalSell function from newhelper
        total_value = totalSell([{"share": num_shares, "worth": price, "date": "current_date"}])

        # Increment the current currency by the total value of the sold stocks
        user_doc["currency"] += total_value

        # Update the model or subtract the sold stock from the data
        self.stock_data[stock_symbol]['shares'] -= num_shares

        # Check if the stock should be removed from the user's portfolio
        if self.stock_data[stock_symbol]['shares'] <= 0:
            del self.stock_data[stock_symbol]

        # Update the database with the changes
        user_stocks = user_doc.get("stocks", {})
        if stock_symbol in user_stocks:
            stock_data = user_stocks[stock_symbol]
            stock_data["shares"] -= num_shares

            # Check if the stock should be removed from the database
            if stock_data["shares"] <= 0:
                del user_stocks[stock_symbol]

                # Add the sell transaction
                stock_data.setdefault("sell", []).append({"share": num_shares, "amount": price, "date": "current_date"})

        user_doc["stocks"] = user_stocks
        user_doc.save()

        # Update the displayed list in the UI
        self.populate_stock_list()

        # Clear the search line edit and numShares line edit
        self.stockToFind.clear()
        self.numShares.clear()

        # Clear the labels
        self.price.clear()
        self.company.clear()

        # Optionally, update the total price as well
        total_price = self.calculate_portfolio_total()
        self.totalPrice.setText(f"{total_price:.2f}" if total_price is not None else "0.00")

    def stock_search(self):
        symbol = self.stockToFind.text()
        # URL of the Flask application
        url = f"https://findstock.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/search_stock/{symbol}"

#        Sending a GET request to the Flask application
        response = requests.get(url)

#        Checking if the request was successful
        if response.status_code == 200:
            # Extracting information from the JSON response
            data = response.json()
            stock_info = data.get('stock_info', {})

            # Assigning values to variables with the same names
            company_name = stock_info.get('Company Name', '')
            current_price = stock_info.get('Current Price', 0.0)

            if(f"{company_name}" == "None"):
                QMessageBox.information(self, "Alert", "Stock Does Not Exist", QMessageBox.Ok)
                return

            self.price.setText(f"{current_price}")
            self.company.setText(f"{company_name}")

        else:
            print(f"Error: {response.status_code}")
            QMessageBox.information(self, "Alert", "Stock Does Not Exist", QMessageBox.Ok)
            return

    def calculate_portfolio_total(self):
           total_value = 0
           for symbol, data in self.stock_data.items():
               price = data['price']
               shares = data['shares']
               total_value += price * shares
           return total_value

if __name__ == "__main__":
    app = QApplication([])
    window = Portfolio()
    window.show()
    print("User's Portfolio Total:", window.calculate_portfolio_total())
    app.exec_()
