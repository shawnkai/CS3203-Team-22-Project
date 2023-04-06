
#ifndef SPA_FACTORNODE_H
#define SPA_FACTORNODE_H

#include "TreeNode.h"

class FactorNode: public TreeNode {
public:
    void accept(DesignExtractor &de) override;
};
#endif //SPA_FACTORNODE_H
