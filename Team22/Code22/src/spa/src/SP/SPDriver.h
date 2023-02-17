#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Parser/TNode.h"//added
#include "DesignExtractor/DesignExtractor.h" //added

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram();
    //void parseSimpleProgram(const char* fileName);
};