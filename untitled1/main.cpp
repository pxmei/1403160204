#include <QCoreApplication>
#include <QDebug>
#include <QList>
typedef quint32 word;
typedef quint8 byte;  //定义word为32位 byte为8位
#define WORD_LLO(xxx) ((byte) ((word)(xxx) & 255))  //取最低8位
#define WORD_HLO(xxx) ((byte) ((word)(xxx) >> 8))  //左移8位取次低8位
#define WORD_LHI(xxx) ((byte) ((word)(xxx) >> 16))  //左移16位取次高8位
#define WORD_HHI(xxx) ((byte) ((word)(xxx) >> 24))  //左移24位取最高8位
int main(int argc, char *argv[])
{
    qint32 i=0x12345678;  //定义一个32位无符号整型数
    qDebug() << "原始值：0x12345678==" << i;   //输出原始值i
    qDebug() << "0x12==" << WORD_HHI(i)   //输出最高8位
             << "0x34==" << WORD_LHI(i)   //输出次高8位
             << "0x56==" << WORD_HLO(i)   //输出次低8位
             << "0x78==" << WORD_LLO(i);  //输出最低8位
    QList<qint8> values;
    values << WORD_HHI(i)
           << WORD_LHI(i)
           << WORD_HLO(i)
           << WORD_LLO(i);  //将取出结果存入values中

    QCoreApplication a(argc, argv);

    return a.exec();
}
