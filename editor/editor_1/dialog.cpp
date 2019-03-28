#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //setStyleSheet(":images/color.png");

   // QWidget *widget = new QWidget();


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_toolButton_clicked()
{
    reject();
}
