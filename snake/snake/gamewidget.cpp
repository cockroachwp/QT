#include "gamewidget.h"
#include"widget.h"
#include<QDebug>

int Gamewidget::m_setDiretion=4;
Gamewidget::Gamewidget(QWidget *parent) : QWidget(parent)
{
    qsrand(time(NULL));//随机数的种子
    Score=0;
    Difficulty=1;
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(891,510);
    this->setWindowTitle("李子的贪吃蛇");
    this->setWindowIcon(QIcon(":/Picture/img/WindowPicture.jpg"));

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/Gamewindow/img/GameBack.jpg").scaled(this->size())));
    this->setPalette(palette);


    upPush =new QPushButton(this);
    downPush=new QPushButton(this);
    leftPush=new QPushButton(this);
    rightPush=new QPushButton(this);
    StartPush=new QPushButton(this);
    ExitPush=new QPushButton(this);

    buttonGroup=new QButtonGroup(this);
    buttonGroup->addButton(upPush,1);
    buttonGroup->addButton(downPush,2);
    buttonGroup->addButton(leftPush,3);
    buttonGroup->addButton(rightPush,4);
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(M_setDiretion(int)));


    upPush->setIconSize(QSize(45,90));
    upPush->setGeometry(750,160,45,90);
    upPush->setIcon(QIcon(":/new/Gamewindow/img/up.png"));
    upPush->setFlat(1);
    downPush->setIconSize(QSize(45,90));
    downPush->setGeometry(750,260,45,90);
    downPush->setIcon(QIcon(":/new/Gamewindow/img/down.png"));
    downPush->setFlat(1);
    leftPush->setIconSize(QSize(90,45));
    leftPush->setGeometry(650,230,90,45);
    leftPush->setIcon(QIcon(":/new/Gamewindow/img/left.png"));
    leftPush->setFlat(1);
    rightPush->setIconSize(QSize(90,45));
    rightPush->setGeometry(800,230,90,45);
    rightPush->setIcon(QIcon(":/new/Gamewindow/img/right.png"));
    rightPush->setFlat(1);

    StartPush->setIconSize(QSize(90,45));
    StartPush->setGeometry(650,400,90,45);
    StartPush->setFlat(1);
    StartPush->setIcon(QIcon(":/Picture/img/Start.png"));


    ExitPush->setIconSize(QSize(90,45));
    ExitPush->setGeometry(780,400,90,45);
    ExitPush->setIcon(QIcon(":/Picture/img/Exit.png"));
    ExitPush->setFlat(1);

    ScoreLabel=new QLabel(this);
    LevelLabel=new QLabel(this);
    ScoreLabel->setText("Score:");
    ScoreLabel->setGeometry(690,10,120,90);
    LevelLabel->setText("Level:");
    LevelLabel->setGeometry(690,50,120,90);

    ScoreLabelNumber=new QLabel(this);
    LevelLabelNumber=new QLabel(this);
    ScoreLabelNumber->setText(QString::number(Score)+"分");
    ScoreLabelNumber->setGeometry(750,10,120,90);
    LevelLabelNumber->setText(QString::number(Difficulty)+"级");
    LevelLabelNumber->setGeometry(750,50,120,90);

    Timer=new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_timeout()));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    connect(ExitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));

    snake[0][0]=(rand()%18+1)*30+30;
    snake[0][1]=(rand()%15+1)*30+30;
    m_setDiretion=(rand()%4)+1;
    foodx=(rand()%20)*30;
    foody=(rand()%15)*30;
    bodycount=1;  //包含蛇的头和尾巴
    Nobite=true;
    this->repaint();

}
void Gamewidget::keyPressEvent(QKeyEvent *e)//按键处理
{
    switch(e->key())
    {
    case Qt::Key_Up:if(m_setDiretion!=2)m_setDiretion=1;  break;
    case Qt::Key_W:if(m_setDiretion!=2)m_setDiretion=1;  break;
    case Qt::Key_Down:if(m_setDiretion!=1)m_setDiretion=2;  break;
    case Qt::Key_S:if(m_setDiretion!=1)m_setDiretion=2;  break;
    case Qt::Key_Left:if(m_setDiretion!=4)m_setDiretion=3;  break;
    case Qt::Key_A:if(m_setDiretion!=4)m_setDiretion=3;  break;
    case Qt::Key_Right:if(m_setDiretion!=3)m_setDiretion=4;  break;
    case Qt::Key_D:if(m_setDiretion!=3)m_setDiretion=4;  break;
    default:                   break;

    }
}
void Gamewidget::paintEvent(QPaintEvent*)//绘图事件
{
    QPainter painter(this);
    if(0<=snake[0][0]&&snake[0][0]<=600&&0<=snake[0][1]&&snake[0][1]<=480&&Nobite)
    {
        qDebug()<<snake[0][0];
        for(int i=bodycount;i>0;i--)
        {
            if(i==bodycount)//画出尾巴部分
            {
                if(snake[i][0]==snake[i-1][0]&&snake[i][1]<snake[i-1][1])
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/taildown.png"));
                }
                else  if(snake[i][0]==snake[i-1][0]&&snake[i][1]>snake[i-1][1])
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/tailup.png"));
                }
                else  if(snake[i][0]<snake[i-1][0]&&snake[i][1]==snake[i-1][1])
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/tailright.png"));
                }
                else  if(snake[i][0]>snake[i-1][0]&&snake[i][1]==snake[i-1][1])
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/tailleft.png"));
                }
            }
            else
            {
                if((snake[i][0]==snake[i-1][0]&& snake[i][1]<snake[i-1][1]&&snake[i+1][0]<snake[i][0]&&snake[i+1][1]==snake[i][1])||
                        ((snake[i][0]>snake[i-1][0])&& snake[i][1]==snake[i-1][1]&&snake[i+1][0]==snake[i][0]&&snake[i+1][1]>snake[i][1]))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/leftdown.png"));
                }
                else if((snake[i][0]<snake[i-1][0]&& snake[i][1]==snake[i-1][1]&&snake[i+1][0]==snake[i][0]&&snake[i+1][1]>snake[i][1])||
                        (snake[i][0]==snake[i-1][0]&& snake[i][1]<snake[i-1][1]&&snake[i+1][0]>snake[i][0]&&snake[i+1][1]==snake[i][1]))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/rightdown.png"));
                }
                else if((snake[i][0]>snake[i-1][0]&& snake[i][1]==snake[i-1][1]&&snake[i+1][0]==snake[i][0]&&snake[i+1][1]<snake[i][1])||
                        (snake[i][0]==snake[i-1][0]&& snake[i][1]>snake[i-1][1]&&snake[i+1][0]<snake[i][0]&&snake[i+1][1]==snake[i][1]))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/leftup.png"));
                }
                else if(((snake[i][0]==snake[i-1][0])&& snake[i][1]>snake[i-1][1]&&snake[i+1][0]>snake[i][0]&&snake[i+1][1]==snake[i][1])||
                        (snake[i][0]<snake[i-1][0]&& snake[i][1]==snake[i-1][1]&&snake[i+1][0]==snake[i][0]&&snake[i+1][1]<snake[i][1]))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/rightup.png"));
                }

                else if((snake[i][0]==snake[i-1][0]&&snake[i][0]==snake[i+1][0])&&((snake[i][1]<snake[i-1][1]&&snake[i+1][1]<snake[i][1])||
                                                                                   (snake[i][1]>snake[i-1][1]&&snake[i+1][1]>snake[i][1])))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/downup.png"));

                }
                else if ((snake[i][1]==snake[i-1][1]&&snake[i][1]==snake[i+1][1])&&((snake[i][0]<snake[i-1][0]&&snake[i+1][0]<snake[i][0])||
                                                                                    (snake[i][0]>snake[i-1][0]&&snake[i+1][0]>snake[i][0])))
                {
                    painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/img/leftright.png"));

                }
            }
        }
    }
    painter.drawImage(QRect(foodx,foody,30,30),QImage(":/new/Gamewindow/img/Apple.png"));

    painter.setPen(Qt::green);

    for(int i=0;i<=widthnumber;i++)
    {
        for(int j=0;j<=longnumber;j++)
        {
            painter.drawRect(QRect(30*j,30*i,30,30));
        }
    }
    switch (m_setDiretion)
    {
    case 1: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headup.png"));
        if(bodycount==1)  painter.drawImage(QRect(snake[0][0],snake[0][1]+30,30,30),QImage(":/new/Gamewindow/img/tailup.png"));
        break;
    case 2: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headdown.png"));
        if(bodycount==1) painter.drawImage(QRect(snake[0][0],snake[0][1]-30,30,30),QImage(":/new/Gamewindow/img/taildown.png"));
        break;
    case 3: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headleft.png"));
        if(bodycount==1) painter.drawImage(QRect(snake[0][0]+30,snake[0][1],30,30),QImage(":/new/Gamewindow/img/tailleft.png"));
        break;
    case 4: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headright.png"));
        if(bodycount==1)  painter.drawImage(QRect(snake[0][0]-30,snake[0][1],30,30),QImage(":/new/Gamewindow/img/tailright.png"));
        break;
    default:
        break;
    }
}

