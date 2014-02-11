#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QBoxLayout>
#include <QtWidgets>
#include "mypushbutton.h"

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void createMenu();
public slots:
    void openUrl();
    void play();
    void fullScreen();

private:
    //菜单
    QMenu *fileMenu;
    //播放
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QBoxLayout *mainLayout;
    //控制
    QPushButton *playPauseBtn;
    QPushButton *stopBtn;
    QPushButton *muteBtn;
    QSlider *volumeCtrl;
};

#endif // WIDGET_H
