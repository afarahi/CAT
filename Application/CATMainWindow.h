#ifndef __CAT_MAINWINDOW_CLASS_H__
#define __CAT_MAINWINDOW_CLASS_H__

#include <QStandardItemModel>
#include <QApplication>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QVector>
#include <QString>
#include <QTimer>

#include <iostream>
#include <string>
using namespace std;
#include "../PlotClass/PlotClass.h"
#include "../constants.h"

#include <Eigen/Dense>
using namespace Eigen;

#include "../StatisticalModels/FittingModels/LeastSquareClass/LeastSquareFitClass.h"

class QAction;
class QActionGroup;
class QPushButton;
class QTableView;
class QLabel;
class QMenu;

class CATMainWindow: public QMainWindow{

   Q_OBJECT

public:

   CATMainWindow();

protected:

private slots:

   // Menu slots 
   //    File slots
   void openSimpleTxtFile();

   //    Fitting slots
   //        Least Square slots
   void makePolynomialFit();
   
   void about();

   // Button slots
   void plotCurrentWorkSpace();
  
private:

   void createActions();
   void createMenus();
   void createButtons();

   QMenu *fileMenu;
   QMenu *openMenu;

   QMenu *fittingMenu;
   QMenu *leastSquareMenu;

   QMenu *helpMenu;

   QMenu *SimulationMenu;

   QMenu *InputMenu;
   QMenu *initialConditionMenu;
   QMenu *fluxSolverMenu;
   QMenu *mainSolverMenu;
  
   QActionGroup *solverGroup;
   QActionGroup *fluxGroup;
   QActionGroup *icGroup;

   // Actions
   //    File actions
   QAction *openSimpleTxtFileAct;
   QAction *exitAct;

   QAction *leastSquarePolynomialAct;

   QAction *aboutAct;
   QAction *aboutQtAct;

   QAction *runAct;
   QAction *pauseAct;
   QAction *restartAct;

   // Input Parameters
   QAction *gridSizeAct;
   QAction *toleranceAct;
   QAction *delaySecAct;
   QAction *realizationTimeStepAct;
    
   // Initial Condition
   QAction *setICSinAct;
   QAction *setICStepAct;
   QAction *setICRndNoiseAct;
  
   // Flux Solver
   QAction *setMUSCLSAct;
   QAction *setLinearReconstructionAct;
   QAction *setPiecewiseParabolicReconstructionAct;

   // Main Solver
   QAction *setRK4Act;
   QAction *setMacCormackAct;
   QAction *setForwardEulerAct;
   QAction *setLaxFriedrichsAct;
   QAction *setKurganovTadmor2000Act;
   QAction *setRK4KurganovTadmor2000Act;
   QAction *setKurganovTadmor2ndOrder2000Act;

   // Tabels
   QTableView *table;
   QStandardItemModel *model;

   //  Labels
   QLabel *infoLabel;
   QLabel *infoLabel2;
   QLabel *timeLabel;

   // For plotting (plotting windows)
   PlotClass *plt;

   // Data Points
   MatrixXd dataPoints;

};

#endif