void Gamewidget::M_timeout()
{
    if(snake[0][0]==foodx&&snake[0][1]==foody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        foodx=(rand()%20)*30;
        foody=(rand()%15)*30;
        bodycount++;  //蛇的身体加一
        Difficulty=bodycount/5+1;
        Score=Score+Difficulty;
        ScoreLabelNumber->setText(QString::number(Score)+"分");
        LevelLabelNumber->setText(QString::number(Difficulty)+"级");
        Timer->start(800-Difficulty>0? 800-Difficulty*80:80/(Difficulty-8));
    }
    memcpy(snake1,snake,sizeof(snake));
    for(int i=bodycount;i>0;i--)//将蛇身体的前一个坐标赋值给后一个坐标，实现蛇身体的连续出现
    {

        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
    }
    QPainter painter(this);

    for(int i=bodycount;i>3;i--)
    {
        if(snake[0][0]==snake[i][0]&&snake[0][1]==snake[i][1])
        {
            Nobite=false;
        }
    }

    switch (m_setDiretion)
    {
    case 1: snake[0][1]=snake[0][1]-30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headup.png"))
                ;break;
    case 2: snake[0][1]=snake[0][1]+30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headdown.png"))
                ; break;
    case 3: snake[0][0]=snake[0][0]-30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headleft.png"))
                ; break;
    case 4: snake[0][0]=snake[0][0]+30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/img/headright.png"))
                ;break;
    default:
        break;
    }
    if(0>snake[0][0]||snake[0][0]>600||0>snake[0][1]||snake[0][1]>480)
    {
        memcpy(snake,snake1,sizeof(snake));
        Nobite=false;
    }

    this->update();
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_CheckGameOver()));
}

