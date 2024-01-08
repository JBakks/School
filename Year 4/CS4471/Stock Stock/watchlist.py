from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QLineEdit, QPushButton, QListWidget, QWidget, QListWidgetItem, QMessageBox
from PyQt5.uic import loadUi
from cloudant.client import Cloudant
import requests

class Watchlist(QMainWindow):
    def __init__(self):
        super(Watchlist, self).__init__()
        loadUi('watchlist.ui', self)
        self.setWindowTitle("Watchlist")

        self.searchButton.clicked.connect(self.stock_search)
        self.addButton.clicked.connect(self.on_add_clicked)
        self.load_user_stock_data()
        self.populate_stock_list()

    def load_user_stock_data(self):
        from loginManagement import LoginApp

        self.API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
        self.API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

        # Get the username from your application
        # username = "test"

        # Replace with your Flask service URL
        flask_url = "http://watchlist.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/user_watchlist?user_id=" + LoginApp.username

        # Make an HTTP request to the Flask service
        response = requests.get(flask_url)

        if response.status_code == 200:
            # Successfully received data from Flask service
            self.stock_data = {'stocks': response.json()}
        else:
            # Handle error response from Flask service
            error_message = f"Error: {response.status_code} - {response.text}"
            QMessageBox.critical(self, "Error", error_message)

    def populate_stock_list(self):
        self.stockList.clear()

        if hasattr(self, 'stock_data') and 'stocks' in self.stock_data:
            for stock_symbol in self.stock_data['stocks']:
                # Fetch percent change using the provided URL
                percent_change = self.get_percent_change(stock_symbol)

                # Check if percent_change is not None before formatting
                if percent_change is not None:
                    item_text = f"{stock_symbol} - {percent_change:.2f}%"
                else:
                    # Display "N/A" when percent_change is None
                    item_text = f"{stock_symbol} - N/A"

                item = QListWidgetItem(item_text)
                self.stockList.addItem(item)

    def get_percent_change(self, symbol):
        # URL of the Flask application
        url = f"http://findstock.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/search_stock/{symbol}"

        # Sending a GET request to the Flask application
        response = requests.get(url)

        # Checking if the request was successful
        if response.status_code == 200:
            # Extracting information from the JSON response
            data = response.json()
            stock_info = data.get('stock_info', {})

            # Return the percent change
            return stock_info.get('Percent Change', 0.0)
        else:
            print("YES")
            print(f"Error: {response.status_code}")
            return 0.0  # Default value in case of an error

    def stock_search(self):
        symbol = self.stockToFind.text().upper()
        # URL of the Flask application
        url = f"http://findstock.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/search_stock/{symbol}"

        # Sending a GET request to the Flask application
        response = requests.get(url)

        # Checking if the request was successful
        if response.status_code == 200:
            # Extracting information from the JSON response
            data = response.json()
            stock_info = data.get('stock_info', {})

            # Assigning values to variables with the same names
            company_name = stock_info.get('Company Name', '')
            percent = stock_info.get('Percent Change', 0.0)

            if company_name == "None":
                QMessageBox.information(self, "Alert", "Stock Does Not Exist", QMessageBox.Ok)
                return

            self.ticker.setText(symbol)
            self.company.setText(f"{company_name}")

        else:
            print("No")
            print(f"Error: {response.status_code}")
            QMessageBox.information(self, "Alert", "Stock Does Not Exist", QMessageBox.Ok)
            return

    def on_add_clicked(self):
        from loginManagement import LoginApp

        self.API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
        self.API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

        client = Cloudant.iam(self.API_USER, self.API_KEY, connect=True)
        data = client["watchlist"]

        # Implement code to add stocks
        stock_symbol = self.stockToFind.text().upper()  # Use the correct field from your UI

        # Update the database
        username = "josh"  # You may need to get the username from your application
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

            # Check if the stock already exists in the user's portfolio
            stock_exists = any(stock["stock"] == stock_symbol for stock in existing_user_stocks)

            if not stock_exists:
                existing_user_stocks.append({"stock": stock_symbol})

            user_data["stocks"] = existing_user_stocks
            user_doc.save()

            # Fetch updated stock data after addition
            user_doc.fetch()
            updated_user_stocks = user_doc.get("stocks", [])
            self.stock_data = {'stocks': [stock["stock"] for stock in updated_user_stocks]}

        else:
            # User doesn't exist, create a new document
            user_data["stocks"] = [{"stock": stock_symbol}]
            data.create_document(user_data)

            # Fetch updated stock data after addition
            user_doc = data[LoginApp.username]
            updated_user_stocks = user_doc.get("stocks", [])
            self.stock_data = {'stocks': [stock["stock"] for stock in updated_user_stocks]}

        # Update the displayed list in the UI
        self.populate_stock_list()

        # Clear the search line edit
        self.stockToFind.clear()

if __name__ == "__main__":
    app = QApplication([])
    window = Watchlist()
    window.show()
    app.exec_()
