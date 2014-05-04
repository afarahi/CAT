#include <QtGui>
#include "CATMainWindow.h"

CATMainWindow::CATMainWindow(){

   menuBar()->setNativeMenuBar(false);
   
   QWidget *widget = new QWidget;
   setCentralWidget(widget);
  
   QWidget *topFiller = new QWidget;
   topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
   infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                            "invoke a context menu</i>"));
   infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   infoLabel->setAlignment(Qt::AlignCenter);
  
   infoLabel2 = new QLabel(tr("<i>Simulation Status: "
                             "Field is not initialized</i>"));
   infoLabel2->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   infoLabel2->setAlignment(Qt::AlignBottom);
  
   timeLabel = new QLabel(tr("Nothing "));
   QString timeLabelString = tr("Nothing : ") + QString::number(10);
   timeLabel->setText(timeLabelString);
  
   QWidget *bottomFiller = new QWidget;
   bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
   QVBoxLayout *layout = new QVBoxLayout;
  
   layout->setMargin(5);
   layout->addWidget(topFiller);
   layout->addWidget(infoLabel);
   layout->addWidget(infoLabel2);
   layout->addWidget(timeLabel);
   layout->addWidget(bottomFiller);
   widget->setLayout(layout);
  
   createActions();
   createMenus();
   createButtons();
  
   QString message = tr("A context menu is available by right-clicking");
   statusBar()->showMessage(message);
  
   setWindowTitle(tr("CAT main window"));
   setMinimumSize(480, 320);
   resize(720, 480);
   
   plt = new PlotClass(this);

   table = new QTableView(bottomFiller);
   model = new QStandardItemModel(2000,2);
   table->setModel(model);
   table->show(); 
   table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void CATMainWindow::about(){
   QMessageBox::about(this, tr("About Menu"), tr("Test"));
}



