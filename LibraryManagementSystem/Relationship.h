#pragma once
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>
#include <iostream>

class Relationship {
private:
    std::string stuno;      // ѧ��
    std::string bookno;     // ���
    std::string stumobile;  // �ֻ���

public:
    // ���ú���
    void setstuno(const std::string& sno);
    void setbookno(const std::string& bno);
    void setstumobile(const std::string& mobi);

    // ��ȡ����
    std::string getstuno() const;
    std::string getbookno() const;
    std::string getstumobile() const;

    // ����������������
    friend std::istream& operator>>(std::istream& is, Relationship& re);
    friend std::ostream& operator<<(std::ostream& os, const Relationship& re);
};

#endif // RELATIONSHIP_H
