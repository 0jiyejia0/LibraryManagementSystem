#include "StudentNode.h"

// 设置函数实现
void StudentNode::setstudentno(const std::string& no) { studentno = no; }

void StudentNode::setborrownum(int b) { borrownum = b; }

// 获取函数实现
std::string StudentNode::getstudentno() const { return studentno; }

int StudentNode::getborrownum() const { return borrownum; }

// 借书
void StudentNode::pushbook(const BorrowInfo& b) {
    bilist.addBorrowInfo(b);
    ++borrownum;
}

// 查询是否借阅某本书
int StudentNode::BookWhetherIn(const std::string& bn) const {
    return bilist.findBook(bn);
}

// 还书
void StudentNode::returnbook(const std::string& bn) {
    bilist.removeBorrowInfo(bn);
    --borrownum;
}

// 输出所有借阅书籍信息
void StudentNode::printallbookinfo() const {
    for (const auto& bi : bilist) {
        std::cout << bi << std::endl;
    }
}

// 输出单本书籍借阅信息
void StudentNode::printsinglebookinfo(const std::string& bn) const {
    int index = bilist.findBook(bn);
    if (index != -1) {
        std::cout << bilist.at(index) << std::endl;
    }
    else {
        std::cout << "未借阅此书。" << std::endl;
    }
}

// 查询是否逾期
void StudentNode::outdate(const Date& now) const {
    const int deadline = 30; // 假设借阅期限为30天
    for (const auto& bi : bilist) {
        int days = now - bi.getborrowday();
        if (days > deadline) {
            std::cout << "书号: " << bi.getbookno() << " 已逾期 " << (days - deadline) << " 天。" << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const StudentNode& sn) {
    // 输出学生的基本信息
    out << sn.studentno << " " << sn.borrownum << std::endl;

    // 输出学生借阅的每本书的信息
    for (const auto& borrowInfo : sn.bilist) {
        out << borrowInfo << std::endl; // 假设 BorrowInfo 也重载了 << 运算符
    }

    return out;
}

std::istream& operator>>(std::istream& in, StudentNode& sn) {
    // 读取学生的基本信息
    in >> sn.studentno >> sn.borrownum;

    sn.bilist.clear();
    BorrowInfo bi;
    for (int i = 0; i < sn.borrownum; ++i) {
        in >> bi;  // 假设 BorrowInfo 重载了 >> 运算符
        sn.bilist.push_back(bi);
    }

    return in;
}

