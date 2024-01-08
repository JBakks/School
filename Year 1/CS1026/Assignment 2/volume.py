#Josh Bakelaar (251139121) Assignment 2 "Volume Calculator"
#Due Date October 21st 2020, 9pm
#Volume Calculator is a program that computs the volume for cubes, pyramids and ellipsoids
#It takes users desired shape(s), and outputs the volume(s).

import math

volume = 0

def cubeVolume(length):
    volume = length**3
    return volume

def pyramidVolume(base,height):
    volume = ((base**2)*height)*1/3
    return volume

def ellipsoidVolume(radiOne,radiTwo,radiThree):
    volume = (4/3*math.pi)*radiOne*radiTwo*radiThree
    return volume
