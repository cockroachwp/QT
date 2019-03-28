#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onUpdateLineColum();
  //  void on_actionOpen_triggered();

    void on_actionOpen_file_triggered();

    void on_actionAbout_triggered();

    void on_actionCorlor_triggered();

    void on_actiontext_triggered();

    void on_action_4_triggered();

    void on_actionWordSize_triggered();

    void on_actioncopy_triggered();

    void on_action_3_triggered();

    void on_actioncut_triggered();

    void on_actionclear_triggered();

    void on_actionz_triggered();

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QLabel *labelStatus;
    QLabel *labelLineColum;

};

#endif // MAINWINDOW_H
