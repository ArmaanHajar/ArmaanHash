/*
 * Author: Armaan Hajar
 * Program: Student.cpp file
 * Date: 1/29/2023
 */
#include <iostream>
#include "student.h"
#include <cstring>

using namespace std;

Student::Student(char* firstName, char* lastName, int studentID, float gpa) {
  strncpy(this->firstName, firstName, 19);
  strncpy(this->lastName, lastName, 19);
  this->studentID = studentID;
  this->gpa = gpa;
}

void Student::set_first_name(char* firstNameTemp) {
  strcpy(firstName, firstNameTemp);
}

void Student::set_last_name(char* lastNameTemp) {
  strcpy(lastName, lastNameTemp);
}

void Student::set_id(int studentIDTemp) {
  studentID = studentIDTemp;
}

void Student::set_gpa(float gpatemp) {
  gpa = gpatemp;
}

char* Student::get_first_name() {
  return firstName;
}

char* Student::get_last_name() {
  return lastName;
}

int Student::get_id() {
  return studentID;
}

float Student::get_gpa() {
  return gpa;
}
