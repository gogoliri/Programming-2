
/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Desc:
* This program asks for the data input which is a system of train stations.
* The program then read the input into a data structure and ask user for their commands.
* The commands can be upper or lower letters. The programs check if the file can be open
* or the file's format is correct.
* Then, the user input command and its required arguments. If there is too few
* argument, the error is announces. If it is too much arguments, the extra arguments are ignore
* There are 9 commands in total and each has it own required arguments.
* QUIT: exit the program
* LINES: print all the lines in the system
* LINE: print all the stops in the line
* STOPS: print all the stops in the system
* STOP: print all the line that goes through stop
* DISTANCE: distance between 2 stops
* ADDLINE: add a new line to the system
* ADDSTOP: add a new stop to a line
* REMOVE: remove the stop from all its lines
* When add line or add stop, the program check if stop/line already exist
* When use line, stop, remove, distance commands, the program check if
* line/stop can be found in the system.
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <set>

using namespace std;

// Choose data struture
using System = map<string,map<double,string>>;

// constant for text
const string STOP_LINE_EXIST = "Error: Stop/line already exists.";
const string LINE_NOT_FOUND = "Error: Line could not be found.";
const string STOP_NOT_FOUND = "Error: Stop could not be found.";
const string INVALID_INPUT = "Error: Invalid input.";
const string FILE_COULD_NOT_BE_READ = "Error: File could not be read.";
const string FILE_FORMAT_INVALID = "Error: Invalid format in file.";

// constant number
const double INITIAL_FIND_KEY = -1;
const unsigned int EMPTY = 0;

// constant of data file fields
const size_t MIN_DATA_FILE_FIELDS = 2;
const size_t MAX_DATA_FILE_FIELDS = 3;
const size_t INDEX_DISTANCE_DATA_FILE_FIELDS = 2;
const char DELIMITER_DATA_FILE = ';';
const size_t INDEX_LINE_DATA_FILE_FIELDS = 0;
const size_t INDEX_STOP_DATA_FILE_FIELDS = 1;

// delimiter for read_input function
const char DELIMITER_QUOTES_CASE = '"';
const char DELIMITER_SPACE_CASE = ' ';

// constant LINE
const size_t ARGUMENT_CMD_LINE = 1;
const size_t LINE_IN_CMD_LINE = 1;
// constant for ADDLINE
const size_t ARGUMENT_CMD_ADDLINE = 1;
const size_t LINE_IN_CMD_ADDLINE = 1;
// constant for command ADDSTOP
const size_t ARGUMENT_CMD_ADDSTOP = 3;
const size_t LINE_IN_CMD_ADDSTOP = 1;
const size_t STOP_IN_CMD_ADDSTOP = 2;
const size_t DISTANCE_IN_CMD_ADDSTOP = 3;
// constant for command STOP
const size_t ARGUMENT_CMD_STOP = 1;
const size_t STOP_IN_CMD_STOP = 1;
// constant for command REMOVE
const size_t ARGUMENT_CMD_REMOVE = 1;
const size_t STOP_IN_CMD_REMOVE = 1;
// constant for command DISTANCE
const size_t ARGUMENT_CMD_DISTANCE = 3;
const size_t LINE_IN_CMD_DISTANCE = 1;
const size_t STOP_1_IN_CMD_DISTANCE = 2;
const size_t STOP_2_IN_CMD_DISTANCE = 3;

// constant for user interface
const size_t INDEX_CMD_IN_USER_INPUT = 0;

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// FUNCTIONS TO HANDLE GENERAL MATTER
// Print items in a set
void print(const set<string>& list, const string& prefix=""){
    for(const auto& item: list){
        cout<<prefix<<item<<endl;
    }
}

// Find a key based on provide value in a map
double find_key(const map<double, string>& the_list,string the_value){
    // Initial value to make sure key not in the list
    double the_key = INITIAL_FIND_KEY;

    for(const auto& item: the_list){
        if(item.second == the_value){
            the_key = item.first;
        }
    }
    return the_key;
}

// Split the content into parts based on delimiter
// Return the vector of splitteed words
vector<string> split(const string& content,
                     const char& delimiter,
                     const bool& ignore_empty = false){
    // Create a vector to contant word.
    vector<string> result={};

    // Since we need to change the content after detaching delimiter
    // we need to make a temporary copy of the command
    string temporary = content;

    // Find the delimiter and do the procedure.
    while(temporary.find(delimiter) != string::npos)
    {
        // Define a new part to be added to the result
        string new_part = temporary.substr(0, temporary.find(delimiter));
        temporary = temporary.substr(temporary.find(delimiter)+1, temporary.size());

        // Add new part to result
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }

    // Heuristic way to handle the case when there is no delimiter in content
    // (delimiter were removed completely or content originally don't have delimiter)
    if(not(ignore_empty and temporary.empty())){
        result.push_back(temporary);
    }
    return result;
}

