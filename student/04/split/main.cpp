#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string line, char seperator, bool ignore_space = false){
     std::vector<std::string> vector_string;
     std::string::size_type index = 0;
     std::vector<std::string::size_type> list_seperator;


     line = seperator + line + seperator;

     while(index < line.size()){
         if(line.at(index) == seperator ){
             list_seperator.push_back(index);
         }
         index++;
     }
     
     if(list_seperator.size() == 0){
         vector_string.push_back(line);
         return vector_string;
     }

     std::vector<std::string> replace;

     std::vector<std::string::size_type>::size_type list_index = 0;
     while(list_index < list_seperator.size() - 1){
       std::string::size_type length = list_seperator.at(list_index+1) - list_seperator.at(list_index) -1;
       std::string::size_type position = list_seperator.at(list_index) + 1;
       replace.push_back(line.substr(position, length));
       list_index++;
     }

     for(auto element: replace){
         if(element == ""){
             if(ignore_space == false){
                 vector_string.push_back(element);
             }
         }else{
             vector_string.push_back(element);
         }
     }
     return vector_string;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
