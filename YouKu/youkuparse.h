#ifndef YOUKUPARSE_H
#define YOUKUPARSE_H

#include "jsondata.h"
#include <QVector>
#include <tuple>

//片段信息结构体
typedef  std::tuple<size_t,size_t ,size_t,QString,QString> SegInfo;

class YoukuParse
{
public:
    YoukuParse(const QString& path);
    ~YoukuParse();

    /*************************************************/
    /*功能:获取json数据中的清晰度列表                    */
    /*参数:无                                         */
    /*返回:返回可提供的清晰度数组                        */
    /*************************************************/
    QVector<std::tuple<QString,QString> > get_definition();


    /*******************************************8******/
    /*功能:获取每个分段的信息                             */
    /*参数:要获取片段信息的清晰                           */
    /*返回:返回整部视频的所有分段信息                      */
     /*************************************************/
    QVector<SegInfo> get_SegInfo(const QString& strDefinition);

    /*********************************************8****/
    /*功能:获取混淆字符串                                */
    /*参数:从json数据获取到的seed                        */
    /*返回:返回整部视频的所有分段信息                      */
     /*************************************************/
    QString get_max();



   /**************************************************/
   /*功能:获取文件的真正id                              */
   /*参数:清晰度                                       */
   /*返回:返回整部视频的id                              */
    /*************************************************/
    QString get_file_id(const QString& strDefinition);


    /**************************************************/
    /*功能:获取真实地址                                  */
    /*参数:清晰度                                       */
    /*返回:返回视频的真实地址                             */
     /*************************************************/
    QVector<QString> get_real_url(const QString& strDefinition);
private:
    JsonData *jsonData;
};

#endif // YOUKUPARSE_H
