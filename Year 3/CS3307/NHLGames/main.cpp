// Josh Bakelaar (251139121)
// main.cpp
// the main function which drives the program, this function will...
// 1) Download the JSON data for games using one or more request objects.
// 2) Parse the downlaoded JSON data into a vector of game objets.
// 3) Iterate through the vector, displaying the scores form each game object to standard output.
// Output should be (Home Team) vs. (Away Team): (Home Score) - (Away Score).

// The program does take time to download each game so please be patient
// Program also displays games that are currently happening

// Includes.
#include "json.hpp"
#include "request.hpp"
#include "game.hpp"

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdbool.h>

using namespace std;
using json = nlohmann::json;

int main() {
    // Vector which will hold all games that have been played, or are being played.
    vector<game> games;
    // String used to increment the game ID
    string gameString;

    cout << "Loading each game this may take awhile..." << endl;
    // Request the first game played of the season 2022020001, where the first 4 digits are the season, next 2 are for which part of the season, last 4 represent game number.
    request req("https://statsapi.web.nhl.com/api/v1/game/2022020001/linescore"); 
    // If the request is good then success = true, else false.
    bool success = req.execute();
    // Json object to parse the string from the request
    json j = json::parse(req.result());

    // A for loop to iterate through different api calls, 1 -> 1271 (There are 1271 games played in a season since 2018).
    for(int i = 1; i <= 1271; i++){

        // For some reason these games were never played, therefore skip them
        if(i == 320 || i == 534 || i == 536 || i == 547){
            i++;
        }

        // The following section formats the gameString to make sure there are 4 digits being passed.
        if(i < 10){
            gameString = "000" + to_string(i);
        }else if(i < 100){
            gameString = "00" + to_string(i);
        }else if(i < 1000){
            gameString = "0" + to_string(i);
        }else{
            gameString = to_string(i);
        }

        // This chunk is the same that was commented early, if you have inquires look to line 32-37.
        request req("https://statsapi.web.nhl.com/api/v1/game/202202" + gameString + "/linescore"); 
        success = req.execute();
        j = json::parse(req.result());

        // The key currentPeriodTimeRemaining only exists for games that have finsihed or are currently being played. if a error occurs when finding it, it means the game hasnt started yet.
        try{
            string final = j.at("currentPeriodTimeRemaining");
        // Break out of the for loop if the game has not started.
        }catch(json::out_of_range){
            break;
        }

        // Set the following from the json keys.
        string homeTeam = j.at("teams").at("home").at("team").at("name");
        string awayTeam = j.at("teams").at("away").at("team").at("name");
        int homeScore = j.at("teams").at("home").at("goals");
        int awayScore = j.at("teams").at("away").at("goals");
        
        // Put above values into a game object.
        game g(homeTeam, awayTeam, homeScore, awayScore);
        
        // Put the game into a vector.
        games.push_back(g);
    }

    // Iterate through all objects in the vector and print out the score.
    for (const auto &g : games){
        cout << g.hTeam << " vs. " << g.aTeam << ": " << g.hScore << " - " << g.aScore << endl;
    }

    return 0;
}