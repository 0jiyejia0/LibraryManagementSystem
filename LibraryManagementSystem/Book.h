#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Date.h"

class Book {
private:
    std::string bookno;     // ���
    std::string bookname;    // ����
    std::string author;      // ����
    std::string publisher;   // ������
    int totalnum;            // �ݲ�����
    int borrownum;           // �������
    Date pubday;             // ��������

public:
    // ���ú���
    void setbookno(const std::string& no);
    void setbookname(const std::string& name);
    void setauthor(const std::string& au);
    void setpublisher(const std::string& pub);
    void settotal(int i);
    void setborrow(int i);
    void setpubday(const Date& d);

    // ��ȡ����
    std::string getbookno() const;
    std::string getbookname() const;
    std::string getauthor() const;
    std::string getpublisher() const;
    int gettotalnum() const;
    int getborrownum() const;
    Date getpubday() const;

    // ����������
    bool operator==(const Book& b) const;

    // ��ѯ����
    bool index_bookno(const std::string& info) const;
    bool index_author(const std::string& info) const;
    bool index_bookname(const std::string& info) const;
    bool index_publisher(const std::string& info) const;

    // �����������
    friend std::istream& operator>>(std::istream& is, Book& boo);
    friend std::ostream& operator<<(std::ostream& os, const Book& boo);
};

#endif // BOOK_H
