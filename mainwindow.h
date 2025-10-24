#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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
    // 数字按钮 - 需要手动连接
    void BNclicked();

    // 以下按钮通过自动连接（命名规范：on_对象名_clicked）
    void on_dain_clicked();        // 小数点
    void on_DEL_clicked();         // 删除
    void on_GUIling_clicked();     // 清空(C)
    void on_JIA_clicked();        // 加号(+)
    void on_JIAN_clicked();        // 减号(-)
    void on_CHEN_clicked();        // 乘号(×)
    void on_CHU_clicked();         // 除号(÷)
    void on_DY_clicked();          // 等号(=)
    void on_ZF_clicked();          // 正负号(±)
    void on_BAIFEN_clicked();      // 百分比(%)
    void on_PF_clicked();          // 平方(x²)
    void on_GENGHAO_clicked();     // 平方根(√)
    void on_DAOSU_clicked();       // 倒数(1/x)
    void on_QINchu_clicked();      // CE清除

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
};

#endif // MAINWINDOW_H
