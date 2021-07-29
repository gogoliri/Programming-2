/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Definition of utilities functions
* These functions do not relate to the game
* but neccessary for the implementation of the game
*/
#ifndef UTILS_HH
#define UTILS_HH

#endif // UTILS_HH

#include <string>

namespace utils {

// Check if the str given is numeric and convert it to unsigned int
unsigned int stoi_with_check(const std::string& str);

// Take a product and calculate 2 nearest factor
void ask_product_and_calculate_factors(unsigned int& product,
                                       unsigned int& smaller_factor,
                                       unsigned int& bigger_factor);
}

