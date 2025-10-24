#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <cmath>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口属性，确保能接收键盘事件
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    // 初始化计算器
    resetCalculator();

    // 连接数字按钮 (0-9)
    connect(ui->BN0, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN1, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN2, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN3, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN4, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN5, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN6, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN7, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN8, &QPushButton::clicked, this, &MainWindow::BNclicked);
    connect(ui->BN9, &QPushButton::clicked, this, &MainWindow::BNclicked);

    // 连接基本运算符按钮 (+, -, ×, ÷)
    connect(ui->JIA, &QPushButton::clicked, this, &MainWindow::CHUcun);
    connect(ui->JIAN, &QPushButton::clicked, this, &MainWindow::CHUcun);
    connect(ui->CHEN, &QPushButton::clicked, this, &MainWindow::CHUcun);
    connect(ui->CHU, &QPushButton::clicked, this, &MainWindow::CHUcun);

    // 连接等号按钮
    connect(ui->DY, &QPushButton::clicked, this, &MainWindow::on_DY_clicked);

    // 连接其他功能按钮
    connect(ui->ZF, &QPushButton::clicked, this, &MainWindow::on_ZF_clicked);
    connect(ui->BAIFEN, &QPushButton::clicked, this, &MainWindow::on_BAIFEN_clicked);
    connect(ui->PF, &QPushButton::clicked, this, &MainWindow::on_PF_clicked);
    connect(ui->GENGHAO, &QPushButton::clicked, this, &MainWindow::on_GENGHAO_clicked);
    connect(ui->DAOSU, &QPushButton::clicked, this, &MainWindow::on_DAOSU_clicked);
    connect(ui->QINchu, &QPushButton::clicked, this, &MainWindow::on_QINchu_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resetCalculator()
{
    operand = "0";
    pendingOperator = "";
    resultSoFar = 0.0;
    waitForNewOperand = false;
    calculationPerformed = false;
    ui->KUANG->setText(operand);
}


QString MainWindow::removeTrailingZeros(const QString &str)
{
    QString result = str;

    if (result.contains('.')) {
        while (result.endsWith('0')) {
            result.chop(1);
        }

        if (result.endsWith('.')) {
            result.chop(1);
        }
    }

    return result;
}

void MainWindow::BNclicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString digit = button->text();


    if (calculationPerformed) {
        operand = "0";
        calculationPerformed = false;
        pendingOperator = "";
    }

    if (waitForNewOperand) {
        operand = digit;
        waitForNewOperand = false;
    } else {
        if (operand == "0" && digit != ".") {
            operand = digit;
        } else {
            operand += digit;
        }
    }

    ui->KUANG->setText(operand);
}

void MainWindow::on_dain_clicked()
{
    if (calculationPerformed) {
        operand = "0";
        calculationPerformed = false;
        pendingOperator = "";
    }

    if (waitForNewOperand) {
        operand = "0.";
        waitForNewOperand = false;
    } else if (!operand.contains('.')) {
        if (operand.isEmpty()) {
            operand = "0.";
        } else {
            operand += ".";
        }
    }

    ui->KUANG->setText(operand);
}

void MainWindow::on_DEL_clicked()
{
    if (waitForNewOperand || calculationPerformed) return;

    if (operand.length() > 1) {
        operand = operand.left(operand.length() - 1);
    } else {
        operand = "0";
    }

    ui->KUANG->setText(operand);
}

void MainWindow::on_GUIling_clicked()
{
    resetCalculator();
}

void MainWindow::CHUcun()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();


    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
    } else {

        resultSoFar = operand.toDouble();
    }

    // 保存新运算符
    pendingOperator = op;
    waitForNewOperand = true;
    calculationPerformed = false;
}

void MainWindow::performCalculation()
{
    double currentValue = operand.toDouble();

    if (pendingOperator == "+") {
        resultSoFar += currentValue;
    } else if (pendingOperator == "-") {
        resultSoFar -= currentValue;
    } else if (pendingOperator == "×") {
        resultSoFar *= currentValue;
    } else if (pendingOperator == "÷") {
        if (currentValue == 0) {
            ui->KUANG->setText("错误");
            resetCalculator();
            return;
        }
        resultSoFar /= currentValue;
    }

    operand = QString::number(resultSoFar, 'g', 10);
    operand = removeTrailingZeros(operand);
    ui->KUANG->setText(operand);
}

