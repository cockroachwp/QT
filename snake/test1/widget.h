#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QKeyEvent>
#include<QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
 protected:
     void keyPressEvent(QKeyEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      //void mousePressEvent(QMouseEvent *event);
      void mousePressEvent(QMouseEvent *event);
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
