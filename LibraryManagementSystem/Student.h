#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    std::string studentno;     // ѧ��
    std::string studentname;   // ����
    std::string studentmajor;  // רҵ
    std::string studentclass;  // �༶
    std::string studentmobile; // �ֻ�

public:
    // ���ú���
    void setstuno(const std::string& no);
    void setstuname(const std::string& name);
    void setstumajor(const std::string& major);
    void setstuclass(const std::string& c);
    void setstumobi(const std::string& mobi);

    // ��ȡ����
    std::string getstuno() const;
    std::string getstuname() const;
    std::string getstumajor() const;
    std::string getstuclass() const;
    std::string getstumobi() const;

    // �Ƚ����������
    bool operator==(const Student& s) const;

    // �ֶ�ƥ��
    bool index_stuno(const std::string& info) const;
    bool index_stuname(const std::string& info) const;
    bool index_stumajor(const std::string& info) const;
    bool index_stuclass(const std::string& info) const;
    bool index_stumobile(const std::string& info) const;

    // �Ƚ�ѧ��ѧ���Ƿ���ͬ
    bool equal_stuno(const Student& b) const;

    // �Ƚ�ѧ����רҵ��༶�Ƿ���ͬ
    bool equal_stuma_or_cl(const Student& b) const;

    // ����������������
    friend std::istream& operator>>(std::istream& is, Student& stu);
    friend std::ostream& operator<<(std::ostream& os, const Student& stu);
};

#endif // STUDENT_H
