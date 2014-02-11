#include "jsondata.h"

QByteArray JsonData::get_json_data(const QString& strPath)
{
    QUrl url(strPath);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form ";
    //发出请求
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();
    //将读到的信息写入文件
    m_json_data=reply->readAll();
    return  m_json_data;
}


QJsonObject JsonData::get_josn_object()
{
    QJsonObject obj;
    QJsonParseError jsonError;//Qt5新类
    QJsonDocument json=QJsonDocument::fromJson(m_json_data,&jsonError);
    if(jsonError.error == QJsonParseError::NoError)//Qt5新类
     {
       if(json.isObject())
        {
            obj = json.object();//Qt5新类
         }
      }
    else
        return obj;
}
