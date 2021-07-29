#include "player.hh"
#include <iostream>

using namespace std;

Player::Player(string name):
    name_(name){
}

string Player::get_name() const{
    return name_;
}

int Player::get_points() const{
    return points;
}

bool Player::has_won() const{
    if(points == 50){
        return true;
    }
    return false;
}

void Player::add_points(int pts){
    points += pts;
    if (points > 50){
        points =25;
    }
}
