#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDebug>
#include"dialog.h"
#include<QColorDialog>
#include<QFontDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    QPalette palette = textEdit->palette();

        palette.setColor(QPalette::Base, QColor(0, 0, 0));
        palette.setColor(QPalette::Text, QColor(255, 255, 255));
        textEdit->setPalette(palette);
        textEdit->setFont(QFont("Arial,30"));

        labelStatus = new QLabel(this);
        ui->statusBar->addWidget(labelStatus);
        labelLineColum  = new QLabel(this);
        ui->statusBar->addPermanentWidget(labelLineColum);

        labelStatus->setText("Ready");
        connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(onUpdateLineColum()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onUpdateLineColum()
{
    int line = textEdit->textCursor().blockNumber();
    int column = textEdit->textCursor().columnNumber();
    QString strLine = QString::number(line);
    QString strColumn = QString::number(column);
    labelLineColum->setText("length: "+strLine + "    lines: " + strColumn);
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       "Open a text file",
                                                       QDir::currentPath(),
                                                       "Text Files (*.txt *.c *.cpp)");
       if (fileName.isEmpty())
           return;
       QFile file(fileName);

           //--打开文件成功
           if (file.open(QIODevice ::ReadOnly | QIODevice ::Text))
           {
               QTextStream textStream(&file);
               while (!textStream.atEnd())
               {
                   //---QtextEdit按行显示文件内容
                   textEdit->setText(textStream.readLine());
               }
           }
}

void MainWindow::on_actionAbout_triggered()
{
    Dialog dialoglogin;

    dialoglogin.exec();
}

/*void MainWindow::on_actionCorlor_triggered()
{
  //QColor c = QColorDialog::getColor(Qt::white,NULL,
      //                              "pick Color",
   //                                 QColorDialog::ShowAlphaChannel);
 //QRgb c = QColorDialog::getRgba(0xffffff,0,0);
     //textEdit->setPalette(QPalette(c));

    QColor uiColor=QColorDialog::getColor(Qt::blue,this,tr("选择背景颜色"));
    //设置打开调色板时的默认颜色是蓝色
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base,uiColor);
    textEdit->setPalette(palette);

    //qDebug()<<c;
}*/

void MainWindow::on_actiontext_triggered()
{
    QColor uiColor=QColorDialog::getColor(Qt::blue,this,tr("选择背景颜色"));
    //设置打开调色板时的默认颜色是蓝色
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Text,uiColor);
    textEdit->setPalette(palette);
}

void MainWindow::on_action_4_triggered()
{
    QColor uiColor=QColorDialog::getColor(Qt::blue,this,tr("选择背景颜色"));
    //设置打开调色板时的默认颜色是蓝色
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base,uiColor);
    textEdit->setPalette(palette);
}

void MainWindow::on_actionWordSize_triggered()
{
    QFont uiFont = QFontDialog::getFont(NULL,textEdit->font(),this,tr("字体设置"));
    textEdit->setFont(uiFont);
}

void MainWindow::on_actioncopy_triggered()
{
    textEdit->copy();
}

void MainWindow::on_action_3_triggered()
{
    textEdit->paste();
}

void MainWindow::on_actioncut_triggered()
{
    textEdit->cut();
}

void MainWindow::on_actionclear_triggered()
{
     textEdit->clear();
}

void MainWindow::on_actionz_triggered()//撤销
{
    textEdit->undo();
}
