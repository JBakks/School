from PyQt5.QtWidgets import QApplication, QMainWindow, QListWidgetItem
from PyQt5.QtCore import QTimer
from PyQt5.uic import loadUi
import requests
from visualization import Visualization
from findStock import findStock
from portfolio import Portfolio
from watchlist import Watchlist
from virtualTrading import VirtualTrading

class ServiceRegistry(QMainWindow):
    def __init__(self):
        super(ServiceRegistry, self).__init__()
        loadUi('ServiceRegistry.ui', self)
        self.populate_service_list()
        self.goButton.clicked.connect(self.open_service_window)

        # Set up a QTimer to periodically refresh the service list
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_service_list)
        self.timer.start(30000)  # 30 seconds interval

    def populate_service_list(self):
        self.serviceList.clear()

        # List of your service URLs
        self.service_urls = [
            "http://portfolio.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/ping",
            "http://virtualtrading.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/ping",
            "http://visual.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/ping",
            "http://watchlist.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/ping",
            "http://findstock.1aola9rr2nrx.ca-tor.codeengine.appdomain.cloud/ping"
        ]

        for service_url in self.service_urls:
            # Fetch status using the provided URL
            status = self.get_service_status(service_url)

            # Check if status is "good" before adding to the list
            if status == "good":
                item_text = f"{service_url} - {status}"
                item = QListWidgetItem(item_text)
                self.serviceList.addItem(item)

    def get_service_status(self, service_url):
        # Concatenate the service_url with "/ping"
        url = f"{service_url}"

        # Sending a GET request to the service endpoint
        response = requests.get(url)

        # Checking if the request was successful
        if response.status_code == 200:
            # Extracting information from the JSON response
            data = response.json()
            return data.get('status', 'unknown')
        else:
            # Handle the case where the request to the service endpoint fails
            print(f"Error: {response.status_code}")
            return 'unknown'

    def update_service_list(self):
        # Iterate through the service URLs and update the list
        for service_url in self.service_urls.copy():  # Make a copy to avoid modifying the list during iteration
            status = self.get_service_status(service_url)

            # Check if the status is not "good"
            if status != "good":
                # Remove the service from the list
                self.service_urls.remove(service_url)

        # Populate the service list with the updated URLs
        self.populate_service_list()

    def open_service_window(self):
        # Get the selected item in the list
        selected_item = self.serviceList.currentItem()

        if selected_item is not None:
            # Get the text of the selected item
            selected_text = selected_item.text()

            # Extract the service URL from the selected text
            selected_url = selected_text.split(" - ")[0]

            # Open the corresponding window based on the selected service
            if "portfolio" in selected_url:
                self.window = Portfolio()
            elif "virtualtrading" in selected_url:
                self.window = VirtualTrading()
            elif "visual" in selected_url:
                self.window = Visualization()
            elif "watchlist" in selected_url:
                self.window = Watchlist()
            elif "findstock" in selected_url:
                self.window = findStock()
            else:
                # Handle the case for unrecognized service
                print("Unrecognized service")
                return

            self.window.show()
        else:
            # Handle the case where no item is selected
            print("No item selected")

if __name__ == "__main__":
    app = QApplication([])
    window = ServiceRegistry()
    window.show()
    app.exec_()
