/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class definition of Player
*/

//
/* Class: Player
 * -------------
 * Represents a single player in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"
#include <string>
#include <iostream>
#include <vector>

class Player
{
public:
    // Rakentaja: luo annetun nimisen pelaajan.
    //
    // Constructor: creates a player with the given name.
    Player(const std::string& name);

    // Palauttaa pelaajan nimen.
    //
    // Returns the name of the player.
    std::string get_name() const;

    // Palauttaa pelaajan tähän asti keräämien parien määrän.
    //
    // Returns the number of pairs collected by the player so far.
    unsigned int number_of_pairs() const;

    // Siirtää annetun kortin pelilaudalta pelaajalle,
    // eli lisää kortin pelaajan keräämiin kortteihin
    // ja poistaa sen pelilaudalta.
    //
    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board.
    void add_card(Card& card);

    // Tulostaa pelaajan tilanteen: nimen ja tähän asti kerättyjen parien määrän.
    //
    // Prints the game status of the player: name and collected pairs so far.
    void print() const;

private:
    // Lisää tarvittavat attribuutit tähän
    // Add necessary attributes here
    std::string name_;
    // We must use float to make it easier later
    // when removing cards and count pairs
    float number_of_pairs_ = 0;
    std::vector<Card> cards_hold_;
};

#endif // PLAYER_HH
