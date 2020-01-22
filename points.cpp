#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string filename = "";
    cout << "Input file: ";
    cin >> filename;

    ifstream file(filename);
    if (not file)
    {
      cout << "Error! The file " << filename << " cannot be opened." << endl;
      return EXIT_FAILURE;
    }
    else
    {
      map<string, int> points;
      map<string, int>::iterator iter;
      string row = "";
      while (getline(file, row))
      {
        string name ="";
        int number = 0;
        name = row.substr(0,row.find(":"));
        number = stoi(row.substr(row.find(":")+1, row.size()));
        iter = points.find(name);
        if (iter != points.end())
        {
          points.at(name) += number;
        }
        else
        {
          points.insert( { name, number } );
        }
      }

      cout << "Final scores:" << endl;
      for (auto person : points )
      {
        cout << person.first << ": " << person.second << endl;
      }

    }
}
