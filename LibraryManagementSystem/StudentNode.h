#pragma once
#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include <string>
#include <iostream>
#include "BorrowInfoSet.h"

class StudentNode {
private:
    std::string studentno;   // ѧ��
    int borrownum;           // ��������
public:
    BorrowInfoSet bilist;    // ������Ϣ�б�

    void setstudentno(const std::string& no);
    void setborrownum(int b);
    std::string getstudentno() const;
    int getborrownum() const;

    void pushbook(const BorrowInfo& b); // ����

    int BookWhetherIn(const std::string& bn) const;   // ������Ų�ѯ�鼮�Ƿ񱻸�ͬѧ����

    void returnbook(const std::string& bn);   // ����

    void printallbookinfo() const;   // ������н����鼮��Ϣ

    void printsinglebookinfo(const std::string& bn) const;  // ��������鼮������Ϣ

    void outdate(const Date& now) const;  // ��ѯ�Ƿ�����

    // ����������������
    friend std::istream& operator>>(std::istream& is, StudentNode& sn);
    friend std::ostream& operator<<(std::ostream& os, const StudentNode& sn);
};

#endif // STUDENTNODE_H
