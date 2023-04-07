#ifndef SPA_SPDRIVER_H
#define SPA_SPDRIVER_H

#endif //SPA_SPDRIVER_H
#pragma once
#include <deque>
#include <list>
#include <memory>
#include <string>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/DesignExtractor/DesignExtractor.h"
#include "SP/Parser/ParserFactory.h"
#include "SP/Cfg/Cfg.h"
#include "SP/DesignExtractor/NextExtractor.h"

class SPDriver {
public:
    SPDriver();
    void parseSimpleProgram(const std::string& filename);
};