#include "PlotClass.h"

PlotClass::PlotClass(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  statusBar()->clearMessage();
}

PlotClass::~PlotClass()
{
  delete ui;
}

void PlotClass::plot(QVector<double> x, QVector<double> y, int dim,
                     bool line){

   setWindowTitle("Data Points"); 

   double maxX, minX, maxY, minY;
   maxX = x[0]; minX = x[0]; maxY = y[0]; minY = y[0];
   for (int i = 1; i < dim; i++){
      if (x[i] < minX){ minX = x[i]; }
      if (x[i] > maxX){ maxX = x[i]; }
      if (y[i] < minY){ minY = y[i]; }
      if (y[i] > maxY){ maxY = y[i]; }
   }
  
   // create graph and assign data to it:
   if ( line ){
      ui->customPlot->addGraph();
      ui->customPlot->graph()->setData(x, y);
      ui->customPlot->graph()->setName("Data Points");
      //ui->customPlot->graph(0)->rescaleAxes(true);
   }
   else{
      ui->customPlot->addGraph();
      ui->customPlot->graph()->setPen(QPen(Qt::red));
      ui->customPlot->graph()->setLineStyle(QCPGraph::lsNone);
      ui->customPlot->graph()->setScatterStyle( 
                                         QCPScatterStyle(
                                             QCPScatterStyle::ssCircle, 4)
                                           );
      ui->customPlot->graph()->setErrorType(QCPGraph::etValue);
      ui->customPlot->graph()->setErrorPen(QPen(QColor(180,180,180)));
      ui->customPlot->graph()->setName("Data Points");
      ui->customPlot->graph()->setData(x, y);
      //ui->customPlot->graph(1)->rescaleAxes(true);
   }
   
   ui->customPlot->setInteractions(QCP::iRangeDrag | 
                                   QCP::iRangeZoom |
                                   QCP::iSelectPlottables);

   // define the properties of the plot
   //QPen pen;
   //pen.setColor(QColor(0, 0, 0, 255));
   //ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
   //ui->customPlot->graph(0)->setPen(pen);

   // give the axes some labels:
   ui->customPlot->xAxis->setLabel("X");
   ui->customPlot->yAxis->setLabel("Y");
   ui->customPlot->xAxis->setRange(minX, maxX);
   ui->customPlot->yAxis->setRange(minY, maxY);
   ui->customPlot->setInteraction(QCP::iRangeDrag, true);
   ui->customPlot->setInteraction(QCP::iRangeZoom, true);
   
   // add interaction "mouse query for data points"
   connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,
           SLOT(clickedGraph(QMouseEvent*)));
   
   ui->customPlot->replot();

}




void PlotClass::plotPolynomial(double xmin, double xmax,
                               VectorXd polyCoef, int numPoints){
   QVector<double> x(numPoints); QVector<double> y(numPoints);
   for (int i = 0; i < numPoints; i++){
      x[i] = xmin + (double)i * (xmax-xmin) / (double)(numPoints-1);
      y[i] = 0.0;
      for (int iPoly = 0; iPoly < polyCoef.size(); iPoly++){
         y[i] += polyCoef(iPoly) * pow(x[i],iPoly);
      }
   }
   ui->customPlot->addGraph();
   ui->customPlot->graph()->setData(x, y);      
   ui->customPlot->replot();
}

void PlotClass::setThePlot_error(string fileName, string fileName_ex,
                              int gridSize)
{
  // function for plotting the error
  setWindowTitle("Error PLot");

  QVector<double> x(gridSize), y(gridSize);
  QVector<double> x_ex(gridSize), y_ex(gridSize);
  QVector<double> x_error(gridSize), y_error(gridSize);

  ifstream inFile,inFile_ex;
  double maxX, minX, maxY, minY;
  maxX = 0;
  minX = 0;
  maxY = 0;
  minY = 0;

  inFile.open(fileName.c_str());
  inFile_ex.open(fileName_ex.c_str());
  string firstLine, firstLine_ex;
  getline(inFile, firstLine);
  getline(inFile_ex, firstLine_ex);

  for (int i = 0; i < gridSize; i++)
  {
    inFile >> x[i];
    inFile_ex >> x_ex[i];
    // update the minX
    if (x[i] < minX)
    {
      minX = x[i];
    }

    // update the maxX
    if (x[i] > maxX)
    {
      maxX = x[i];
    }

    inFile >> y[i];
    inFile_ex >> y_ex[i];
    y_error[i] = y[i] - y_ex[i];

    // update the minY
    if (y_error[i] < minY)
    {
      minY = y_error[i];
    }

    // update the maxY
    if (y_error[i] > maxY)
    {
      maxY = y_error[i];
    }
  }

  // create graph and assign data to it:
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y_error);
  ui->customPlot->graph(0)->setName("Error");

  // define the properties of the plot
  QPen pen;
  pen.setColor(QColor(255, 0, 0, 255));
  ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
  ui->customPlot->graph()->setPen(pen);
  // give the axes some labels:
  ui->customPlot->xAxis->setLabel("r");
  ui->customPlot->yAxis->setLabel("Phi");
  // set axes ranges, so we see all data:
  ui->customPlot->xAxis->setRange(minX, maxX);
  ui->customPlot->yAxis->setRange(minY, maxY);
  ui->customPlot->setInteraction(QCP::iRangeDrag, true);
  ui->customPlot->setInteraction(QCP::iRangeZoom, true);
  ui->customPlot->setInteraction(QCP::iSelectPlottables, true);
  ui->customPlot->setInteraction(QCP::iMultiSelect, true);
  ui->customPlot->setInteraction(QCP::iSelectAxes, true);

  ui->customPlot->replot();
}

void PlotClass::clickedGraph(QMouseEvent *event)
{
   // function for mouse interaction

   // ontain the mouse position when click on the plot and transfer the pixel
   // position to the coord position
   xPosition = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
   yPosition = ui->customPlot->yAxis->pixelToCoord(event->pos().y());

   // get the closest solution point w.r.t. the mouse clicked coord position
   int i = 0;
   while (xPosition > x_hist[i]){
      i = i+1;
   }

   // update the status bar message
   //ui->statusBar->showMessage(QString("r: %1;  Phi(num.): %2;  "
   //                                   "Phi(exa.): %3;  Error: %4")
   //                           .arg(xPosition_dis)
   //                           .arg(yPosition_dis)
   //                           .arg(yPosition_ex_dis)
   //                           .arg(error_dis)
   //                          , 0);

   QVector<double> x(2), y(2);
   x[0] = xPosition_dis;
   y[0] = yPosition_dis;

   // plot the clicked data points
   ui->customPlot->addGraph();
   ui->customPlot->graph()->setData(x, y);
   ui->customPlot->graph()->setName("Point track");
   ui->customPlot->graph()->setLineStyle(QCPGraph::lsNone);
   ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(
                                        QCPScatterStyle::ssSquare,
                                        QPen(Qt::red),
                                        QBrush(Qt::white),
                                        10));
}
