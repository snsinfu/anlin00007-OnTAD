#pragma once
#include "common.h"

void loadMatrix(const std::string& fname, std::vector<std::vector<double>>& x, int maxsz); // Step1
void loadMatrixFromHiC(
    const std::string& fname,
    std::vector<std::vector<double>>& x,
    int maxsz,
    const std::string& hic_norm,
    int resolution,
    const std::string& chrnum,
    int chrlength);
