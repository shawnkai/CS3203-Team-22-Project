//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_VARNODE_H
#define SPA_VARNODE_H

#include "TreeNode.h"

class VarNode: public TreeNode {
public:
    VarNode() {
        nodeType = TokenType::NAME_IDENTIFIER;
    }
};

#endif //SPA_VARNODE_H
