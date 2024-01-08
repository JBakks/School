#Josh Bakelaar Assignment 1 "Good Morning Canada!
#Due Date October 7th 2020, 9pm
#Good Morning Canada is a program which acts as a server at a resturant.
#It takes users order through input, than adds up the total, gives you tax, and price after tax


#Prices of all items
egg = 0.99
bacon = 0.49
sausage = 1.49
hashbrown = 1.19
toast = 0.79
coffee = 1.49
tea = 1.09

preTax = 0

#constants
TAX = 0.13

order = input("Enter item (q to terminate): small breakfast, regular breakfast, big breakfast, egg, bacon, sausage, hash brown, toast, coffee, tea:")

#formats order so its always lowercase and only one space between words
order = order.lower().strip()
wordList = order.split()
order = " ".join(wordList)

validMenuItems = ['egg', 'bacon', 'sausage', 'hash brown', 'toast', 'coffee', 'tea', 'small breakfast', 'regular breakfast', 'big breakfast']

#loops unless q is typed
while order not in 'q':
    item = 0

    #If item is not on menu
    while order not in validMenuItems:
        print("ERROR: Not a valid menu item")
        order = input("Enter next item (or q to terminate)")
        order = order.lower().strip()
        wordList = order.split()
        order = " ".join(wordList)
        pass

    #Assignment for cost
    if order in 'egg':
        item=item+egg
    if order in 'bacon':
        item=item+bacon
    if order in 'sausage':
        item=item+sausage
    if order in 'hash brown':
        item=item+hashbrown
    if order in 'toast':
        item=item+toast
    if order in 'coffee':
        item=item+coffee
    if order in 'tea':
        item=item+tea
    if order in 'small breakfast':
        item=item+(egg+hashbrown+(toast*2)+(bacon*2)+sausage)
    if order in 'regular breakfast':
        item=item+((egg*2)+hashbrown+(toast*2)+(bacon*4)+(sausage*2))
    if order in 'big breakfast':
        item=item+((egg*3)+(hashbrown*2)+(toast*4)+(bacon*6)+(sausage*3))

    amount = input("Enter quantity:")
    while amount.isnumeric() == False:
        print('ERROR: Please enter valid number')
        amount = input("Enter quantity:")

    amount = int(amount)

    item = item * amount
    preTax = preTax+item

    #Line for debugging and testing, remove # to see total after each item(s) added
    #print(preTax)

    #Get next item
    order = input("Enter item (q to terminate): small breakfast, regular breakfast, big breakfast, egg, bacon, sausage, hash brown, toast, coffee, tea:")

    #formats order so its always lowercase and only one space between words
    order = order.lower().strip()
    wordList = order.split()
    order = " ".join(wordList)

#prints all costs
print("Cost :  {:0.2f}".format(preTax))
tax=preTax*TAX
print("Tax :   {:0.2f}".format(tax))
total= preTax+tax
print("Total : {:0.2f}".format(total))
