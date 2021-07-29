#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string filename_input = "";
    cout << "Input file: ";
    getline(cin, filename_input);
    
    string filename_output = "";
    cout<< "Output file: ";
    getline(cin, filename_output);
    
    vector<string> lines;

    ifstream file_object(filename_input);
    if(not file_object){
        cout<<"Error! The file "<< filename_input
           <<" cannot be opened."<<endl;
        return EXIT_FAILURE;
    }else{
        string line;
        while (getline(file_object,line)){
                lines.push_back(line);
    }
    }
    file_object.close();

    ofstream file_output;


    vector<string>::size_type length = lines.size();
    file_output.open(filename_output);
    for(vector<string>::size_type i = 0; i<length;i++){
        file_output<<i+1<<" "<<lines.at(i)<<endl;
    }
    file_output.close();
    return 0;
}
