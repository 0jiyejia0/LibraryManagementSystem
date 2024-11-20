#include "RelationshipSet.h"

// ���
bool RelationshipSet::EnQueue(const Relationship& e) {
    this->push_back(e);
    return true;
}

// ����
bool RelationshipSet::DeQueue(Relationship& e) {
    if (this->empty()) {
        return false;
    }
    e = this->front();
    this->erase(this->begin());
    return true;
}

// �п�
bool RelationshipSet::QueueEmpty() const {
    return this->empty();
}
