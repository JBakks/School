// Josh Bakelaar (251139121)
// request.hpp
// Header file used for request.cpp

// Includes
#include <curl/curl.h>
#include "callback.hpp"
#include <string>
#include <iostream>

using namespace std;

// If curious on any of these methods look to request.cpp to understand what each of them do
class request{
    public:

        string url;
        string str;
        CURL *curl;
        CURLcode res;
        
        request(string s);
        ~request();
        bool execute();
        string result();
};
