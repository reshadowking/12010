#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include<QStack>

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

    QString operand;
    QStack<QString> operands;

private slots:
    void BNclicked();

    void on_dain_clicked();

    void on_DEL_clicked();

    void on_GUIling_clicked();

    void CHUcun();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
