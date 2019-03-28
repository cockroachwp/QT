#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   resize(800,600);
   textEdit = new QTextEdit(this);
   setCentralWidget(textEdit);

   actionlove = new QAction(QIcon(":images/love.ico"), "&Open",NULL);
   actionlove->setShortcut(QKeySequence("Ctrl+O"));
   ui->mainToolBar->addAction(actionlove);

   actionnew = new QAction( "&New",NULL);
   actionnew->setShortcut(QKeySequence("Ctrl+N"));

   actionSave = new QAction( "&Save",NULL);
   actionSave->setShortcut(QKeySequence("Ctrl+S"));



   connect(actionlove,SIGNAL(triggered()),this,SLOT(onOpenFile()));

  fileMenu=ui->menuBar->addMenu("&File");
  fileMenu->addAction(actionnew);
  fileMenu->addAction(actionlove);
  fileMenu->addAction(actionSave);
  fileMenu->addSeparator();
  fileEdit=ui->menuBar->addMenu("&编辑");
  //ui->mainToolBar->addAction(actionlove);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString fileName =QFileDialog::getOpenFileName(this,
                                                   "Open atext file",
                                                   "Text Files(*.text)"
                                                     );
   // QDebug()<<fileName;
}
