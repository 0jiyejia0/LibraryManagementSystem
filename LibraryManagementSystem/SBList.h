#pragma once
#ifndef SBLIST_H
#define SBLIST_H

#include "StudentNodeSet.h"

class SBList {
private:
    int studentnum;           // �����鼮������
    int borrownum;            // ���ȥ��������
public:
    StudentNodeSet sblist;    // ѧ��������Ϣ�б�

    bool begin_borrow();    // ������Ϣ��ʼ��

    bool OpenBorrowList();     // �����ļ��еĽ�����Ϣ

    int StuWhetherIn(const std::string& no) const;   // ��ѯѧ���Ƿ��������鼮

    void pushelem(const StudentNode& sn);   // ����һ�����Ĺ�ϵ

    bool SaveBorrowList();

    void setstudentnum(int s);
    void setborrownum(int b);
    int getstudentnum() const;
    int getborrownum() const;

    int getpersonalnum(const std::string& no) const;   // ��ȡ����ѧ���Ľ�����

    int BookWhetherIn(const std::string& sn, const std::string& bn) const;   // ��ѯĳһѧ���Ƿ����ĳһ����

    void addanewrelation(const std::string& sn, const BorrowInfo& bi);   // ĳһѧ���½�һ����

    void returnbook(const std::string& sn, const std::string& bn);   // ĳһѧ���黹ĳ����

    void printbookinfo(const std::string& sn) const;  // ���ĳ�˵Ľ�����Ϣ

    void printsinglebookinfo(const std::string& bn) const;   // ���ĳһ���鱻���ĵ����

    void outdate(const Date& now);   // ��ѯ���д������ڵ�ͬѧ
};

#endif // SBLIST_H
