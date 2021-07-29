/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Implementation of utilities functions
* These functions do not relate to the game
* but neccessary for the implementation of the game
*/
#include "utils.hh"
#include <string>

unsigned int utils::stoi_with_check(const std::string &str)
{
    bool is_numeric = true;
    if(str.length() == 0){
        return 0;
    }
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

void utils::ask_product_and_calculate_factors(unsigned int &product, unsigned int &smaller_factor, unsigned int &bigger_factor)
{

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}
