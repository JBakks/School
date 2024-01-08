// Josh Bakelaar (251139121)
// game.cpp
// Used to hold each game that has been played or is being played.

// Includes
#include "game.hpp"

using namespace std;

// Constructor
// Takes in home team name, away team name, home team score, away team score.
game::game(string homeTeam, string awayTeam, int homeScore, int awayScore){
    hTeam = homeTeam;
    aTeam = awayTeam;
    hScore = homeScore;
    aScore = awayScore;
}

// Deconstructor
game::~game(){
}

// Getter which returns home team
string game::getHomeTeam(){
    return hTeam;
}

// Getter which returns away team
string game::getAwayTeam(){
    return aTeam;
}

// Setter that sets home team
bool game::setHomeTeam(string newTeam){
    hTeam = newTeam;
    return true;
}

// Setter that sets away team
bool game::setAwayTeam(string newTeam){
    aTeam = newTeam;
    return true;
}

// Getter for home score
int game::getHomeScore(){
    return hScore;
}

// Getter for away score
int game::getAwayScore(){
    return aScore;
}

// Setter for home score
bool game::setHomeScore(int newScore){
    hScore = newScore;
    return true;
}

// Setter for away score
bool game::setAwayScore(int newScore){
    aScore = newScore;
    return true;
}
