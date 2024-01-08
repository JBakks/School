#Josh Bakelaar 251139121
#Country Classes is a program which takes a data file and a file of "Updates" and then creates a new version of the data file with the updates applied.
#processUpdates.py finds the new updates and creates the new output file which goes to outputs.txt
from catalogue import CountryCatalogue
from country import Country
import sys

def processUpdates(cntryFileName,updateFileName):
    output = open("output.txt", "w")

    #Check to see if file exists
    cntryFileName = checkFileCntry(cntryFileName,output)
    #Open the country file
    file = open(cntryFileName, "r")

    #Create an object to the CountryCatalogue class
    cntry = CountryCatalogue(cntryFileName)

    #Check to see if file exists
    updateFileName = checkFileUpdate(updateFileName, output)
    #Open the update file
    updatefile = open(updateFileName,"r")

    for i in updatefile:
        #Strip lines
        i = i.strip()
        #Split the data at semicolon
        data = i.split(';')
        #Create country object
        cntry1 = Country(data[0], '', '', '')
        #Find country for existence
        obj = cntry.findCountry(cntry1)

        if obj == None:
            #Fetch values
            for elem in data[1:]:
                #Strip spaces
                elem = elem.strip()
                #Check update
                if elem[0] == 'P':
                    cntry1.setPopulation(elem[2:])

                elif elem[0] == 'A':
                    cntry1.setArea(elem[2:])

                elif elem[0] == 'C':
                    cntry1.setContinent(elem[2:])

            #Add country to catalogue
            cntry.addCountry(cntry1.getName(), cntry1.getPopulation(), cntry1.getArea(), cntry1.getContinent())

        else:
            for elem in data[1:]:
                #Strip spaces
                elem = elem.strip()
                #Check update

                if elem[0] == 'P':
                    cntry.setPopulation(cntry1, elem[2:])

                elif elem[0] == 'A':
                    cntry.setArea(cntry1, elem[2:])

                elif elem[0] == 'C':
                    cntry.setContinent(cntry1, elem[2:])

    #Close the file
    file.close()
    #Saving to file
    cntry.saveCountryCatalogue("output.txt")
    return True

def checkFileCntry(cntryFileName, output):
    block = False
    #Check the file exists or not
    while block == False:
        try:
            file = open(cntryFileName, "r")
            return cntryFileName
            block = True
        except FileNotFoundError:
            choice = input("Do you want to Quit? 'Y' (yes) or 'N' (no): ")
            if choice.lower() == "n":
                cntryFileName = input("Enter name of file with country data: ")
                try:
                    file = open(cntryFileName,"r")
                    return cntryFileName
                except FileNotFoundError:
                    continue
            elif choice.lower() != "n":
                print("Update Unsuccessful\n")
                output.write("Update Unsuccessful\n")
                sys.exit()
                return False

def checkFileUpdate(updateFileName, output):
    block = False
    #Check the file exists or not
    while block == False:
        try:
            file = open(updateFileName, "r")
            return updateFileName
            block = True
        except FileNotFoundError:
            choice = input("Do you want to Quit? 'Y' (yes) or 'N' (no): ")
            if choice.lower() == "n":
                updateFileName = input("Enter name of file with update data: ")
                try:
                    file = open(updateFileName,"r")
                    return updateFileName
                except FileNotFoundError:
                    continue
            elif choice.lower() != "n":
                print("Update Unsuccessful\n")
                output.write("Update Unsuccessful\n")
                sys.exit()
                return False