// Change lower case letters to upper case letters
void change_to_upper(string& content){
    // Initialize value
    string converted_content="";
    char character=' ';

    for(size_t index = 0; index < content.size(); index++){
        character = toupper(content[index]);
        content.at(index) = character;
    }
}

// Function convert string to double
double string_to_double(const string& distance){
    double distance_converted = static_cast<double>(stod(distance));
    return distance_converted;
}


// FUNCTION TO SUPPORT TASKS RELATED TO THE PROJECT

// Check if line already exists in the system or not
bool is_line_exist(const System& system, const string& line){
    return system.count(line) != EMPTY;
}

// Function check if line could be found in the system.
// Print an error line if not found
// This function is relatively similar to is_line_exist
// except it print an error line, so we can use 2 functions suitably
// according to the situation
bool is_line_found(const System& system, const string& line){
    if(!is_line_exist(system, line)){
        cout<<LINE_NOT_FOUND<<endl;
        return false;
    }
    return true;
}

// Check if the file's format is correct
bool is_valid(const System& system, const vector<string>& fields){
    // Check if there is too much or too few arguments
    if(fields.size()<MIN_DATA_FILE_FIELDS
            or fields.size()>MAX_DATA_FILE_FIELDS){
        return false;
    }
    for (size_t i = 0; i<fields.size();i++){
        string field = fields.at(i);

        // Mark when we process the distance field
        bool is_distance = i == INDEX_DISTANCE_DATA_FILE_FIELDS;
        string line = fields.at(0);

        // Only the distance field can be left emptied
        // If it is not the distance fields and it is empty
        // return false
        // or if line does not exist, return false also
        if(field == "" and (!is_distance or is_line_exist(system,line))){
            return false;
        }
    }
    return true;
}

// Read user input for commands and their argument
vector<string> read_input(const string& user_input){
    vector<string> first_split = {};
    vector<string> second_split = {};

    // If there are quotes in the input
    if(user_input.find(DELIMITER_QUOTES_CASE) != string::npos){
        // Split the first time, to eliminate the case of quotes
        // (two-word name for example)
        first_split = split(user_input, DELIMITER_QUOTES_CASE,true);

        // we go through the result of first split
        // to do the second split
        for(auto& word: first_split){
            // If, after the split, the word has a space
            // in the begin or end position => it is not the name originally in quotes
            // we split it to smaller parts
            size_t n = word.size();
            if(word.at(0)==DELIMITER_SPACE_CASE
                    or word.at(n-1)==DELIMITER_SPACE_CASE){
                vector<string> temporal = split(word,DELIMITER_SPACE_CASE,true);
                for(auto& word_temporal: temporal){
                    second_split.push_back(word_temporal);
                }
            }else{
                // If this is the name in quotes, just add it to the vector
                second_split.push_back(word);
            }
        }
    }else{
        // If there is no quote, just do normal split
        second_split = split(user_input,DELIMITER_SPACE_CASE);
    }
    return second_split;
}

// Check if a stop exists in a line
bool is_stop_exist(System& system,
                   const string& line,
                   const double& distance,
                   const string& stop){
    // Check if the distance in the line are already occupied
    if(system[line].count(distance) !=0 ){
        return false;
    }

    // Check if the name of the stop exists
    for(const auto& distance_stop_pair: system[line]){
        if(distance_stop_pair.second == stop ){
            return false;
        }
    }
    return true;
}

// Add a line to the system
bool add_line(System& system, const string& line){
    // Check if line exists already
    if(is_line_exist(system,line)){
        cout<<STOP_LINE_EXIST<<endl;
        return false;
    }

    system[line] = {};
    return true;
}

// Add a stop to the system
bool add_stop(System& system,
              const string& line,
              const double& distance,
              const string& stop){
    // Is the mentioned line exists
    // if not, return false
    if(!is_line_found(system,line)){
        return false;
    }

    // Is the stop exist already
    // if yes, return false
    if(!is_stop_exist(system, line, distance, stop)){
        cout<<STOP_LINE_EXIST<<endl;
        return false;
    }else{
        system[line][distance] = stop;
    }
    return true;
}

