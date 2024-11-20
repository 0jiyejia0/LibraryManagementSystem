#include "Book.h"
#include <iostream>

// 设置函数
void Book::setbookno(const std::string& no) {
    bookno = no;
}

void Book::setbookname(const std::string& name) {
    bookname = name;
}

void Book::setauthor(const std::string& au) {
    author = au;
}

void Book::setpublisher(const std::string& pub) {
    publisher = pub;
}

void Book::settotal(int i) {
    totalnum = i;
}

void Book::setborrow(int i) {
    borrownum = i;
}

void Book::setpubday(const Date& d) {
    pubday = d;
}

// 获取函数
std::string Book::getbookno() const {
    return bookno;
}

std::string Book::getbookname() const {
    return bookname;
}

std::string Book::getauthor() const {
    return author;
}

std::string Book::getpublisher() const {
    return publisher;
}

int Book::gettotalnum() const {
    return totalnum;
}

int Book::getborrownum() const {
    return borrownum;
}

Date Book::getpubday() const {
    return pubday;
}

// 运算符重载
bool Book::operator==(const Book& b) const {
    return bookno == b.getbookno();
}

// 查询函数
bool Book::index_bookno(const std::string& info) const {
    return bookno.find(info) != std::string::npos;
}

bool Book::index_author(const std::string& info) const {
    return author.find(info) != std::string::npos;
}

bool Book::index_bookname(const std::string& info) const {
    return bookname.find(info) != std::string::npos;
}

bool Book::index_publisher(const std::string& info) const {
    return publisher.find(info) != std::string::npos;
}

// 输入输出运算符重载
std::istream& operator>>(std::istream& is, Book& boo) {
    is >> boo.bookno >> boo.bookname >> boo.author >> boo.publisher
        >> boo.totalnum >> boo.borrownum >> boo.pubday;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Book& boo) {
    os << boo.bookno << " " << boo.bookname << " " << boo.author << " "
        << boo.publisher << " " << boo.totalnum << " " << boo.borrownum
        << " " << boo.pubday;
    return os;
}
