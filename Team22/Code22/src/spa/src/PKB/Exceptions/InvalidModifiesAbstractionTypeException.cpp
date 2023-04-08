//
// Created by Jai Lulla  on 9/3/23.
//

#include <iostream>

using namespace std;

class InvalidModifiesAbstractionTypeException : public exception {
    char *message;

public:
    explicit InvalidModifiesAbstractionTypeException(char *message) : message(message) {}

    char *what() {
        return this->message;
    }
};
