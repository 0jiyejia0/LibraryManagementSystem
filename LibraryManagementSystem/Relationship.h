#pragma once
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>
#include <iostream>

class Relationship {
private:
    std::string stuno;      // 学号
    std::string bookno;     // 书号
    std::string stumobile;  // 手机号

public:
    // 设置函数
    void setstuno(const std::string& sno);
    void setbookno(const std::string& bno);
    void setstumobile(const std::string& mobi);

    // 获取函数
    std::string getstuno() const;
    std::string getbookno() const;
    std::string getstumobile() const;

    // 重载输入输出运算符
    friend std::istream& operator>>(std::istream& is, Relationship& re);
    friend std::ostream& operator<<(std::ostream& os, const Relationship& re);
};

#endif // RELATIONSHIP_H
