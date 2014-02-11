#include "youkuparse.h"

YoukuParse::YoukuParse(const QString& path)
{
    jsonData=new JsonData();
    jsonData->get_json_data(path);
}
YoukuParse::~YoukuParse()
{
    delete jsonData;
}

/*************************************************/
/*功能:获取json数据中的清晰度列表                    */
/*参数:无                                         */
/*返回:返回可提供的清晰度数组                        */
/*************************************************/
QVector<std::tuple<QString,QString> > YoukuParse::get_definition()
{

    QVector<std::tuple<QString,QString>> defVec;
    QJsonObject hdtypeObj=jsonData->get_josn_object();
    hdtypeObj=hdtypeObj["data"].toArray()[0].toObject()["streamfileids"].toObject();
    QJsonObject::iterator it;
    for(it=hdtypeObj.begin();it!=hdtypeObj.end();++it)
    {
        std::tuple<QString,QString> myTuple;
        myTuple=std::make_tuple(it.key(),it.value().toString());
        defVec.push_back(myTuple);
    }
    return defVec;
}


/*******************************************8******/
/*功能:获取每个分段的信息                             */
/*参数:要获取片段信息的清晰                           */
/*返回:返回整部视频的所有分段信息                      */
 /*************************************************/
QVector<SegInfo> YoukuParse::get_SegInfo(const QString& strDefinition)
{
    QVector<SegInfo> segsVec;
    QJsonObject nodeObj=jsonData->get_josn_object();
    QJsonArray jsonArray=nodeObj["data"].toArray()[0].toObject()["segs"].toObject()[strDefinition].toArray();
    QJsonArray::iterator it;
    for(it=jsonArray.begin();it!=jsonArray.end();++it)
    {
        if((*it).isObject())
        {
            QJsonObject obj=(*it).toObject();
            size_t no=obj.find("no").value().toInt();
            size_t size=obj.find("size").value().toInt();
            size_t seconds=obj.find("seconds").value().toInt();
            QString k=obj.find("k").value().toString();
            QString k1=obj.find("k1").value().toString();
            segsVec.push_back(std::make_tuple(no,size,seconds,k,k1));
        }
    }
    return segsVec;
}

/*********************************************8****/
/*功能:获取混淆字符串                                */
/*参数:从json数据获取到的seed                        */
/*返回:返回整部视频的所有分段信息                      */
 /*************************************************/
QString YoukuParse::get_max()
{
    QString str_max="";
    int Seed=0,index=0;
    QJsonObject hdtypeObj=jsonData->get_josn_object();
    hdtypeObj=hdtypeObj["data"].toArray()[0].toObject();
    Seed=hdtypeObj.find("seed").value().toInt();
    QString source="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ/\\:._-1234567890";
    size_t strlen=source.length();
    for(size_t i=0;i<strlen;++i)
     {
        Seed = (Seed * 211 + 30031) % 65536;
        index=(Seed*source.length()/65536);
        str_max=str_max+source[index];
        source=source.replace(index,1,"");
     }
    return str_max;
}



/**************************************************/
/*功能:获取文件的真正id                              */
/*参数:清晰度                                       */
/*返回:返回整部视频的id                              */
/*************************************************/
QString YoukuParse::get_file_id(const QString& strDefinition)
{
    QString str_real_id="";
    QString mixed=get_max();
    QVector<std::tuple<QString,QString> > defVec=get_definition();
    QVector<std::tuple<QString,QString> >::iterator it;
    for(it=defVec.begin();it!=defVec.end();++it)
    {
        if(strDefinition == std::get<0>(*it))
        {
            QString defValue=std::get<1>(*it);
            defValue=defValue.replace(defValue.length()-1,1,"");
            QStringList ids=defValue.split("*");
            foreach (QString v, ids)
            {
             str_real_id=str_real_id+mixed[v.toInt()];
            }
            break;
        }
    }
    return str_real_id;
}


/**************************************************/
/*功能:获取真实地址                                  */
/*参数:清晰度                                       */
/*返回:返回视频的真实地址                             */
 /*************************************************/
QVector<QString> YoukuParse::get_real_url(const QString& strDefinition)
{
    QVector<QString> realUrlVec;
    QString real_url="";
    QString pre_url="http://f.youku.com/player/getFlvPath/sid/00_00/st/";
    QVector<SegInfo> segVec=get_SegInfo(strDefinition);
    int i=0;
    foreach (SegInfo seg, segVec)
    {
       //获取每一集
       QString fileID=get_file_id(strDefinition);
       QString newfileID=fileID.left(8);
       char buff[3]={0};
       sprintf(buff,"%02X",i);
       QString tmp(buff);
       newfileID+=tmp;
       newfileID+=fileID.right(fileID.length()-10);
       if(strDefinition == "hd2")
       {
           real_url=pre_url+"flv/fileid/"+newfileID+"?K="+std::get<3>(seg);
           realUrlVec.push_back(real_url);
       }
       else
       {
           real_url=pre_url+strDefinition+"/fileid/"+newfileID+"?K="+std::get<3>(seg);
           realUrlVec.push_back(real_url);
       }
       ++i;
    }
    return realUrlVec;

}