void CATMainWindow::createActions(){
  
   // Menu Actions
   //    File actions
   exitAct = new QAction(tr("E&xit"), this);
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip(tr("Exit the application"));
   connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
  
   openSimpleTxtFileAct = new QAction(tr("simple txt file"), this);
   openSimpleTxtFileAct->setStatusTip(tr("Open simple txt file"));
   connect(openSimpleTxtFileAct, SIGNAL(triggered()), this,
           SLOT(openSimpleTxtFile()));
  

   //    Fitting Actions
   //        Least Square
   leastSquarePolynomialAct = new QAction(tr("&Polynomial Fitting"), this);
   connect(leastSquarePolynomialAct,
           SIGNAL(triggered()), this, SLOT(makePolynomialFit()));

  
   aboutAct = new QAction(tr("&About"), this);
   aboutAct->setStatusTip(tr("Show the application's About box"));
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));  
   
   // Simulation menu actions 
   runAct = new QAction(tr("&Run"), this);
   runAct->setShortcut(tr("Ctrl+Alt+R"));
   runAct->setStatusTip(tr("Running the simulation"));
   //connect(runAct, SIGNAL(triggered()), this, SLOT(runSimulation()));
  
   pauseAct = new QAction(tr("&Pause"), this);
   pauseAct->setShortcut(tr("Ctrl+Alt+P"));
   pauseAct->setStatusTip(tr("Pause the simulation"));
   //connect(pauseAct, SIGNAL(triggered()), this, SLOT(pauseSimulation()));
  
   restartAct = new QAction(tr("&Restart"), this);
   restartAct->setShortcut(tr("Ctrl+Alt+N"));
   restartAct->setStatusTip(tr("Restart the simulation"));
   //connect(restartAct, SIGNAL(triggered()), this, SLOT(restartSimulation()));
  
   // Input manu actions
   gridSizeAct = new QAction(tr("&Grid Size"), this);
   //connect(gridSizeAct, SIGNAL(triggered()), this, SLOT(setGridSize()));
  
   toleranceAct = new QAction(tr("&Error Tolerance"), this);
   //connect(toleranceAct, SIGNAL(triggered()), this, SLOT(setTolerance()));

   delaySecAct = new QAction(tr("&Animation Delay"), this);
   //connect(delaySecAct, SIGNAL(triggered()), this, SLOT(setDelaySec()));
  
   realizationTimeStepAct = new QAction(tr("&Realization Time Step"), this);
   //connect(realizationTimeStepAct, SIGNAL(triggered()),
   //        this, SLOT(setRealizationTimeStep()));
  
   // Setting the initial condition
   setICSinAct = new QAction(tr("&Sin"), this);
   setICSinAct->setCheckable(true);
   //connect(setICSinAct, SIGNAL(triggered()), this, SLOT(setICSin()));

   setICStepAct = new QAction(tr("&Step"), this);
   setICStepAct->setCheckable(true);
   //connect(setICStepAct, SIGNAL(triggered()), this, SLOT(setICStep()));

   setICRndNoiseAct = new QAction(tr("&Random Noise"), this);
   setICRndNoiseAct->setCheckable(true);
   //connect(setICRndNoiseAct, SIGNAL(triggered()), this, SLOT(setICRndNoise()));

   icGroup = new QActionGroup(this);
   icGroup->addAction(setICSinAct);
   icGroup->addAction(setICStepAct);
   icGroup->addAction(setICRndNoiseAct);
   setICSinAct->setChecked(true);
  
   // Setting main solver
   setLaxFriedrichsAct = new QAction(tr("Lax-FriedRichs Scheme"), this);
   setLaxFriedrichsAct->setCheckable(true);
   //connect(setLaxFriedrichsAct, SIGNAL(triggered()), this,
   //         SLOT(setLaxFriedrichsScheme()));

   setRK4Act = new QAction(tr("RK4 Scheme"), this);
   setRK4Act->setCheckable(true);
   //connect(setRK4Act, SIGNAL(triggered()), this,SLOT(setRK4Scheme()));

   setMacCormackAct = new QAction(tr("MacCormack Scheme"), this);
   setMacCormackAct->setCheckable(true);
   //connect(setMacCormackAct, SIGNAL(triggered()), this,
   //         SLOT(setMacCormackScheme()));

   setForwardEulerAct = new QAction(tr("Forward Euler Scheme"), this);
   setForwardEulerAct->setCheckable(true);
   //connect(setForwardEulerAct, SIGNAL(triggered()), this,
   //         SLOT(setForwardEulerScheme()));
  
   setKurganovTadmor2000Act = new QAction(tr("Kurganov-Tadmor Scheme"), this);
   setKurganovTadmor2000Act->setCheckable(true);
   //connect(setKurganovTadmor2000Act, SIGNAL(triggered()), this,
   //         SLOT(setKurganovTadmor2000Scheme()));

   setRK4KurganovTadmor2000Act = 
           new QAction(tr("RK4 Kurganov-Tadmor Scheme"), this);
   setRK4KurganovTadmor2000Act->setCheckable(true);
   //connect(setRK4KurganovTadmor2000Act, SIGNAL(triggered()), this,
   //         SLOT(setRK4KurganovTadmor2000Scheme()));

   setKurganovTadmor2ndOrder2000Act = 
           new QAction(tr("2nd Order Kurganov-Tadmor Scheme"), this);
   setKurganovTadmor2ndOrder2000Act->setCheckable(true);
   //connect(setKurganovTadmor2ndOrder2000Act, SIGNAL(triggered()), this,
   //         SLOT(setKurganovTadmor2ndOrder2000Scheme()));
 
   solverGroup = new QActionGroup(this);
   solverGroup->addAction(setMacCormackAct);
   solverGroup->addAction(setForwardEulerAct);
   solverGroup->addAction(setLaxFriedrichsAct);
   solverGroup->addAction(setKurganovTadmor2000Act);
   solverGroup->addAction(setRK4KurganovTadmor2000Act);
   solverGroup->addAction(setKurganovTadmor2ndOrder2000Act);
   solverGroup->addAction(setRK4Act);
   setRK4Act->setChecked(true);
 
   // Setting flux solver
   setMUSCLSAct = new QAction(tr("MUSCL Scheme"), this);
   setMUSCLSAct->setCheckable(true);
   //connect(setMUSCLSAct, SIGNAL(triggered()), this, SLOT(setMUSCLSScheme()));

   setLinearReconstructionAct = 
             new QAction(tr("Linear Reconstruction Scheme"), this);
   setLinearReconstructionAct->setCheckable(true);
   //connect(setLinearReconstructionAct, SIGNAL(triggered()), this,
   //          SLOT(setLinearReconstructionScheme()));

   setPiecewiseParabolicReconstructionAct = 
             new QAction(tr("Piecewise Parabolic Reconstruction Scheme"), this);
   setPiecewiseParabolicReconstructionAct->setCheckable(true);
   //connect(setPiecewiseParabolicReconstructionAct, SIGNAL(triggered()), this,
   //          SLOT(setPiecewiseParabolicReconstructionScheme()));

   fluxGroup = new QActionGroup(this);
   fluxGroup->addAction(setMUSCLSAct);
   fluxGroup->addAction(setPiecewiseParabolicReconstructionAct);
   fluxGroup->addAction(setLinearReconstructionAct);
   setLinearReconstructionAct->setChecked(true);
 
}

