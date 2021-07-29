#include <cstdlib>
#include <iostream>

// Write your swap function here.

void swap(int& number_1,int& number_2){
    int replace_1 = number_1;
    int replace_2 = number_2;
    number_2 = replace_1;
    number_1 = replace_2;
}

#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
