#include "SBList.h"
#include <iostream>
#include <fstream>

// ������Ϣ��ʼ��
bool SBList::begin_borrow() {
    studentnum = 0;
    borrownum = 0;
    sblist.clear();
    return true;
}

// �����ļ��еĽ�����Ϣ
bool SBList::OpenBorrowList() {
    std::ifstream inFile("BorrowList.txt");
    if (!inFile.is_open()) {
        return false;
    }

    // ��ȡѧ�������ͽ�������
    inFile >> studentnum >> borrownum;

    sblist.clear();

    // ��ȡÿ��ѧ���Ľ�����Ϣ
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

    // ���ȱ���ѧ�������ͽ�������
    outFile << studentnum << " " << borrownum << std::endl;

    // ����ÿ��ѧ���Ľ�����Ϣ
    for (const auto& studentNode : sblist) {
        outFile << studentNode; // ʹ�����ص���������
    }

    outFile.close();
    return true;
}

// ��ѯѧ���Ƿ��������鼮
int SBList::StuWhetherIn(const std::string& no) const {
    return sblist.findStudent(no);
}

// ����һ�����Ĺ�ϵ
void SBList::pushelem(const StudentNode& sn) {
    sblist.addStudentNode(sn);
    ++studentnum;
}

// ���úͻ�ȡ����
void SBList::setstudentnum(int s) { studentnum = s; }

void SBList::setborrownum(int b) { borrownum = b; }

int SBList::getstudentnum() const { return studentnum; }

int SBList::getborrownum() const { return borrownum; }

// ��ȡ����ѧ���Ľ�����
int SBList::getpersonalnum(const std::string& no) const {
    int index = StuWhetherIn(no);
    if (index != -1) {
        return sblist.at(index).getborrownum();
    }
    return 0;
}

// ��ѯĳһѧ���Ƿ����ĳһ����
int SBList::BookWhetherIn(const std::string& sn, const std::string& bn) const {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        return sblist.at(index).BookWhetherIn(bn);
    }
    return -1;
}

// ĳһѧ���½�һ����
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

// ĳһѧ���黹ĳ����
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

// ���ĳ�˵Ľ�����Ϣ
void SBList::printbookinfo(const std::string& sn) const {
    int index = StuWhetherIn(sn);
    if (index != -1) {
        sblist.at(index).printallbookinfo();
    }
    else {
        std::cout << "��ѧ��û�н��ļ�¼��" << std::endl;
    }
}

// ���ĳһ���鱻���ĵ����
void SBList::printsinglebookinfo(const std::string& bn) const {
    for (const auto& sn : sblist) {
        if (sn.BookWhetherIn(bn) != -1) {
            std::cout << "ѧ��: " << sn.getstudentno() << " ���������Ϊ " << bn << " ��ͼ�顣" << std::endl;
        }
    }
}

// ��ѯ���д������ڵ�ͬѧ
void SBList::outdate(const Date& now) {
    for (const auto& sn : sblist) {
        sn.outdate(now);
    }
}
