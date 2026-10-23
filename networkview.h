#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QGraphicsView>

class NetworkView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit NetworkView(QWidget *parent = nullptr);

signals:
};

#endif // NETWORKVIEW_H
