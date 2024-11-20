#include "BorrowInfo.h"

// 设置函数实现
void BorrowInfo::setbookno(const std::string& bno) { bookno = bno; }

void BorrowInfo::setborrowday(const Date& d) { borrowday = d; }

// 获取函数实现
std::string BorrowInfo::getbookno() const { return bookno; }

Date BorrowInfo::getborrowday() const { return borrowday; }

bool BorrowInfo::isOverdue(const Date& currentDate) const {
    int daysBetween = borrowday.daysBetween(currentDate);
    return daysBetween > 30;
}

std::ostream& operator<<(std::ostream& out, const BorrowInfo& bi) {
    out << bi.bookno << " " << bi.borrowday.getYear() << " " << bi.borrowday.getMonth() << " " << bi.borrowday.getDay();
    return out;
}

std::istream& operator>>(std::istream& in, BorrowInfo& bi) {
    int year, month, day;
    in >> bi.bookno >> year >> month >> day;
    bi.borrowday = Date(year, month, day);
    return in;
}
