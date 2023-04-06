
#ifndef SPA_RELATIONALFACTORPARSER_H
#define SPA_RELATIONALFACTORPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class RelationalFactorParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_RELATIONALFACTORPARSER_H
