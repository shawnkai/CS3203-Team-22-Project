//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

using namespace std;

class InvalidAbstractionTypeException : public exception {
    char *message;

public:
    explicit InvalidAbstractionTypeException(char *message) : message(message) {}

    char *what() {
        return this->message;
    }
};
