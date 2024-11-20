#include "Student.h"

// 设置函数实现
void Student::setstuno(const std::string& no) { studentno = no; }

void Student::setstuname(const std::string& name) { studentname = name; }

void Student::setstumajor(const std::string& major) { studentmajor = major; }

void Student::setstuclass(const std::string& c) { studentclass = c; }

void Student::setstumobi(const std::string& mobi) { studentmobile = mobi; }

// 获取函数实现
std::string Student::getstuno() const { return studentno; }

std::string Student::getstuname() const { return studentname; }

std::string Student::getstumajor() const { return studentmajor; }

std::string Student::getstuclass() const { return studentclass; }

std::string Student::getstumobi() const { return studentmobile; }

// 比较运算符重载
bool Student::operator==(const Student& s) const {
    return studentno == s.studentno;
}

// 字段匹配
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

// 比较学生学号是否相同
bool Student::equal_stuno(const Student& b) const {
    return studentno == b.studentno;
}

// 比较学生的专业或班级是否相同
bool Student::equal_stuma_or_cl(const Student& b) const {
    return studentmajor == b.studentmajor || studentclass == b.studentclass;
}

// 重载输入输出运算符
std::istream& operator>>(std::istream& is, Student& stu) {
    // 假设输入格式为：学号 姓名 专业 班级 手机号
    is >> stu.studentno >> stu.studentname >> stu.studentmajor >> stu.studentclass >> stu.studentmobile;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& stu) {
    os << "学号: " << stu.studentno << ", 姓名: " << stu.studentname
        << ", 专业: " << stu.studentmajor << ", 班级: " << stu.studentclass
        << ", 手机号: " << stu.studentmobile;
    return os;
}