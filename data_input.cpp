#include "data_input.h"
#include<QMenuBar>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>
#include<imageditscene.h>
#include<QTimer>

data_input::data_input(QMainWindow*parent)
    :QMainWindow{parent}
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


    /////////////////////////////////////////主界面右侧功能区//////////////////////////////

    chooseDocument_Btn=new QPushButton(this);//导入数据按钮
    chooseDocument_Btn->setText("导入数据");
    chooseDocument_Btn->resize(100,40);
    chooseDocument_Btn->move(0.618*this->width(),mybar->height());

    imageModule_Btn=new QPushButton(this);//图例模板按钮，打开保存好的图形参数设置，方便使用
    imageModule_Btn->setText("图例模板");
    imageModule_Btn->resize(100,40);
    imageModule_Btn->move(0.618*this->width(),mybar->height()+ imageModule_Btn->height());

    save_Btn=new QPushButton(this);//保存数据按钮，并跳到下一界面
    save_Btn->setText("图片预览");
    save_Btn->resize(100,40);
    save_Btn->move(0.8*this->width(),this->height()-save_Btn->height());

    scatterDiagram_Btn=new QPushButton(this);//散点图
    scatterDiagram_Btn->setText("散点图");
    scatterDiagram_Btn->resize(100,40);
    scatterDiagram_Btn->move(0.618*this->width(),0.618*this->height());

    lineChart_Btn=new QPushButton(this);//折现图
    lineChart_Btn->setText("折线图");
    lineChart_Btn->resize(100,40);
    lineChart_Btn->move(0.618*this->width(),0.618*this->height()+  lineChart_Btn->height());

    pointPlot_Btn=new QPushButton(this);//点线图
    pointPlot_Btn->setText("点线图");
    pointPlot_Btn->resize(100,40);
    pointPlot_Btn->move(0.618*this->width(),0.618*this->height()+  2* pointPlot_Btn->height());



    ///////////////////////处理数据的方式 QTextStream 方式打开文件/////////////////////////


    pathText=new QLineEdit(this);
    pathText->resize(150,chooseDocument_Btn->height());
    pathText->move(0.618*this->width()+chooseDocument_Btn->width(),mybar->height());

    tableWidget=new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->resize(0.618*this->width(),this->height()-mybar->height()+5);
    tableWidget->move(0,mybar->height()-5);

    QStringList headerText;
        headerText<<"横坐标"<<"纵坐标";
    tableWidget->setHorizontalHeaderLabels(headerText);
    //表头显示方式
       tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //===============控件tableWidget操作新增数据===========================
    //                int rowcount = tableWidget->rowCount();           //获取当前行数
    //                if (rowcount < i+1)                                  //如果添加的数据所在的行数大于实际控件存在的列数，则新增一列
    //                {
    //                   tableWidget->insertRow(rowcount);                 //新增行
    //                }

    tableWidget->resizeColumnToContents(0);


    connect(chooseDocument_Btn,&QPushButton::clicked,[=](){

        QString path_2=QFileDialog::getOpenFileName(this,"打开文件","D:\\Document");

        QFile f(path_2);

        if(!f.open(QIODevice::ReadOnly| QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(f.errorString()));
            return;
        }
        pathText->setText(path_2);
        QTextStream output(&f);

        QString lineStr;//文件的每一行的字符串
        QStringList lineList_1; //整行字符串，分割处理为单个字符串，存入到表中



        lineList_1.clear();//操作前，清空

        while(!output.atEnd())
        {


            lineStr = output.readLine(); //读取文件的一行
            lineList_1 = lineStr.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts); //去除换行符获取字符串，存放到表中
            //            lineList_2 << lineList_1.split('\t'); //去除换行符获取字符串，存放到表中

            //            qDebug()<<"lineStr"<<lineStr;
            //            qDebug()<<"lineList_1"<<lineList_1;
            //            qDebug()<<"lineList_2"<<lineList_2;
            //            qDebug()<<tableWidget->rowCount();
            //            qDebug()<<"lineList_1.lenth()"<<lineList_1.length();
            //            qDebug()<<"lineList_2.lenth()"<<lineList_2.length();
            int rowCount = tableWidget->rowCount();
            tableWidget->insertRow(rowCount);


            lineList_x<<lineList_1[0];
            lineList_y<<lineList_1[1];

            for(int i = 0; i < 2; i++)
            {
                //向表里面动态添加参数

                tableWidget->setItem(rowCount,i,new QTableWidgetItem(lineList_1[i]));
            }
        }

        //qDebug()<<"lineList_x[4]"<<lineList_x[4];
        //qDebug()<<"lineList_y[4]"<<lineList_y[4];

        f.close();//关闭文件

    });

    /////////////////////////////////监听保存按钮的点击事件/////////////////////////////
    connect(save_Btn,&QPushButton::clicked,[=]()
    {
        QString str=QString("保存当前属性");
        qDebug()<<str;
        //选择界面隐藏
        this->hide();
        //进入游戏场景,实例化
        imageditscene * image =new imageditscene(lineList_x,lineList_y);
        //          imageditscene * image =new imageditscene();
        image->show();

        //图片界面的返回功能
        connect(image,&imageditscene::dataSceneBack,[=]()
        {
            //            qDebug()<<"检验，触发效果";
            QTimer::singleShot(500,this,[=]()
            {
                delete image;//将游戏场景隐藏
                this->show();//重新显示选择场景
                //                image = NULL;
            });
        });
    });
}



