//
// Created by Tanishq Sharma on 17/2/23.
//

#ifndef SPA_UTILITIES_H
#define SPA_UTILITIES_H

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
struct Hasher {
    std::size_t operator()(const T& obj) const {
        return std::hash<string>{}(obj->toString());
    }
};

template <typename T>
struct Equalizer {
    bool operator()(const T& val1, const T& val2) const{
        return val1->toString() == val2->toString();
    }
};

class Utilities {
private:
    /**
     * Determines if a given character is an operator (+, -, *, /, or %).
     *
     * @param c The character to check.
     *
     * @return True if the character is an operator, false otherwise.
     */
    static bool isOperator(char c);

    /**
     * Gets the precedence of a given operator.
     *
     * Operators with higher precedence are evaluated before operators with lower precedence.
     * The order of precedence is: *, /, %, +, -
     *
     * @param op The operator to get the precedence of.
     *
     * @return The precedence of the operator.
     */
    static int getPrecedence(char op);

public:
    /**
     * Converts an infix expression to prefix notation.
     *
     * An infix expression is one in which the operator appears between the operands (e.g. 2 + 3).
     * A prefix expression is one in which the operator appears before the operands (e.g. + 2 3).
     *
     * @param exp The infix expression to convert.
     *
     * @return The prefix notation of the expression.
     */
    static string infixToPrefix(string exp);

    /**
     * Removes all occurrences of a given character from a string.
     *
     * @param str The string to remove characters from.
     * @param c The character to remove.
     *
     * @return The resulting string.
     */
    static string removeAllOccurrences(string str, char c);

    /**
     * Determines if a given string is a valid number.
     *
     * @param s The string to check.
     *
     * @return True if the string is a number, false otherwise.
     *
     * @throws SyntacticException If the string is a number with a leading 0.
     */
    static bool isNumber(string s);


    /**
     * Determines if a given string is a valid variable name.
     *
     * A valid variable name is a string consisting of alphanumeric characters
     * and/or underscores, which may or may not be followed by a number.
     *
     * @param str The string to check.
     *
     * @return True if the string is a valid variable name, false otherwise.
     */
    static bool isValidVariableName(string str);

    /**
     * Finds the intersection of multiple vectors of strings.
     *
     * @param all_vectors The vectors to find the intersection of.
     *
     * @return The intersection of all vectors.
     */
    static vector<string> findIntersection(vector<vector<string>>& all_vectors);

    /**
     * Check if a given value is present in a vector of strings.
     *
     * An infix expression is one in which the operator appears between the operands (e.g. 2 + 3).
     * A prefix expression is one in which the operator appears before the operands (e.g. + 2 3).
     *
     * @param list The vector of strings to search.
     * @param value The value to search for in the vector.
     *
     * @return True if the value is present in the vector, false otherwise.
     */
    static bool checkIfPresent(vector<string> list, string value);

    /**
     * Checks if a given infix expression is valid.
     *
     * An infix expression is considered valid if it satisfies the following conditions:
     * - The expression contains only alphanumeric characters, operators (+, -, *, /, %),
     *   parentheses, brackets, and/or curly braces.
     * - Two operands cannot appear in a row (e.g. "2 3 + 4" is invalid).
     * - An operator must be preceded by an operand.
     * - The brackets, parentheses, and curly braces are balanced (i.e. every opening bracket
     *   has a corresponding closing bracket in the correct order).
     * - There are no consecutive alphanumeric substrings of length 2 or greater (e.g. "ab23c" is invalid).
     *
     * @param str The infix expression to check.
     *
     * @return True if the expression is valid, false otherwise.
     */
    static bool checkInfixExpression(string str);

    /**
     * Concatenates two vectors and stores the result in the first vector.
     *
     * @tparam T Type of elements in the first vector.
     * @tparam U Type of elements in the second vector.
     * @param vec1 First vector to concatenate.
     * @param vec2 Second vector to concatenate.
     *
     * @details This function takes in two vectors and concatenates the second vector to the end of the first vector.
     * The second vector should be convertible to the type of the first vector's elements.
     */
    template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    static void concatenateVectors(std::vector<T>& vec1, const std::vector<U>& vec2) {
        vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    }

    /**
     * Returns a vector of unique elements from the input vector.
     *
     * @tparam T Type of elements in the vector. This class must implement the toString() method.
     * @param input Input vector.
     *
     * @return A vector of unique elements from the input vector.
     *
     * @details This function takes in a vector of elements and returns a vector containing only the unique elements.
     * The elements are compared using a custom Hasher and Equalizer.
     */
    template <typename T>
    static std::vector<T> getUniqueElements(const std::vector<T>& input) {
        std::unordered_set<T, Hasher<T>, Equalizer<T>> seenElements; // Keep track of seen elements
        std::vector<T> output; // Output vector to store unique elements
        for (const T& elem : input) {
            if (seenElements.count(elem) == 0) { // If element is not seen before, add it to output vector and mark as seen
                auto p = seenElements.insert(elem);
                output.push_back(elem);
            }
        }
        return output;
    }
};

#endif //SPA_UTILITIES_H
