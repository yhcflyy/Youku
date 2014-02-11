#ifndef JSONDATA_H
#define JSONDATA_H

#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class JsonData
{
public:
    QByteArray get_json_data(const QString& url);
    QJsonObject get_josn_object();
private:
    QByteArray m_json_data;
};

#endif // JSONDATA_H
