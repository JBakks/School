// Josh Bakelaar (251139121)
// game.hpp
// Header file for game.cpp

// Includes
#include <curl/curl.h>
#include "callback.hpp"
#include <string>

using namespace std;

// If curious on any of these methods look to game.cpp to understand what each of them do.
class game{
    public:
        string hTeam;
        string aTeam;
        int hScore;
        int aScore;
        
        game(string homeTeam, string awayTeam, int homeScore, int awayScore);
        ~game();
        
        string getHomeTeam();
        string getAwayTeam();
        bool setHomeTeam(string s);
        bool setAwayTeam(string s);

        int getHomeScore();
        int getAwayScore();
        bool setHomeScore(int i);
        bool setAwayScore(int i);

};
