#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string inputfilename = "";
    cout << "Input file: ";
    getline(cin, inputfilename);
    string outputfilename = "";
    cout << "Output file: ";
    getline(cin, outputfilename);

    ifstream inputfile(inputfilename );
    vector<string> output;

    if (not inputfile)
    {
      cout << "Error! The file " << inputfilename << " cannot be opened." << endl;
      return EXIT_FAILURE;
    }
    else
    {
      string row_input = "";
      string row_output = "";
      int rownumber = 1;
      while (getline(inputfile, row_input))
      {
        row_output += to_string(rownumber) + " ";
        row_output += row_input;
        rownumber += 1;
        output.push_back(row_output);
        row_output = "";
      }
      inputfile.close();

      ofstream outputfile(outputfilename);

      for (string row:output)
      {
        outputfile << row << endl;
      }
    }
}
