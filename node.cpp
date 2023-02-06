//Written by Eric Chen
//Date: 1/6/2023
//This is the cpp file of the Node class

#include <iostream>
#include <cstring>

#ifndef STUDENT_H
#define STUDENT_H
#include "student.h"
#endif

#ifndef NODE_H
#define NODE_H
#include "node.h"
#endif

using namespace std;

Node::Node(Student* myStudent)
{
  //make a new student using the Student pointer provided
  this->myStudent = new Student(myStudent->get_first_name(), myStudent->get_last_name(), myStudent->get_id(), myStudent->get_gpa());

  //set the next pointer to NULL for now
  myNode = NULL;
}

Node::~Node()
{
  
}

Node* Node::getNext()
{
  //return a pointer to the next node
  return myNode;
}

Student* Node::getStudent()
{
  //return a pointer of the student stored
  return myStudent;
}

void Node::setNext(Node* myNode)
{
  //setting the next node pointer to the myNode pointer
  this->myNode = myNode;
}
