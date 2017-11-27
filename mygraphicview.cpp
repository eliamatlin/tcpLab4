#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scene = new QGraphicsScene();
    this->setScene( scene );
}


MyGraphicView::~MyGraphicView()
{
}

void MyGraphicView::NewPoints(int x, int y)
{
    scene->addEllipse(x,y,5,5);
}

int MyGraphicView::GetWidth()
{
    int w = this->width();
    return w;
}
int MyGraphicView::GetHeight()
{
    int h = this->height();
    return h;
}

void MyGraphicView::Centres( qreal &x1, qreal &y1, int k)
{
        static QList <QGraphicsItem*> objl;
        if (k == 0) objl=scene->items();
        int size = objl.size();
        int a = qrand() % size;
        QGraphicsItem *item = objl.takeAt(a);
        QGraphicsEllipseItem *itemtemp = dynamic_cast < QGraphicsEllipseItem * > (item);
        QRectF rect = itemtemp->rect();
        qreal x2 = 0; qreal y2 = 0;
        rect.getCoords ( &x1, &y1, &x2, &y2 );
        rect.setSize(QSizeF( 10, 10 ));
        QColor color = Qt::red;
        itemtemp->setBrush(color);
        itemtemp->setRect(rect);
}

void MyGraphicView::Vectors(qreal &X, qreal &Y, int j)
{
    QList <QGraphicsItem*> objl;
    objl=scene->items();
    QGraphicsItem *item = objl.at(j);
    QGraphicsEllipseItem *itemtemp = dynamic_cast < QGraphicsEllipseItem * > (item);
    QRectF rect = itemtemp->rect();
    qreal x2 = 0; qreal y2 = 0;
    rect.getCoords ( &X, &Y, &x2, &y2 );
}
void MyGraphicView::ToCluster(QColor c, qreal x, qreal y)
{
    QGraphicsItem *item = scene->itemAt(x+2.5, y+2.5, QTransform());
    if (item != NULL)
    {
        QGraphicsEllipseItem *itemtemp = dynamic_cast
< QGraphicsEllipseItem * > (item);
        itemtemp->setBrush(c);
    }
}

QColor MyGraphicView::GetColorCentre(qreal x, qreal y)
{
     QGraphicsItem *item = scene->itemAt(x+5, y+5, QTransform());
     if (item != NULL)
     {
        QGraphicsEllipseItem *itemtemp = dynamic_cast
< QGraphicsEllipseItem * > (item);
        QColor color = itemtemp->brush().color();
        return color;
     }
     return -1;
}

QColor MyGraphicView::GetColor(qreal &X, qreal &Y, int j)
{
    static QList <QGraphicsItem*> objl;
    objl=scene->items();
    QGraphicsItem *item = objl.at(j);
    QGraphicsEllipseItem *itemtemp = dynamic_cast
< QGraphicsEllipseItem * > (item);
    QColor const color = itemtemp->brush().color();
    QRectF rect = itemtemp->rect();
    qreal x2 = 0; qreal y2 = 0;
    rect.getCoords ( &X, &Y, &x2, &y2 );
    return color;
}

void MyGraphicView::Move(qreal &X, qreal &Y, qreal newX, qreal newY, qreal &dx, qreal &dy)
{
    QGraphicsItem *item = scene->itemAt(X+5, Y+5, QTransform());
    if (item != NULL)
    {
        QGraphicsEllipseItem *itemtemp = dynamic_cast
< QGraphicsEllipseItem * > (item);
        itemtemp->setRect(newX, newY, 10, 10);
        dx = X - newX; dy = Y - newY;
        X = newX; Y = newY;
    }
}
