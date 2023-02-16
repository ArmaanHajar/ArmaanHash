/*
 * Author: Armaan Hajar
 * Program:
 * Date:
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include "student.h"
#include "node.h"

using namespace std;

void rehash(int &bucketSize, Node** &hashTable);

int main() {
  srand(time(NULL));
  int initialBucket = 100;
  int bucketSize = initialBucket;
  Node** hashTable = new Node*[bucketSize];

  for (int i = 0; i < bucketSize; i++) {
    hashTable[i] = NULL;
  }

  char input[10];
  bool running = true;

  // main code, running will stay true until user says "QUIT"
  while (running == true) {
    cout << "---------------------------------------------------------------" << endl;
    cout << "What Would You Like To Do? (ADD/GENERATE/PRINT/DELETE/QUIT/HELP)" << endl;

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
      
      int hashIndex = newStudent->get_id() % bucketSize;

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

      // rehash if any bucket has more than 3 students
      for (int i = 0; i < bucketSize; i++) {
        if (hashTable[i] != NULL) {
          Node* temp = hashTable[i];
          int count = 0;
          while (temp != NULL) {
            count++;
            temp = temp->getNext();
          }
          if (count > 3) {
            rehash(bucketSize, hashTable);
          }
        }
      }
    }
    else if (input[0] == 'G' || input[0] == 'g') { // generates random students
      int studentCount = 0;
      char* firstcpy = new char[20];
      char* lastcpy = new char[20];
      ifstream firstNames;
      firstNames.open("firstname.txt");

      char** fName = new char*[50];
      for (int i = 0; i < 50; i++) {
        if (firstNames.eof()) {
          break;
        }
        else {
          fName[i] = new char[20];
          firstNames >> firstcpy;
          strcpy(fName[i], firstcpy);
          studentCount++;
        }
      }
      fName[studentCount] = NULL;
      firstNames.close();

      ifstream lastNames;
      lastNames.open("lastname.txt");

      char** lName = new char*[studentCount];
      for (int i = 0; i < 50; i++) {
        if (lastNames.eof()) {
         break;
        }
        else {
          lName[i] = new char[20];
          lastNames >> lastcpy;
          strcpy(lName[i], lastcpy);
        }
      }
      lName[studentCount] = NULL;
      lastNames.close();

      int generateStudent = 0;
      cout << "How Many Students Would You Like To Generate? " << endl;
      cin >> generateStudent;
      cin.ignore();

      char firstName[20];
      char lastName[20];
      int studentID = 0;
      float gpa = 0.0;
      Student* newStudent = new Student(firstName, lastName, studentID, gpa);
      for (int i = 0; i < generateStudent; i++) {
        char firsttemp[20];
        char lasttemp[20];
        int randFirst = rand() % studentCount;
        int randLast = rand() % studentCount;
        strncpy(firsttemp, fName[randFirst], 20);
        strncpy(lasttemp, lName[randLast], 20);
        newStudent->set_first_name(firsttemp);
        newStudent->set_last_name(lasttemp);
        newStudent->set_id(rand() % 100000);
        newStudent->set_gpa((rand() % 500) / 100.0);

        Node* newNode = new Node(newStudent);
        int hashIndex = newStudent->get_id() % bucketSize;

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
        // rehash if any bucket has more than 3 students
        for (int i = 0; i < bucketSize; i++) {
          if (hashTable[i] != NULL) {
            Node* temp = hashTable[i];
            int count = 0;
            while (temp != NULL) {
              count++;
              temp = temp->getNext();
            }
            if (count > 3) {
              rehash(bucketSize, hashTable);
            }
          }
        }
      }
    }
    else if (input[1] == 'R' || input[1] == 'r') { // prints all students inputted
      for (int i = 0; i < bucketSize; i++) {
        if (hashTable[i] != NULL) {
          Node* temp = hashTable[i];
          while (temp != NULL) {
            cout << temp->getStudent()->get_first_name() << " " << temp->getStudent()->get_last_name() << ", " << temp->getStudent()->get_id() << ", " << temp->getStudent()->get_gpa() << endl;
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

      int hashIndex = studentID % bucketSize;

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
      cout << "Type \"ADD\" To Enter A New Student" << endl;
      cout << "Type \"PRINT\" To Print Out All Stored Students" << endl;
      cout << "Type \"DELETE\" To Delete A Student" << endl;
      cout << "Type \"QUIT\" To End Program" << endl;
    }
    else {
      cout << "Not Sure What You're Trying to Do" << endl;
    }
  }  
  return 0;
}
// when called, it will double the bucket size and rehash all students
void rehash(int &bucketSize, Node** &hashTable) {
  bucketSize = bucketSize * 2;
  Node** temp = new Node*[bucketSize];
  for (int i = 0; i < bucketSize; i++) {
    temp[i] = NULL;
  }
  for (int i = 0; i < bucketSize / 2; i++) {
    if (hashTable[i] != NULL) {
      Node* temp2 = hashTable[i];
      while (temp2 != NULL) {
        Node* newNode = new Node(temp2->getStudent());
        int hashIndex = temp2->getStudent()->get_id() % bucketSize;
        if (temp[hashIndex] == NULL) {
          temp[hashIndex] = newNode;
        }
        else if (temp[hashIndex] != NULL) {
          Node* temp3 = temp[hashIndex];
          while (temp3->getNext() != NULL) {
            temp3 = temp3->getNext();
          }
          temp3->setNext(newNode);
        }
        temp2 = temp2->getNext();
      }
    }
  }
  hashTable = temp;
}