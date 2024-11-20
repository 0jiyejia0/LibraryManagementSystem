#pragma once
#ifndef STUDENTSET_H
#define STUDENTSET_H

#include <vector>
#include "Student.h"

class StudentSet : public std::vector<Student> {
public:
    bool ListInsert_S(const Student& e);   // 插入对象

    int ListLength_S();   // 获取容器大小

    int findStudent(const std::string& stuno) const;

    bool ListDelete_S(int i, Student& e);  // 删除第i个学生

    bool LocateAllElem_S(const Student& e, bool (Student::* compare)(const Student&) const, std::vector<int>& find);   // 按一定条件查找

    bool GetElem_S(int i, Student& e);    // 获取第i个对象存储于e

    bool SetElem_S(int i, const Student& e);    // 第i个位置对象设为e

    bool OpenStuList();                   // 载入学生信息

    bool AppendStuList();

    bool SaveStuList();

    void stu_manage_output(int pos = 0); // 输出学生信息
};

#endif // STUDENTSET_H
