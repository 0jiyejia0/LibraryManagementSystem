#pragma once
#ifndef STUDENTNODESET_H
#define STUDENTNODESET_H

#include <vector>
#include "StudentNode.h"

class StudentNodeSet : public std::vector<StudentNode> {
public:
    void addStudentNode(const StudentNode& sn);   // ���ѧ�����Ľڵ�

    int findStudent(const std::string& stuno) const;  // ����ѧ���ڵ�
};

#endif // STUDENTNODESET_H