void CATMainWindow::createMenus(){
	
   fileMenu = menuBar()->addMenu(tr("&File"));
   openMenu = fileMenu->addMenu(tr("&Open data file"));
   openMenu->addAction(openSimpleTxtFileAct);
   fileMenu->addSeparator();
   fileMenu->addAction(exitAct);

   fittingMenu = menuBar()->addMenu(tr("&Fitting"));
   leastSquareMenu = fittingMenu->addMenu(tr("&Least Square"));
   leastSquareMenu->addAction(leastSquarePolynomialAct);

   SimulationMenu = menuBar()->addMenu(tr("&Simulation"));
   SimulationMenu->addAction(runAct);
   SimulationMenu->addAction(pauseAct);
   SimulationMenu->addAction(restartAct);
  
   InputMenu = menuBar()->addMenu(tr("&Input"));
   InputMenu->addAction(gridSizeAct);
   InputMenu->addAction(toleranceAct);
   InputMenu->addAction(delaySecAct);
   InputMenu->addAction(realizationTimeStepAct);
   
   initialConditionMenu = InputMenu->addMenu(tr("&Initial Condition"));
   initialConditionMenu->addAction(setICSinAct);
   initialConditionMenu->addAction(setICStepAct);
   initialConditionMenu->addAction(setICRndNoiseAct);

   fluxSolverMenu = InputMenu->addMenu(tr("&Flux Solver"));
   fluxSolverMenu->addSeparator()->setText(tr("Alignment"));
   fluxSolverMenu->addAction(setMUSCLSAct);
   fluxSolverMenu->addAction(setLinearReconstructionAct);
   fluxSolverMenu->addAction(setPiecewiseParabolicReconstructionAct);
   fluxSolverMenu->addSeparator();
    
   mainSolverMenu = InputMenu->addMenu(tr("&Main Solver"));
   mainSolverMenu->addAction(setRK4Act);
   mainSolverMenu->addAction(setMacCormackAct);
   mainSolverMenu->addAction(setForwardEulerAct);
   mainSolverMenu->addAction(setLaxFriedrichsAct);
   mainSolverMenu->addAction(setKurganovTadmor2000Act);
   mainSolverMenu->addAction(setRK4KurganovTadmor2000Act);
   mainSolverMenu->addAction(setKurganovTadmor2ndOrder2000Act);

   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutAct);
  
}


void CATMainWindow::createButtons(){
  
   QPushButton *runButton = new QPushButton("&Plot", this);
   runButton->setGeometry(QRect(QPoint(10, 40), QSize(80, 30)));
   connect(runButton, SIGNAL(released()), this, SLOT(plotCurrentWorkSpace()));
  
   //QPushButton *pauseButton = new QPushButton("&Pause", this);
   //pauseButton->setGeometry(QRect(QPoint(10, 80), QSize(80, 30)));
   //connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseSimulation()));
  
   //QPushButton *restartButton = new QPushButton("&Restart", this);
   //restartButton->setGeometry(QRect(QPoint(10, 120), QSize(80, 30)));
   //connect(restartButton, SIGNAL(clicked()), this, SLOT(restartSimulation()));

}


