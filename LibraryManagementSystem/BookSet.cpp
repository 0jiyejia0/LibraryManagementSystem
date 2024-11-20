#include "BookSet.h"
#include <iostream>
#include <fstream>
#include <string>

// 构造函数和析构函数
BookSet::BookSet() {}

BookSet::~BookSet() {}

// 基本操作
int BookSet::ListLength_B() const {
    return books.size();
}

int BookSet::findBook(const std::string& bookno) const {
    for (size_t i = 0; i < this->getBooks().size(); ++i) {
        if (this->getBooks().at(i).getbookno() == bookno) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool BookSet::ListInsert_B(const Book& e) {
    books.push_back(e);
    return true;
}

bool BookSet::LocateAllElem_B(const Book& e, bool (*compare)(const Book&, const Book&), std::vector<int>& find) const {
    find.clear();
    for (size_t i = 0; i < books.size(); ++i) {
        if (compare(books[i], e)) {
            find.push_back(i);
        }
    }
    return !find.empty();
}

bool BookSet::GetElem_B(int i, Book& e) const {
    if (i >= 0 && i < books.size()) {
        e = books[i];
        return true;
    }
    return false;
}

bool BookSet::SetElem_B(int i, const Book& e) {
    if (i >= 0 && i < books.size()) {
        books[i] = e;
        return true;
    }
    return false;
}

// 文件操作
void BookSet::OpenBookList() {
    std::ifstream infile("books.txt");
    if (!infile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    Book b;
    while (infile >> b) {
        books.push_back(b);
    }
    infile.close();
    std::cout << "图书信息已载入" << std::endl;
}

void BookSet::AppendBookList() {
    std::ifstream infile("Append_Books.txt");
    if (!infile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    Book b;
    while (infile) {
        std::string bookno, bookname, author, publisher;
        int totalnum;
        Date pubday;
        infile >> bookno >> bookname >> author >> publisher
            >> totalnum >> pubday;
        if (bookno.empty())continue;
        b.setbookno(bookno);
        b.setbookname(bookname);
        b.setauthor(author);
        b.setpublisher(publisher);
        b.settotal(totalnum);
        b.setborrow(0);
        b.setpubday(pubday);
        books.push_back(b);
    }
    infile.close();
    std::cout << "图书信息已载入" << std::endl;
}

void BookSet::Output_Book(int pos) const {
    if (pos >= books.size()) {
        std::cout << "图书超出范围" << std::endl;
        return;
    }

    for (size_t i = pos; i < books.size(); ++i) {
        std::cout << books[i] << std::endl;
    }
}

// 图书管理操作
void BookSet::Append_book() {
    Book b;
    std::cin >> b;
    books.push_back(b);
}

void BookSet::book_manage_append() {
    Append_book();
}

void BookSet::book_search_char(const std::string& info, bool (Book::* f)(const std::string&) const) const {
    int count = 0;
    for (size_t i = 0; i < books.size(); ++i) {
        if ((books[i].*f)(info)) {
            std::cout << books[i] << std::endl;
            count++;
        }
    }
    if (count == 0) {
        std::cout << "未找到符合条件的书籍" << std::endl;
    }
}

void BookSet::book_search_have() const {
    int count = 0;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].gettotalnum() > books[i].getborrownum()) {
            std::cout << books[i] << std::endl;
            count++;
        }
    }
    if (count == 0) {
        std::cout << "所有书籍已被借完" << std::endl;
    }
}

void BookSet::book_search_date(int year, int month) const {
    int count = 0;
    for (size_t i = 0; i < books.size(); ++i) {
        Date d = books[i].getpubday();
        if (d.getYear() == year && d.getMonth() == month) {
            std::cout << books[i] << std::endl;
            count++;
        }
    }
    if (count == 0) {
        std::cout << "未找到指定日期的书籍" << std::endl;
    }
}

void BookSet::book_manage_search() {
    std::string info;
    std::cout << "请输入查询信息：";
    std::cin >> info;
    book_search_char(info, &Book::index_bookname);  // 示例：按书名查找
}

bool BookSet::RemoveElem_B(int i) {
    if (i >= 0 && i < books.size()) {
        books.erase(books.begin() + i);  // 删除指定位置的书籍
        return true;
    }
    return false;  // 索引无效
}

bool BookSet::SaveBookList()
{
    std::ofstream outfile("books.txt");
    if (!outfile.is_open()) {
        std::cerr << "无法打开图书信息文件进行保存！" << std::endl;
        return false;
    }
    for (const auto& book : *this) {
        outfile << book.getbookno() << " "
            << book.getbookname() << " "
            << book.getauthor() << " "
            << book.getpublisher() << " "
            << book.gettotalnum() << " "
            << book.getborrownum() << " "
            << book.getpubday().getYear() << " "
            << book.getpubday().getMonth() << " "
            << book.getpubday().getDay() << std::endl;
    }
    outfile.close();
    return true;
}

std::vector<Book>& BookSet::getBooks() {
    return books;
}

const std::vector<Book>& BookSet::getBooks() const {
    return books;
}