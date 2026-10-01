#pragma once
#include "common.h"

struct TAD
{
    std::vector<std::vector<int>> bound;
    std::vector<int> level;
    std::vector<double> score, mean;
};

struct DATA
{
    std::string fname;
    std::vector<std::vector<double>> x;
    std::vector<std::vector<bool>> sel;
    TAD tad;
};

void dpcall(std::vector<std::vector<double>> const& x, std::vector<std::vector<double>> const& sx, int st, int ed, int minsz, int maxsz, double penalty, std::vector<std::vector<bool>> const& sel, double& score, double& mean);
void getBound(int st, int ed, int level, std::vector<std::vector<double>> const& x, std::vector<std::vector<double>> const& sx, TAD& tad);
void outputTAD(const std::string& fname, TAD const& tad);
void runone(DATA& data, int minsz, int maxsz, double penalty, clock_t timeed, clock_t time0);
void outputBED(const std::string& fnamebed, TAD const& tad, const std::string& chrnum, int chrlength, int res);
