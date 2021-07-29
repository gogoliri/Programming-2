#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    unsigned int seed;
    cout <<"Enter a seed value: ";
    cin >> seed;



    default_random_engine gen(seed);
    uniform_int_distribution<int> number(lower, upper);

    char decision = 'c';

    for(int i = 1;i>0; i++){
        cout << endl;
        cout << "Your drawn random number is "<< number(gen)<<endl;
        cout <<"Press c to continue or q to quit: ";
        cin >> decision;

        if(decision == 'c'){

        }else if(decision =='q'){
            i=-1;
        }

    }

}

int main()  
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
