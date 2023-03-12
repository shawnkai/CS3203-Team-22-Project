
#ifndef SPA_PRINTNODE_H
#define SPA_PRINTNODE_H
#include "TreeNode.h"
class PrintNode: public TreeNode{
public:
    void accept(DesignExtractor &de);
};
#endif //SPA_PRINTNODE_H
