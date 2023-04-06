
#ifndef SPA_CALLNODE_H
#define SPA_CALLNODE_H

#include "TreeNode.h"

class CallNode: public TreeNode {
public:
    CallNode() {
        nodeType = TokenType::CALL;
    }

    void accept(DesignExtractor &de) override;
};
#endif //SPA_CALLNODE_H
