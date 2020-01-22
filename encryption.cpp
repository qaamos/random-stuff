#include <iostream>
#include <cctype>

using namespace std;

string encrypt ( string key, string text ) {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  int i = 0;
  for ( char& c : text ) {
    string to_replace = "";
    to_replace = key.at(alphabet.find(c));
    text.replace(i, 1, to_replace);
    i++;
  }

  return text;
}

int main() {
  cout << "Enter the encryption key: ";
  string key = "";
  cin >> key;

  if ( key.length() != 26 ) {
    cout << "Error! The encryption key must contain 26 characters." << endl;
    return EXIT_FAILURE;
  }

  for ( char& c : key ) {
    int ascii = static_cast< int >(c);
    if ( 97 > ascii || ascii > 122 ) {
      cout << "Error! The encryption key must contain only lower case characters."
      << endl;
      return EXIT_FAILURE;
    }
  }

  for ( char i = 'a'; i < 'z' ; ++i ) {
    if ( key.find(i) == string::npos ) {
      cout << "Error! The encryption key must contain all alphabets a-z." << endl;
      return EXIT_FAILURE;
    }
  }

  cout << "Enter the text to be encrypted: ";
  string text = "";
  cin >> text;

  string encrypted = "";
  encrypted = encrypt(key, text);

  cout << "Encrypted text: " << encrypted << endl;

}
