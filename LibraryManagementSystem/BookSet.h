#pragma once
#ifndef BOOKSET_H
#define BOOKSET_H

#include <vector>
#include "Book.h"

class BookSet {
private:
    std::vector<Book> books;

public:
    // 构造函数和析构函数
    BookSet();
    ~BookSet();

    // 基本操作
    int ListLength_B() const;                // 获取容器大小
    bool ListInsert_B(const Book& e);        // 插入单本书
    int findBook(const std::string& bookno) const;
    bool LocateAllElem_B(const Book& e, bool (*compare)(const Book&, const Book&), std::vector<int>& find) const; // 查找
    bool GetElem_B(int i, Book& e) const;    // 获取指定位置的书籍信息
    bool SetElem_B(int i, const Book& e);    // 修改指定位置的书籍信息

    // 文件操作
    void OpenBookList();
    void Output_Book(int pos = 0) const;

    // 添加 begin() 和 end() 成员函数
    std::vector<Book>::iterator begin() { return books.begin(); }
    std::vector<Book>::iterator end() { return books.end(); }
    std::vector<Book>::const_iterator begin() const { return books.begin(); }
    std::vector<Book>::const_iterator end() const { return books.end(); }

    std::vector<Book>& getBooks();               // 非 const 版本
    const std::vector<Book>& getBooks() const;   // const 版本

    // 图书管理操作
    void Append_book();
    void AppendBookList();
    void book_manage_append();
    void book_search_char(const std::string& info, bool (Book::* f)(const std::string&) const) const;
    void book_search_have() const;
    void book_search_date(int year, int month) const;
    void book_manage_search();

    bool RemoveElem_B(int i);
    bool SaveBookList();
};

#endif // BOOKSET_H
