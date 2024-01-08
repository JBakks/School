#Josh Bakelaar 251139121
#Country Classes is a program which takes a data file and a file of "Updates" and then creates a new version of the data file with the updates applied.
#catalogue.py holds different methods for manipulating a new file
from country import Country

class CountryCatalogue:
    def __init__(self, countryFile):
        #Create a List that contains country info
        self.countryCat = []
        #Open the country file
        file = open(countryFile, "r")
        #Read the header line from the text file
        Header_line = file.readline()
        #Create a for loop to read each line from the data file
        for i in file:
            #Strip each line
            i = i.strip()
            #Remove '|' in eac line
            content = i.split('|')
            #Create an object to country
            cntry = Country(content[0], content[2], content[3], content[1])
            #Add an object to the list
            self.countryCat.append(cntry)
        #Close the file
        file.close()

    def setPopulation(self, country, population):
        #Use for loop to iterate through all countries
        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == country.getName():
                self.countryCat[i].setPopulation(population)

    def setArea(self, country, area):
        #Use for loop to iterate through all countries
        for j in range(len(self.countryCat)):
            if self.countryCat[j].getName() == country.getName():
                self.countryCat[j].setArea(area)

    def setContinent(self, country, continent):
        #Use for loop to iterate through all countries
        for k in range(len(self.countryCat)):
            if self.countryCat[k].getName() == country.getName():
                self.countryCat[k].setContinent(continent)

    def findCountry(self,country):
        #Use for loop to iterate through all countries
        for cntry in self.countryCat:
            if cntry.getName() == country.getName():
                return country
        return None

    def addCountry(self,countryName,pop,area,cont):
        Flag = False
        #Use for loop to iterate through all countries
        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == countryName:
                Flag = True
        if Flag:
            return False
        else:
            #Add a country
            cntry = Country(countryName, pop, area, cont)
            self.countryCat.append(cntry)
            return True

    def printCountryCatalogue(self):
        for cntry in self.countryCat:
            print(repr(cntry))

    def saveCountryCatalogue(self,fname):
        count=0
        #Sort the list
        for i in range(len(self.countryCat)):
            for j in range(i):
                if self.countryCat[i].getName() < self.countryCat[j].getName():
                    t = self.countryCat[i]
                    self.countryCat[i] = self.countryCat[j]
                    self.countryCat[j] = t

        #Open the file
        file = open(fname, "w")
        #Write the header
        file.write("Country|Continent|Population|Area\n")

        #Use for loop to iterate through all objects
        for cntry in self.countryCat:
            file.write(cntry.getName() + "|" + cntry.getContinent() + "|" + cntry.getPopulation() + "|" + cntry.getArea() + "\n")
            count=count+1

        #Close the file
        file.close();

        if(count==len(self.countryCat)):
            return count
        else:
            return -1
