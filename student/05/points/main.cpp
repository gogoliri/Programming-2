#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string>split(string line, char seperator = ':'){
    vector<string> name_and_score;
    string::iterator iter;

    iter = find(line.begin(), line.end(),seperator);



    string name;
    copy(line.begin(), iter,name.begin());
    for(string::iterator index = line.begin();index < iter;index++){
        name.push_back(*index);
    }


    string score;
    iter++;
    for(string::iterator index = iter;index < line.end();index++){
        score.push_back(*index);
    }

    name_and_score.push_back(name);
    name_and_score.push_back(score);
    return name_and_score;
}

int main()
{
    map<string, int> results;

    string filename = "";
    cout<<"Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
    if(not file_object){
        cout<<"Error! The file "
           <<filename << " cannot be opened."<<endl;
        return EXIT_FAILURE;
    }else{
        cout<<"Final scores:"<<endl;
        string line;
        while(getline(file_object,line)){
            string name;
            string score;
            int score_int;

            vector<string> name_score = split(line);
            name = name_score[0];
            score = name_score[1];
            score_int = stoi(score);
            if(results.find(name) == results.end()){
                results.insert({name, score_int});
            }else{
                results.at(name) += score_int;
            }
        }
        file_object.close();
    }
    for(map<string, int>::iterator i = results.begin();i != results.end();i++){
        cout<<i->first << ": "<<i->second<<endl;
    }
    return EXIT_SUCCESS;
}
