EE355 Phase 1 Project

This submission implements Contact, Email, Phone, Date, Person, and Network for the Trojan-Book database.

Build examples:
g++ -std=c++98 test_person_eq.cpp person.cpp date.cpp contact.cpp -o test_person_eq
g++ -std=c++98 test_network.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp -o test_network

Implemented features:
- Email and Phone contact storage, input, formatting, and printing.
- Date parsing for numeric dates and printing in Month D, YYYY format.
- Person construction from input, file data, and direct field values.
- Doubly linked list storage for Network entries.
- Network load, save, search, remove, push_front, push_back, print, menu, and destructor.

Tested with networkDB.txt, person_template.txt, test_person_eq.cpp, and test_network.cpp.
