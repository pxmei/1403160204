#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDebug>


class student//创建一个类，定义数据类型student
{
public:
    int num;  //定义学号
    QString name;  //定义姓名
    float cour1;  //定义课程1
    float cour2;  //定义课程2
};   //创建一个类，定义数据类型student


bool comparename(const student &student1,const student &student2)//定义姓名比较函数
{
    if(student1.name>student2.name)
    {
        return true;
    }
    if(student1.name<student2.name)
    {
        return false;
    }
    return 0;
}

bool comparecour1(const student &student1,const student &student2)//定义课程1成绩比较函数
{
   if(student1.cour1>student2.cour1)
   {
       return true;
   }
   if(student1.cour1<student2.cour1)
   {
       return false;
   }
   return 0;
}

bool comparecour2(const student &student1,const student &student2)//定义课程2成绩比较函数
{
   if(student1.cour2>student2.cour2)
   {
       return true;
   }
   if(student1.cour2<student2.cour2)
   {
       return false;
   }
   return 0;
}


int main(int argc, char *argv[])
{
    argv=argv;
    argc=argc;//消除对未使用变量的警告
    student stu1,stu2,stu3,stu4;//定义四个学生，录入数据
    stu1.num=1403130209;
    stu1.name="lzs鲁智深";
    stu1.cour1=80;
    stu1.cour2=72;
    stu2.num=1403140101;
    stu2.name="lc林冲";
    stu2.cour1=82;
    stu2.cour2=76;
    stu3.num=1403140102;
    stu3.name="sj宋江";
    stu3.cour1=76;
    stu3.cour2=85;
    stu4.num=1403140103;
    stu4.name="ws武松";
    stu4.cour1=88;
    stu4.cour2=80;
    QList<student> grade;//定义一个list，将四个类放入其中
    grade<<stu1<<stu2<<stu3<<stu4;

    qDebug()<<"以姓名为标准排序结果如下："<<"\n"
           <<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<"\t"<<"课程2";
    std::sort(grade.begin(),grade.end(),comparename);//利用sort函数进行排序
    for(int i=0;i<4;i++)
    {
        qDebug()<<grade.at(i).num<<"\t"<<grade.at(i).name<<"\t"
               <<grade.at(i).cour1<<"\t"<<grade.at(i).cour2;
    }

    qDebug()<<"———————————————————————"
           <<"\n"<<"以课程1成绩为标准排序结果如下："<<"\n"
          <<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<"\t"<<"课程2";
    std::sort(grade.begin(),grade.end(),comparecour1);
    for(int i=0;i<4;i++)
    {
        qDebug()<<grade.at(i).num<<"\t"<<grade.at(i).name<<"\t"
               <<grade.at(i).cour1<<"\t"<<grade.at(i).cour2;
    }

    qDebug()<<"———————————————————————"
           <<"\n"<<"以课程2成绩为标准排序结果如下："<<"\n"
          <<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<"\t"<<"课程2";
    std::sort(grade.begin(),grade.end(),comparecour2);
    for(int i=0;i<4;i++)
    {
        qDebug()<<grade.at(i).num<<"\t"<<grade.at(i).name<<"\t"
               <<grade.at(i).cour1<<"\t"<<grade.at(i).cour2;
    }
}

