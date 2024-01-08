#Josh Bakelaaar (251139121) Assignment 3 "Sentiment Analysis"
#Due Date November 18th, 9pm
#Sentiment Analysis looks at tweets to determine their happiness score
#it then takes find the time zone which the tweet is from and then finds the happiness score for the region
#sentiment_analysis.py holds the functions for analysing the tweets

#Variables for longitude
P1 = -67.444574
P3 = -87.518395
P5 = -101.998892
P7 = -115.236428
P9 = -125.242264
#Variables for Lat
MAX = 49.189787
MIN = 24.660845

def compute_tweets(tweetsFile, keywordsFile):
    #Variables hold the amount of lines within the txt files
    tweetsLineCount = 0
    keywordLineCount = 0

    #Variable for how many keywords
    keywordCounter = 0

    #Variable for how many tweets
    tweetCounter = 0

    #Temp list used to store sentiment values & happiness scores
    tempList = []

    #list that holds the following
    keywordList = []
    scoreList = []

    #punctuation characters
    punctuation = ['#', '!', ',', ';', ':', '\'', '[', ']']

    sentimentValue = 0

    easternCount = 0
    centralCount = 0
    mountainCount = 0
    pacificCount = 0
    easternKeywordTweet = 0
    centralKeywordTweet = 0
    mountainKeywordTweet = 0
    pacificKeywordTweet = 0
    easternHappinessScore = 0
    centralHappinessScore = 0
    mountainHappinessScore = 0
    pacificHappinessScore = 0

    #checking if the file exists, if not it returns an empty list
    try:
        with open(tweetsFile, 'r') as fh:
            pass
        with open(keywordsFile, 'r') as fh:
            pass
    except FileNotFoundError:
        print('one of the files are not found')
        return tempList

    #find the files given and open them
    keywordsText = open(keywordsFile).readlines()
    tweetsText = open(tweetsFile).readlines()

    #counting the amount of lines within each file
    for line in open(tweetsFile).readlines():
        tweetsLineCount += 1
    for line in open(keywordsFile).readlines():
        keywordLineCount += 1

    #putting together the keyword list
    while keywordCounter != keywordLineCount:
        keyword = keywordsText[keywordCounter]
        list = keyword.split(',')
        keywordList.append(list[0])
        list[1] = int(list[1])
        scoreList.append(list[1])
        keywordCounter += 1

    #making a list for each word in a tweet
    while tweetCounter != tweetsLineCount:
        words = str(tweetsText[tweetCounter])
        words = words.lower()
        for i in punctuation:
            words = words.replace(i, '')
        list = words.split(' ')

        #get the longitude value from the tweet with this value we will be able to determine which timezone the tweet is coming from
        x = float(list[1])
        y = float(list[0])

        #If not Eastern, Central, Mountain, or Pacific skip tweet
        if x>P1 or x<P9 or y<MIN or y>MAX:
            tweetCounter += 1
            continue

        #if Eastern
        if x<=P1 and x>=P3:
            easternCount += 1

            #putting the numbers returned from the tweet analysis into a list
            tempList= analysis(words, sentimentValue, keywordList, scoreList)
            sentimentValue= tempList[0]
            happinessScore= tempList[1]

            #count how many keyword tweets there are for the timezone
            if sentimentValue>0:
                easternKeywordTweet += 1
            #get a total happiness score for the timezone
            if happinessScore>0:
                easternHappinessScore = easternHappinessScore+happinessScore

        #if Central
        if x<P3 and x>=P5:
            centralCount += 1

            #putting the numbers returned from the tweet analysis into a list
            tempList= analysis(words, sentimentValue, keywordList, scoreList)
            sentimentValue= tempList[0]
            happinessScore= tempList[1]

            #count how many keyword tweets there are for the time zone
            if sentimentValue>0:
                centralKeywordTweet += 1
            #get a total happiness score for the timezone
            if happinessScore>0:
                centralHappinessScore = centralHappinessScore+happinessScore

        #if Mountain
        if x<P5 and x>=P7:
            mountainCount += 1

            #putting the numbers returned from the tweet analysis into a list
            tempList= analysis(words, sentimentValue, keywordList, scoreList)
            sentimentValue= tempList[0]
            happinessScore= tempList[1]

            #count how many keyword tweets there are for the timezone
            if sentimentValue>0:
                mountainKeywordTweet += 1

            #get a total happiness score for the timezone
            if happinessScore>0:
                mountainHappinessScore = mountainHappinessScore+happinessScore

        #if Pacific
        if x<P7 and x>P9:
            pacificCount += 1

            #putting the numbers returned from the tweet analysis into a list
            tempList= analysis(words, sentimentValue, keywordList, scoreList)
            sentimentValue= tempList[0]
            happinessScore= tempList[1]

            #count how many keyword tweets there are for the timezone
            if sentimentValue>0:
                pacificKeywordTweet += 1

            #get a total happiness score for the timezone
            if happinessScore>0:
                pacificHappinessScore = pacificHappinessScore+happinessScore

        tweetCounter += 1

    #find the happiness score for each timezone by dividing the total happiness score by how many keyword tweets there are in the timezone
    if easternKeywordTweet !=0 :
        easternHappinessScore = easternHappinessScore/easternKeywordTweet
    if centralKeywordTweet != 0:
        centralHappinessScore = centralHappinessScore/centralKeywordTweet
    if mountainKeywordTweet != 0:
        mountainHappinessScore = mountainHappinessScore/mountainKeywordTweet
    if pacificKeywordTweet != 0:
        pacificHappinessScore = pacificHappinessScore/pacificKeywordTweet

    #put values into a list
    easternList = (easternHappinessScore, easternKeywordTweet, easternCount)
    centralList = (centralHappinessScore, centralKeywordTweet, centralCount)
    mountainList = (mountainHappinessScore, mountainKeywordTweet, mountainCount)
    pacificList = (pacificHappinessScore, pacificKeywordTweet,pacificCount)

    #return the tuples in order from eastern, central, mountain, pacific
    return(easternList, centralList, mountainList, pacificList)

#used to analyse individual tweets
def analysis(words, sentimentValue, keywordList, scoreList):
    words = words.replace('.', '')
    list = words.split(' ')
    happinessScore = 0
    sentimentValue = 0

    sentimentWords = set (list) & set (keywordList)
    numberOfSentimentWords = int(len(sentimentWords))

    for i in sentimentWords:
        #find the position for the sentiment word and then compare it with the score for said sentiment word
        position = int(keywordList.index(i))
        position = position
        sentimentValue = sentimentValue + int(scoreList[position])

        #find happiness score of individual tweet by total sentiment value divided by the number of sentiment words
        if numberOfSentimentWords != 0:
            happinessScore = sentimentValue/numberOfSentimentWords

    return [numberOfSentimentWords, happinessScore]
