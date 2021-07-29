#include <iostream>
#include <vector>
using namespace std;

bool is_operator(char c){
    if(c!='+' and c!='-' and c!='*' and c!='/'){
        return false;
    }
    return true;
}

bool is_operand(char c){
    if(c>'9' or c<'0'){
        return false;
    }
    return true;
}

double calculate(const double& A, const double& B, const char& symbol){
    //double A = static_cast<double>(a);
    //double B = static_cast<double>(b);

    if(symbol == '+'){
        return A+B;
    }else if(symbol =='-'){
        return A-B;
    }else if(symbol =='*'){
        return A*B;
    }else if(symbol == '/'){
        return A/B;
        }

    return EXIT_FAILURE;
}

int main()
{
    cout <<"Input an expression in reverse Polish notation (end with #):"<<endl;

    
    // Push back char to vector
    string str;
    cout<<"EXPR> ";
    getline(cin, str);
    vector<char> ch;
    for(const auto& c:str){
        if(c!= ' '){
            ch.push_back(c);
        }
    }
    
    // Start with number
    if(!is_operand(ch[0])){
        cout<<"Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }

    // Unknown character
    for(const auto& item: ch){
        if(!is_operand(item) and !is_operator(item) and item != '#'){
            cout<<"Error: Unknown character" <<endl;
            return EXIT_FAILURE;
        }
    }

    // Division by zero
    for(size_t i = 0; i<ch.size() - 1; i++){
        if(ch[i]=='0' and ch[i+1] == '/'){
            cout<<"Error: Division by zero"<<endl;
            return EXIT_FAILURE;
        }
    }

    int expression[81];
    int* pntr = &expression[0];

    for(size_t i=0; i<ch.size(); i++){
        // If operand, add to array
        if(is_operand(ch[i])){
            *pntr = ch[i] - '0';
            pntr+=1;

        }

        // If symbol, perform calculation
        if(is_operator(ch[i])){
            if((pntr) == &expression[1]){
                cout<<"Error: Too few operands"<<endl;
                return EXIT_FAILURE;
            }

            if(ch[i] == '/' and *(pntr-1) == 0){
                cout<<"Error: Division by zero"<<endl;
                return EXIT_FAILURE;
            }
            double tmp = calculate(*(pntr-2),*(pntr-1), ch[i]);
            pntr-=2;
            *pntr = tmp;
            pntr +=1;
        }
        // Last
        if(ch[i] == '#'){
            if(pntr != &expression[1]){

                cout<<"Error: Too few operators"<<endl;
                return EXIT_FAILURE;
            }else {
                cout <<"Correct: "<< expression[0]<<" is the result" <<endl;
            }
        }
    }

    
    return EXIT_SUCCESS;
}
