//
// Created by Tanishq Sharma on 17/2/23.
//

#ifndef SPA_UTILITIES_H
#define SPA_UTILITIES_H

#include <string>
#include <vector>
#include <stack>

using namespace std;

class Utilities {
private:
    static bool isOperator(char c);
    static int getPrecedence(char op);

public:

    static string infixToPrefix(string exp);

    static string removeAllOccurrences(string str, char c);

    static bool isNumber(string s);

    static bool isAlphanumericString(string s);

    static vector<string> findIntersection(vector<vector<string>>& all_vectors);

    static bool checkIfPresent(vector<string> list, string value);

    static bool checkInfixExpression(string str);
};

#endif //SPA_UTILITIES_H
