#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Token;


std::vector<std::string> Parse(std::string const &simpleProgramString, std::vector<std::string> &out);

int dummy();
