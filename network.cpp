
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <cstring>

Network::Network() {
    head = NULL;
    tail = NULL;
    count = 0;
}

Network::Network(string fileName) {
    head = NULL;
    tail = NULL;
    count = 0;
    loadDB(fileName);
}

Network::~Network() {
    Person* current = head;
    while (current != NULL) {
        Person* temp = current;
        current = current->next;
        delete temp;
    }
}

Person* Network::search(Person* searchEntry) {
    Person* ptr = head;
    while (ptr != NULL) {
        if (*ptr == *searchEntry) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Person* Network::search(string fname, string lname) {
    Person* ptr = head;
    while (ptr != NULL) {
        if (ptr->f_name == fname && ptr->l_name == lname) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void Network::loadDB(string filename) {
    ifstream file(filename.c_str());
    if (!file) {
        cout << "File " << filename << " does not exist!" << endl;
        return;
    }

    // Clear existing list
    Person* current = head;
    while (current != NULL) {
        Person* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    tail = NULL;
    count = 0;

    string fname, lname, dateStr, line4, line5, separator;

    while (getline(file, fname)) {
        if (fname.empty()) continue;
        if (fname[0] == '-') continue;

        getline(file, lname);
        getline(file, dateStr);
        getline(file, line4);
        getline(file, line5);

        string emailLine, phoneLine;
        if (line4.find('@') != string::npos) {
            emailLine = line4;
            phoneLine = line5;
        } else {
            phoneLine = line4;
            emailLine = line5;
        }

        Person* p = new Person(fname, lname, dateStr, emailLine, phoneLine);
        push_back(p);

        if (file.peek() != EOF) {
            getline(file, separator);
        }
    }

    file.close();
}

void Network::saveDB(string filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    Person* ptr = head;
    while (ptr != NULL) {
        file << ptr->f_name << endl;
        file << ptr->l_name << endl;
        file << ptr->birthdate->get_date_str() << endl;
        file << ptr->phone->get_contact() << endl;
        file << ptr->email->get_contact() << endl;
        file << "--------------------" << endl;
        ptr = ptr->next;
    }

    file.close();
}

void Network::printDB() {
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while (ptr != NULL) {
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

void Network::push_front(Person* newEntry) {
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;

    head = newEntry;
    count++;
}

void Network::push_back(Person* newEntry) {
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
}

bool Network::remove(string fname, string lname) {
    Person* target = search(fname, lname);
    if (target == NULL) return false;

    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        head = target->next;

    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        tail = target->prev;

    delete target;
    count--;
    return true;
}

void Network::showMenu() {
    int opt;
    while (1) {
        cout << "\033[2J\033[1;1H";
        printMe("banner");

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt == 1) {
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt == 2) {
            cout << "Loading network database \n";

            // List all .txt files in current directory
            DIR* dir = opendir(".");
            if (dir != NULL) {
                struct dirent* entry;
                while ((entry = readdir(dir)) != NULL) {
                    string name = entry->d_name;
                    if (name.length() > 4 && name.substr(name.length() - 4) == ".txt") {
                        cout << name << endl;
                    }
                }
                closedir(dir);
            }

            cout << "Enter the name of the load file: ";
            getline(cin, fileName);

            ifstream testFile(fileName.c_str());
            if (!testFile) {
                cout << "File " << fileName << " does not exist!" << endl;
            } else {
                testFile.close();
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        }
        else if (opt == 3) {
            cout << "Adding a new person \n";
            Person* newPerson = new Person();

            if (search(newPerson->f_name, newPerson->l_name) != NULL) {
                cout << "Person already exists! \n";
                delete newPerson;
            } else {
                push_front(newPerson);
            }
        }
        else if (opt == 4) {
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);

            if (remove(fname, lname)) {
                cout << "Remove Successful! \n";
            } else {
                cout << "Person not found! \n";
            }
        }
        else if (opt == 5) {
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);

            bool found = false;
            Person* ptr = head;
            while (ptr != NULL) {
                if (ptr->l_name == lname) {
                    ptr->print_person();
                    cout << "------------------------------" << endl;
                    found = true;
                }
                ptr = ptr->next;
            }
            if (!found) {
                cout << "Person not found! \n";
            }
        }
        else
            cout << "Nothing matched!\n";

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        getline(cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}
