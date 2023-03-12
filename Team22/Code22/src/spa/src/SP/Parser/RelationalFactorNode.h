
#ifndef SPA_RELATIONALFACTORNODE_H
#define SPA_RELATIONALFACTORNODE_H

#include "TreeNode.h"

class RelationalFactorNode: public TreeNode {
public:
    void accept(DesignExtractor &de);
};

#endif //SPA_RELATIONALFACTORNODE_H
