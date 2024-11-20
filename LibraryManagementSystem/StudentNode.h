#pragma once
#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include <string>
#include <iostream>
#include "BorrowInfoSet.h"

class StudentNode {
private:
    std::string studentno;   // 学号
    int borrownum;           // 借阅数量
public:
    BorrowInfoSet bilist;    // 借阅信息列表

    void setstudentno(const std::string& no);
    void setborrownum(int b);
    std::string getstudentno() const;
    int getborrownum() const;

    void pushbook(const BorrowInfo& b); // 借书

    int BookWhetherIn(const std::string& bn) const;   // 根据书号查询书籍是否被该同学借阅

    void returnbook(const std::string& bn);   // 还书

    void printallbookinfo() const;   // 输出所有借阅书籍信息

    void printsinglebookinfo(const std::string& bn) const;  // 输出单本书籍借阅信息

    void outdate(const Date& now) const;  // 查询是否逾期

    // 重载输入输出运算符
    friend std::istream& operator>>(std::istream& is, StudentNode& sn);
    friend std::ostream& operator<<(std::ostream& os, const StudentNode& sn);
};

#endif // STUDENTNODE_H
