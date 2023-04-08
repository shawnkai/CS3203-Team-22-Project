//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

using namespace std;

class InvalidEntityTypeException : public exception {
    char *message;

public:
    explicit InvalidEntityTypeException(char *message) : message(message) {}

    char *what() {
        return this->message;
    }
};
