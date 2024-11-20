#include "SBList.h"
#include <iostream>
#include <fstream>

// 借阅信息初始化
bool SBList::begin_borrow() {
    studentnum = 0;
    borrownum = 0;
    sblist.clear();
    return true;
}

// 读入文件中的借阅信息
bool SBList::OpenBorrowList() {
    std::ifstream inFile("BorrowList.txt");
    if (!inFile.is_open()) {
        return false;
    }

    // 读取学生数量和借阅总数
    inFile >> studentnum >> borrownum;

    sblist.clear();

    // 读取每个学生的借阅信息
    StudentNode sn;
    while (inFile >> sn) {
        sblist.push_back(sn);
    }

    inFile.close();
    return true;
}

bool SBList::SaveBorrowList() {
    std::ofstream outFile("BorrowList.txt");
    if (!outFile.is_open()) {
        return false;
    }

    // 首先保存学生数量和借阅总数
    outFile << studentnum << " " << borrownum << std::endl;

    // 保存每个学生的借阅信息
    for (const auto& studentNode : sblist) {
        outFile << studentNode; // 使用重载的输出运算符
    }

    outFile.close();
    return true;
}

// 查询学生是否曾借阅书籍
int SBList::StuWhetherIn(const std::string& no) const {
    return sblist.findStudent(no);
}

// 新增一个借阅关系
void SBList::pushelem(const StudentNode& sn) {
    sblist.addStudentNode(sn);
    ++studentnum;
}

// 设置和获取函数
void SBList::setstudentnum(int s) { studentnum = s; }

void SBList::setborrownum(int b) { borrownum = b; }

int SBList::getstudentnum() const { return studentnum; }

int SBList::getborrownum() const { return borrownum; }

// 获取单个学生的借书量
int SBList::getpersonalnum(const std::string& no) const {
    int index = StuWhetherIn(no);
    if (index != -1) {
        return sblist.at(index).getborrownum();
    }
    return 0;
}

// 查询某一学生是否借阅某一本书
int SBList::BookWhetherIn(const std::string& sn, const std::string& bn) const {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        return sblist.at(index).BookWhetherIn(bn);
    }
    return -1;
}

// 某一学生新借一本书
void SBList::addanewrelation(const std::string& sn, const BorrowInfo& bi) {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        sblist.at(index).pushbook(bi);
    }
    else {
        StudentNode new_sn;
        new_sn.setstudentno(sn);
        new_sn.setborrownum(1);
        new_sn.pushbook(bi);
        pushelem(new_sn);
    }
    ++borrownum;
}

// 某一学生归还某本书
void SBList::returnbook(const std::string& sn, const std::string& bn) {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        sblist.at(index).returnbook(bn);
        --borrownum;
        if (sblist.at(index).getborrownum() == 0) {
            sblist.erase(sblist.begin() + index);
            --studentnum;
        }
    }
}

// 输出某人的借阅信息
void SBList::printbookinfo(const std::string& sn) const {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        sblist.at(index).printallbookinfo();
    }
    else {
        std::cout << "该学生没有借阅记录。" << std::endl;
    }
}

// 输出某一本书被借阅的情况
void SBList::printsinglebookinfo(const std::string& bn) const {
    for (const auto& sn : sblist) {
        if (sn.BookWhetherIn(bn) != -1) {
            std::cout << "学号: " << sn.getstudentno() << " 借阅了书号为 " << bn << " 的图书。" << std::endl;
        }
    }
}

// 查询所有存在逾期的同学
void SBList::outdate(const Date& now) {
    for (const auto& sn : sblist) {
        sn.outdate(now);
    }
}
