#Josh Bakelaar 251139121
#Country Classes is a program which takes a data file and a file of "Updates" and then creates a new version of the data file with the updates applied.
#country.py makes it so countrys from the file are now an object
class Country:
    def __init__(self, name, pop, area, continent):
        self.name=name
        self.pop=pop
        self.area=area
        self.continent=continent
    #getter methods
    def getName(self):
        return self.name

    def getPopulation(self):
        return self.pop

    def getArea(self):
        return self.area

    def getContinent(self):
        return self.continent

    #Setter methods
    def setPopulation(self, pop):
        self.pop=pop

    def setArea(self, area):
        self.area = area

    def setContinent(self, continent):
        self.continent = continent

    #Returns the string
    def __repr__(self):
        return (self.name +"(pop:"+str(self.pop)+", size: "+str(self.area)+") in "+self.continent)
