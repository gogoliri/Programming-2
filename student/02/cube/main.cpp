#include <iostream>
#include <cmath>
using namespace std;
int number;
int main()
{
    cout << "Enter a number: ";
    cin >> number;
    if (number==0){
        cout<<"The cube of 0 is 0."<<endl;
        return 0;
    }
    int cube = pow(number,3);
    if(cube/number/number==number){
        cout<<"The cube of "<< number <<" is "<<cube<<"."<<endl;
    }else{
    cout<<"Error! The cube of "<<number<<" is not "<<cube<< "." <<endl;
    }
    return 0;
}
