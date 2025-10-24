#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void BNclicked();  // 数字按钮点击
    void on_dain_clicked();  // 小数点
    void on_DEL_clicked();  // 删除
    void on_GUIling_clicked();  // 清空
    void CHUcun();  // 运算符点击
    void on_DY_clicked();  // 等号
    void on_ZF_clicked();  // 正负号
    void on_BAIFEN_clicked();  // 百分比
    void on_PF_clicked();  // 平方
    void on_GENGHAO_clicked();  // 平方根
    void on_DAOSU_clicked();  // 倒数
    void on_QINchu_clicked();  // 清除

private:
    Ui::MainWindow *ui;
    QString operand;  // 当前操作数
    QString pendingOperator;  // 等待的运算符
    double resultSoFar;  // 当前累计结果
    bool waitForNewOperand;  // 是否等待新操作数
    bool calculationPerformed;  // 是否已执行计算

    void resetCalculator();
    void performCalculation();
    QString removeTrailingZeros(const QString &str);

protected:
    void keyPressEvent(QKeyEvent *event) override;  // 键盘
};

#endif // MAINWINDOW_H
