#include "imageditscene.h"
#include<QMenuBar>
#include<QDebug>
imageditscene::imageditscene(QStringList x,QStringList y)
//imageditscene::imageditscene()
{
    ////////////////////////////////////////////创建菜单栏/////////////////////////////////////
    QMenuBar *mybar=menuBar();//创建
    setMenuBar(mybar);//放入窗口(父窗)
    //创建菜单
    QMenu * fileMenu=mybar->addMenu("开始");//可以多次调用此函数添加条目
    //创建菜单项
    QAction * quit=fileMenu->addAction("退出");//可以多次调用此函数添加条目

    //设置标题、图标和固定大小
    this->setWindowTitle("主界面");
    this->resize(1000,600);
    //this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //退出按钮实现
    connect(quit,&QAction::triggered,[=]()
    {
        this->close();
    });

    //返回按钮，注意是返回到选关界面
    backBtn=new QPushButton(this);
        //    this->show();//为什么这个位置必须要加一个show（）函数？？？？？？？
    backBtn->move(0.4*this->width(),this->height()-backBtn->height()-10);
    backBtn->resize(100,40);
    backBtn->setText("返回");
    qDebug()<<backBtn->height();
    //返回按钮需要实现的两个功能，1返回上一层界面，2本身的动画演示过程，实现一个动画
    connect(backBtn,&QPushButton::clicked,[=](){
        qDebug()<<"游戏界面中，点击了返回按钮！！！";
        //告诉选关场景，我返回了
        emit this->dataSceneBack();
    });





    ///////////////////////开始画图//////////////////////////////////////
    QChartView *chartView=new QChartView (this);//创建ChartView
    QChart *chart=new QChart();//创建Charrt
    chart->setTitle("绘制图像");
    chartView->setChart(chart);
    chartView->resize(0.5*this->width(),this->height()-20);
    chartView->move(0.5*this->width(),mybar->height());

    QPushButton * drawBtn=new QPushButton(this);
    drawBtn->setText("绘制图片");
    drawBtn->move(80,320);

    ////////////////////创建数列/////////////////////
    QSplineSeries *series=new QSplineSeries();
//    qDebug()<<"lineList_x.length:"<<lineList_x.length();

    series->setName("光滑曲线图");
    //////////////////创建坐标轴////////////////////
    QValueAxis *axisX=new QValueAxis;
    axisX->setRange(-1,3);
    axisX->setTitleText("X");

    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(-1.5,1.5);
    axisY->setTitleText("Y");


    connect(drawBtn,&QPushButton::clicked,[=](){

        for(int i=0;i<x.length();i++)
        {
            series->append(x[i].toDouble(),y[i].toDouble());

        }


        chart->addSeries(series);
        chart->setAxisX(axisX,series);
        chart->setAxisY(axisY,series);

    });

}
