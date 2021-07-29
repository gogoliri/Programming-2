#ifndef PLAYER_HH
#define PLAYER_HH
#include<iostream>
using namespace std ;

class Player
{
public:
    Player(string name);

    string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int pts);

    int points =0;

private:
    string name_;
};

#endif // PLAYER_HH
