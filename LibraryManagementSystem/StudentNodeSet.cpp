#include "StudentNodeSet.h"
#include "StudentNodeSet.h"

// 添加学生借阅节点
void StudentNodeSet::addStudentNode(const StudentNode& sn) {
    this->push_back(sn);
}

// 查找学生节点
int StudentNodeSet::findStudent(const std::string& stuno) const {
    for (size_t i = 0; i < this->size(); ++i) {
        if (this->at(i).getstudentno() == stuno) {
            return i;
        }
    }
    return -1;
}
