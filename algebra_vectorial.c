#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define N 512

void PrintVect( float vect[N], int from, int numel)
{
    int i;
    for ( i = from; i <= from+numel; i++)
    {
        printf("%f ", vect[i]);
    }
    printf("\n");
}

void PrintRow( float mat[N][N], int row, int from, int numel )
{
    int i;
    for ( i = from; i <= from+numel; i++)
    {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa )
{
    int i;
    for ( i = 0; i < N; i++)
    {
        vectres[i] = vect[i]*alfa;
    }
}

float Scalar( float vect1[N], float vect2[N] )
{
    int i;
    int suma;
    for ( i=0; i < N; i++)
    {
        suma = suma + (vect1[i]*vect2[i]);
    }
    return suma;
}

float Magnitude( float vect[N] )
{
    int i;
    int result;
    for ( i=0; i < N; i++)
    {
        result = sqrt(Scalar( vect, vect ));
    }
    return result;
}

int Ortogonal( float vect1[N], float vect2[N] )
{
    if ( Scalar( vect1, vect2 ) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Projection( float vect1[N], float vect2[N], float vectres[N] )
{
    float alfa = (( Scalar( vect1, vect2 ) / Magnitude( vect2 ) ));
    return MultEscalar( vect2, vectres, alfa );
}

int main()
{
    float Mat[N][N], MatDD[N][N];
    float V1[N], V2[N], V3[N];
    void InitData()
    {
        int i,j;
        srand(334411);
        for ( i = 0; i < N; i++ )
            for ( j = 0; j < N; j++)
            {
                Mat [i] [j] = (((i*j)%3) ?-1:1)*(100.0*(rand() / (1.0*RAND_MAX)));
                if ( (abs( i - j ) <= 3) && ( i != j))
                MatDD [i] [j] = (((i*j)%3) ?-1:1)*(rand() / (1.0*RAND_MAX));
                else if ( i==j )
                MatDD [i] [j] = (((i*j)%3) ?-1:1)*(10000.0*(rand() / (1.0*RAND_MAX)));
                else MatDD [i] [j] = 0.0;
            }
        for ( i = 0; i < N; i++)
        {
            V1 [i] = (i < N/2)?(((i*j)%3)?-1:1)*(100.0*(rand() / (1.0*RAND_MAX))):0.0;
            V2 [i] = (i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
            V3 [i] = (((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
        }
    }
}