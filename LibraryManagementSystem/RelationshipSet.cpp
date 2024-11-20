#include "RelationshipSet.h"

// 入队
bool RelationshipSet::EnQueue(const Relationship& e) {
    this->push_back(e);
    return true;
}

// 出队
bool RelationshipSet::DeQueue(Relationship& e) {
    if (this->empty()) {
        return false;
    }
    e = this->front();
    this->erase(this->begin());
    return true;
}

// 判空
bool RelationshipSet::QueueEmpty() const {
    return this->empty();
}
