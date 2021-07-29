#include "utils.hh"
#include <iostream>
#include <set>
std::vector<std::string> utils::split( std::string& str, char delim )
{
    std::vector<std::string> result = {""};
    bool cont = false;
    for ( auto cha : str )
    {
        if ( cha == '"' )
        {
            cont = not cont;
        }
        else if ( cha == delim and not cont)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(cha);
        }
    }
    if ( result.back() == "" )
    {
        result.erase(--result.end());
    }
    return result;
}

bool utils::is_numeric(std::string s, bool zero_allowed)
{
    if( not zero_allowed )
    {
        bool all_zeroes = true;
        for( unsigned int i = 0; i < s.length(); ++i )
        {
            if( s.at(i) != '0' )
            {
                all_zeroes = false;
            }
        }
        if( all_zeroes )
        {
            return false;
        }
    }
    for( unsigned int i = 0; i < s.length(); ++i )
    {
        if( not isdigit(s.at(i)) )
        {
            return false;
        }
    }
    return true;
}

// Change a string to a vector of string with 1 element
std::vector<std::string> utils::string_to_vector(const std::string &id)
{
    std::vector<std::string> id_vector = {id};
    return id_vector;
}

// Print none if the given variable is false
void utils::print_none(bool &is_any)
{
    if(is_any == false){
        std::cout<<NONE<<std::endl;
    }
}


