#include "widget.h"
#include"gamewidget.h"
#include<QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(891,510);
    this->setWindowTitle("王鹏的贪吃蛇你说帅不帅");
    this->setWindowIcon(QIcon(":/Picture/img/WindowPicture.jpg"));
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/Picture/img/Back2.jpg")));
    this->setStyleSheet("background-image:url(qrc:/new/Gamewindow/img/GameBack.jpg)");
    this->setPalette(palette);

    startPush=new QPushButton(this);
    exitPush=new QPushButton(this);
    startPush->setIconSize(QSize(920,45));
    startPush->setGeometry(400,360,90,45);
    startPush->setIcon(QIcon(":/Picture/img/Start.png"));
    startPush->setFlat(1);
    exitPush->setIconSize(QSize(90,45));
    exitPush->setGeometry(400,420,90,45);
    exitPush->setIcon(QIcon(":/Picture/img/Exit.png"));
    exitPush->setFlat(1);//设置按钮的透明属性

    exitBox=new QMessageBox;
    connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));
    connect(startPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
}

Widget::~Widget()
{

}

void Widget::M_startPush()
{
    gamewindow=new Gamewidget(this);  //创建一个新的界面，任然以原来的界面为父窗口，退出后可以直接回到上一个界面。
    gamewindow->show();

}

void Widget::M_exitPush()
{
    if(QMessageBox::Yes==QMessageBox::question(this,"Tips：","Do you want to leave the game?",QMessageBox::Yes|QMessageBox::No))
    {
        delete this;
        exit(0);
    }
}
