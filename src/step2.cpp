#include "step2.h"
/*---------------------------------------------------------------*/
/* Step2: calculate local minimum
 *    Input: data from step1
 *    
 *                      **/

void cumsum(vector<vector<double>> const& x, vector<vector<double>>& sx) //cumsum the value vertically and horizontally, then the value of each cell (i,j) represent the sum of matrix[0:i,0:j]
{
    const size_t l = x.size();
    sx = x;
    for (size_t i = 0; i < l; i++)
    {
        printProgress(static_cast<double>(i + 1) / static_cast<double>(l));
        for (size_t j = 1; j < l; j++)
        {
            sx[i][j] += sx[i][j - 1];
        }
        if (i > 0)
        {
            for (size_t j = 0; j < l; j++)
            {
                sx[i][j] += sx[i - 1][j];
            }
        }
    }
}

void getScore(vector<vector<double>> const& sx, int maxsz, vector<vector<double>>& score) //use matrix[0:i,0:(i+j)] minus matrix[0:i,0:i] and minus (matrix[0:i-j,0:i+j]-matrix[0:i-j,0:i])
{
    const int l = static_cast<int>(sx.size());

    score.clear();
    score.resize(static_cast<size_t>(l), vector<double>(static_cast<size_t>(maxsz), 0));

    for (int i = 1; i < l; i++)
    {
        printProgress(static_cast<double>(i + 1) / static_cast<double>(l));
        for (int j = 0; j < maxsz; j++)
        {
            score[i][j] = sx[i - 1][min(l - 1, i + j + 1)] - sx[i - 1][i];
            if (i - j - 2 >= 0)
            {
                score[i][j] += -sx[i - j - 2][min(l - 1, i + j + 1)] + sx[i - j - 2][i];
            }
            const int k = min(l - i, j + 1) * min(i, j + 1);
            score[i][j] /= static_cast<double>(k);
        }
    }
}

void calMins(vector<vector<double>> const& score, vector<vector<bool>>& lm, int hsz, double ldiff) //compare score for each bin with adjacent bins and determine local minimum
{
    const int l = static_cast<int>(score.size());
    const int n = static_cast<int>(score[0].size());
    lm.clear();
    lm.resize(static_cast<size_t>(l), vector<bool>(static_cast<size_t>(n), false));

    vector<int> map;
    for (int i = 0; i < l; i++)
    {
        double m = 0, s = 0;
        for (int j = 0; j < n; j++)
        {
            m += score[i][j];
            s += score[i][j] * score[i][j];
        }
        if (s > m * m / static_cast<double>(n))
        {
            map.push_back(i);
        }
    }
    if (static_cast<int>(map.size()) < 2)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printProgress(static_cast<double>(i + 1) / static_cast<double>(n));
        double m = 0, s = 0;
        for (int j = 1; j < static_cast<int>(map.size()); j++)
        {
            m += score[map[j]][i] - score[map[j - 1]][i];
            s += pow(score[map[j]][i] - score[map[j - 1]][i], 2.);
        }
        m /= static_cast<double>(static_cast<int>(map.size()) - 1);
        s = sqrt(s / static_cast<double>(static_cast<int>(map.size()) - 1) - m * m);
        double cut = s * ldiff; // 1.96 std from mean
        for (int j = 0; j < static_cast<int>(map.size()); j++)
        {
            double mins = score[map[j]][i], maxs = mins;
            int k = max(0, j - hsz);
            for (; k < min(static_cast<int>(map.size()), j + hsz + 1); k++)
            {
                if (mins >= score[map[k]][i] && k != j)
                {
                    break;
                }
                maxs = max(maxs, score[map[k]][i]);
            }
            if (k >= min(l, j + hsz + 1) && maxs - mins > cut)
            {
                lm[map[j]][i] = true;
            }
        }
        lm[0][i] = lm[l - 1][i] = true;
    }
}

void setPair(vector<vector<bool>> const& lm, vector<vector<bool>>& sel) //create a sel matrix that mark local minimum bins on diag and edges.
{
    const int l = static_cast<int>(lm.size());
    const int n = static_cast<int>(lm[0].size());
    sel.clear();
    sel.resize(static_cast<size_t>(l), vector<bool>(static_cast<size_t>(l), false));

    for (int i = 0; i < n; i++)
    {
        vector<int> map;
        for (int j = 0; j < l; j++)
        {
            if (lm[j][i])
            {
                map.push_back(j);
            }
        }
        for (int j = 0; j < static_cast<int>(map.size()); j++)
        {
            for (int k = 1; k <= 5; k++)
            {
                if (j + k >= static_cast<int>(map.size()))
                {
                    break;
                }
                sel[0][map[j]] = sel[0][map[j + k]] = sel[map[j]][l - 1] = sel[map[j + k]][l - 1] = sel[map[j]][map[j + k]] = true;
            }
        }
    }
}
