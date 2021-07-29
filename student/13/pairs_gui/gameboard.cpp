/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class implementation of Gameboard (window)
*/
#include "gameboard.hh"
#include "ui_gameboard.h"
#include "utils.hh"

#include <algorithm>
#include <random>
#include <chrono>

const QString COLOR = "background-color: #ffffff;";
const QString BACK_COLOR = "background-color: #daffff;";
const QString LCD_COLOR = "background-color: #daffaf;";
const QString BACK_LETTER = "#";
const QString WIN = " win!";
const QString TURN = "'s turn.";
const QString TIE = "It is a tie!";
const QString EMPTY_MESSAGE = "";
const QString SELECT_2_CARDS = "Please select 2 cards.";
const QString IMAGE_APPLE = ":/Resources/apple.png";

GameBoard::GameBoard(QString player1_name,
                     QString player2_name,
                     unsigned int number_of_card,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameBoard),
    number_of_card_(number_of_card),
    player1_name_(player1_name),
    player2_name_(player2_name),
    timer_(new QTimer(this))
{
    ui->setupUi(this);

    connect(timer_, &QTimer::timeout, this, &GameBoard::display_time);
    init_tiny();
    init_string_letter();
    init_cards();
}

GameBoard::~GameBoard()
{
    delete player_1;
    delete player_2;

    for(unsigned int rowth =0; rowth<row_;rowth++){
        for(auto& card: list_of_cards_.at(rowth)){
            delete card.second;
            card.second = nullptr;
        }
    }
    delete  timer_;
    delete ui;
}

// Turn a card and disabled the button when card is clicked
void GameBoard::pushCard_clicked()
{
    // Only have effect when current cards list has less than 2 cards
    if(current_cards_.size() <2){
        // Find the signal sender button
        QPushButton* button = static_cast<QPushButton*>(sender());

        // Find the card corespondent to that button and turn it
        // also turnt he button
        // Add the card to the current_cards list for comparison
        for(auto& row: list_of_cards_){
            if(row.find(button) != row.end()){
                row.at(button)->turn();
                
                button->setDisabled(true);
                current_cards_.push_back(row.at(button));
                std::string card_letter="";
                card_letter+= row.at(button)->get_letter();
                button->setText(QString::fromStdString(card_letter));
            }
        }
    }
}

// Initialize small details
void GameBoard::init_tiny()
{
    ui->centralwidget->setStyleSheet(COLOR);
    utils::ask_product_and_calculate_factors(number_of_card_,
                                             row_,
                                             column_);

    // Set the players' names for labels
    ui->labelPlayer1->setText(player1_name_);
    ui->labelPlayer2->setText(player2_name_);
    ui->labelTurn->setText(player1_name_+TURN);
    // Set the color for LCDs
    ui->lcdMinute->setStyleSheet(LCD_COLOR);
    ui->lcdSecond->setStyleSheet(LCD_COLOR);
    // Set score at 0 for both players
    update_score();

    timer_start();
}

// Initialized the letter string for the random order of cards
void GameBoard::init_string_letter()
{
    // Initialize a letter string AABBCC...
    char c = 'A';
    for( unsigned int count = 0; count<number_of_card_;count++){
        card_letters_ += c;
        if(count%2 ==1){
            c++;
        }
    }
    // Shuffle the letter string
    std::shuffle(card_letters_.begin(),
                 card_letters_.end(),
                 std::default_random_engine(seed_));
}

// Set geometry a button and connect it signal
void GameBoard::set_a_button(QPushButton *button,
                             unsigned int &rowth,
                             unsigned int &columnth)
{
    button->setGeometry(2 * MARGIN + columnth * (NARROW_BUTTON_WIDTH + MARGIN),
                        2 * MARGIN + rowth * (DEFAULT_BUTTON_HEIGTH + MARGIN),
                        NARROW_BUTTON_WIDTH,
                        DEFAULT_BUTTON_HEIGTH);
    connect(button, &QPushButton::clicked,
            this, &GameBoard::pushCard_clicked);
   button->setStyleSheet(BACK_COLOR);
   QPixmap image = make_image();
   button->setIcon(image);
}

