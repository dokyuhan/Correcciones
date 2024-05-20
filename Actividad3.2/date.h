#include <iostream>

#pragma once
class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() {};
    Date(int day, int month, int year) : day(day), month(month), year(year) {};

    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    bool operator < (const Date& otra) const {
        if (year < otra.year) {
            return true;

        } else if (year == otra.year && month < otra.month) {
            return true;

        } else if (year == otra.year && month == otra.month && day < otra.day) {
            return true;

        }
        return false;
    }
    
    bool operator == (const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator != (const Date& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator << (std::ostream& os, const Date& date) {
        os << date.day << "/" << date.month << "/" << date.year;
        return os;
    }

};