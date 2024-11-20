#pragma once
#ifndef STUDENTNODESET_H
#define STUDENTNODESET_H

#include <vector>
#include "StudentNode.h"

class StudentNodeSet : public std::vector<StudentNode> {
public:
    void addStudentNode(const StudentNode& sn);   // 添加学生借阅节点

    int findStudent(const std::string& stuno) const;  // 查找学生节点
};

#endif // STUDENTNODESET_H
