#Josh Bakelaar (251139121) Assignment 2 "Volume Calculator"
#Due Date October 21st 2020, 9pm
#Volume Calculator is a program that computs the volume for cubes, pyramids and ellipsoids
#It takes users desired shape(s), and outputs the volume(s).
#main.py gets user input, puts volumes into a list and prints the final statement. while volume.py does all of the computing of volumes

import volume

validShapes = ['cube', 'c', 'pyramid', 'p', 'ellipsoid', 'e']

shapesComputed = []

shape = input("Please enter shape (quit/q, cube/c, pyramid/p, ellipsoid/e): ")
shape = ''.join(shape.lower())

#loops unless q is typed
while shape != 'quit' or shape != 'q':
    #If item is not a valid shape
    while shape not in validShapes:
        if shape == 'q' or shape == 'quit': break
        print("-- invalid input: enter (quit/q, cube/c, pyramid/p, ellipsoid/e)")
        shape = input("Please enter shape: ")
        shape = ''.join(shape.lower())

    if shape == 'q' or shape == 'quit': break

    if shape == 'cube' or shape == 'c':
        length = float(input("Enter length of side for the cube: "))
        print("The volume of a cube with the side length of {} is: {:.2f}". format(length, volume.cubeVolume(length)))
        shapesComputed.append(("cube",volume.cubeVolume(length)))

    if shape == 'pyramid' or shape == 'p':
        base = float(input("Enter the base for the pyramid: "))
        height = float(input("Enter the height for the pyramid: "))
        print("The volume of a pyramid with base {} and height {} is: {:.2f}". format(base, height, volume.pyramidVolume(base, height)))
        shapesComputed.append(("pyramid",volume.pyramidVolume(base, height)))

    if shape == 'ellipsoid' or shape == 'e':
        radiOne = float(input("Enter the first radius: "))
        radiTwo = float(input("Enter the second radius: "))
        radiThree = float(input("Enter the third radius: "))
        print("The volume of an ellipsoid with radii {} and {} and {} is: {:.2f}". format(radiOne, radiTwo, radiThree, volume.ellipsoidVolume(radiOne, radiTwo, radiThree)))
        shapesComputed.append(("ellipsoid",volume.ellipsoidVolume(radiOne,radiTwo,radiThree)))

    shape = input("\nPlease enter shape (quit/q, cube/c, pyramid/p, ellipsoid/e): ")
    shape = ''.join(shape.lower())

shapesComputed.sort(key= lambda shapesComputed:shapesComputed[1])


if len(shapesComputed)<=0:
    print("Output: No shapes entered.")
else:
    print("Output: Volumes of shapes entered in sorted order:")

for (shape, vol) in shapesComputed:
    print("{} {:.2f}".format(shape, vol))


