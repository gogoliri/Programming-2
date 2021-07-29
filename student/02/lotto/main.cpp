#include <iostream>

using namespace std;
int draw;
int ball;

unsigned long int factorial(int number){
    if(number == 0){
        return 1;
    }
    unsigned long int factorial=1;
    for(int i=1; i <= number;i++){
        factorial *= i;
    }
    return factorial;
}
int main()
{
    cout << "Enter the total number of lottery balls: ";
    cin >> draw;
    cout<<"Enter the number of drawn balls: ";
    cin >> ball;
    if (draw<=0 or ball<= 0){
        cout<<"The number of balls must be a positive number."<<endl;
        return 0;
    }
    if (ball>draw){
        cout<<"The maximum number of drawn balls is the total amount of balls."<<endl;
        return 0;
    }
    cout <<"The probability of guessing all "<<ball<<" balls correctly is 1/"<<factorial(draw)/(factorial(draw-ball)*factorial(ball))<<endl;
    return EXIT_SUCCESS;
}
