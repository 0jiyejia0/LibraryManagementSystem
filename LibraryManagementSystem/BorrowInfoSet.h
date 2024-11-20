#pragma once
#ifndef BORROWINFOSET_H
#define BORROWINFOSET_H

#include <vector>
#include "BorrowInfo.h"

class BorrowInfoSet : public std::vector<BorrowInfo> {
public:
    void addBorrowInfo(const BorrowInfo& bi);   // 添加借阅信息

    int findBook(const std::string& bookno) const;  // 查找借阅信息

    void removeBorrowInfo(const std::string& bookno);  // 移除借阅信息
};

#endif // BORROWINFOSET_H