// Initialized a card and its button
void GameBoard::init_a_card(unsigned int& rowth,
                            unsigned int& columnth,
                            std::map<QPushButton *, Card *>& list_of_cards_row,
                            unsigned int& count)
{
    Card* card = new Card(card_letters_.at(count));

    QPushButton* pushButton = new QPushButton("", this);
    set_a_button(pushButton, rowth, columnth);

    list_of_cards_row.insert(std::pair<QPushButton*, Card*>(pushButton, card));
}

// Initialize cards and buttons on the game board
void GameBoard::init_cards()
{

    unsigned int count = 0;
    for(unsigned int rowth =0; rowth < row_; rowth++){
        std::map<QPushButton*, Card*> list_of_cards_row = {};

        for(unsigned int columnth = 0; columnth< column_; columnth++, count++){
            init_a_card(rowth,columnth,list_of_cards_row, count);
        }
        list_of_cards_.push_back(list_of_cards_row);
    }
}

// Change the turn
void GameBoard::change_turn()
{
    turnth_+=1;
    if(turnth_%2 ==1){
        current_player_ = player_1;
    }else{
        current_player_ = player_2;
    }
    QString name_of_current_player = QString::fromStdString(current_player_->get_name());
    ui->labelTurn->setText(name_of_current_player+TURN);
}

// Annouce the winner at the end of the game
void GameBoard::winner()
{
    if(player_1->number_of_pairs()+player_2->number_of_pairs() == number_of_card_/2){
        ui->pushTurn->setDisabled(true);
        turnth_-=1;
        if(player_1->number_of_pairs()>player_2->number_of_pairs()){
            ui->labelTurn->setText(player1_name_+WIN);
        }else if(player_1->number_of_pairs()<player_2->number_of_pairs()){
            ui->labelTurn->setText(player2_name_+WIN);
        }else if(player_1->number_of_pairs()==player_2->number_of_pairs()){
            ui->labelTurn->setText(TIE);
        }
        timer_stop();
    }
}

// Update the scores
void GameBoard::update_score()
{
    ui->labelPlayer1Score->setNum(static_cast<int>(player_1->number_of_pairs()));
    ui->labelPlayer2Score->setNum(static_cast<int>(player_2->number_of_pairs()));
}

// Check 2 cards of current turn
// if they are similar, remove from table, add point for player
void GameBoard::check_cards()
{
    if(current_cards_.at(0)->get_letter() == current_cards_.at(1)->get_letter()){
        for(auto& card: current_cards_){
            card->remove_from_game_board();
            current_player_->add_card(card);
        }
    }
}

// Hide the card for new turn
// remove empty card
void GameBoard::hide_card()
{
    for(auto& row : list_of_cards_){
        for(auto& pairs: row){
            if(pairs.second->get_visibility() == EMPTY){
                pairs.first->setText(EMPTY_MESSAGE);
                pairs.first->setStyleSheet(COLOR);
            }else if(pairs.second->get_visibility() == OPEN){
                pairs.first->setIcon(make_image());
                pairs.first->setText(EMPTY_MESSAGE);
                pairs.first->setStyleSheet(BACK_COLOR);
                pairs.first->setEnabled(true);
                pairs.second->turn();
            }
        }
    }
}

// Generate an image of apple
QPixmap GameBoard::make_image()
{
    QPixmap image(IMAGE_APPLE);
    image = image.scaled(NARROW_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGTH);
    return image;
}

// Define action when click the Next Turn button
void GameBoard::on_pushTurn_clicked()
{
    if(current_cards_.size() == 2){
        check_cards();
        hide_card();
        // Clear the current cards list to make a new turn
        current_cards_.clear();

        change_turn();
        update_score();
        winner();
        ui->labelShowTurnth->setNum(turnth_);
        ui->labelWarning->setText(EMPTY_MESSAGE);
    }else{
        ui->labelWarning->setText(SELECT_2_CARDS);
    }
}

// Timer start
void GameBoard::timer_start()
{
    if(!timer_->isActive()){
    timer_->start(1000);
    }
}

// Stop timer at the end
void GameBoard::timer_stop()
{
    timer_->stop();
}

// Display time on lcds
void GameBoard::display_time()
{
    int current_minutes = ui->lcdMinute->intValue();
    int current_seconds = ui->lcdSecond->intValue();

    if(current_seconds == 59){
        ui->lcdMinute->display(current_minutes + 1);
        ui->lcdSecond->display(0);
    }else{
        ui->lcdSecond->display(current_seconds+1);
    }
}
