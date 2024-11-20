#pragma once
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QDate>

class Date {
private:
    int year;
    int month;
    int day;

public:
    Date();
    Date(int y, int m, int d);

    void setDate(int y, int m, int d);
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // ���ؼ�����������������ڲ�
    int operator-(const Date& other) const;

    // ����������������
    friend std::istream& operator>>(std::istream& is, Date& date);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    static Date fromQDate(const QDate& qdate);
    QDate toQDate() const {
        return QDate(year, month, day);
    }

    // daysBetween ����
    int daysBetween(const Date& other) const;

    // ������������ڱȽ�����
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
};

#endif // DATE_H