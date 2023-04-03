
#ifndef SPA_PROGRAMNODE_H
#define SPA_PROGRAMNODE_H
#include "TreeNode.h"
using namespace std;

class ProgramNode: public TreeNode
{
public:
    ProgramNode() {
        nodeType = TokenType::PROGRAM;
    }

    void accept(DesignExtractor &de);
};
#endif //SPA_PROGRAMNODE_H
