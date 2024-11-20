#include "StudentSet.h"
#include <iostream>
#include <fstream>

// 插入对象
bool StudentSet::ListInsert_S(const Student& e) {
    this->push_back(e);
    return true;
}

// 获取容器大小
int StudentSet::ListLength_S() {
    return this->size();
}

int StudentSet::findStudent(const std::string& stuno) const {
    for (size_t i = 0; i < this->size(); ++i) {
        if (this->at(i).getstuno() == stuno) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 删除第i个学生
bool StudentSet::ListDelete_S(int i, Student& e) {
    if (i >= 0 && i < this->size()) {
        e = this->at(i);
        this->erase(this->begin() + i);
        return true;
    }
    return false;
}

// 按一定条件查找
bool StudentSet::LocateAllElem_S(const Student& e, bool (Student::* compare)(const Student&) const, std::vector<int>& find) {
    for (size_t i = 0; i < this->size(); ++i) {
        if ((this->at(i).*compare)(e)) {
            find.push_back(i);
        }
    }
    return !find.empty();
}

// 获取第i个对象存储于e
bool StudentSet::GetElem_S(int i, Student& e) {
    if (i >= 0 && i < this->size()) {
        e = this->at(i);
        return true;
    }
    return false;
}

// 第i个位置对象设为e
bool StudentSet::SetElem_S(int i, const Student& e) {
    if (i >= 0 && i < this->size()) {
        this->at(i) = e;
        return true;
    }
    return false;
}

// 载入学生信息
bool StudentSet::OpenStuList() {
    std::ifstream infile("students.txt");
    if (!infile.is_open()) {
        std::cerr << "无法打开学生信息文件！" << std::endl;
        return false;
    }
    Student stu;
    while (infile >> stu) {
        this->push_back(stu);
    }
    infile.close();
    return true;
}

bool StudentSet::AppendStuList() {
    std::ifstream infile("Append_Students.txt");
    if (!infile.is_open()) {
        std::cerr << "无法打开学生信息文件！" << std::endl;
        return false;
    }
    Student stu;
    while (infile >> stu) {
        this->push_back(stu);
    }
    infile.close();
    return true;
}

bool StudentSet::SaveStuList() {
    std::ofstream outfile("Append_Students.txt");
    if (!outfile.is_open()) {
        std::cerr << "无法打开图书信息文件进行保存！" << std::endl;
        return false;
    }
    for (const auto& student : *this) {
        outfile << student.getstuno() << " "
            << student.getstuname() << " "
            << student.getstumajor() << " "
            << student.getstuclass() << " "
            << student.getstumobi() << std::endl;
    }
    outfile.close();
    return true;
};

// 输出学生信息
void StudentSet::stu_manage_output(int pos) {
    for (size_t i = pos; i < this->size(); ++i) {
        std::cout << this->at(i) << std::endl;
    }
}

// 其他函数根据需求实现
