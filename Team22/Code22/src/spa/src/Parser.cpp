#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "PKB.h"
#include "TNode.h"

std::vector<std::string> Parse (std::string const &simpleProgramString, std::vector<std::string> &out) {
    // construct a stream from the string
    std::stringstream ss(simpleProgramString);

    std::string s;
    while (std::getline(ss, s, ' ')) {
        out.push_back(s);
    }
    return out;
}

int dummy() {
    return 0;
}
