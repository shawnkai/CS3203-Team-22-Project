//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

using namespace std;

class DataNotFoundInCacheException: public exception {
    char* message;

public:
    explicit DataNotFoundInCacheException(char* message) : message(message) {}

    char * what () {
        return this->message;
    }
};
