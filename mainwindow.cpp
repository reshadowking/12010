#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->BN0,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN1,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN2,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN3,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN4,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN5,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN6,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN7,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN8,SIGNAL(clicked()),this,SLOT(BNclicked()));
    connect(ui->BN9,SIGNAL(clicked()),this,SLOT(BNclicked()));

    connect(ui->JIA,SIGNAL(clicked()),this,SLOT(CHUcun()));
    connect(ui->JIAN,SIGNAL(clicked()),this,SLOT(CHUcun()));
    connect(ui->CHEN,SIGNAL(clicked()),this,SLOT(CHUcun()));
    connect(ui->CHU,SIGNAL(clicked()),this,SLOT(CHUcun()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BNclicked()
{
    QString digit =  qobject_cast<QPushButton *>(sender())->text();
    if(digit == "0" && operand ==  "0")
        digit = "";
    else if(digit !="0" && operand == "0"){
        if(digit != "."){
            operand = digit;}
        else{
            operand += digit;
        }}

    operand += digit;

    ui->KUANG->setText(operand);
    ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text()+"BN clicked");

}

void MainWindow::on_dain_clicked()
{
    if(!operand.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->KUANG->setText(operand);

}


void MainWindow::on_DEL_clicked()
{

    operand =operand.left(operand.length()-1);
    ui->KUANG->setText(operand);
}


void MainWindow::on_GUIling_clicked()
{
    operand.clear();
    ui->KUANG->setText(operand);
}

void MainWindow::CHUcun()
{
    if(operand != ""){
        operands.push_back(operand);
        operand = "";
    }

}

