#include "Relationship.h"

// 设置函数实现
void Relationship::setstuno(const std::string& sno) { stuno = sno; }

void Relationship::setbookno(const std::string& bno) { bookno = bno; }

void Relationship::setstumobile(const std::string& mobi) { stumobile = mobi; }

// 获取函数实现
std::string Relationship::getstuno() const { return stuno; }

std::string Relationship::getbookno() const { return bookno; }

std::string Relationship::getstumobile() const { return stumobile; }

// 重载输入输出运算符
std::istream& operator>>(std::istream& is, Relationship& re) {
    // 假设输入格式为：学号 书号 手机号
    is >> re.stuno >> re.bookno >> re.stumobile;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Relationship& re) {
    os << "学号: " << re.stuno << ", 书号: " << re.bookno << ", 手机号: " << re.stumobile;
    return os;
}
