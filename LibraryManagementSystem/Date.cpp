#include "Date.h"

Date::Date() : year(0), month(0), day(0) {}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

void Date::setDate(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

int Date::getYear() const { return year; }

int Date::getMonth() const { return month; }

int Date::getDay() const { return day; }

int Date::operator-(const Date& other) const {
    // 简单起见，这里不考虑闰年和平月，大致计算日期差
    int totalDays1 = year * 360 + month * 30 + day;
    int totalDays2 = other.year * 360 + other.month * 30 + other.day;
    return totalDays1 - totalDays2;
}

std::istream& operator>>(std::istream& is, Date& date) {
    char separator;
    is >> date.year >> date.month >> date.day;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.year << "-" << date.month << "-" << date.day;
    return os;
}

Date Date::fromQDate(const QDate& qdate) {
    return Date(qdate.year(), qdate.month(), qdate.day());
}

int Date::daysBetween(const Date& other) const {
    QDate thisDate = this->toQDate();
    QDate otherDate = other.toQDate();
    return thisDate.daysTo(otherDate);
}

bool Date::operator>(const Date& other) const {
    if (year != other.year)
        return year > other.year;
    if (month != other.month)
        return month > other.month;
    return day > other.day;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year)
        return year < other.year;
    if (month != other.month)
        return month < other.month;
    return day < other.day;
}

