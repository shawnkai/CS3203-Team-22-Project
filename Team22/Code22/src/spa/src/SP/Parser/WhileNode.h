
#ifndef SPA_WHILENODE_H
#define SPA_WHILENODE_H

#include "TreeNode.h"

class WhileNode: public TreeNode {
public:
    WhileNode() {
        nodeType = TokenType::WHILE;
    }

    void accept(DesignExtractor &de) override;
};
#endif //SPA_WHILENODE_H
