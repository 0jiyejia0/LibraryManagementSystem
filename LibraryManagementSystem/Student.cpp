#include "Student.h"

// ���ú���ʵ��
void Student::setstuno(const std::string& no) { studentno = no; }

void Student::setstuname(const std::string& name) { studentname = name; }

void Student::setstumajor(const std::string& major) { studentmajor = major; }

void Student::setstuclass(const std::string& c) { studentclass = c; }

void Student::setstumobi(const std::string& mobi) { studentmobile = mobi; }

// ��ȡ����ʵ��
std::string Student::getstuno() const { return studentno; }

std::string Student::getstuname() const { return studentname; }

std::string Student::getstumajor() const { return studentmajor; }

std::string Student::getstuclass() const { return studentclass; }

std::string Student::getstumobi() const { return studentmobile; }

// �Ƚ����������
bool Student::operator==(const Student& s) const {
    return studentno == s.studentno;
}

// �ֶ�ƥ��
bool Student::index_stuno(const std::string& info) const {
    return studentno.find(info) != std::string::npos;
}

bool Student::index_stuname(const std::string& info) const {
    return studentname.find(info) != std::string::npos;
}

bool Student::index_stumajor(const std::string& info) const {
    return studentmajor.find(info) != std::string::npos;
}

bool Student::index_stuclass(const std::string& info) const {
    return studentclass.find(info) != std::string::npos;
}

bool Student::index_stumobile(const std::string& info) const {
    return studentmobile.find(info) != std::string::npos;
}

// �Ƚ�ѧ��ѧ���Ƿ���ͬ
bool Student::equal_stuno(const Student& b) const {
    return studentno == b.studentno;
}

// �Ƚ�ѧ����רҵ��༶�Ƿ���ͬ
bool Student::equal_stuma_or_cl(const Student& b) const {
    return studentmajor == b.studentmajor || studentclass == b.studentclass;
}

// ����������������
std::istream& operator>>(std::istream& is, Student& stu) {
    // ���������ʽΪ��ѧ�� ���� רҵ �༶ �ֻ���
    is >> stu.studentno >> stu.studentname >> stu.studentmajor >> stu.studentclass >> stu.studentmobile;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& stu) {
    os << "ѧ��: " << stu.studentno << ", ����: " << stu.studentname
        << ", רҵ: " << stu.studentmajor << ", �༶: " << stu.studentclass
        << ", �ֻ���: " << stu.studentmobile;
    return os;
}