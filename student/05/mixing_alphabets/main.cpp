#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;
int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }else if(word.size() == 2 or word.size() == 1){
            cout<< word << endl;
        }else{

        // TODO: implement your solution here
        string::iterator range_begin = word.begin();
        string::iterator range_end = word.end();
        ++range_begin;   // Pointing now to the second element
        --range_end;	 // Pointing now to the last elment

        shuffle(range_begin, range_end,generator);
        std::cout << word << std::endl;
    }
    }
}
