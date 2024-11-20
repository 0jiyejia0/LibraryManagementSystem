#include "StudentNodeSet.h"
#include "StudentNodeSet.h"

// ���ѧ�����Ľڵ�
void StudentNodeSet::addStudentNode(const StudentNode& sn) {
    this->push_back(sn);
}

// ����ѧ���ڵ�
int StudentNodeSet::findStudent(const std::string& stuno) const {
    for (size_t i = 0; i < this->size(); ++i) {
        if (this->at(i).getstudentno() == stuno) {
            return i;
        }
    }
    return -1;
}
