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


    void on_dain_clicked();
    void on_DEL_clicked();
    void on_GUIling_clicked();
    void on_JIA_clicked();
    void on_JIAN_clicked();
    void on_CHEN_clicked();
    void on_CHU_clicked();
    void on_DY_clicked();
    void on_ZF_clicked();
    void on_BAIFEN_clicked();
    void on_PF_clicked();
    void on_GENGHAO_clicked();
    void on_DAOSU_clicked();
    void on_QINchu_clicked();

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
