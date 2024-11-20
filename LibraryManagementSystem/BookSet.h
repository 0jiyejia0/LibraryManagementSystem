#pragma once
#ifndef BOOKSET_H
#define BOOKSET_H

#include <vector>
#include "Book.h"

class BookSet {
private:
    std::vector<Book> books;

public:
    // ���캯������������
    BookSet();
    ~BookSet();

    // ��������
    int ListLength_B() const;                // ��ȡ������С
    bool ListInsert_B(const Book& e);        // ���뵥����
    int findBook(const std::string& bookno) const;
    bool LocateAllElem_B(const Book& e, bool (*compare)(const Book&, const Book&), std::vector<int>& find) const; // ����
    bool GetElem_B(int i, Book& e) const;    // ��ȡָ��λ�õ��鼮��Ϣ
    bool SetElem_B(int i, const Book& e);    // �޸�ָ��λ�õ��鼮��Ϣ

    // �ļ�����
    void OpenBookList();
    void Output_Book(int pos = 0) const;

    // ��� begin() �� end() ��Ա����
    std::vector<Book>::iterator begin() { return books.begin(); }
    std::vector<Book>::iterator end() { return books.end(); }
    std::vector<Book>::const_iterator begin() const { return books.begin(); }
    std::vector<Book>::const_iterator end() const { return books.end(); }

    std::vector<Book>& getBooks();               // �� const �汾
    const std::vector<Book>& getBooks() const;   // const �汾

    // ͼ��������
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