// Return list of lines that go through a given stop
set<string> list_lines(const System& system, const string& stop){
    set<string> line_list = {};

    // Check line by line to find the stop
    for(const auto& line:system){
        for(const auto& distance_stop_pair: line.second){
            string stop_to_be_checked = distance_stop_pair.second;

            // if the line goes through the stop, add it to list
            if(stop == stop_to_be_checked){
                line_list.insert(line.first);
            }
        }
    }
    return line_list;
}

// Check if a stop exists in the system
// The previous is_stop_exist check if a stop exists in a line
bool is_stop_found(const System& system, const string& stop){
    set<string> line_list = list_lines(system, stop);

    // If line_list is empty, return error
    if(line_list.size() == 0){
        cout<<STOP_NOT_FOUND<<endl;
        return false;
    }
    return true;
}

// Check if user provides enough argument for each command
// If not, return error
bool is_enough_argument(const vector<string> cmd_fields, const size_t required){
    if(cmd_fields.size()<=required){
        cout<<INVALID_INPUT<<endl;
        return false;
    }
    return true;
}


// FUNCTIONS TO HANDLE FILE'S INPUT

// Read the file input to a vector<string>
// annouce an error if file could not be opened
bool read_file(const string& filename, vector<string>& data_from_file){
    ifstream file_object(filename);
    if(not file_object){
        cout<<FILE_COULD_NOT_BE_READ<<endl;
        return false;
    }else{
        string data="";
        while(getline(file_object,data)){
            data_from_file.push_back(data);
        }
        file_object.close();
    }
    return true;
}

// Read the data into data struture
bool process_data(System& system, const vector<string>& data_from_file){
    // Divide data into vector fields with order: line, stop, distance
    for(const auto& data: data_from_file){
        vector<string> fields = split(data, DELIMITER_DATA_FILE);
        if(!is_valid(system, fields)){
            cout<< FILE_FORMAT_INVALID<<endl;
            return false;
        }

        // Name the fields accordingly for clarification purpose
        string line = fields.at(INDEX_LINE_DATA_FILE_FIELDS);
        string stop = fields.at(INDEX_STOP_DATA_FILE_FIELDS);
        double distance = 0.0;
        if(fields.size()==MAX_DATA_FILE_FIELDS
                and fields.at(INDEX_DISTANCE_DATA_FILE_FIELDS) != ""){
            distance = string_to_double(
                        fields.at(INDEX_DISTANCE_DATA_FILE_FIELDS));
        }

        // If line is not in system, add line
        if(!is_line_exist(system, line)){
            add_line(system, line);
        }

        // Add stop to the system
        if(!add_stop(system, line, distance, stop)){
            return false;
        }
    }
    return true;
}


// FUNCTION TO HANDLE USER'S COMMANDS

// Execute the command lines
// List all the lines
void cmd_lines(const System& system){
    cout<<"All tramlines in alphabetical order:" << endl;
    for(const auto& line : system){
        cout<<line.first<<endl;
    }
}

// Execute the command line
// Print all the stops in a line
void cmd_line(const System& system,
              const vector<string>& cmd_fields){
    // Check if enough argument provided
    if(is_enough_argument(cmd_fields, ARGUMENT_CMD_LINE)){
        string line = cmd_fields.at(LINE_IN_CMD_LINE);

        // Check if line is in the system
        if(is_line_found(system, line)){
            cout<<"Line "
               <<line
              <<" goes through these stops in the order they are listed:"
             <<endl;

            // Print stop by stop
            for(const auto& distance_stop_pair : system.at(line)){
                cout<<" - "<<distance_stop_pair.second<<" : "<<distance_stop_pair.first<<endl;
            }
        }
    }
}

// Execute the command addline
// add a line to the system
void cmd_addline(System& system,
                 const vector<string> cmd_fields){
    // Check if enough argument provided
    if(is_enough_argument(cmd_fields,ARGUMENT_CMD_ADDLINE)){
        string line = cmd_fields.at(LINE_IN_CMD_ADDLINE);

        //Add line, check was done already in the add_line function
        if(add_line(system, line)){
            cout<<"Line was added."<<endl;
        }
    }
}

// Execute the command addstop
// add a stop to the system
void cmd_addstop(System& system,
                 const vector<string> cmd_fields){
    // Check if enough argument provided
    if(is_enough_argument(cmd_fields, ARGUMENT_CMD_ADDSTOP)){
        // Name the fields accordingly for clarification purpose
        string line = cmd_fields.at(LINE_IN_CMD_ADDSTOP);
        string stop = cmd_fields.at(STOP_IN_CMD_ADDSTOP);
        double  distance = string_to_double(cmd_fields.at(DISTANCE_IN_CMD_ADDSTOP));

        // Add stop, check was done already in add_stop function
        if(add_stop(system,line, distance, stop)){
            cout<<"Stop was added."<<endl;
        }
    }
}

