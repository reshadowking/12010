#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <cmath>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化计算器
    resetCalculator();

    // 只连接数字按钮 (0-9) - 这些按钮没有自动连接
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

    // 注意：其他所有按钮都通过自动连接（命名规范：on_对象名_clicked）
    // 不要手动连接它们，否则会导致重复调用
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 重置计算器状态
void MainWindow::resetCalculator()
{
    operand = "0";
    pendingOperator = "";
    resultSoFar = 0.0;
    waitForNewOperand = false;
    calculationPerformed = false;
    ui->KUANG->setText(operand);
}

// 辅助函数：移除末尾不必要的零
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

    // 如果刚刚执行了计算，重新开始输入
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

// 运算符按钮的槽函数 - 替换原来的CHUcun函数
void MainWindow::on_JIA_clicked()
{
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
    } else {
        resultSoFar = operand.toDouble();
    }

    pendingOperator = "+";
    waitForNewOperand = true;
    calculationPerformed = false;
}

void MainWindow::on_JIAN_clicked()
{
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
    } else {
        resultSoFar = operand.toDouble();
    }

    pendingOperator = "-";
    waitForNewOperand = true;
    calculationPerformed = false;
}

void MainWindow::on_CHEN_clicked()
{
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
    } else {
        resultSoFar = operand.toDouble();
    }

    pendingOperator = "×";
    waitForNewOperand = true;
    calculationPerformed = false;
}

void MainWindow::on_CHU_clicked()
{
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
    } else {
        resultSoFar = operand.toDouble();
    }

    pendingOperator = "÷";
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
    if (!pendingOperator.isEmpty() && !waitForNewOperand) {
        performCalculation();
        pendingOperator = "";
        calculationPerformed = true;
    } else if (calculationPerformed && !pendingOperator.isEmpty()) {
        double currentValue = operand.toDouble();
        performCalculation();
        operand = QString::number(resultSoFar, 'g', 10);
        operand = removeTrailingZeros(operand);
        ui->KUANG->setText(operand);
    } else {
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