void Gamewidget::M_startPush()//时间函数开始计时
{
    Timer->start(100);
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush->setIcon(QIcon(":/Picture/img/Pause.png"));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));
}
void Gamewidget::M_pausePush()//实现开始与暂停按钮的管理
{
    Timer->stop();
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush->setIcon(QIcon(":/Picture/img/Start.png"));
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));
}


void Gamewidget::M_setDiretion(int index)//接收按钮组的整数，确定方向
{
    switch (index)
    {
    case 1:if(m_setDiretion!=2)m_setDiretion=1;  break;
    case 2:if(m_setDiretion!=1)m_setDiretion=2;  break;
    case 3:if(m_setDiretion!=4)m_setDiretion=3;  break;
    case 4:if(m_setDiretion!=3)m_setDiretion=4;  break;
    default:                   break;
    }
}

void Gamewidget::M_exitPush()
{
    this->close();
    delete this;
}


void Gamewidget::M_CheckGameOver()//该部分原本在绘图事件函数中，但是由于在其中的时候程序总是意外关闭，故将其提出
{


    if(0>snake[0][0]||snake[0][0]>600||0>snake[0][1]||snake[0][1]>480||(!Nobite))
    {
        Nobite=true;//将其设置为真,进入绘图函数画出蛇的身体
        this->update();//调用绘图事件函数
        Timer->stop();
        if(QMessageBox::Yes==QMessageBox::information(this,"Tips：","Game Over!",QMessageBox::Yes))
        {
            this ->hide();
            delete this;
            return;
        }

    }

}







