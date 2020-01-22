#include <iostream>
#include <string>

using namespace std;

int main()
{
    string upperBoundStr = "";
    cout << "Enter an upper bound: ";
    getline(cin, upperBoundStr);
    int upperBoundInt = 0;
    upperBoundInt = stoi(upperBoundStr);

    bool isPrime[upperBoundInt];

    cout << "Prime numbers smaller than " << upperBoundStr << ": " << endl;
    for (int i = 0; i < upperBoundInt; ++i)
    {
      isPrime[i] = true;
      if (i == 0 || i == 1)
      {
        isPrime[i] = false;
      }
      else
      {
        for (int j = 2; j <= i; ++j)
        {
          if (i % j == 0 && j != i)
          {
            isPrime[i] = false;
          }
        }
      }
    }

    for (int i = 0; i < upperBoundInt; ++i)
    {
      if (isPrime[i])
      {
        if (not (i == upperBoundInt - 1))
          cout << i << " ";
        else
          cout << i << endl;
      }
    }

    return EXIT_SUCCESS;
}
