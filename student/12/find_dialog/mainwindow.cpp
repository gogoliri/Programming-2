#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_findPushButton_clicked()
{
    file_name_ = ui->fileLineEdit->text();
    word_ = ui->keyLineEdit->text();

    std::ifstream file_object(file_name_.toStdString());
    if(not file_object){
        ui->textBrowser->setText(FILE_NOT_FOUND);
    }else{
        if(word_.size() == 0){
            ui->textBrowser->setText(FILE_FOUND);
        }else{
            std::string text = "";
            while(getline(file_object,text)){
                std::string word = word_.toStdString();
                bool match = ui->matchCheckBox->isChecked();

                if(find_string(text,word,match)){
                    return;
                }
                ui->textBrowser->setText(WORD_NOT_FOUND);
            }
        }
    }

    file_object.close();

}

void MainWindow::change_to_upper(std::string &content)
{
    std::string converted_content="";
    char character=' ';

    for(size_t index = 0; index < content.size(); index++){
        character = toupper(content[index]);
        content.at(index) = character;
    }
}

bool MainWindow::find_string(std::string &text, std::string &word, bool &match)
{
    if(match == false){
        change_to_upper(text);
        change_to_upper(word);
    }

    if(text.find(word)!= std::string::npos){
        ui->textBrowser->setText(WORD_FOUND);
        return true;
    }
    return false;
}
