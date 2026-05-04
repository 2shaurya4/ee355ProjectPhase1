
#include "date.h"
#include <sstream>

Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

Date::Date(string dateStr) {
    if (dateStr.find('/') != string::npos) {
        char slash;
        stringstream ss(dateStr);
        ss >> month;
        ss >> slash;
        ss >> day;
        ss >> slash;
        ss >> year;
    } else {
        string monthStr;
        char comma;
        stringstream ss(dateStr);
        string monthNames[] = {"", "January", "February", "March", "April",
                               "May", "June", "July", "August", "September",
                               "October", "November", "December"};

        ss >> monthStr;
        month = 0;
        for (int i = 1; i <= 12; i++) {
            if (monthStr == monthNames[i]) {
                month = i;
            }
        }
        ss >> day;
        ss >> comma;
        ss >> year;
    }
}

void Date::print_date(string format) {
    cout << get_date_str(format) << endl;
}

string Date::get_date_str(string format) {
    string monthNames[] = {"", "January", "February", "March", "April",
                           "May", "June", "July", "August", "September",
                           "October", "November", "December"};
    stringstream ss;
    if (format == "Month D, YYYY" && month >= 1 && month <= 12)
        ss << monthNames[month] << " " << day << ", " << year;
    else
        ss << month << "/" << day << "/" << year;
    return ss.str();
}

bool Date::operator==(const Date& rhs) {
    return (month == rhs.month && day == rhs.day && year == rhs.year);
}
