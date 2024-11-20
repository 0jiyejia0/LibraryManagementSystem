#pragma once
#ifndef RELATIONSHIPSET_H
#define RELATIONSHIPSET_H

#include <vector>
#include "Relationship.h"

class RelationshipSet : public std::vector<Relationship> {
public:
    bool DeQueue(Relationship& e);   // ����

    bool EnQueue(const Relationship& e);    // ���

    bool QueueEmpty() const;     // �п�
};

#endif // RELATIONSHIPSET_H
