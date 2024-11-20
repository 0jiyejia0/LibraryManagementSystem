#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Date.h"

class Book {
private:
    std::string bookno;     // 书号
    std::string bookname;    // 书名
    std::string author;      // 作者
    std::string publisher;   // 出版社
    int totalnum;            // 馆藏数量
    int borrownum;           // 借出数量
    Date pubday;             // 出版日期

public:
    // 设置函数
    void setbookno(const std::string& no);
    void setbookname(const std::string& name);
    void setauthor(const std::string& au);
    void setpublisher(const std::string& pub);
    void settotal(int i);
    void setborrow(int i);
    void setpubday(const Date& d);

    // 获取函数
    std::string getbookno() const;
    std::string getbookname() const;
    std::string getauthor() const;
    std::string getpublisher() const;
    int gettotalnum() const;
    int getborrownum() const;
    Date getpubday() const;

    // 操作符重载
    bool operator==(const Book& b) const;

    // 查询函数
    bool index_bookno(const std::string& info) const;
    bool index_author(const std::string& info) const;
    bool index_bookname(const std::string& info) const;
    bool index_publisher(const std::string& info) const;

    // 输入输出重载
    friend std::istream& operator>>(std::istream& is, Book& boo);
    friend std::ostream& operator<<(std::ostream& os, const Book& boo);
};

#endif // BOOK_H
