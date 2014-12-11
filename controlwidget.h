#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "ImageWidget.h"
#include <QPushButton>
namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = 0);
    ~ControlWidget();
    QPushButton *pushButtonAntiClock();
    QPushButton *pushButtonLeft();
    QPushButton *pushButtonFitSize();
    QPushButton *pushButtonRight();
    QPushButton *pushButtonClock();
protected:
    void paintEvent ( QPaintEvent * event );
private:
    Ui::ControlWidget *ui;
};

#endif // CONTROLWIDGET_H
