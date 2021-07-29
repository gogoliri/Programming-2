/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Class definition of Mainwindow
*/

//
/* Class: Card
 * -------------
 * Represents the starting window of
 * pairs (memory) game
 *
 * COMP.CS.110 K2021
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GameBoard *gameboard = nullptr;

private slots:
    void on_pushNewGame_clicked();

private:
    Ui::MainWindow *ui;

    //Function to check if the number of card is valid
    // Valid: even number between 2 and 26
    bool is_valid_card();
    unsigned int number_of_card_ = 0;

    //Default users' names
    QString player1_name_ = "Player 1";
    QString player2_name_ = "Player 2";
    
    // Take players name from the lines boxes
    void take_players_names();

};
#endif // MAINWINDOW_HH
