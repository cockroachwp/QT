#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void  Widget::keyPressEvent(QKeyEvent *event)
{
     if(event->key()==Qt::Key_Down)
    {
    QPoint pos = ui->labelMove->pos();
    if(pos.y()<this->height()-5)
        pos.setY(pos.y()+5);
    else
         pos.setY(0);
    ui->labelMove->move(pos);

     }


     if(event->key()==Qt::Key_Up)
    {
    QPoint pos = ui->labelMove->pos();
    if(pos.y()<5)
       pos.setY(this->height()-5);
    else
          pos.setY(pos.y()-5);
    ui->labelMove->move(pos);

     }

}
void Widget::mousePressEvent(QMouseEvent *event)
{
    ui->labelMove->move(event->pos());
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    ui->labelMove->move(event->pos());
}

