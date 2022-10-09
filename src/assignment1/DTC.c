#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define DTC_L 8 // Transform length
#define DTC_M 4 // number of coefficients to transfer
#define DTC_N 16 // Test signal length


// Headers
double pi();
void generateDTCMatrix(double H[DTC_L][DTC_L]);
void generateInverseMatrix(double matrix[DTC_L][DTC_L], double invMatrix[DTC_L][DTC_L]);
void display(double matrix[DTC_L][DTC_L]);
double determinant(double matrix[DTC_L][DTC_L], double k);

double pi()
{
    return 2 * acos(0.0);
}

void generateDTCMatrix(double H[DTC_L][DTC_L])
{
    // Looping the k'th row.
    for (int k = 0; k < DTC_L; k++)
    {
        // for k'th n'th coefficent
        for (int n = 0; n < DTC_L; n++)
        {
            // The following implementation is computed using the formula in the assignment.
            // Data has been validated using Matlab dtmtx function
            if (k == 0)
            {
                H[k][n] = sqrt((2.0 - 1.0) / DTC_L);
            }
            else
            {
                H[k][n] = sqrt((2.0 - 0.0) / DTC_L) * cos((pi() / DTC_L) * k * (n + 0.5));
            }
        }
    }
}

void generateInverseMatrix(double matrix[DTC_L][DTC_L], double invMatrix[DTC_L][DTC_L])
{
    double f = (double)DTC_L;
    double d = determinant(matrix, f);
    if (d == 0.0){
        printf("Determinant is zero, inverse not possible to compute.");
        return;
    }
    // Get co factor
    double b[DTC_L][DTC_L], fac[DTC_L][DTC_L];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++){
        for(p = 0; p < f; p++){
            m = 0;
            n = 0;
            for(i = 0; i < f; i++){
                for(j = 0; j < f; j++){
                    if(i != q && j != p){
                        b[m][n] = matrix[i][j];
                        if( n < (f - 2.0)){
                            n++;
                        }
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1.0,q + p) * determinant(b, f - 1.0);
        }
    }

    // Now find transpose and inverse

    double t[DTC_L][DTC_L];
    for (i = 0;i < f; i++)
    {
        for (j = 0;j < f; j++)
        {
            t[i][j] = fac[j][i];
        }
    }
    for (i = 0;i < f; i++)
    {
        for (j = 0;j < f; j++)
        {
            invMatrix[i][j] = t[i][j] / d;
        }
    }
    
}

// Display the matrix
void display(double matrix[DTC_L][DTC_L])
{
    for (int i = 0; i < DTC_L; i++)
    {
        for (int j = 0; j < DTC_L; j++)
            if (j == 0)
            {
                printf("%.3f", matrix[i][j]);
            }
            else
            {
                printf("\t%.3f", matrix[i][j]);
            }
        printf("\n");
    }
}

double determinant(double matrix[DTC_L][DTC_L], double k)
{
    double s = 1, det = 0.0, b[DTC_L][DTC_L];
    int i, j, m, n, c;
    if (k == 1)
    {
        return matrix[0][0];
    }
    else
    {
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    
                    b[i][j] = 0.0;
                    if (i != 0.0 && j != c)
                    {
                        b[m][n] = matrix[i][j];
                        if (n < (k - 2.0))
                        {
                            n++;
                        }
                        else
                        {
                            n = 0.0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (matrix[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }
    return det;
}