#include "StudentNode.h"

// ���ú���ʵ��
void StudentNode::setstudentno(const std::string& no) { studentno = no; }

void StudentNode::setborrownum(int b) { borrownum = b; }

// ��ȡ����ʵ��
std::string StudentNode::getstudentno() const { return studentno; }

int StudentNode::getborrownum() const { return borrownum; }

// ����
void StudentNode::pushbook(const BorrowInfo& b) {
    bilist.addBorrowInfo(b);
    ++borrownum;
}

// ��ѯ�Ƿ����ĳ����
int StudentNode::BookWhetherIn(const std::string& bn) const {
    return bilist.findBook(bn);
}

// ����
void StudentNode::returnbook(const std::string& bn) {
    bilist.removeBorrowInfo(bn);
    --borrownum;
}

// ������н����鼮��Ϣ
void StudentNode::printallbookinfo() const {
    for (const auto& bi : bilist) {
        std::cout << bi << std::endl;
    }
}

// ��������鼮������Ϣ
void StudentNode::printsinglebookinfo(const std::string& bn) const {
    int index = bilist.findBook(bn);
    if (index != -1) {
        std::cout << bilist.at(index) << std::endl;
    }
    else {
        std::cout << "δ���Ĵ��顣" << std::endl;
    }
}

// ��ѯ�Ƿ�����
void StudentNode::outdate(const Date& now) const {
    const int deadline = 30; // �����������Ϊ30��
    for (const auto& bi : bilist) {
        int days = now - bi.getborrowday();
        if (days > deadline) {
            std::cout << "���: " << bi.getbookno() << " ������ " << (days - deadline) << " �졣" << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const StudentNode& sn) {
    // ���ѧ���Ļ�����Ϣ
    out << sn.studentno << " " << sn.borrownum << std::endl;

    // ���ѧ�����ĵ�ÿ�������Ϣ
    for (const auto& borrowInfo : sn.bilist) {
        out << borrowInfo << std::endl; // ���� BorrowInfo Ҳ������ << �����
    }

    return out;
}

std::istream& operator>>(std::istream& in, StudentNode& sn) {
    // ��ȡѧ���Ļ�����Ϣ
    in >> sn.studentno >> sn.borrownum;

    sn.bilist.clear();
    BorrowInfo bi;
    for (int i = 0; i < sn.borrownum; ++i) {
        in >> bi;  // ���� BorrowInfo ������ >> �����
        sn.bilist.push_back(bi);
    }

    return in;
}

