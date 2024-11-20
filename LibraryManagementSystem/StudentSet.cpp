#include "StudentSet.h"
#include <iostream>
#include <fstream>

// �������
bool StudentSet::ListInsert_S(const Student& e) {
    this->push_back(e);
    return true;
}

// ��ȡ������С
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

// ɾ����i��ѧ��
bool StudentSet::ListDelete_S(int i, Student& e) {
    if (i >= 0 && i < this->size()) {
        e = this->at(i);
        this->erase(this->begin() + i);
        return true;
    }
    return false;
}

// ��һ����������
bool StudentSet::LocateAllElem_S(const Student& e, bool (Student::* compare)(const Student&) const, std::vector<int>& find) {
    for (size_t i = 0; i < this->size(); ++i) {
        if ((this->at(i).*compare)(e)) {
            find.push_back(i);
        }
    }
    return !find.empty();
}

// ��ȡ��i������洢��e
bool StudentSet::GetElem_S(int i, Student& e) {
    if (i >= 0 && i < this->size()) {
        e = this->at(i);
        return true;
    }
    return false;
}

// ��i��λ�ö�����Ϊe
bool StudentSet::SetElem_S(int i, const Student& e) {
    if (i >= 0 && i < this->size()) {
        this->at(i) = e;
        return true;
    }
    return false;
}

// ����ѧ����Ϣ
bool StudentSet::OpenStuList() {
    std::ifstream infile("students.txt");
    if (!infile.is_open()) {
        std::cerr << "�޷���ѧ����Ϣ�ļ���" << std::endl;
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
        std::cerr << "�޷���ѧ����Ϣ�ļ���" << std::endl;
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
        std::cerr << "�޷���ͼ����Ϣ�ļ����б��棡" << std::endl;
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

// ���ѧ����Ϣ
void StudentSet::stu_manage_output(int pos) {
    for (size_t i = pos; i < this->size(); ++i) {
        std::cout << this->at(i) << std::endl;
    }
}

// ����������������ʵ��
