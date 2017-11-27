#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Generation();
    int Random(int S);

private slots:
    void GenerationClicked();
    void StartClicked();

private:
    Ui::MainWindow *ui;
    int NumPoints = 0;
    int NumClusters = 0;
};

#endif // MAINWINDOW_H
