// Josh Bakelaar (251139121)
// request.cpp
// Is used or pulling the data using libcurl.

// Includes
#include "request.hpp"
#include <curl/curl.h>

// Constructor
// Takes in a string obj as a parameter, containing the URL to fetch.
request::request(std::string s){
    url = s;
}

// Deconstructor
// Cleans up after the object when it is destroyed.
request::~request(){
    curl_easy_cleanup(curl);
}

// execute()
// Executes the request and retrieves the document from the URL provided on construction.
// This method returns a boolean value of true on success or false on failure.
bool request::execute(){
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
        res = curl_easy_perform(curl);
        return true;
    }else{
        return false;
    }
}

// request()
// Returns a string object containing the JSON data retrieved on executing the request.
std::string request::result(){
    return str;
}
