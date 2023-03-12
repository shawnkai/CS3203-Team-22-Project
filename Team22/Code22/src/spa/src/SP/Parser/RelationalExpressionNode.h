
#ifndef SPA_RELATIONALEXPRESSIONNODE_H
#define SPA_RELATIONALEXPRESSIONNODE_H

#include "TreeNode.h"

class RelationalExpressionNode: public TreeNode {
public:
    void accept(DesignExtractor &de);
};

#endif //SPA_RELATIONALEXPRESSIONNODE_H
