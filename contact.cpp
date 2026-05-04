
#include "contact.h"
#include <sstream>

Email::Email(string type, string email_addr) {
    this->type = type;
    this->email_addr = email_addr;
}

void Email::set_contact() {
    cout << "Enter the type of email address: ";
    getline(cin, type);
    cout << "Enter email address: ";
    getline(cin, email_addr);
}

string Email::get_contact(string style) {
    if (style == "full")
        return "(" + type + "): " + email_addr;
    else
        return email_addr;
}

void Email::print() {
    cout << "Email " << get_contact() << endl;
}

Phone::Phone(string type, string num) {
    this->type = type;
    string clean = "";
    for (string::size_type i = 0; i < num.length(); i++) {
        if (num[i] != '-') {
            clean += num[i];
        }
    }
    this->phone_num = clean;
}

void Phone::set_contact() {
    cout << "Enter the type of phone number: ";
    getline(cin, type);
    cout << "Enter the phone number: ";
    string num;
    getline(cin, num);
    string clean = "";
    for (string::size_type i = 0; i < num.length(); i++) {
        if (num[i] != '-') {
            clean += num[i];
        }
    }
    phone_num = clean;
}

string Phone::get_contact(string style) {
    string formatted = phone_num.substr(0, 3) + "-" +
                      phone_num.substr(3, 3) + "-" +
                      phone_num.substr(6, 4);
    if (style == "full") {
        return "(" + type + "): " + formatted;
    }
    else {
        return formatted;
    }
}

void Phone::print() {
    cout << "Phone " << get_contact() << endl;
}
