#include "exer01widget.h"
#include "ui_exer01widget.h"
#include<QVector>
#include<ctime>
#include<QDebug>

void exer01Widget::on_pushButton_clicked()
{
    QVector<float> v;
    for (int i=0;i<5;i++)
    {
        v.push_back(float((rand()%100))/10.0);
    }
    qDebug()<<v;
    QString s="";
    foreach(float f,v)
    {
        s += QString("%1").arg(f);
    }
    ui->textEdit->insertPlainText(QString("%1%2").arg(s,"\n"));
}

exer01Widget::exer01Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exer01Widget)
{
    ui->setupUi(this);
    srand((unsigned int)time(NULL));
}

exer01Widget::~exer01Widget()
{
    delete ui;
}

