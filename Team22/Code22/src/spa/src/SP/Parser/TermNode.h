//
// Created by Yi Zhang on 12/3/23.
//

#ifndef SPA_TERM_H
#define SPA_TERM_H

#include "TreeNode.h"

class TermNode: public TreeNode {
public:
    void accept(DesignExtractor &de) override;
};
#endif //SPA_TERM_H
