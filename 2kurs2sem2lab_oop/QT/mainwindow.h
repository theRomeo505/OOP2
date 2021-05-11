#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**Default QT constructor for GUI*/
    MainWindow(QWidget *parent = nullptr);
    /**Default QT destructor for GUI*/
    ~MainWindow();

private slots:
    /**
    Function that adds element to array (from spinBox) to listWidget_2
*/
    void on_pushButton_clicked();
    /**
    Function that clears array (listWidget_2) and creates a new one with size from spinBox_2 (elements are random)
*/
    void on_pushButton_4_clicked();
    /**
    Function that clears array (listWidget_2)
*/
    void on_pushButton_5_clicked();
    /**
    Function that applies sort from listWidget to array from listWidget_2
*/
    void on_pushButton_3_clicked();
    /**
    Function that shows difference in time between listWidget_5 and listWidget_4 sorts (listWidget_5 time - listWidget_4 time) in ms
*/
    void on_pushButton_6_clicked();
    void add_items_to_lw2(int num);
    void old_func();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
