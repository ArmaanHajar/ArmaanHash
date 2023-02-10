/*
 * Author: Armaan Hajar
 * Program:
 * Date:
 */

#include <iostream>
#include <cstring>
#include "student.h"
#include "node.h"

using namespace std;

int main() {
  int bucketSize = 100;
  Node* hashTable[bucketSize];

  for (int i = 0; i < bucketSize; i++) {
    hashTable[i] = NULL;
  }

  char input[10];
  bool running = true;

  // main code, running will stay true until user says "QUIT"
  while (running == true) {
    cout << "---------------------------------------------------------------" << endl;
    cout << "What Would You Like To Do? (ADD/PRINT/DELETE/QUIT/HELP)" << endl;

    cin.get(input, 10);
    cin.ignore(1, '\n');

    if (input[1] == 'D' || input[1] == 'd') { // adds student
      char firstName[20];
      char lastName[20];
      int studentID = 0;
      float gpa = 0.0;
      Student* newStudent = new Student(firstName, lastName, studentID, gpa);
      
      // read in first name
      cout << "First Name: " << endl;
      cin.get(firstName, 20);
      cin.ignore(1, '\n');
      newStudent->set_first_name(firstName);

      // read in last name
      cout << "Last Name: " << endl;
      cin.get(lastName, 20);
      cin.ignore(1, '\n');
      newStudent->set_last_name(lastName);

      // read in student id
      cout << "Student ID: " << endl;
      cin >> studentID;
      cin.ignore();
      newStudent->set_id(studentID);

      // read in gpa
      cout << "GPA: " << endl;
      cin >> gpa;
      cin.ignore();
      newStudent->set_gpa(gpa);

      Node* newNode = new Node(newStudent);
      
      int hashIndex = newStudent->get_id() % 100;

      if (hashTable[hashIndex] == NULL) {
        hashTable[hashIndex] = newNode;
      }
      else if (hashTable[hashIndex] != NULL) {
        Node* temp = hashTable[hashIndex];
        while (temp->getNext() != NULL) {
          temp = temp->getNext();
        }
        temp->setNext(newNode);
      }
      else {
        cout << "Error" << endl;
      }
    }
    else if (input[1] == 'R' || input[1] == 'r') { // prints all students inputted
      for (int i = 0; i < bucketSize; i++) {
        if (hashTable[i] != NULL) {
          Node* temp = hashTable[i];
          while (temp != NULL) {
            cout << temp->getStudent()->get_first_name() << ", " << temp->getStudent()->get_last_name() << ", " << temp->getStudent()->get_id() << ", " << temp->getStudent()->get_gpa() << endl;
            temp = temp->getNext();
          }
        }
      }  
    }
    else if (input[2] == 'L' || input[2] == 'l') { // deletes a student
      int studentID = 0;
      cout << "What Is The Student ID Of The Student You Would Like To Delete?" << endl;
      cin >> studentID;
      cin.ignore();

      int hashIndex = studentID % 100;

      if (hashTable[hashIndex] != NULL) {
        Node* temp = hashTable[hashIndex];
        Node* prev = NULL;
        while (temp != NULL) {
          if (temp->getStudent()->get_id() == studentID) {
            if (prev == NULL) {
              hashTable[hashIndex] = temp->getNext();
              delete temp;
              break;
            }
            else {
              prev->setNext(temp->getNext());
              delete temp;
              break;
            }
          }
          prev = temp;
          temp = temp->getNext();
        }
      }
      else {
        cout << "Student Not Found" << endl;
      }
    }
    else if (input[0] == 'Q' || input[0] == 'q') { // ends program
      cout << "Thank You For Using the Student List Maker!" << endl;
      running = false;
    }
    else if (input[0] == 'H' || input[0] == 'h') { // prints help message
      help();
    }
    else {
      cout << "Type \"ADD\" To Enter A New Student" << endl;
      cout << "Type \"PRINT\" To Print Out All Stored Students" << endl;
      cout << "Type \"DELETE\" To Delete A Student" << endl;
      cout << "Type \"QUIT\" To End Program" << endl;
    }
  }  
  return 0;
}