// Slots


void CATMainWindow::openSimpleTxtFile(){

   QString selectedFile = QFileDialog::getOpenFileName(this,
                               "Select a .txt file.",
                               "",
                               tr("text file (*.txt);;All (*.*)"));

   QFile file(selectedFile);

   int iRow, iCol;
   int columnNum = 2;

   QStandardItem *item;
   
   if (file.open(QIODevice::ReadOnly) | (QIODevice::Text)){
      QString line; QStringList fields; 
      QTextStream in(&file);
      
      iRow = 0;
      while(!in.atEnd()){
         line = in.readLine();    
         fields = line.split(" ",QString::SkipEmptyParts);
         for (iCol = 0; iCol < columnNum; iCol++){
            item = new QStandardItem(QString(fields.at(iCol)));
            model->setItem(iRow,iCol,item);
         }
         iRow++;
      }

      file.close();

      iRow--;
      dataPoints.resize(iRow,columnNum);
      for (iRow = 0; iRow < dataPoints.rows(); iRow++){
         for (iCol = 0; iCol < dataPoints.cols(); iCol++){
            dataPoints(iRow,iCol) = 
                ((model->item(iRow,iCol))->text()).toDouble();
         }
      }

   }
   else{
      QMessageBox::warning(this, "Error", "Unable to open file.");
   }

   table->show(); 
   table->setEditTriggers(QAbstractItemView::NoEditTriggers);


/* SAVING
 * QString saveFileName = QFileDialog::getSaveFileName(this,"Select the file you wish to save to.","","");

QFile saveFile(saveFileName);

if(saveFile.open(QIODevice::WriteOnly))
{
    QTextStream stream(&saveFile);
    QString stringToSaveToFile;
    stream << stringToSaveToFile;
    saveFile.close();
}
else
{
    QMessageBox::warning(this, "Error", "Cannot open file.");
}
*/

}



void CATMainWindow::makePolynomialFit(){
   bool ok;
   int polyDegree = QInputDialog::getInt(this,
                           tr("Get the polynomial degree"),
                           tr("Polynomial degree:"), 1,
                               0, dataPoints.rows(), 1, &ok);
   if ( ok ){

      LeastSquareFitClass lsf;
      MatrixXd polyMat;
      VectorXd polyCoef(polyDegree);

      lsf.make1dPolynomialMatrix(&polyMat, dataPoints.col(0), polyDegree);
      lsf.solveLeastSquareFit(polyMat, dataPoints.col(1), &polyCoef);

      cout << polyCoef << endl;

      QVector<double> x(dataPoints.rows());
      QVector<double> y(dataPoints.rows());

      delete plt;  plt = new PlotClass(this);

      for (int i = 0; i < dataPoints.rows(); i++){
         x[i] = dataPoints(i,0);
         y[i] = dataPoints(i,1);
      }
      plt->plot(x,y,dataPoints.rows(),false);

      plt->plotPolynomial(dataPoints.col(0).minCoeff(),
                          dataPoints.col(0).maxCoeff(),
                          polyCoef);

      plt->show();
   }

}

void CATMainWindow::plotCurrentWorkSpace(){

   /*
   dataPoints = new Array2D< double >(10,2);

   QVector<double> x(dataPoints->dim1());
   QVector<double> y(dataPoints->dim1());

   cout << dataPoints->dim1() << endl;
   cout << dataPoints->dim2() << endl;
   for (int i = 0; i < 10; i++){
       (*dataPoints)[i][0] = 5 * (double) i;  
       (*dataPoints)[i][1] = (double) i + 100 ;  
       x[i] = (*dataPoints)[i][0];
       y[i] = (*dataPoints)[i][1];
   }
   
   plt->plot(x,y,dataPoints->dim1(),false);

   for (int i = 0; i < 10; i++){
       x[i] = (*dataPoints)[i][0] + 1;
       y[i] = (*dataPoints)[i][1];
   }

   plt->plot(x,y,dataPoints->dim1(),true);

   plt->show();
   
   timeLabel->setText(tr("<i>Plot current work space</i>"));                             
   */
 
}