// Execute the command stops
// List all the stops
void cmd_stops(const System& system){
    set<string> stops_list={};
    // Goes through line by line and add stops to a set
    // This will make the print in alphabetical oder
    for(const auto& line : system){
        for(const auto& pair : line.second){
            string stop = pair.second;
            stops_list.insert(stop);
        }
    }
    cout<<"All stops in alphabetical order:"<<endl;
    print(stops_list);
}

// Execute the command stop
// Print all the lines that go through a stop
void cmd_stop(const System& system,
              vector<string> cmd_fields){
    // Check if enough argument provided
    if(is_enough_argument(cmd_fields, ARGUMENT_CMD_STOP)){
        string stop = cmd_fields.at(STOP_IN_CMD_STOP);

        // Check if stop is in the system
        if(is_stop_found(system,stop)){
            set<string> line_list = list_lines(system,stop);
            cout<<"Stop "<<stop<<" can be found on the following lines:"<<endl;
            print(line_list," - ");
        }
    }
}

// Execute the remove command
// Remove the stop from all lines
void cmd_remove(System& system, vector<string> cmd_fields){
    // Check if enough argument
    if(is_enough_argument(cmd_fields, ARGUMENT_CMD_REMOVE)){
        string stop = cmd_fields.at(STOP_IN_CMD_REMOVE);
        set<string> line_list = list_lines(system, stop);

        // Check if the stop is in the system then remove it from all lines
        // if not, return error
        if(is_stop_found(system, stop)){
            for(const auto& line : line_list){
                double distance = find_key(system.at(line),stop);
                system.at(line).erase(distance);
            }
            cout<<"Stop was removed from all lines."<<endl;
        }
    }
}

// Execute the distance command
// Calculate distance between 2 stops
void cmd_distance(const System& system, vector<string> cmd_fields){
    // Check if enough arguments
    if(is_enough_argument(cmd_fields, ARGUMENT_CMD_DISTANCE)){
        // Name the fields accordingly for clarification purpose
        string line = cmd_fields.at(LINE_IN_CMD_DISTANCE);
        string stop_1 = cmd_fields.at(STOP_1_IN_CMD_DISTANCE);
        string stop_2 = cmd_fields.at(STOP_2_IN_CMD_DISTANCE);

        // Check if the line and stops are in the system
        // if not, return error
        if(is_line_found(system, line)
                and is_stop_found(system, stop_1)
                and is_stop_found(system, stop_2)){
            //Calculate the distance using absolute value
            double distance_1 = find_key(system.at(line), stop_1);
            double distance_2 = find_key(system.at(line), stop_2);
            double distance = abs(distance_1 - distance_2);
            cout<<"Distance between "<<stop_1<<" and "<<stop_2;
            cout<<" is "<<distance<<endl;
        }
    }
}

void user_interface(System& system){
    while(true){
        // Read user input
        cout<<"tramway> ";
        string user_input = "";
        getline(cin, user_input);

        //Read the input to command fields
        vector<string> cmd_fields = read_input(user_input);
        // Change to upper case
        change_to_upper(cmd_fields.at(INDEX_CMD_IN_USER_INPUT));

        // Execute command by case
        if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT)=="LINES"){
            cmd_lines(system);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "LINE"){
            cmd_line(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "ADDLINE"){
            cmd_addline(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "ADDSTOP"){
            cmd_addstop(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "STOPS"){
            cmd_stops(system);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "STOP"){
            cmd_stop(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "DISTANCE"){
            cmd_distance(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "REMOVE"){
            cmd_remove(system, cmd_fields);
        }else if(cmd_fields.at(INDEX_CMD_IN_USER_INPUT) == "QUIT"){
            break;
        }else{
            cout<<INVALID_INPUT<<endl;
        }

    }
}


// Short and sweet main.
int main()
{
    print_rasse();
    System system = {};

    // Read input file
    string filename;
    cout<<"Give a name for input file: ";
    getline(cin, filename);
    vector<string> data_from_file;

    // Check if file could be open
    if(!read_file(filename,data_from_file)){
        return EXIT_FAILURE;
    }

    // Process the file
    // Check the file data format
    if(!process_data(system, data_from_file)){
        return EXIT_FAILURE;
    }

    // User interface
    user_interface(system);

    return EXIT_SUCCESS;
}
