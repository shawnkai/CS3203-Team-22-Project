//
// Created by Tanishq Sharma on 20/2/23.
//

#ifndef SPA_EXCEPTIONS_H
#define SPA_EXCEPTIONS_H

#include <exception>

using namespace std;

class ParseException : public exception {
    /**
     * Exception class for parse errors.
     */
};

class SyntacticException : public ParseException {
    /**
     * Exception class for syntactic errors during parsing.
     * Inherits from ParseException.
     */
};

class SemanticException : public ParseException {
    /**
     * Exception class for semantic errors during parsing.
     * Inherits from ParseException.
     */
};


#endif //SPA_EXCEPTIONS_H
