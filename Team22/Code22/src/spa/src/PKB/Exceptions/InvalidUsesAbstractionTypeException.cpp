//
// Created by Jai Lulla  on 9/3/23.
//

#include <iostream>

using namespace std;

class InvalidUsesAbstractionTypeException : public exception {
    char *message;

public:
    explicit InvalidUsesAbstractionTypeException(char *message) : message(message) {}

    char *what() {
        return this->message;
    }
};
