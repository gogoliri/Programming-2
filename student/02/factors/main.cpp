#include <iostream>
#include <cmath>
using namespace std;
int number;

int main()
{
    cout << "Enter a positive number: ";
    cin >> number;

    if(number<=0){
        cout<<"Only positive numbers accepted";
        return 0;
    }
     double sqrt_number = sqrt(number);
     int check = static_cast<int>(sqrt_number);
     for(int i = check;i>0;i--){
         if (number%i==0){
             cout<<number<<" = "<<i<<" * "<<number/i<<endl;
             return 0;
         }
     }

    return 0;
}
