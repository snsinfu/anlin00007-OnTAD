#pragma once
#include "common.h"

void cumsum(std::vector<std::vector<double>> const& x, std::vector<std::vector<double>>& sx);                           // Step2
void getScore(std::vector<std::vector<double>> const& sx, int maxsz, std::vector<std::vector<double>>& score);          // Step2
void calMins(std::vector<std::vector<double>> const& score, std::vector<std::vector<bool>>& lm, int hsz, double ldiff); // Step2
void setPair(std::vector<std::vector<bool>> const& lm, std::vector<std::vector<bool>>& sel);                            // Step2
