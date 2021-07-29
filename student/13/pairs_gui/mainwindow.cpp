/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class implementation of Mainwindow
*/
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "utils.hh"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(gameboard != nullptr){
        delete gameboard;
        gameboard = nullptr;
    }
    delete ui;
}

// Check if the number of card is an even number between 2 and 26
bool MainWindow::is_valid_card()
{
    if(number_of_card_ < 2 or
            number_of_card_ >26 or
            number_of_card_%2 == 1){
        return false;
    }
    return true;
}

// Function to take the input players' names from user.
void MainWindow::take_players_names()
{
    QString player1 = ui->lineEditPlayer1Name->text();
    QString player2 = ui->lineEditPlayer2Name->text();

    if(player1 != ""){
        player1_name_ = player1;
    }

    if(player2 != ""){
        player2_name_ = player2;
    }
}

void MainWindow::on_pushNewGame_clicked()
{
    // Take the number of card input by user
    std::string number_of_card = ui->lineEdit->text().toStdString();
    number_of_card_ = utils::stoi_with_check(number_of_card);

    // If the number of card is valid
    // Then start a new game
    // Delete the old game if there is any
    // At any given time, there is only one game
    if(is_valid_card()){
        ui->lineEdit->setText("");
        if(gameboard != nullptr){
            delete gameboard;
            gameboard = nullptr;
        }
        take_players_names();
        gameboard = new GameBoard(player1_name_, player2_name_, number_of_card_);
        gameboard->show();
    }

}
