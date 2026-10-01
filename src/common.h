#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>
#include "straw.h"
//#define GSL_DLL
//#include <gsl/gsl_cdf.h> //use gaussian p-value function
void printProgress(double percentage);
bool hasEnding(std::string const& fullString, std::string const& ending);
