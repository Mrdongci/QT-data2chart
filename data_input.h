/*
主界面



*/
#ifndef DATA_INPUT_H
#define DATA_INPUT_H

#include <QMainWindow>
#include<QPushButton>
#include<QLineEdit>
#include<QTextEdit>
#include<QTableWidget>
#include<QLabel>
class data_input: public QMainWindow
{
     Q_OBJECT
public:

    explicit  data_input(QMainWindow *parent = nullptr);
private:

    QStringList lineList_x;//向图片场景传入参数x坐标,实参
    QStringList lineList_y;//向图片场景传入参数y坐标

    QLineEdit *pathText;   //路径显示框
    QTextEdit *textDisplay;//读取的文件文本显示
    QTableWidget *tableWidget;//存放数据的表格

   QPushButton * chooseDocument_Btn;//点击选择文件，以读取数据
    QPushButton *imageModule_Btn;//图例模板按钮，打开保存好的图形参数设置，方便使用
    QPushButton *save_Btn;//保存数据按钮，并跳到下一界面

    QLabel * scatterDiagram_Lab;//散点图
    QLabel *lineChart_Lab;//折现图
    QLabel * pointPlot_Lab;//点线图
    QPushButton * scatterDiagram_Btn;//散点图
     QPushButton *lineChart_Btn;//折现图
     QPushButton *pointPlot_Btn;//点线图

     void keyPressEvent(QKeyEvent *event);

     void Copy();



     void Paste();
//     void copySelectFromTable();
//     void pasteToTable();
};

#endif // DATA_INPUT_H
