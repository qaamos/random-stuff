#include <iostream>

using namespace std;

// calculates factorial of param n
unsigned long int calculate_factorial( unsigned long int n ) {
  unsigned long int factorial = 1;

  if ( n == 0 ) {
    factorial = 1;
  }
  else {
    for ( unsigned long int i = 1; i <= n; ++i ) {
      factorial *= i;
    }
  }
  return factorial;
}

// calculates probability of n balls drawn from total of p balls
unsigned long int calculate_probability( unsigned long int n, unsigned long int p ) {
  unsigned long int probability = 1;
  probability = calculate_factorial(n) / ( calculate_factorial(n - p) * calculate_factorial(p) );
  return probability;
}

int main() {
  cout << "Enter the total number of lottery balls: ";
  long int n = 1;
  cin >> n;
  cout << "Enter the number of drawn balls: ";
  long int p = 1;
  cin >> p;

  if ( p <= 0 or n <= 0 ) {
    cout << "The number of balls must be a positive number." << endl;
  }

  else if (  p > n ) {
    cout << "The maximum number of drawn balls is the total amount of balls." << endl;
  }

  else {
  unsigned long int probability = 1;
  probability = calculate_probability(n, p);
  cout << "The probability of guessing all " << p << " balls correctly is 1/"
  << probability << endl;
  }
}
