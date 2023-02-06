/*
 * Author: Armaan Hajar
 * Program:
 * Date:
 */

#include <iostream>
#include <cstring>

using namespace std;

void help();

int main() {
  char input[10];
  bool running = true;

  // main code, running will stay true until user says "QUIT"
  while (running == true) {
    cout << "---------------------------------------------------------------" << endl;
    cout << "What Would You Like To Do? (ADD/PRINT/DELETE/QUIT/HELP)" << endl;

    cin.get(input, 10);
    cin.ignore(1, '\n');

    if (input[1] == 'D' || input[1] == 'd') { // adds student
      
    }
    else if (input[1] == 'R' || input[1] == 'r') { // prints all students inputted
      
    }
    else if (input[2] == 'L' || input[2] == 'l') { // deletes a student
      
    }
    else if (input[0] == 'Q' || input[0] == 'q') { // ends program
      
    }
    else if (input[0] == 'H' || input[0] == 'h') { // prints help message
      
    }
    else {
      cout << "Not Sure What You're Trying To Do" << endl;
    }
  }  
  return 0;
}

void help() {
  cout << "Type \"ADD\" To Enter A New Student" << endl;
  cout << "Type \"PRINT\" To Print Out All Stored Students" << endl;
  cout << "Type \"DELETE\" To Delete A Student" << endl;
  cout << "Type \"QUIT\" To End Program" << endl;
}
