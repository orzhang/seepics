#include "controlwidget.h"
#include "ui_controlwidget.h"
#include <QPainter>
ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);
    ui->pushButtonAntiClock->setFocusPolicy(Qt::NoFocus);
    ui->pushButtonLeft->setFocusPolicy(Qt::NoFocus);;
    ui->pushButtonFitSize->setFocusPolicy(Qt::NoFocus);;
    ui->pushButtonRight->setFocusPolicy(Qt::NoFocus);;
    ui->pushButtonClock->setFocusPolicy(Qt::NoFocus);;
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::paintEvent ( QPaintEvent * event ){
    QPainter p(this);
    p.fillRect(rect(), QBrush(QColor(255,255,255,128)));
}

QPushButton *ControlWidget::pushButtonAntiClock()
{
    return ui->pushButtonAntiClock;
}

QPushButton *ControlWidget::pushButtonLeft()
{
    return ui->pushButtonLeft;
}

QPushButton *ControlWidget::pushButtonFitSize()
{
    return ui->pushButtonFitSize;
}

QPushButton *ControlWidget::pushButtonRight()
{
    return ui->pushButtonRight;
}

QPushButton *ControlWidget::pushButtonClock()
{
    return ui->pushButtonClock;
}

