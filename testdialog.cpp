#include "testdialog.h"
#include "ui_testdialog.h"

#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include<QProcess>

testDialog::testDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮               // 禁止拖动窗口大小
    setWindowTitle(QStringLiteral("登录"));    //设置窗口标题
    connect(ui->forgetpassword,SIGNAL(clicked()), this,SLOT(findPasswod_clicked()));
//    QObject::connect(tcpSocket, &QTcpSocket::readyRead, this, &testDialog::socket_Read_Data);
}

testDialog::~testDialog()
{
    delete ui;
}

void testDialog::on_login_clicked()
{

    //点击登陆按钮时    此处注释的等连接数据库后再进行处理
//    if(ui->id->text()=="")
//    {
//        //当id未填写时
//        QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("请填写id"));
//    }else {
//        if(ui->password->text()=="")
//        {
//            //当密码未填写时
//            QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("请填写密码"));
//        }else {
//            chuanshu *ss=new chuanshu("0######0#");         //先建立一个发送类
//            QString s="";
//            s+="$";
//            s+=ui->id->text()+"$";
//            s+="$";
//            s+=ui->password->text()+"$";
//            s+="$";
//            s+="$";
//            s+="";

//            qDebug()<<"s:"<<s;

//            ss->type = 15;
//            ss->info = s;
//            ss->timer = "";
//            ss->name = ui->id->text();
//            ss->fileName = "";
//            ss->wantsendto = "";
//            ss->size = 0;
//            ss->ip = "";

//            QString sender="";
//            sender+=QString::number(ss->type)+"#"+(QString)ss->info+"#"+(QString)ss->timer+"#"+(QString)ss->name+"#"+(QString)ss->fileName+"#"+(QString)ss->wantsendto+"#"+QString::number(ss->size)+"#"+(QString)ss->ip;

//            // 发送
//            char la=0xff;
//            qDebug() <<sender.toUtf8();
//            tcpSocket->write(sender.toUtf8()+la);
//            tcpSocket->flush();
//            qDebug() <<"send over";

//            //对接收的数据包str进行分析     get是接受的类对象
//            QStringList jiexi=str.split("#");

//            chuanshu *get=new chuanshu("0######0#");
//            get->type = jiexi[0].toInt();;
//            get->info = jiexi[1];
//            get->timer = jiexi[2];
//            get->name = jiexi[3];
//            get->fileName = jiexi[4];
//            get->wantsendto = jiexi[5];
//            get->size = jiexi[6].toInt();
//            get->ip = jiexi[7];


//            if(get->info=="1"){     //代表能进行登录  get->info是从服务器中获取的指令状态
//                extern int quit_login;
//                quit_login=0;           //退出状态重置
//                this->hide();           //登录界面隐藏起来
//                mainwidget = new MainWidget;
//                mainwidget->transfer(tcpSocket,ss->name);
//                mainwidget->show();

//                if(mainwidget->doExec() == MainWidget::Rejected){           //代表主界面的退出  因此result的状态会设置为rejected
//                    this->show();
//                    qDebug()<<"quit1"<<endl;

//                }
//            }

//        }
//    }
    loginID=ui->id->text();     //储存登录ID
    chuanshu *ss=new chuanshu("0######0#");         //先建立一个发送类
    QString s="";
    s+="0$";
    s+=ui->id->text()+"$";
    s+="0$";
    s+=ui->password->text()+"$";
    s+="0$";
    s+="0$";
    s+="0";

    qDebug()<<"login info1:"<<s;

    ss->type = 15;
    ss->info = s;
    ss->timer = "";
    ss->name = ui->id->text();
    ss->fileName = "";
    ss->wantsendto = "";
    ss->size = 0;
    ss->ip = "";

    QString sender="";
    sender+=QString::number(ss->type)+"#"+(QString)ss->info+"#"+(QString)ss->timer+"#"+(QString)ss->name+"#"+(QString)ss->fileName+"#"+(QString)ss->wantsendto+"#"+QString::number(ss->size)+"#"+(QString)ss->ip;

    // 发送
    char la=0xff;
    qDebug() <<sender.toUtf8();
    tcpSocket->write(sender.toUtf8()+la);
    tcpSocket->flush();
    qDebug() <<"send over";

    //登录完后进行清空文本框
    ui->id->text().clear();
    ui->password->text().clear();

    exec();     //登录进程结束
    close();

}


void testDialog::on_registeButton_clicked()
{
    //点击注册按钮
//    QObject::disconnect(tcpSocket, &QTcpSocket::readyRead, this, &testDialog::socket_Read_Data);
//    qDebug()<<"in regi";
//    regi = new Register();
//    regi->state=0;
//    regi->setSocket(this->tcpSocket);       //设置套接字
//    regi->show();

//    if(regi->doExec() == Register::Rejected){           //代表主界面的退出  因此result的状态会设置为rejected
////        this->show();
//        QObject::connect(tcpSocket, &QTcpSocket::readyRead, this, &testDialog::socket_Read_Data);   //登录界面重新连接tcpSocket槽函数
//        qDebug()<<"quit Register page"<<endl;

//    }

//    MainWidget *test=new MainWidget;
//    test->doExec();

//    regi->doExec();


//     mainwidget = new MainWidget;
//     mainwidget->show();
//     mainwidget->doExec();


//    qDebug()<<"exit1";
//    QObject::connect(tcpSocket, &QTcpSocket::readyRead, this, &testDialog::socket_Read_Data);
}

void testDialog::findPasswod_clicked()        //找回密码的按钮
{
    qDebug()<<"找回密码";
    forget1.show();
    forget1.exec();
}

//void testDialog::socket_Read_Data()
//{
//    qDebug()<<"socket_Read_Data";
//    QByteArray buffer;
//    //读取缓冲区数据
//    buffer = tcpSocket->readAll();

//    if(!buffer.isEmpty())
//    {
//        str=QString::fromLocal8Bit(buffer.data());//将收到的utf-8格式转换回String
//        qDebug()<<"rec:"<<str;
////        ui->id->clear();
////        ui->id->setText(str);
//    }

//    QStringList sstr=str.split("#");
//    qDebug()<<"type:"<<sstr[0].toInt();

//}

