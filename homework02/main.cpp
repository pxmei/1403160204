#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>

namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}


typedef struct{  // 用QStringList定义一个存放信息结构studData
    //int num;
    //QString name;
    //QVector<int> cour;
    QStringList stu;
} studData;

QDebug operator<< (QDebug d, const studData &data){  //QDebug左移操作符重载，实现输出结构studData
    //QDebugStateSaver saver(d);
    //d.nospace()<<data.num<<"\t"<<data.name<<"\t"<<data.cour;
    for(int i=0;i<data.stu.size();i++){
       d.noquote().nospace()<<QString(data.stu.at(i))<<"\t";
   }
   return d;
}

// 比较类，用于std::sort第三个参数
class myCmp{  //定义类myCmp排序
public:
    myCmp(int selectedColumn){this->currentColumn = selectedColumn;}
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};

bool myCmp::operator()(const studData &d1, const studData &d2){  //定义排序方式
    return d1.stu.at(currentColumn+1)>d2.stu.at(currentColumn+1);
    /*bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    case SK::col01:
        result=(d1.num>d2.num);
        break;
    case SK::col02:
        result=(d1.name>d2.name);
        break;
    default:
        result=(d1.cour>d2.cour);
        break;*/
}

class ScoreSorter{ //定义整体结构
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString FilePath;
    QList<studData> data;
    studData listtitle;
    void myMessageOutput(quint8 lie);
};

ScoreSorter::ScoreSorter(QString dataFile){  //初始化文件名
    this->FilePath=dataFile;
}

void ScoreSorter::readFile(){  //读取文档
    QFile file(this->FilePath);   //只读方式打开文件
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"文件打开失败！"<<endl;
        }
        QString titile(file.readLine());  //读取表头
        this->listtitle.stu = titile.split(" ", QString::SkipEmptyParts);
        if((this->listtitle.stu).last() == "\n") this->listtitle.stu.removeLast();  // 除去末尾的'\n'
        studData perdata;
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            QString str(line);
            perdata.stu = str.split(" ", QString::SkipEmptyParts);
            if((perdata.stu).last() == "\n") perdata.stu.removeLast();
            if(perdata.stu.size()==0) continue;
            this->data.append(perdata);
        }
        file.close();
}
void ScoreSorter::doSort(){  //排序并输出
    for(int i=1;i<this->listtitle.stu.size();i++){
           myCmp thiscmp(i-1);    //初始化规则对象
           std::sort(this->data.begin() , this->data.end() , thiscmp );  //排序
           qDebug()<<"当前排序第 "<<i+1 <<" 列：";
           qDebug() << '\t'<< (this->listtitle);    //qDebug重载输出
           for(int i=0;i<this->data.size();i++)
               qDebug() << this->data.at(i);
           qDebug()<<"------------------------------------------------------------------\n";
       }
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){  //输出至文档
    Q_UNUSED(type);
    Q_UNUSED(context);
    QFile file("D:/Dev/project/homework2/homework02/sorter_data.txt");
    file.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");  //编码方式
    stream<<msg<<endl;
    file.flush();
    file.close();
    QTextStream ts(stdout);
    ts<<msg<<endl;
    file.flush();
    file.close();
}

int main(){
    qInstallMessageHandler(myMessageOutput);//输出文档
    QString datafile = "D:/Dev/project/homework2/homework02/data.txt";
    QFile f("sorted_"+datafile);
    if (f.exists()){  // 如果排序后文件已存在，则删除之
        f.remove();
    }

    ScoreSorter s(datafile);
    s.readFile();//读取文档
    s.doSort();//排序并输出
    return 0;
}
