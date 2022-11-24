#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<QTimer>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    this->setWindowFlags(Qt::Dialog);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);//这样会把标题栏都去掉。
    //设置标题和图标
    this->setWindowTitle("数据图转化工具");
    this->setFixedSize(320,300);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    QLabel *start_Btn=new QLabel(this);
    start_Btn->resize(100,40);
    start_Btn->setText("Qt简易出图程序");
    start_Btn->move(0.5*(this->width()-start_Btn->width()),0.618*(this->height()-start_Btn->height()));


    //实例化选择关卡
    mainScence=new data_input;
    //延时进入到选择窗口,0.5秒让当前页面进入表达式中的函数
    QTimer::singleShot(1000,this,[=]()
    {
        //进入到主场景
        mainScence->show();
        //将自已隐藏
        this->hide();});
    //connect(start_Btn,&QPushButton::clicked,[=]()
    //{
    //    qDebug()<<"start按钮点击了！！！";

    //    //延时进入到选择窗口,0.5秒让当前页面进入表达式中的函数
    //    QTimer::singleShot(500,this,[=]()
    //    {
    //        //进入到主场景
    //        mainScence->show();
    //        //将自已隐藏
    //        this->hide();});
    //});



}

MainWindow::~MainWindow()
{
    delete ui;
}

