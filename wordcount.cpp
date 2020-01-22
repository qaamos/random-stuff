#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector< std::string > split(std::string input, char separator, bool skip_empty = false)
{
  vector< string > output;
  string word = "";
  for (char character:input)
  {
    if (character == separator)
    {
      if (skip_empty == true && word == "")
      {
        ;
      }
      else
      {
        output.push_back(word);
      }
      word = "";
    }
    else
    {
    word += character;
    }
  }
  if (skip_empty == true && word == "")
  {
    ;
  }
  else
  {
    output.push_back(word);
  }
  return output;
}

int main()
{
    // Words are stored in a map containing name strings as keys, and
    // sets containing row numbers as values
    map<string, set<int>> words;
    cout << "Input file: ";
    string filename = "";
    cin >> filename;

    ifstream file(filename);
    if (not file)
    {
      cout << "Error! The file " << filename << " cannot be opened." << endl;
      return EXIT_FAILURE;
    }
    else
    {
      string row = "";
      string word = "";
      //string::iterator iter;
      int i = 1;
      //int wordbegin = 0;
      //int wordend = 0;
      while (getline(file, row))
      {
        //iter = row.begin();
        //wordend = 0;
        /*
        while (iter != row.end())
        {
        if (*iter == ' ')
        {
          string to_iter = "";
          to_iter = row.substr(0,wordend);
          word = to_iter.substr(to_iter.rfind(" "), to_iter.size());
          if (words.find(word) != words.end())
          {
            set<int>& rownumbers = words.at(word);
            rownumbers.insert(i);
          }
          else
          {
            set<int> rows;
            rows.insert(i);
            words.insert( { word, rows } );
          }
        }
        ++iter;
        wordend += 1;
        */

        /*
        for ( auto character : row )
        {
          if ( character == ' ' || iter == row.end())
          {
            word = row.substr(wordbegin, wordend);

            if (words.find(word) != words.end())
            {
              set<int>& rownumbers = words.at(word);
              rownumbers.insert(i);
            }
            else
            {
              set<int> rows;
              rows.insert(i);
              words.insert( { word, rows } );
            }
          }
          wordend += 1;
          ++iter;
        }
        */

        vector<string> wordlist;
        wordlist = split(row, ' ');
        for ( string word : wordlist )
        {
          if (words.find(word) != words.end())
          {
            set<int>& rownumbers = words.at(word);
            rownumbers.insert(i);
          }
          else
          {
            set<int> rows;
            rows.insert(i);
            words.insert( { word, rows } );
          }
        }
        i += 1;
        }


      for (auto word : words)
      {
        cout << word.first << " " << word.second.size() << ": ";
        set<int>::iterator iter;
        iter = word.second.begin();
        for ( int number : word.second )
        {
          ++iter;
          if ( iter == word.second.end())
          {
            cout << to_string(number);
          }
          else
          {
            cout << to_string(number) << ", ";
          }
        }
        cout << endl;
      }
      }
    file.close();
    }
