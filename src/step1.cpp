#include "step1.h"

using namespace std;
/*---------------------------------------------------------------*/
/* Step1: read input matrix
 *    Input: matrix file
 *    Requirement: input file must be a N*N matrix, seperated by TAB.
 *                      **/

int num_space(const char* str, size_t len)
{
    int num = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (str[i] == ' ' || str[i] == '\t')
        {
            num++;
        }
    }

    return num + 1;
}

constexpr size_t kMaxLineLen = 10000000;

void loadMatrix(const string& fname, vector<vector<double>>& x, int maxsz) //read input file line by line and only store the value near diagonal
{
    int k, n = 0, L = 0;
    size_t l = 0;
    vector<char> tmp(kMaxLineLen, '\0');
    x.clear();

    FILE* f = fopen(fname.c_str(), "r");
    if (f == nullptr)
    {
        printf("Cannot open %s\n", fname.c_str());
        exit(EXIT_FAILURE); //stop if cannot find file
    }
    int nrow = 0;                                                         //name a variable to store row number
    while (fgets(tmp.data(), static_cast<int>(tmp.size()), f) != nullptr) //read the file line by line with maximum string in each line as kMaxLineLen
    {
        l = strlen(tmp.data()); //the number of bytes of each row

        vector<double> tx(L, 0);
        k = 0;
        size_t j = 0;
        const int lo = n - maxsz;
        const int hi = n + maxsz;
        while (j < l)
        {
            if (L == 0)
            {
                if (k > maxsz)
                {
                    tx.push_back(0);
                }
                else
                {
                    tx.push_back(atof(&tmp[j]));
                }
                k++;
            }
            else
            {
                if (k >= lo && k <= hi)
                {
                    tx[k] = atof(&tmp[j]);
                }
                k++;
                if (k > hi)
                {
                    break;
                }
            }
            j++;
            while (j < l && tmp[j] != ' ' && tmp[j] != '\t')
            {
                j++;
            }
            if (j < l)
            {
                j++;
            }
        }
        if (L == 0)
        {
            L = k;
        }
        printProgress(static_cast<double>(n + 1) / static_cast<double>(L));
        if (x.empty())
        {
            x.resize(static_cast<size_t>(L));
        }
        if (n >= static_cast<int>(x.size()))
        {
            printf("Input doesn't match N*N format or was not seperated by TAB or space!");
            exit(-3);
        }
        x[n++] = tx;
        nrow++;
    }
    if (nrow != num_space(tmp.data(), l))
    {
        printf("Input doesn't match N*N format or was not seperated by TAB or space!");
        exit(-3); //stop if input is not a N*N matrix
    }
    fclose(f);
}

/**
 * Load matrix from .hic file, also only read values near diagonal
 * 
*/
void loadMatrixFromHiC(
    const string& fname,
    vector<vector<double>>& x,
    int maxsz,
    const string& hic_norm,
    int resolution,
    const string& chrnum,
    int chrlength)
{
    if (resolution <= 0)
    {
        printf("Error: resolution must be a positive integer for .hic input\n");
        exit(-1);
    }
    if (chrlength <= 0)
    {
        printf("Error: chrlength must be a positive integer for .hic input\n");
        exit(-1);
    }
    string matrixType = "observed";
    string unit = "BP";
    vector<contactRecord> records;

    string chr_name = chrnum;
    string chrloc = chr_name + ":0" + ":" + to_string(chrlength);
    records = straw(matrixType, hic_norm, fname, chrloc, chrloc, unit, static_cast<int32_t>(resolution));

    int L;
    if ((chrlength % resolution) == 0)
    {
        L = chrlength / resolution;
    }
    else
    {
        L = (chrlength / resolution) + 1;
    }

    for (int i = 0; i < L; i++)
    {
        vector<double> tx(L, 0);
        x.push_back(tx);
    }

    size_t length = records.size();
    int start = 0, end = 0;
    int print_per_count = max(1, static_cast<int>(length / 20));
    for (size_t i = 0; i < length; i++)
    {
        start = records[i].binX / resolution;
        end = records[i].binY / resolution;
        if (start >= 0 && start < L && end >= 0 && end < L && abs(end - start) <= maxsz)
        {
            x[start][end] = records[i].counts;
        }
        if (print_per_count > 0 && (i % print_per_count) == 0)
        {
            printProgress(static_cast<double>(i) / static_cast<double>(length));
        }
    }
    printProgress(1.0);
}
