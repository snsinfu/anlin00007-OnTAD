#include "step3.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>

/*---------------------------------------------------------------*/
/* Step3: remove distance effect
 *    Input: data matrix
 *    
 *                      **/
void HiCnorm(vector<vector<double>>& x, int maxsz)
{
    const int l = static_cast<int>(x.size());
    printf("\n");

    for (int i = 0; i < min(l - 1, maxsz); i++)
    {
        printProgress(static_cast<double>(i + 1) / static_cast<double>(min(l - 1, maxsz)));
        vector<double> tx(static_cast<size_t>(l - i));
        for (int j = 0; j < l - i; j++)
        {
            tx[j] = x[j][j + i];
        }
        double tm = 0, ts = 0;
        for (int j = 0; j < l - i; j++)
        {
            x[j][j + i] = x[j + i][j] = tx[j];
            tm += tx[j];
            ts += tx[j] * tx[j];
        }
        tm /= static_cast<double>(l - i);
        ts = sqrt(max(1e-6, ts / static_cast<double>(l - i) - tm * tm));
        for (int j = 0; j < l - i; j++)
        {
            x[j][j + i] = (x[j][j + i] - tm) / ts + 1.;
            if (i > 0)
            {
                x[j + i][j] = (x[j + i][j] - tm) / ts + 1.;
            }
        }
    }
}
