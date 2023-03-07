//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

using namespace std;

class InvalidAPICallException: public exception {
    char* message;
public:
    InvalidAPICallException(char* message) : message(message) {}

    char * what () {
        return this->message;
    }
};
