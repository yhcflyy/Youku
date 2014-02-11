#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "mypushbutton.h"

class InputWidget : public QDialog
{
    Q_OBJECT
public:
    explicit InputWidget(QWidget *parent = 0);
    ~InputWidget();
signals:

public slots:
    void parase();
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *okBtn;
    QHBoxLayout *layout;
};

#endif // INPUTWIDGET_H
