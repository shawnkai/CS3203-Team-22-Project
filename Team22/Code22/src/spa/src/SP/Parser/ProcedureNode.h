
#ifndef SPA_PROCEDURENODE_H
#define SPA_PROCEDURENODE_H

#include "TreeNode.h"

class ProcedureNode: public TreeNode {
public:
    ProcedureNode() {
        nodeType = TokenType::PROCEDURE;
    }
    void accept(DesignExtractor &de) override;
};

#endif //SPA_PROCEDURENODE_H
