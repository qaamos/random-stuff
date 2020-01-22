#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

struct Book
{
    string title;
    string author;
    int reservations;
};

/*
Splits string into multiples strings stored in vector.

s: string to be processed
delimiter: character separating the substrings
ignore_empty: indicates if empty substrings should be skipped
*/
vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

/*
   Reads data from input csv file into map.

   filename: name of the file to be read
   return: map containing library data, or empty map if reading fails
*/
map<string, vector<Book>> read_file(string filename)
{
    map<string, vector<Book>> libraries;

    ifstream file(filename);
    if (not file)
        cout << "Error: the input file cannot be opened" << endl;
    else
    {
        string row = "";
        while (getline(file, row))
        {
            vector<string> splitrow;
            splitrow = split(row, ';');

            // check for incorrect formatting
            if (splitrow.size() != 4)
            {
                cout << "Error: empty field" << endl;
                map<string, vector<Book>> empty;
                return empty;
            }
            string library = "";
            string author = "";
            string title = "";
            string reservations_str = "";
            int reservations_int = 0;
            library = splitrow.at(0);
            author = splitrow.at(1);
            title = splitrow.at(2);
            reservations_str = splitrow.at(3);

            // check for incorrect values
            if (library == "" || author == "" || title == "" || reservations_str == "")
            {
                cout << "Error: empty field" << endl;
                map<string, vector<Book>> empty;
                return empty;
            }

            if (reservations_str != "on-the-shelf")
                reservations_int = stoi(reservations_str);

            // check for incorrect reservations
            if (reservations_str != "on-the-shelf" && not stoi(reservations_str))
            {
                cout << "Error: empty field" << endl;
                map<string, vector<Book>> empty;
                return empty;
            }

            // if library doesn't exist, creates one
            if (libraries.find(library) == libraries.end())
            {
                vector<Book> librarybooks;
                libraries.insert({library, librarybooks});
            }

            Book kirja;
            kirja.title = title;
            kirja.author = author;
            if (reservations_str != "on-the-shelf")
                kirja.reservations = reservations_int;
            else
                kirja.reservations = 0;

            // Check if book already exists in library. If yes, update book data. If no, add new book.
            bool bookExists = false;
            for (Book tmp : libraries.at(library))
            {
                if (tmp.title == kirja.title)
                    bookExists = true;
            }
            if (bookExists)
            {
                for (Book& tmp : libraries.at(library))
                {
                    if (tmp.title == kirja.title)
                    {
                        tmp.author = kirja.author;
                        tmp.reservations = kirja.reservations;
                    }
                }
            }
            else
                libraries.at(library).push_back(kirja);

        }
    }
    file.close();

    return libraries;
}

/*
This helper function is used for sorting book titles by alphabetical order
in command books.
*/
bool sort_title(Book i, Book j)
{
  return i.title < j.title;
}

/*
This helper function is used for sorting book authors by alphabetical order
in command loanable.
*/
bool sort_author(Book i, Book j)
{
  return i.author < j.author;
}

/*
This helper function is used for sorting strings alphabetically
in command reservable.
*/
bool sort_string(string i, string j)
{
  return i < j;
}

/*
Implements command libraries.

libraries: data structure containing libraries and books
*/
void libraries_command(map<string, vector<Book>> libraries)
{
  for (auto library : libraries)
  {
    cout << library.first << endl;
  }
}

/*
Implements command material.

libraries: data structure containing libraries and books
parts: vector containing user input split into strings
*/
void material_command(map<string, vector<Book>> libraries, vector<string> parts)
{
    string libraryname = "";
    libraryname = parts.at(1);
    if (libraries.find(libraryname) == libraries.end())
    {
      cout << "Error: unknown library name" << endl;
    }
    else
    {
      for (auto library : libraries)
      {
        if (library.first == libraryname)
        {
          vector<Book> librarybooks = library.second;
          sort(librarybooks.begin(), librarybooks.end(), sort_author);
          for (Book kirja : librarybooks)
          {
            cout << kirja.author << ": " << kirja.title << endl;
          }
        }
      }
    }
}

/*
Implements command books.

libraries: data structure containing libraries and books
parts: vector containing user input split into strings
*/
void books_command(map<string, vector<Book>> libraries, vector<string> parts)
{

  string libraryname = "";
  string authorname = "";
  libraryname = parts.at(1);
  authorname = parts.at(2);

  // checks if requested author exists in libraries
  bool unknownAuthor = true;
  for (auto library : libraries)
  {
    for (Book kirja : library.second)
    {
      if (kirja.author == authorname)
        unknownAuthor = false;
    }
  }

  if (libraries.find(libraryname) == libraries.end())
    cout << "Error: unknown library name" << endl;
  else if (unknownAuthor)
    cout << "Error: unknown author" << endl;

  else
  {
    for (auto library : libraries)
    {
      if (library.first == libraryname)
      {
        vector<Book> booklist = library.second;
        sort(booklist.begin(), booklist.end(), sort_title);
        for (Book kirja : booklist)
        {
          if (kirja.author == authorname)
          {
            if (kirja.reservations != 0)
              cout << kirja.title << " --- " << kirja.reservations << " reservations" <<endl;
            else
              cout << kirja.title << " --- " << "on the shelf" <<endl;
          }
        }
      }
    }
  }

}

