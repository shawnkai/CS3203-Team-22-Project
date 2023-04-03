
#ifndef SPA_IFNODE_H
#define SPA_IFNODE_H

#include "TreeNode.h"

class IfNode: public TreeNode {
public:
    IfNode() {
        nodeType = TokenType::IF;
    }

    void accept(DesignExtractor &de) ;
};

#endif //SPA_IFNODE_H
