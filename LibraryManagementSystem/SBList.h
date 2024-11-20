#pragma once
#ifndef SBLIST_H
#define SBLIST_H

#include "StudentNodeSet.h"

class SBList {
private:
    int studentnum;           // 借阅书籍的人数
    int borrownum;            // 借出去的书总数
public:
    StudentNodeSet sblist;    // 学生借阅信息列表

    bool begin_borrow();    // 借阅信息初始化

    bool OpenBorrowList();     // 读入文件中的借阅信息

    int StuWhetherIn(const std::string& no) const;   // 查询学生是否曾借阅书籍

    void pushelem(const StudentNode& sn);   // 新增一个借阅关系

    bool SaveBorrowList();

    void setstudentnum(int s);
    void setborrownum(int b);
    int getstudentnum() const;
    int getborrownum() const;

    int getpersonalnum(const std::string& no) const;   // 获取单个学生的借书量

    int BookWhetherIn(const std::string& sn, const std::string& bn) const;   // 查询某一学生是否借阅某一本书

    void addanewrelation(const std::string& sn, const BorrowInfo& bi);   // 某一学生新借一本书

    void returnbook(const std::string& sn, const std::string& bn);   // 某一学生归还某本书

    void printbookinfo(const std::string& sn) const;  // 输出某人的借阅信息

    void printsinglebookinfo(const std::string& bn) const;   // 输出某一本书被借阅的情况

    void outdate(const Date& now);   // 查询所有存在逾期的同学
};

#endif // SBLIST_H
