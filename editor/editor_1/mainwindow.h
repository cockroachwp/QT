#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextEdit>
#include<QAction>
#include<QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
     void onOpenFile();

private:
    Ui::MainWindow *ui;
    QTextEdit   *textEdit;
    QAction   *actionlove,*actionnew,*actionSave;
    QMenu    *fileMenu,*fileEdit;

};

#endif // MAINWINDOW_H
