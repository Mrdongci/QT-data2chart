#ifndef IMAGEDITSCENE_H
#define IMAGEDITSCENE_H
#include <QtCharts>
#include <QMainWindow>
#include<QPushButton>
class imageditscene:public QMainWindow
{
    Q_OBJECT
public:
    imageditscene(QStringList x,QStringList y);
//     imageditscene();
private:

    QPushButton *backBtn;






signals:
   void dataSceneBack();
};

#endif // IMAGEDITSCENE_H
