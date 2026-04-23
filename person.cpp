
#include "person.h"
#include <fstream>
#include <sstream>

Person::Person() {
    set_person();
}

Person::~Person() {
    delete birthdate;
    delete email;
    delete phone;
}

Person::Person(string f_name, string l_name, string b_date, string email_str, string phone_str) {
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(b_date);
    this->next = NULL;
    this->prev = NULL;

    // Parse email: "(Type) address"
    int open = email_str.find('(');
    int close = email_str.find(')');
    string eType = email_str.substr(open + 1, close - open - 1);
    string eAddr = email_str.substr(close + 2);
    this->email = new Email(eType, eAddr);

    // Parse phone: "(Type) number"
    open = phone_str.find('(');
    close = phone_str.find(')');
    string pType = phone_str.substr(open + 1, close - open - 1);
    string pNum = phone_str.substr(close + 2);
    this->phone = new Phone(pType, pNum);
}

Person::Person(string filename) {
    set_person(filename);
}

void Person::set_person() {
    string temp;
    string eType, eAddr, pType, pNum;

    cout << "First Name: ";
    getline(cin, f_name);

    cout << "Last Name: ";
    getline(cin, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin, temp);
    birthdate = new Date(temp);

    cout << "Type of email address: ";
    getline(cin, eType);
    cout << "Email address: ";
    getline(cin, eAddr);
    email = new Email(eType, eAddr);

    cout << "Type of phone number: ";
    getline(cin, pType);
    cout << "Phone number: ";
    getline(cin, pNum);
    phone = new Phone(pType, pNum);

    next = NULL;
    prev = NULL;
}

void Person::set_person(string filename) {
    ifstream file(filename.c_str());
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    getline(file, f_name);
    getline(file, l_name);

    string dateStr;
    getline(file, dateStr);
    birthdate = new Date(dateStr);

    // Read two lines, could be phone then email or email then phone
    string line4, line5;
    getline(file, line4);
    getline(file, line5);

    string emailLine, phoneLine;
    // Detect which is which by looking for '@'
    if (line4.find('@') != string::npos) {
        emailLine = line4;
        phoneLine = line5;
    } else {
        phoneLine = line4;
        emailLine = line5;
    }

    int open = phoneLine.find('(');
    int close = phoneLine.find(')');
    string pType = phoneLine.substr(open + 1, close - open - 1);
    string pNum = phoneLine.substr(close + 2);
    phone = new Phone(pType, pNum);

    open = emailLine.find('(');
    close = emailLine.find(')');
    string eType = emailLine.substr(open + 1, close - open - 1);
    string eAddr = emailLine.substr(close + 2);
    email = new Email(eType, eAddr);

    file.close();
    next = NULL;
    prev = NULL;
}

bool Person::operator==(const Person& rhs) {
    return (f_name == rhs.f_name && l_name == rhs.l_name && *birthdate == *rhs.birthdate);
}

bool Person::operator!=(const Person& rhs) {
    return !(*this == rhs);
}

void Person::print_person() {
    cout << l_name << ", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}
