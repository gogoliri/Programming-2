#include "account.hh"
#include <iostream>


Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit){
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

std::string Account::get_name() const{
    return owner_;
}

std::string Account::get_iban() const{
    return iban_;
}

int Account::get_balance() const{
    return balance;
}
void Account::print() const{
    std::cout<<get_name()<<" : "<<get_iban()<<" : "<<get_balance()
            <<" euros"<<std::endl;
}

void Account::set_credit_limit(int limit){
    if (has_credit_ == true){
        credit_limit = limit;
    }else if(has_credit_==false){
        std::cout<<"Cannot set credit limit: the account has no credit card"<<std::endl;
    }
}

void Account::save_money(int money){
    balance += money;
}

bool Account::take_money(int taken){
    if(balance-taken < (-1)*credit_limit){
        if(has_credit_==false){
        std::cout<< "Cannot take money: balance underflow"<<std::endl;
        }else {
        std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
        }
        return false;
    }else{
        balance -= taken;
        std::cout<<taken<<" euros taken: new balance of "<<iban_<<" is "<<balance<<" euros"
                <<std::endl;
    }
    return true;
}

void Account::transfer_to(Account& target, int amount){
    if(take_money(amount) == false){
        std::cout<<"Transfer from "<<iban_<<" failed"<<std::endl;
    }else{
        target.save_money(amount);
    }
}
