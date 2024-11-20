#pragma once
#ifndef BORROWINFO_H
#define BORROWINFO_H

#include <string>
#include <iostream>
#include "Date.h"

class BorrowInfo {    // 借阅信息
private:
    std::string bookno;    // 书号
    Date borrowday;        // 借阅日期

public:
    void setbookno(const std::string& bno);
    void setborrowday(const Date& d);
    std::string getbookno() const;
    Date getborrowday() const;
    bool isOverdue(const Date& currentDate) const;
    // 重载输入输出运算符
    friend std::istream& operator>>(std::istream& is, BorrowInfo& bi);
    friend std::ostream& operator<<(std::ostream& os, const BorrowInfo& bi);
};

#endif // BORROWINFO_H
