#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mygraphicview.h>
#include <math.h>

MyGraphicView* myPicture;

struct Point
{
    qreal x;
    qreal y;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        myPicture = new MyGraphicView();
        ui->verticalLayout->addWidget(myPicture);

        QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(GenerationClicked()));
        QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(StartClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::Random(int S)
{
   int coo = qrand() % S;
   return coo;
}

void MainWindow::GenerationClicked()
{
    ui->pushButton->setEnabled(false);
    NumPoints = ui->textEdit_2->toPlainText().toInt();
    for (int i=0; i<NumPoints; i++)
    {
            int W = myPicture->GetWidth();
            int H = myPicture->GetHeight();
            int X = Random(W);
            int Y = Random(H);
            myPicture->NewPoints(X,Y);
    }
}

void MainWindow::StartClicked()
{
    ui->pushButton_2->setEnabled(false);

    NumClusters = ui->textEdit->toPlainText().toInt();

    QList <bool> Movement;
    int iter = 0;
    QList <Point> cntr;

    for (int i = 0; i < NumClusters; i++)
    {
        Point p1;
        myPicture->Centres(p1.x, p1.y, i);
        cntr.append(p1);
    }

do {
    Movement.clear();

    for (int j = 0; j < NumPoints; j++)
    {
        Point pointToCheck;
        myPicture->Vectors(pointToCheck.x, pointToCheck.y, j);
        int min = 10000000;
        int cluster = 1;
        for (int k = 0; k < cntr.size(); k++)
        {
            int temp = (cntr.at(k).x - pointToCheck.x);
            int temp2 = (cntr.at(k).y - pointToCheck.y);
            int a = sqrt(pow(temp,2)+pow(temp2,2));
            if (a<min) {
                min=a;
                cluster = k+1;
            }
        }

        switch (cluster)
        {
        case 1: { myPicture->ToCluster (Qt::red, pointToCheck.x, pointToCheck.y); break; }
        case 2: { myPicture->ToCluster (Qt::blue, pointToCheck.x, pointToCheck.y); break; }
        case 3: { myPicture->ToCluster (Qt::green, pointToCheck.x, pointToCheck.y); break;}
        case 4: { myPicture->ToCluster (Qt::yellow, pointToCheck.x, pointToCheck.y); break;}
        case 5: {  myPicture->ToCluster (Qt::black, pointToCheck.x, pointToCheck.y); break;}
        case 6: {  myPicture->ToCluster (Qt::magenta, pointToCheck.x, pointToCheck.y); break;}
        case 7: {  myPicture->ToCluster (Qt::cyan, pointToCheck.x, pointToCheck.y); break;}
        case 8: {  myPicture->ToCluster (Qt::lightGray, pointToCheck.x, pointToCheck.y); break;}
        case 9: {  myPicture->ToCluster (Qt::darkGreen, pointToCheck.x, pointToCheck.y); break;}
        case 10: {  myPicture->ToCluster (Qt::darkRed, pointToCheck.x, pointToCheck.y); break;}
        }
    }

for (int k = 0; k < cntr.size(); k++)
{
    QColor colorCentre = myPicture->GetColorCentre(cntr.at(k).x, cntr.at(k).y);
    int summax = 0;
    int summay = 0;
    int numberofpoints = 0;
    for (int j = 0; j < NumPoints; j++)
    {
            Point pointToCheck;
            QColor color = myPicture->GetColor(pointToCheck.x, pointToCheck.y, j);
            if (colorCentre == color)
            {
                if (pointToCheck.x != cntr.at(k).x || pointToCheck.y != cntr.at(k).y)
                {
                    summax = summax + pointToCheck.x;
                    summay = summay + pointToCheck.y;
                    numberofpoints = numberofpoints+1;
                }
           }
     }
    Point movement;
    movement.x = 0; movement.y = 0;
    if (numberofpoints != 0)
    {
    int SrednX = summax/numberofpoints;
    int SrednY = summay/numberofpoints;
    Point tempCoor;
    tempCoor.x = cntr.at(k).x; tempCoor.y = cntr.at(k).y;
    myPicture->Move(tempCoor.x, tempCoor.y, SrednX, SrednY, movement.x, movement.y);
    cntr.replace(k, tempCoor);
    }
    if (movement.x == 0 && movement.y == 0) Movement.append(true);
    else Movement.append(false);
}

iter++;

} while (Movement.contains(false) && iter < 30);

    ui->label_4->setText(QString::number(iter));

}
