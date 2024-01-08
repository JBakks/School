from catalogue import CountryCatalogue
from country import Country
from processUpdates import processUpdates

def main():
    print()
    print(40*"*")
    print("*** Updating country files")
    print()
    cntryFileName = input("Enter name of file with country data: ")
    updateFileName = input("Enter name of file with country updates: ")
    result = processUpdates(cntryFileName,updateFileName)
    print()
    print(40*"*")
    if result:
        print("*** Updating successfully completed")
    else:
        print("*** Updating NOT successfully completed")
main()
