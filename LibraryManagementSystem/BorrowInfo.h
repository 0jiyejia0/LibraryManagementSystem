#pragma once
#ifndef BORROWINFO_H
#define BORROWINFO_H

#include <string>
#include <iostream>
#include "Date.h"

class BorrowInfo {    // ������Ϣ
private:
    std::string bookno;    // ���
    Date borrowday;        // ��������

public:
    void setbookno(const std::string& bno);
    void setborrowday(const Date& d);
    std::string getbookno() const;
    Date getborrowday() const;
    bool isOverdue(const Date& currentDate) const;
    // ����������������
    friend std::istream& operator>>(std::istream& is, BorrowInfo& bi);
    friend std::ostream& operator<<(std::ostream& os, const BorrowInfo& bi);
};

#endif // BORROWINFO_H
