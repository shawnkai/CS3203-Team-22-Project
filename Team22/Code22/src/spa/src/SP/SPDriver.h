#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "SP/Tokenizer/Tokenizer.h"
//#include "SP/Parser/TNode.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/SPDriver.h"
#include "SP/Parser/ParserFactory.h"
#include "SP/Parser/MainParser.h"
#include "SP/Cfg/Cfg.h"

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram(std::string filename);
};