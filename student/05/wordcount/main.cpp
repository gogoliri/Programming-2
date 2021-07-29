#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

vector<string> split(string sentence){
    vector<string> list_of_words;
    string word = "";
    for(auto cha : sentence){
        if(cha == ' '){
            list_of_words.push_back(word);
            word ="";
        }else{
            word.push_back(cha);
        }
    }
    list_of_words.push_back(word);
    return list_of_words;
}

int main()
{
    string filename = "";
    cout<<"Input file: ";
    getline(cin, filename);
    ifstream file_object(filename);
    if(not file_object){
        cout<<"Error! The file "
           <<filename << " cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    
    vector<string> lines;
    string line;
    while(getline(file_object, line)){
        lines.push_back(line);
    }
    
    file_object.close();
    
    
    map<string, set<int>> words_dictionary;
    for(size_t index_line = 0; index_line <lines.size(); index_line++){
        vector<string> list_words = split(lines.at(index_line));
        for(size_t index_word = 0; index_word < list_words.size(); index_word++){
            string word = list_words.at(index_word);
            
            if(words_dictionary.find(word)!= words_dictionary.end()){
                words_dictionary[word].insert(static_cast<int>(index_line) + 1);
            }else{
                words_dictionary.insert({word, {}});
                words_dictionary[word].insert(static_cast<int>(index_line)+1);
            }
        }
    }
    
    
    for(auto key_value : words_dictionary){
        string word = key_value.first;
        set<int> lines = key_value.second;
        
        cout<<word<<" "<<lines.size()<<": ";

        for(set<int>::iterator current_line = lines.begin();
            current_line != lines.end();
            current_line++){
            cout<<*current_line;
            if(current_line != --lines.end()){
                cout<<", ";
            }else{
                cout<<endl;
            }
        }
    }
        
        
    return EXIT_SUCCESS;
}
