#ifndef PICAPPLICATION_H
#define PICAPPLICATION_H

#include <QApplication>

class PicApplication : public QApplication
{
    Q_OBJECT
public:
    explicit PicApplication(int &argc, char **argv);
protected:
    bool event(QEvent *event);
private:
    void loadFile(const QString &file);
signals:
    void eventLoadFile(const QString &file);
public slots:

};

#endif // PICAPPLICATION_H
