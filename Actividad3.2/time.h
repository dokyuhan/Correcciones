#include <iostream>

#pragma once
class Time
{
private:
    int hour;
    int minute;
    int second;

public:
    Time() {};
    Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {};

    void setHour(int hour) { this->hour = hour; }
    void setMinute(int minute) { this->minute = minute; }
    void setSecond(int second) { this->second = second; }

    int getHour() { return hour; }
    int getMinute() { return minute; }
    int getSecond() { return second; }

    bool operator < (const Time& otra) const {
        if (hour < otra.hour) {
            return true;

        } else if (hour == otra.hour && minute < otra.minute) {
            return true;

        } else if (hour == otra.hour && minute == otra.minute && second < otra.second) {
            return true;
            
        }
        return false;
    }

    friend std::ostream& operator << (std::ostream& os, const Time& time) {
        os << time.hour << ":" << time.minute << ":" << time.second;
        return os;
    }

};