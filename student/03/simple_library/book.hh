#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>
#include "date.hh"

using namespace std;

class Book
{
public:
    Book(string author, string title);
    string get_author() const;
    string get_title() const;

    void print() const;
    void give_back();
    void renew();
    void loan(Date date);

    bool has_loaned = false;
    Date loan_date;
    Date return_date;

private:
    string author_;
    string title_;
};

#endif // BOOK_HH
