
#ifndef SPA_PROCEDURENODE_H
#define SPA_PROCEDURENODE_H

#include "TreeNode.h"

class ProcedureNode: public TreeNode {
public:
    void accept(DesignExtractor &de);
};

#endif //SPA_PROCEDURENODE_H
