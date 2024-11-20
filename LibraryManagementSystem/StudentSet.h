#pragma once
#ifndef STUDENTSET_H
#define STUDENTSET_H

#include <vector>
#include "Student.h"

class StudentSet : public std::vector<Student> {
public:
    bool ListInsert_S(const Student& e);   // �������

    int ListLength_S();   // ��ȡ������С

    int findStudent(const std::string& stuno) const;

    bool ListDelete_S(int i, Student& e);  // ɾ����i��ѧ��

    bool LocateAllElem_S(const Student& e, bool (Student::* compare)(const Student&) const, std::vector<int>& find);   // ��һ����������

    bool GetElem_S(int i, Student& e);    // ��ȡ��i������洢��e

    bool SetElem_S(int i, const Student& e);    // ��i��λ�ö�����Ϊe

    bool OpenStuList();                   // ����ѧ����Ϣ

    bool AppendStuList();

    bool SaveStuList();

    void stu_manage_output(int pos = 0); // ���ѧ����Ϣ
};

#endif // STUDENTSET_H
