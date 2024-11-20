#pragma once
#ifndef RELATIONSHIPSET_H
#define RELATIONSHIPSET_H

#include <vector>
#include "Relationship.h"

class RelationshipSet : public std::vector<Relationship> {
public:
    bool DeQueue(Relationship& e);   // 出队

    bool EnQueue(const Relationship& e);    // 入队

    bool QueueEmpty() const;     // 判空
};

#endif // RELATIONSHIPSET_H
