
#ifndef SPA_PROGRAMNODE_H
#define SPA_PROGRAMNODE_H
#include "TreeNode.h"
using namespace std;

class ProgramNode: public TreeNode
{
public:
    void accept(DesignExtractor &de);
};
#endif //SPA_PROGRAMNODE_H
