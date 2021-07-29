/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class definition of Gameboard (window)
*/

//
/* Class: Gameboard (window)
 * -------------
 * Represents a single a single game in pairs (memory) game
 *
 * COMP.CS.110 K2021
 * */
#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "card.hh"
#include "player.hh"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

#include <vector>
#include <map>
#include <random>
#include <chrono>

namespace Ui {
class GameBoard;
}

class GameBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameBoard(QString player1_name,
                       QString player2_name,
                       unsigned int number_of_card = 0,
                       QWidget *parent = nullptr);
    ~GameBoard();

private slots:
    void on_pushTurn_clicked();
    void pushCard_clicked();

private:
    Ui::GameBoard *ui;

    // Space between elements, both horizontally and vertically
    const int MARGIN = 25;

    // Constants for push buttons
    const int NARROW_BUTTON_WIDTH = 20;
    const int DEFAULT_BUTTON_HEIGTH = 30;
    
    unsigned int number_of_card_ ;
    unsigned int row_ = 0;
    unsigned int column_ = 0;
    int turnth_ = 1;
    QString player1_name_;
    QString player2_name_;

    QTimer* timer_;

    // Initialize players
    Player *player_1 = new Player(player1_name_.toStdString());
    Player *player_2 = new Player(player2_name_.toStdString());
    // The current player of each turn
    Player *current_player_ = player_1;

    // Take a time based seed
    unsigned seed_ = std::chrono::system_clock::now().time_since_epoch().count();

    // Card letter in random order
    std::string card_letters_ = "";

    // List of card, us map to map the card to correspondent button
    std::vector<std::map<QPushButton*, Card*>> list_of_cards_ = {};

    // Current 2 cards that chosen by player
    std::vector<Card*> current_cards_ = {};

    // Miscellanous init
    // initiallize some small detail
    void init_tiny();

    // Initialize the game board
    void init_cards();

    // Initialize a string letter for order of card
    void init_string_letter();

    // Initialized a card
    void init_a_card(unsigned int& rowth,
                     unsigned int& columnth,
                     std::map<QPushButton*, Card*>& list_of_cards_row,
                     unsigned int& count);

    // Set geometry a button and connect it signal
    void set_a_button(QPushButton* button,
                      unsigned int& rowth,
                      unsigned int& columnth);

    // Change turn every time the Next turn button is clicked
    void change_turn();

    // Annouce winner
    void winner();

    // Update score
    void update_score();

    // Check 2 cards of current turn
    void check_cards();

    // turn the card hidden for new turn
    void hide_card();

    // Make an image
    QPixmap make_image();

    // Function for timer
    // Timer start
    void timer_start();
    // Timer stop
    void timer_stop();
    // Display time
    void display_time();
};

#endif // GAMEBOARD_HH
