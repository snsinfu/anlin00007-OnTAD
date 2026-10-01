#include "common.h"

using namespace std;

void loadMatrix(const string& fname, vector<vector<double>>& x, int maxsz); // Step1
void loadMatrixFromHiC(
    const string& fname,
    vector<vector<double>>& x,
    int maxsz,
    const string& hic_norm,
    int resolution,
    const string& chrnum,
    int chrlength);
