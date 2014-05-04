#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <string>

const double PI_CONST = 3.1415926535897932384626433832795028841971693993751058209749;

//Default values
const string MainSolverDefault = "RK4";
const string FluxSolverDefault = "LinearReconstruction";
const double DelaySecondDefault = 0.2;
const int RealizationTimeStepDefault = 10;
const double SimulationErrorToleranceDefault = 0.1;

// 1D simulation
const string InitialConditionNameDefault = "Sin";
const int GridSizeDefault = 100;

// 2D simulation
const int XGridSizeDefault = 400;
const int YGridSizeDefault = 250;
const double XVelocityDefault = 1.0;
const double YVelocityDefault = -1.0;


#endif
