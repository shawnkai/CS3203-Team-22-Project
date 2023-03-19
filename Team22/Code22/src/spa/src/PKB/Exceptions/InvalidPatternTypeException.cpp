//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

using namespace std;

class InvalidPatternTypeException: public exception {
    char* message;
public:
    explicit InvalidPatternTypeException(char* message) : message(message) {}

    char * what () {
        return this->message;
    }
};
