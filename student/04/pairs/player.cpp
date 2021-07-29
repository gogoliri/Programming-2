/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class implementation of Player
*/

#include "player.hh"
#include "card.hh"
#include <iostream>
// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.
using namespace std;

Player::Player(const string& name):
    name_(name){

}

string Player::get_name() const{
    return name_;
}

unsigned int Player::number_of_pairs() const{
    return static_cast<unsigned int>(number_of_pairs_);
}

void Player::add_card(Card &card){
    cards_hold_.push_back(card);
    number_of_pairs_ +=0.5; // Function called 2 times when removing cards
    card.remove_from_game_board();
}

void Player::print() const{
    std::cout<<"*** "<< Player::get_name()
             << " has "<<Player::number_of_pairs()
             <<" pair(s)." << endl;
}







