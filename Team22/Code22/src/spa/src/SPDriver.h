#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "Tokenizer.h"

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram(const char* fileName);
};