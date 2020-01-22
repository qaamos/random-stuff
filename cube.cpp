
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  cout << "Enter a number: ";
  int number = 0;
  cin >> number;
  int cube = 0;
  cube = number * number * number;
  if ( number == 0 ) {
    cout << "The cube of 0 is 0." << endl;
  }
  else if ( cube/(number*number) == number ) {
    cout << "The cube of " << number << " is " << cube << "." << endl;
  }
  else {
    cout << "Error! The cube of " << number << " is not " << cube << endl;
  }
}
