// Josh Bakelaar (251139121);
// callback.cpp
// Allows us to customize behavior and receive information as a string.

#include "callback.hpp"

using namespace std;

size_t callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Make user data a string pointer.
    string *str = (std::string*)userdata;
    // Append data to the string.
    str->append(ptr, size * nmemb);
    // Return siz.
    return size * nmemb;
}