void MainWindow::on_DY_clicked()
{
    // 如果有待处理的计算，执行它
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
        pendingOperator = "";
        calculationPerformed = true;
    }

    else if (calculationPerformed && !pendingOperator.isEmpty()) {
        // 重复最后一次计算
        double currentValue = operand.toDouble();
        performCalculation();
        operand = QString::number(resultSoFar, 'g', 10);
        operand = removeTrailingZeros(operand);
        ui->KUANG->setText(operand);
    }

    else {
        calculationPerformed = true;
    }

    waitForNewOperand = true;
}

void MainWindow::on_ZF_clicked()
{
    if (operand == "0") return;

    if (operand.startsWith('-')) {
        operand = operand.mid(1);
    } else {
        operand = "-" + operand;
    }

    ui->KUANG->setText(operand);
}

void MainWindow::on_BAIFEN_clicked()
{
    double value = operand.toDouble();
    value = value / 100.0;  // 百分比计算
    operand = QString::number(value, 'g', 10);
    operand = removeTrailingZeros(operand);
    ui->KUANG->setText(operand);

    // 重置状态
    pendingOperator = "";
    calculationPerformed = true;
    waitForNewOperand = true;
}

void MainWindow::on_PF_clicked()
{
    double value = operand.toDouble();
    value = value * value;  // 平方计算
    operand = QString::number(value, 'g', 10);
    operand = removeTrailingZeros(operand);
    ui->KUANG->setText(operand);

    // 重置状态
    pendingOperator = "";
    calculationPerformed = true;
    waitForNewOperand = true;
}

void MainWindow::on_GENGHAO_clicked()
{
    double value = operand.toDouble();
    if (value < 0) {
        ui->KUANG->setText("错误");
        resetCalculator();
        return;
    }
    value = sqrt(value);  // 平方根计算
    operand = QString::number(value, 'g', 10);
    operand = removeTrailingZeros(operand);
    ui->KUANG->setText(operand);

    // 重置状态
    pendingOperator = "";
    calculationPerformed = true;
    waitForNewOperand = true;
}

void MainWindow::on_DAOSU_clicked()
{
    double value = operand.toDouble();
    if (value == 0) {
        ui->KUANG->setText("错误");
        resetCalculator();
        return;
    }
    value = 1.0 / value;  // 倒数计算
    operand = QString::number(value, 'g', 10);
    operand = removeTrailingZeros(operand);
    ui->KUANG->setText(operand);

    // 重置状态
    pendingOperator = "";
    calculationPerformed = true;
    waitForNewOperand = true;
}

void MainWindow::on_QINchu_clicked()
{
    operand = "0";
    ui->KUANG->setText(operand);
    waitForNewOperand = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();
    int key = event->key();

    // 数字键处理
    if (keyText >= "0" && keyText <= "9") {
        if (keyText == "0") ui->BN0->click();
        else if (keyText == "1") ui->BN1->click();
        else if (keyText == "2") ui->BN2->click();
        else if (keyText == "3") ui->BN3->click();
        else if (keyText == "4") ui->BN4->click();
        else if (keyText == "5") ui->BN5->click();
        else if (keyText == "6") ui->BN6->click();
        else if (keyText == "7") ui->BN7->click();
        else if (keyText == "8") ui->BN8->click();
        else if (keyText == "9") ui->BN9->click();
    }
    // 运算符处理
    else if (keyText == "+") {
        ui->JIA->click();
    }
    else if (keyText == "-") {
        ui->JIAN->click();
    }
    else if (keyText == "*" || keyText == "x" || keyText == "X") {
        ui->CHEN->click();
    }
    else if (keyText == "/") {
        ui->CHU->click();
    }
    // 小数点
    else if (keyText == ".") {
        ui->dain->click();
    }
    // 等号或回车
    else if (key == Qt::Key_Enter || key == Qt::Key_Return || keyText == "=") {
        ui->DY->click();
    }
    // 退格键
    else if (key == Qt::Key_Backspace) {
        ui->DEL->click();
    }
    // 清除键
    else if (key == Qt::Key_Escape || key == Qt::Key_Delete) {
        ui->GUIling->click();
    }
    // 百分比
    else if (keyText == "%") {
        ui->BAIFEN->click();
    }
    // 平方 (使用^符号)
    else if (keyText == "^") {
        ui->PF->click();
    }
    // 平方根 (使用S键)
    else if (keyText == "s" || keyText == "S") {
        ui->GENGHAO->click();
    }
    // 倒数 (使用R键)
    else if (keyText == "r" || keyText == "R") {
        ui->DAOSU->click();
    }
    // 正负号 (使用N键)
    else if (keyText == "n" || keyText == "N") {
        ui->ZF->click();
    }
    else {
        // 其他按键交给父类处理
        QMainWindow::keyPressEvent(event);
    }
}
