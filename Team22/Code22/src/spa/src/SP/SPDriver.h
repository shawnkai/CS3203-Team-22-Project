#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "Tokenizer.h"
#include "TNode.h"//added
#include "DesignExtractor.h" //added

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram();
    //void parseSimpleProgram(const char* fileName);
};