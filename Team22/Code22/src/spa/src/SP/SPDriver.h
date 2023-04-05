#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Parser/TNode.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/SPDriver.h"
#include "SP/Parser/Parser.h"
#include "SP/Cfg/Cfg.h"
#include "SP/DesignExtractor/NextExtractor.h"

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram(std::string filename);
};