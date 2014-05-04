#ifndef __PLOT_CLASS_H__
#define __PLOT_CLASS_H__

#include <QMainWindow>
#include <QTimer>
#include "./QCustomPlot/qcustomplot.h" 
#include "../ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QVector>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

namespace Ui {
   class MainWindow;
}

class PlotClass : public QMainWindow
{
   Q_OBJECT

public:

   explicit PlotClass(QWidget *parent = 0);
   ~PlotClass();
  
   void plot(QVector<double> x, QVector<double> y, int dim,
             bool line = false);

   void setThePlot_error(string fileName, string fileName_ex, int gridSize);
 
   void plotPolynomial(double xmin, double xmax,
                       VectorXd polyCoef, int numPoints=101);
  
private slots:

   void clickedGraph(QMouseEvent *event);

private:

   Ui::MainWindow *ui;
   QString demoName;
   QTimer dataTimer;
   QCPItemTracer *itemDemoPhaseTracer;

   double xPosition, yPosition;
   double *x_hist;
   double *y_hist;
   double *y_ex_hist;

   double xPosition_dis;
   double yPosition_dis;
   double yPosition_ex_dis;

};

#endif 
