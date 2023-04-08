#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif//SPA_SPDRIVER_H
#pragma once
#include "SP/Cfg/Cfg.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/DesignExtractor/NextExtractor.h"
#include "SP/Parser/ParserFactory.h"
#include "SP/Tokenizer/Tokenizer.h"
#include <deque>
#include <list>
#include <memory>
#include <string>

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram(const std::string &filename);
};