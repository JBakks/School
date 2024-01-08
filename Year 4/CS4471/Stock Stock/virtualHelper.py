from cloudant.client import Cloudant

# Cloudant credentials (replace with your actual credentials)
API_USER = "3fdf89c0-70ae-421c-8a5c-f3f07abc3988-bluemix"
API_KEY = "IGzHN-SnHoE7X-Xn_wlCK0ogL62UusTafB2ZO8CZeXub"

def totalBuy(buy: list) -> float:

    total = 0
    for item in buy:
        total += item["share"] * item["worth"]

    return total

def totalSell(sell: list) -> float:

    total = 0
    for item in sell:

        total += item["share"] * item["worth"]

    return total

def totalStocks(stock: dict) -> int:

    buyStocks = 0
    sellStocks = 0
    for item in stock["buy"]:
        buyStocks += item["share"]

    for item in stock["sell"]:
        sellStocks += item["share"]

    return buyStocks - sellStocks


if __name__ == "__main__":

    client = Cloudant.iam(API_USER, API_KEY, connect=True)

    virt = client["virtualcurrency"]

    doc = {
        "_id": "test001",
        "username": "test001",
        "currency": 1000,
        "stocks":
            {
             "AAPL": {"buy": [{"share": 5, "worth": 14.5, "date": "25/5/2023"}],
                      "sell": [{"share": 4, "worth": 12.5, "date": "26/5/2023"}]
                      }
            }


        }

    if "test001" not in virt:
        virt.create_document(doc)

    # Test out the functions

    if totalBuy(doc["stocks"]["AAPL"]["buy"]) == 5 * 14.5:
        print("totalBuy Works!!!")
    else:
        print("totalBuy Failure")

    if totalSell(doc["stocks"]["AAPL"]["sell"]) == 4 * 12.5:
        print("totalSell works")

    else:
        print("totalSell Failure")

    if totalStocks(doc["stocks"]["AAPL"]) == 1:
        print("totalStocks works")
    else:
        print("totalStocks Failure")
