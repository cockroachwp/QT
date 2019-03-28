#include "widget.h"
#include "ui_widget.h"
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->frame->setAutoFillBackground(true);
    ui->frame->setPalette(QPalette(QColor(Qt::black)));
    //ui->spinBox->setValue(5);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)
{
    QPen pen(QColor(Qt::black));
       QBrush brush(QColor(Qt::white));

       QPainter painter(this);
       painter.setPen(pen);
       painter.setBrush(brush);
       painter.drawRect(QRect(0, 0, width() * 2 / 3, height()));

       pen.setColor(ui->frame->palette().color(QPalette::Background));
        pen.setWidth(ui->horizontalSlider->value());
       pen.setStyle(Qt::DashLine);
       painter.setPen(pen);

       brush.setColor(Qt::blue);
       brush.setStyle(Qt::Dense4Pattern);
       painter.setBrush(brush);
       if (ui->comboBox->currentText() == "line")
               painter.drawLine(start, end);
           else
               painter.drawRect(QRect(start, end));

}
void Widget::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
    if (start.x() > width() * 2 / 3)
        start.setX(width() * 2 / 3);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    end = event->pos();
    if (end.x() > width() * 2 / 3)
        end.setX(width() * 2 / 3);
    update();
}

void Widget::on_pushButton_clicked()
{
    QColor c = QColorDialog::getColor(Qt::black, this, "Get Color");
        ui->frame->setPalette(QPalette(c));
}
