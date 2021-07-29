#include "book.hh"
#include <iostream>

using namespace std;

Book::Book(string author, string title):
    author_(author), title_(title){
}

void Book::print() const{
    cout<<get_author()<<" : "<<get_title()<<endl;
    if(has_loaned == false){
        cout<<"- available"<<endl;
    }else{
        cout<<"- loaned: ";
        loan_date.print();
        cout<<"- to be returned: ";
        return_date.print();
    }
}

string Book::get_title() const{
    return title_;
}

string Book::get_author() const{
    return author_;
}

void Book::give_back(){
    has_loaned = false;
}

void Book::loan(Date date){
    if(has_loaned==true){
        cout<<"Already loaned: cannot be loaned"<<endl;
    }else if(has_loaned == false){
        has_loaned = true;
        loan_date = date;
        date.advance(28);
        return_date = date;
    }
}

void Book::renew(){
    if(has_loaned == false){
        cout<<"Not loaned: cannot be renewed"<<endl;
    }else{
        return_date.advance(28);
    }
}
