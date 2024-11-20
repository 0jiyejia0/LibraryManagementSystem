#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    std::string studentno;     // 学号
    std::string studentname;   // 姓名
    std::string studentmajor;  // 专业
    std::string studentclass;  // 班级
    std::string studentmobile; // 手机

public:
    // 设置函数
    void setstuno(const std::string& no);
    void setstuname(const std::string& name);
    void setstumajor(const std::string& major);
    void setstuclass(const std::string& c);
    void setstumobi(const std::string& mobi);

    // 获取函数
    std::string getstuno() const;
    std::string getstuname() const;
    std::string getstumajor() const;
    std::string getstuclass() const;
    std::string getstumobi() const;

    // 比较运算符重载
    bool operator==(const Student& s) const;

    // 字段匹配
    bool index_stuno(const std::string& info) const;
    bool index_stuname(const std::string& info) const;
    bool index_stumajor(const std::string& info) const;
    bool index_stuclass(const std::string& info) const;
    bool index_stumobile(const std::string& info) const;

    // 比较学生学号是否相同
    bool equal_stuno(const Student& b) const;

    // 比较学生的专业或班级是否相同
    bool equal_stuma_or_cl(const Student& b) const;

    // 重载输入输出运算符
    friend std::istream& operator>>(std::istream& is, Student& stu);
    friend std::ostream& operator<<(std::ostream& os, const Student& stu);
};

#endif // STUDENT_H
