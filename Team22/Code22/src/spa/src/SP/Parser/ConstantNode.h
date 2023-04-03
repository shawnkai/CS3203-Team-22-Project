//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_CONSTANTNODE_H
#define SPA_CONSTANTNODE_H

#include "TreeNode.h"

class ConstantNode: public TreeNode {
public:
    ConstantNode() {
        nodeType = TokenType::INTEGER;
    }
};
#endif //SPA_CONSTANTNODE_H
