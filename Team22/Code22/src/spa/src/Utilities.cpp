//
// Created by Tanishq Sharma on 17/2/23.
//

#include "Utilities.h"
#include <algorithm>
#include <regex>
#include "QPS/Exceptions/Exceptions.h"

using namespace std;

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

bool Utilities::isNumber(string s)
{
    if (s[0] == '0' && s.size() != 1) {
        throw SyntacticException();
    }

    for (char i : s) {
        if (isdigit(i) == false) {
            return false;
        }
    }

    return true;
}

bool Utilities::isValidVariableName(string str) {
    static const std::regex pattern("[a-zA-Z_][a-zA-Z0-9_]*");
    bool temp = std::regex_match(str, pattern);
    return temp;
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
    exp = Utilities::removeAllOccurrences(exp, ' ');

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

bool Utilities::checkInfixExpression(string str) {
    std::stack<char> stk;
    bool prevIsOperand = false; // to check if the previous character was an operand
    str = Utilities::removeAllOccurrences(str, ' ');
    str = regex_replace(str, regex("(\\w){2,}"), "$1");
    for (char c : str) {
        if (isalpha(c)) {
            if (prevIsOperand) {
                return false; // two operands in a row
            }
            prevIsOperand = true;
        } else if (isdigit(c)) {
            if (prevIsOperand) {
                return false; // two operands in a row
            }
            prevIsOperand = true;
        } else if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
            prevIsOperand = false;
        } else if (c == ')' || c == ']' || c == '}') {
            if (stk.empty()) {
                return false;
            }
            char top = stk.top();
            stk.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
            prevIsOperand = true;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            if (!prevIsOperand) {
                return false; // an operator must be preceded by an operand
            }
            prevIsOperand = false;
        } else {
            return false; // invalid character
        }
    }
    return stk.empty();
}

bool Utilities::checkIfPresent(vector<string> list, string value) {
    for (string v : list) {
        if (v == value) {
            return true;
        }
    }
    return false;
}
