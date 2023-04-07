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
        ::printf("%s: %d\n", obj->toString().c_str(), std::hash<string>{}(obj->toString()));
        return std::hash<string>{}(obj->toString());
    }
};

class Utilities {
private:
    static bool isOperator(char c);
    static int getPrecedence(char op);

public:

    static string infixToPrefix(string exp);

    static string removeAllOccurrences(string str, char c);

    static bool isNumber(string s);

    static bool isValidVariableName(string str);

    static vector<string> findIntersection(vector<vector<string>>& all_vectors);

    static bool checkIfPresent(vector<string> list, string value);

    static bool checkInfixExpression(string str);

    template <typename T, typename U,
            typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    static void concatenateVectors(std::vector<T>& vec1, const std::vector<U>& vec2) {
        vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    }

    template <typename T>
    static std::vector<T> getUniqueElements(const std::vector<T>& input) {
        std::unordered_set<T, Hasher<T>> seenElements; // Keep track of seen elements
        std::vector<T> output; // Output vector to store unique elements
        for (const T& elem : input) {
            ::printf("%d\n", seenElements.count(elem));
            if (seenElements.count(elem) == 0) { // If element is not seen before, add it to output vector and mark as seen
                auto p = seenElements.insert(elem);
                output.push_back(elem);
            }
        }
        return output;
    }
};

#endif //SPA_UTILITIES_H