void data_input::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Copy))
    {
        Copy();
    }
    if(event->matches(QKeySequence::Paste))
    {
        Paste();
    }
}

void data_input::Copy()
{
    QList<QTableWidgetItem*> tableWidgetItem = tableWidget->selectedItems();
    if(tableWidgetItem.count()==0) //如果没有选择，返回
        return;

    //选择范围
    int topRow ,buttomRow, leftColumn, rightColumn;
    QList<QTableWidgetSelectionRange> tableSelectRange= tableWidget->selectedRanges();
    for(int i=0;i<tableSelectRange.count();i++)
    {
        topRow= tableSelectRange.at(i).topRow();
        buttomRow=tableSelectRange.at(i).bottomRow();
        leftColumn=tableSelectRange.at(i).leftColumn();
        rightColumn=tableSelectRange.at(i).rightColumn();
    }

    //复制到cliptext
    QString clipText;
    for (int i=topRow;i<=buttomRow;i++) {
        for (int j=leftColumn;j<=rightColumn;j++) {
            QString text;
            if( tableWidget->item(i,j)!=nullptr )//这个很重要
                text = tableWidget->item(i,j)->text();
            clipText.append(text);
            clipText.append("\t");
        }
        clipText.chop(1);//删除末尾一个字符
        clipText.append("\n");
    }

    QClipboard *clipboard = QApplication::clipboard();//复制到剪贴板，可以粘贴到excel
    clipboard->setText(clipText);
    qDebug()<<clipText;
    qDebug()<<clipboard->text();

}


void data_input::Paste()
{

    // 粘贴，从选中的第一个单元格开始

    QList<QTableWidgetSelectionRange> sRangeList = tableWidget->selectedRanges();
    int allRow = tableWidget->rowCount();
    int allCol = tableWidget->columnCount();
    QClipboard *clipboard = QApplication::clipboard();//从excle复制到剪贴板，可以粘贴到tablewidget
    for(const auto &p : qAsConst(sRangeList)) {
        QString str = clipboard->text();
        int ColCnt = tableWidget->columnCount();
        QList<QString> RowStr = str.split("\n");
        int copyAreaAllRow = RowStr.size();
        qDebug()<<"copyAreaAllRow"<<copyAreaAllRow;
        int x = p.topRow();
        int rightIndex = p.rightColumn();
        int surplusRow = allRow - x;
        int surplusCol = allCol - rightIndex;
        if((RowStr.size() -1) > surplusRow)//如果复制的行数大于剩余的行数，去除掉多余的赋值内容
        {
            int len = RowStr.size();
            for(int i=len -2;i>=surplusRow;i--)
            {
                RowStr.removeAt(i);
            }
        }


        for(const auto &Row : qAsConst(RowStr)) {
            if(!Row.isEmpty()) {
                QList<QString> ColStr = Row.split("\t");//赋值的列数
                if(ColStr.size() > surplusCol)//如果复制的列数大于剩余的列数，去除掉多余的赋值内容
                {
                    int len = ColStr.size();
                    for(int i=len -1;i>=surplusCol;i--)
                    {
                        ColStr.removeAt(i);
                    }
                }
                int y = p.leftColumn();
                for(const auto &Col : qAsConst(ColStr)) {
                    QTableWidgetItem* item = tableWidget->item(x, y);
                    if(item == nullptr)
                    {
                        tableWidget->setItem(x, y, new QTableWidgetItem(Col));
                        tableWidget->item(x,y)->setForeground(QBrush(QColor(255,0,0)));
                    }
                    else
                    {
                        tableWidget->item(x, y)->setText(Col);
                        tableWidget->item(x,y)->setForeground(QBrush(QColor(255,0,0)));
                    }
                    if(y + 1 == ColCnt)
                        break;
                    ++y;
                }
                ++x;
            }
        }
    }
}

