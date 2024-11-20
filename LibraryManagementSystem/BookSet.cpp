#include "BookSet.h"
#include <iostream>
#include <fstream>
#include <string>

// ���캯������������
BookSet::BookSet() {}

BookSet::~BookSet() {}

// ��������
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

// �ļ�����
void BookSet::OpenBookList() {
    std::ifstream infile("books.txt");
    if (!infile) {
        std::cerr << "�޷����ļ�" << std::endl;
        return;
    }
    Book b;
    while (infile >> b) {
        books.push_back(b);
    }
    infile.close();
    std::cout << "ͼ����Ϣ������" << std::endl;
}

void BookSet::AppendBookList() {
    std::ifstream infile("Append_Books.txt");
    if (!infile) {
        std::cerr << "�޷����ļ�" << std::endl;
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
    std::cout << "ͼ����Ϣ������" << std::endl;
}

void BookSet::Output_Book(int pos) const {
    if (pos >= books.size()) {
        std::cout << "ͼ�鳬����Χ" << std::endl;
        return;
    }

    for (size_t i = pos; i < books.size(); ++i) {
        std::cout << books[i] << std::endl;
    }
}

// ͼ��������
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
        std::cout << "δ�ҵ������������鼮" << std::endl;
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
        std::cout << "�����鼮�ѱ�����" << std::endl;
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
        std::cout << "δ�ҵ�ָ�����ڵ��鼮" << std::endl;
    }
}

void BookSet::book_manage_search() {
    std::string info;
    std::cout << "�������ѯ��Ϣ��";
    std::cin >> info;
    book_search_char(info, &Book::index_bookname);  // ʾ��������������
}

bool BookSet::RemoveElem_B(int i) {
    if (i >= 0 && i < books.size()) {
        books.erase(books.begin() + i);  // ɾ��ָ��λ�õ��鼮
        return true;
    }
    return false;  // ������Ч
}

bool BookSet::SaveBookList()
{
    std::ofstream outfile("books.txt");
    if (!outfile.is_open()) {
        std::cerr << "�޷���ͼ����Ϣ�ļ����б��棡" << std::endl;
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