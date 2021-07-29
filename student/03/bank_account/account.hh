#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void set_credit_limit(int limit);
    void print() const;
    void save_money(int money);
    bool take_money(int taken);
    void transfer_to(Account& target, int amount);

    std::string get_name() const;
    std::string get_iban() const;
    int get_balance() const;

    int balance = 0;
    int credit_limit = 0;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    std::string iban_;
    std::string owner_;
    bool has_credit_;

};

#endif // ACCOUNT_HH
