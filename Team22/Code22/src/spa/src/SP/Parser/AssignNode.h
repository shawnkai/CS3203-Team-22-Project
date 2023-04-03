
#ifndef SPA_ASSIGNNODE_H
#define SPA_ASSIGNNODE_H
#include "TreeNode.h"

class AssignNode: public TreeNode {
public:
    AssignNode() {
        nodeType = TokenType::ASSIGN;
    }
    void accept(DesignExtractor &de);
};
#endif //SPA_ASSIGNNODE_H
