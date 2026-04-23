
#include "date.h"
#include <sstream>

Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

Date::Date(string dateStr) {
    char slash;
    stringstream ss(dateStr);
    ss >> month;
    ss >> slash;
    ss >> day;
    ss >> slash;
    ss >> year;
}

void Date::print_date(string format) {
    string monthNames[] = {"", "January", "February", "March", "April",
                           "May", "June", "July", "August", "September",
                           "October", "November", "December"};

    if (month >= 1 && month <= 12) {
        cout << monthNames[month] << " " << day << ", " << year << endl;
    }
}

string Date::get_date_str() {
    stringstream ss;
    ss << month << "/" << day << "/" << year;
    return ss.str();
}

bool Date::operator==(const Date& rhs) {
    return (month == rhs.month && day == rhs.day && year == rhs.year);
}
