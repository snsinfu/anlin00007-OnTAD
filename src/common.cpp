#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>
//#define GSL_DLL
//#include <gsl/gsl_cdf.h> //use gaussian p-value function
constexpr char PBSTR[] = ".........................";
constexpr int PBWIDTH = 25;
using namespace std;

void printProgress(double percentage)
{
    int val = static_cast<int>(percentage * 100);
    int lpad = static_cast<int>(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

bool hasEnding(string const& fullString, string const& ending)
{
    if (fullString.length() >= ending.length())
    {
        return fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0;
    }
    else
    {
        return false;
    }
}
