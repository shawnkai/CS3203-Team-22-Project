
#ifndef SPA_READNODE_H
#define SPA_READNODE_H
#include "TreeNode.h"
class ReadNode: public TreeNode{
public:
    void accept(DesignExtractor &de);
};
#endif //SPA_READNODE_H
