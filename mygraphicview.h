#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

struct Coor;

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

private:
    QGraphicsScene      *scene;

public:
    int GetHeight();
    int GetWidth();
    void NewPoints(int, int);
    void Centres(qreal&, qreal&, int);
    void Vectors(qreal&, qreal&, int);
    void ToCluster(QColor, qreal, qreal);
    QColor GetColorCentre(qreal, qreal);
    QColor GetColor(qreal& , qreal& , int);
    void Move(qreal& , qreal&, qreal, qreal, qreal&, qreal&);

};

#endif // MYGRAPHICVIEW_H
