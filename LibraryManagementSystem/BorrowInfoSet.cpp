#include "BorrowInfoSet.h"

// ��ӽ�����Ϣ
void BorrowInfoSet::addBorrowInfo(const BorrowInfo& bi) {
    this->push_back(bi);
}

// ���ҽ�����Ϣ
int BorrowInfoSet::findBook(const std::string& bookno) const {
    for (size_t i = 0; i < this->size(); ++i) {
        if (this->at(i).getbookno() == bookno) {
            return i;
        }
    }
    return -1;
}

// �Ƴ�������Ϣ
void BorrowInfoSet::removeBorrowInfo(const std::string& bookno) {
    int index = findBook(bookno);
    if (index != -1) {
        this->erase(this->begin() + index);
    }
}
