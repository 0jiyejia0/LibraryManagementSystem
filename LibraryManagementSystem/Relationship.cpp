#include "Relationship.h"

// ���ú���ʵ��
void Relationship::setstuno(const std::string& sno) { stuno = sno; }

void Relationship::setbookno(const std::string& bno) { bookno = bno; }

void Relationship::setstumobile(const std::string& mobi) { stumobile = mobi; }

// ��ȡ����ʵ��
std::string Relationship::getstuno() const { return stuno; }

std::string Relationship::getbookno() const { return bookno; }

std::string Relationship::getstumobile() const { return stumobile; }

// ����������������
std::istream& operator>>(std::istream& is, Relationship& re) {
    // ���������ʽΪ��ѧ�� ��� �ֻ���
    is >> re.stuno >> re.bookno >> re.stumobile;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Relationship& re) {
    os << "ѧ��: " << re.stuno << ", ���: " << re.bookno << ", �ֻ���: " << re.stumobile;
    return os;
}
