#include "widget.h"
#include "inputwidget.h"
#include <QDesktopWidget>


Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单
    createMenu();

    player=new QMediaPlayer();
    player->setMedia(QUrl("http://f.youku.com/player/getFlvPath/sid/00_00/st/flv/fileid/030002010052F8142B5DB30230E416C918235D-507A-88AD-BC0E-9EAB59FBC4B9?K=85170318cbf7a9cb2411b355"));

    videoWidget = new QVideoWidget;
    videoWidget->setFullScreen(true);
    QVBoxLayout *topLayout=new QVBoxLayout;
    topLayout->addWidget(videoWidget);

    playPauseBtn=new QPushButton("播放");
    stopBtn=new QPushButton("全屏");
    muteBtn=new QPushButton("静音");
    volumeCtrl=new QSlider(Qt::Horizontal);
    QHBoxLayout *bottomlayout=new QHBoxLayout;
    bottomlayout->addWidget(playPauseBtn);
    bottomlayout->addWidget(stopBtn);
    bottomlayout->addWidget(muteBtn);
    bottomlayout->addWidget(volumeCtrl);

    mainLayout=new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomlayout);


    QWidget * widget = new QWidget (this) ;
    widget->setLayout(mainLayout) ;
    this->setCentralWidget(widget) ;

    connect(playPauseBtn,SIGNAL(clicked()),this,SLOT(play()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(fullScreen()));
    player->setVideoOutput(videoWidget);
    videoWidget->show();
    //player->play();
}

void Widget::createMenu()
{
    fileMenu=menuBar()->addMenu(tr("&File"));

    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QAction* actionOpen;

    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 400, 24));
    QMenu* menu = menuBar->addMenu(tr("&File"));
    actionOpen = menu->addAction(tr("&New"));
    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    layout->setMenuBar(menuBar);

    connect(actionOpen,SIGNAL(triggered()),this,SLOT(openUrl()));
}

Widget::~Widget()
{
    delete player;
    delete videoWidget;
    delete mainLayout;
    delete playPauseBtn;
    delete stopBtn;
    delete muteBtn;
    delete volumeCtrl;
}

void Widget::openUrl()
{
    InputWidget *inputWidget=new InputWidget(NULL);
    inputWidget->setGeometry(QRect(0, 0, 400, 50));
    inputWidget->setAttribute(Qt::WA_ShowModal, true);
    int x=this->x()+this->width()/2,y=this->y()+this->height()/2;
    int width=inputWidget->width(),heigth=inputWidget->height();
    inputWidget->move(x-width/2,y-heigth/2);
    inputWidget->show();
}

void Widget::play()
{
    player->play();
}

void Widget::fullScreen()
{
    videoWidget->setFullScreen(true);
}
