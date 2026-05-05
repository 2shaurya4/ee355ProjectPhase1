EE355 Phase 1

Basic TrojanBook database project.

Compile:
g++ -std=c++98 test_person_eq.cpp person.cpp date.cpp contact.cpp -o test_person_eq
g++ -std=c++98 test_network.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp -o test_network

Main parts:
- Contact, Email, and Phone classes
- Date class
- Person class
- Network class
- load and save database
- add, remove, print, and search

Test files used:
networkDB.txt
person_template.txt
test_person_eq.cpp
test_network.cpp

Test results:
- test_person_eq.cpp compiled successfully.
- test_network.cpp compiled successfully.
- networkDB.txt loaded and printed the people in the database.
