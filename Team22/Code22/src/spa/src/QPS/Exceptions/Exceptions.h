//
// Created by Tanishq Sharma on 20/2/23.
//

#ifndef SPA_EXCEPTIONS_H
#define SPA_EXCEPTIONS_H

#include <exception>

using namespace std;

class ParseException : public exception {

};

class SyntacticException : public ParseException {

};

class SemanticException : public ParseException {

};


#endif //SPA_EXCEPTIONS_H
