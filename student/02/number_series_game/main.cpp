#include <iostream>
#include <string>
using namespace std;
int quantity;

int main()
{
    std::cout << "How many numbers would you like to have? ";
    std::cin >> quantity;
    for (int i = 1; i <= quantity; i++){
        if(i%3==0 and i%7==0){
            cout<<"zip boing"<<endl;
        }else if(i%3==0){
            cout<<"zip"<<endl;
        }else if(i%7==0){
            cout<<"boing"<<endl;
        }else{
            cout<<i<<endl;
        }
    }
    return 0;
}
