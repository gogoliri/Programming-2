#include "mainwindow.hh"
#include "ui_mainwindow.h"

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


void MainWindow::on_countButton_clicked()
{
    std::string weight = ui->weightLineEdit->text().toStdString();
    if(weight == ""){
        return;
    }
    weight_ = std::stod(weight);

    std::string height = ui->heightLineEdit->text().toStdString();
    if(height == ""){
        return;
    }
    height_ = std::stod(height);

    double bmi = (weight_/(height_*height_))*10000;

    ui->resultLabel->setNum(bmi);

    QString info = "";
    if(bmi < 18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    }else if(bmi > 25){
        ui->infoTextBrowser->setText("You are overweight.");
    }else{
        ui->infoTextBrowser->setText("Your weight is normal.");
    }

}
