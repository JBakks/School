#Josh Bakelaaar (251139121) Assignment 3 "Sentiment Analysis"
#Due Date November 18th, 9pm
#Sentiment Analysis looks at tweets to determine their happiness score
#it then takes find the time zone which the tweet is from and then finds the happiness score for the region
#main.py runs the functions and handles user input

import sentiment_analysis

#ask the user for the files
keywordsFile = input("Please enter the name of the keyword file: ")
tweetsFile = input("Please enter the name of the tweet file: ")

#print results
print(sentiment_analysis.compute_tweets(tweetsFile, keywordsFile))
