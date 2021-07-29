#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    connect(ui->startButton,&QPushButton::clicked, this,&MainWindow::on_start);
    connect(ui->stopButton,&QPushButton::clicked, this,&MainWindow::on_stop);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_reset);

    ui->lcdNumberMin->setStyleSheet("background-color: #012345;");

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0x40));
    ui->lcdNumberSec->setPalette(palette);
    ui->lcdNumberSec->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_timeout()
{
    int current_minutes = ui->lcdNumberMin->intValue();
    int current_seconds = ui->lcdNumberSec->intValue();

    if(current_seconds == 59){
        ui->lcdNumberMin->display(current_minutes + 1);
        ui->lcdNumberSec->display(0);
    }else{
        ui->lcdNumberSec->display(current_seconds+1);
    }
}

void MainWindow::on_start()
{
    if(!timer->isActive()){
    timer->start(1000);
    }
}

void MainWindow::on_reset()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::on_stop()
{
    timer->stop();
}
