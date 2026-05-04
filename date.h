
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

public:
    Date();
    Date(string dateStr);
    void print_date(string format = "Month D, YYYY");
    string get_date_str(string format = "M/D/YYYY");
    bool operator==(const Date& rhs);
};

#endif
