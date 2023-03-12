
#ifndef SPA_WHILENODE_H
#define SPA_WHILENODE_H

#include "TreeNode.h"

class WhileNode: public TreeNode {
public:
    void accept(DesignExtractor &de);
};
#endif //SPA_WHILENODE_H