/*
Implements command reservable.

libraries: data structure containing libraries and books
parts: vector containing user input split into strings
*/
void reservable_command(map<string, vector<Book>> libraries, vector<string> parts)
{

  string title = "";

  // removes command from parts; only book title is left
  parts.erase(parts.begin());

  // puts together book title
  for (string word : parts)
  {
    if (title == "")
      title += word;
    else
      title += " " + word;
  }

  // removes quotation marks from title
  for (char c : title)
  {
    if (c == '"')
      title.erase(title.find(c), 1);
  }

  bool book_exists = false;
  int reservations = 999;
  // names of libraries in which book is reservable
  vector<string> reservable_libraries;

  for (auto library : libraries)
  {
    for (Book kirja : library.second)
    {
      if ( (kirja.title == title) && (kirja.reservations <= reservations) )
      {
          book_exists = true;
          // clears list of libraries if new library with less
          // reservations is found
          if (kirja.reservations < reservations)
          {
            vector<string> empty;
            reservable_libraries = empty;
          }
          if (find(reservable_libraries.begin(), reservable_libraries.end(), library.first) == reservable_libraries.end())
            reservable_libraries.push_back(library.first);
          reservations = kirja.reservations;
      }
    }
  }
  if (reservations < 100)
  {
    if (reservations != 0)
      cout << reservations << " reservations" << endl;
    else
      cout << "on the shelf" << endl;
    sort(reservable_libraries.begin(), reservable_libraries.end(), sort_string);
    for (string library_name : reservable_libraries)
    {
      cout << "--- " << library_name << endl;
    }
  }
  else if (not book_exists)
    cout << "Book is not a library book." << endl;
  else
    cout << "The book is not reservable from any library." << endl;

}

/*
Implements command loanable.

libraries: data structure containing libraries and books
*/
void loanable_command(map<string, vector<Book>> libraries)
{

  vector<Book> all_loanables;
  for (auto library : libraries)
  {
      vector<Book> booklist = library.second;
      for (Book kirja : booklist)
      {
        if (kirja.reservations == 0)
        {

          //checks if book already exists in all_loanables
          bool book_exists = false;
          for (Book livre : all_loanables)
          {
            if (livre.title == kirja.title)
              book_exists = true;
          }

          if (not book_exists)
            all_loanables.push_back(kirja);
        }
      }
  }
  sort(all_loanables.begin(), all_loanables.end(), sort_title);
  sort(all_loanables.begin(), all_loanables.end(), sort_author);
  for (Book kirja : all_loanables)
  {
    cout << kirja.author << ": " << kirja.title << endl;
  }

}

int main()
{

    // data is stored in a map, containing library names as keys and Books stored in vectors as values
    map<string, vector<Book>> libraries;

    string filename = "";
    cout << "Input file: ";
    getline(cin, filename);
    libraries = read_file(filename);
    if (libraries.size() == 0)
        return EXIT_FAILURE;
    else
    {

        while (true)
        {
            string line;
            string command;
            cout << "> ";
            getline(cin, line);
            vector<string> parts = split(line, ' ', true);
            command = parts.at(0);

            if (command == "quit")
              return EXIT_SUCCESS;

            // prints out names of all libraries
            else if (command == "libraries")
              libraries_command(libraries);

            // prints out titles of all books in requested library
            else if (command == "material")
            {
              if (parts.size() != 2)
              {
                cout << "Error: error in command " << command << endl;
              }
              else
                material_command(libraries, parts);
            }

            // prints out titles of all books by requested author in requested library,
            // in alphabetic order
            else if (command == "books")
            {
              if (parts.size() != 3)
                cout << "Error: error in command " << command << endl;
              else
                books_command(libraries, parts);
            }

            // prints smallest amount of reservations for requested book
            // and names of libraries to which the above applies
            else if (command == "reservable")
            {
              if (parts.size() < 2)
                cout << "Error: error in command " << command << endl;
              else
              {
                reservable_command(libraries, parts);
              }

            }

            // prints list of all books marked as "on-the-shelf", in all libraries
            else if (command == "loanable")
              loanable_command(libraries);

            else
              cout << "Error: Unknown command: " << command << endl;
        }

    }

}
