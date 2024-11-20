#pragma once
#ifndef BORROWINFOSET_H
#define BORROWINFOSET_H

#include <vector>
#include "BorrowInfo.h"

class BorrowInfoSet : public std::vector<BorrowInfo> {
public:
    void addBorrowInfo(const BorrowInfo& bi);   // ��ӽ�����Ϣ

    int findBook(const std::string& bookno) const;  // ���ҽ�����Ϣ

    void removeBorrowInfo(const std::string& bookno);  // �Ƴ�������Ϣ
};

#endif // BORROWINFOSET_H
