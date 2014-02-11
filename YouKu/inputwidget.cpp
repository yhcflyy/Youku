#include "inputwidget.h"
#include "widget.h"
InputWidget::InputWidget(QWidget *parent) :
    QDialog(parent)
{
    label=new QLabel(tr("优酷页面地址:"));
    lineEdit=new QLineEdit();
    okBtn=new QPushButton("OK");
    layout=new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(okBtn);
    setLayout(layout);
    connect(okBtn,SIGNAL(clicked()),this,SLOT(parase()));
}

InputWidget::~InputWidget()
{
    delete label;
    delete lineEdit;
    delete okBtn;
    delete layout;
}

void InputWidget::parase()
{
    QString weburl=lineEdit->text();
    QString strid="";
    if(weburl == "")
    {
        QMessageBox::information(this,"提示",tr("请输入优酷页面播放地址"));
        return;
    }
    const QString str="http://v.youku.com/v_show/id_";
    int pos=weburl.indexOf(str);
    if(pos == -1)
    {
        QMessageBox::information(this,"提示",tr("地址解析错误"));
        return;
    }
    pos=str.length();
    int i=pos;
    while(i<weburl.length())
    {
        if(weburl[i] == '.' && weburl[i+1] == 'h' && weburl[i+2] == 't' && weburl[i+3] == 'm')
            break;
        strid +=weburl[i];
        ++i;
    }
    qDebug()<<strid;
    this->close();
}
