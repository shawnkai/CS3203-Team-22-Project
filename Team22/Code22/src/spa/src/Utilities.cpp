//
// Created by Tanishq Sharma on 17/2/23.
//

#include "Utilities.h"
#include <algorithm>

vector<string> Utilities::findIntersection(vector<vector<string>> &all_vectors) {
    vector<string> intersection;
    if (all_vectors.empty()) {
        return intersection;
    }

    sort(all_vectors.begin(), all_vectors.end());
    for (const string& str : all_vectors[0]) {
        bool present = true;
        for (int i = 1; i < all_vectors.size(); i++) {
            if (find(all_vectors[i].begin(), all_vectors[i].end(), str) == all_vectors[i].end()) {
                present = false;
                break;
            }
        }
        if (present) {
            intersection.push_back(str);
        }
    }
    return intersection;
}

bool Utilities::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Returns true if s is a number else false
bool Utilities::isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

/**
 * Checks if a String is alphanumeric
 *
 * @param str input
 * @return true if String is alphanumeric else false
 */
bool Utilities::isAlphanumericString(string str) {
    return std::all_of(
            str.begin(),
            str.end(),
            [](char c){return std::isalnum(c);});
}

string Utilities::removeAllOccurrences(string str, char c) {
    str.erase(remove(str.begin(), str.end(), c), str.end());
    return str;
}

int Utilities::getPrecedence(char op) {
    if (op == '*' || op == '/' || op == '%') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0;
    }
}

string Utilities::infixToPrefix(string exp) {
    stack<char> operatorStack;

    if (exp.length() == 1) {
        return exp;
    }

    string prefix;

    bool isLeftWildcard = exp[0] == '_';
    bool isRightWildcard = exp[exp.length() - 1] == '_';

    exp = Utilities::removeAllOccurrences(exp, '_');

    reverse(exp.begin(), exp.end());

    for (char c : exp) {
        int currentPrecedence = getPrecedence(c);
        if (Utilities::isOperator(c)) {
            while (!operatorStack.empty() && Utilities::getPrecedence(operatorStack.top()) > currentPrecedence) {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        } else if (c == ')') {
            operatorStack.push(c);
        } else if (c == '(') {
            while (!operatorStack.empty() && operatorStack.top() != ')') {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        } else {
            prefix += c;
        }
    }

    while (!operatorStack.empty()) {
        prefix += operatorStack.top();
        operatorStack.pop();
    }

    reverse(prefix.begin(), prefix.end());

    if (isLeftWildcard) {
        prefix = '_' + prefix;
    }

    if (isRightWildcard) {
        prefix = prefix + '_';
    }

    return prefix;
}

bool Utilities::checkIfPresent(vector<string> list, string value) {
    for (string v : list) {
        if (v == value) {
            return true;
        }
    }
    return false;
}