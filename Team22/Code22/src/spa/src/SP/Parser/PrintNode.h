
#ifndef SPA_PRINTNODE_H
#define SPA_PRINTNODE_H
#include "TreeNode.h"
class PrintNode: public TreeNode{
public:
    PrintNode() {
        nodeType = TokenType::PRINT;
    }
    void accept(DesignExtractor &de) override;
};
#endif //SPA_PRINTNODE_H
