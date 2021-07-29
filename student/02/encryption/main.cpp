#include <iostream>
#include <string>
#include <cctype>

using namespace std;
string key;
string words;

bool check(string sentence){
    for(string::size_type i = 0; i<sentence.length();i++){
        if(sentence.at(i) < 'a' or sentence.at(i)>'z'){
            cout<<"Error! The encryption key must contain only lower case characters."<<endl;
            return false;
        }
    }
    return true;
}
int main()
{
    cout << "Enter the encryption key: ";
    cin>> key;
    if(key.length() != 26){
        cout<<"Error! The encryption key must contain 26 characters."<<endl;
        return EXIT_FAILURE;
    }
    if (check(key) == false){
        return EXIT_FAILURE;
    }
    for(char ch = 'a';ch<='z';ch++){
        if(key.find(ch)==string::npos){
            cout<<"Error! The encryption key must contain all alphabets a-z."<<endl;
            return EXIT_FAILURE;
        }
    }


    cout<<"Enter the text to be encrypted: ";
    cin>>words;
    if(check(words)==false){
        return EXIT_FAILURE;
    }
    cout<<"Encrypted text: ";
    for(string::size_type i = 0;i<words.length();i++){
        char current_char = words.at(i);
        string::size_type index = static_cast<string::size_type>(current_char - 'a');
        char new_char = key.at(index);
        cout<<new_char;
    }
    cout<<endl;
    return EXIT_SUCCESS;
}
