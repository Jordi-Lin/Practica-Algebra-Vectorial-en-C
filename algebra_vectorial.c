#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define N 512

void PrintVect( float vect[N], int from, int numel)
{
    int i;
    for ( i = from; i <= numel; i++ )
    {
        printf("%f ", vect[i]);
    }
    printf("\n");
}

void PrintRow( float mat[N][N], int row, int from, int numel )
{
    int i;
    for ( i = from; i <= numel; i++ )
    {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa )
{
    int i;
    for ( i = 0; i < N; i++ )
    {
        vectres[i] = vect[i]*alfa;
    }
}

float Scalar( float vect1[N], float vect2[N] )
{
    int i;
    float suma = 0;
    for ( i = 0; i < N; i++ )
    {
        suma = suma + (vect1[i]*vect2[i]);
    }
    return suma;
}

float Magnitude( float vect[N] )
{
    int i;
    float result;
    for ( i = 0; i < N; i++ )
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

float Infininorm( float M[N][N] )
{
    float max = 0;
    float suma = 0;
    int i;
    int j;
    for ( i = 0; i < N; i++ )
    {
        for ( j = 0; j < N; j++ )
        {
            suma = suma + fabs(M[i][j]);
        }
        if ( max < suma )
        {
            max = suma;
        }
        suma = 0;
    }
    return max;
}

float Onenorm( float M[N][N] )
{
    int i;
    int j;
    float max = 0;
    float suma = 0;
    for ( i = 0; i < N; i++ )
    {
        for ( j = 0; j < N; j++ )
        {
            suma = suma + fabs(M[j][i]);
        }
        if ( max < suma )
        {
            max = suma;
        }
        suma = 0;
    }
    return max;
}

float NormFrobenius( float M[N][N] )
{
    int i;
    int j;
    float suma = 0;
    for ( i = 0; i < N; i++ )
    {
        for ( j = 0; j < N; j++ )
        {
            suma = suma + (M[i][j]*M[i][j]);
        }
    }
    return sqrt(suma);
}

int DiagonalDom( float M[N][N] )
{
    int i;
    int j;
    float suma = 0;
    for ( i = 0; i < N; i++ )
    {
        for ( j = 0; j < N; j++ )
        {
            suma = suma + fabs(M[i][j]);
        }
        if ( fabs(M[i][i]) < (suma - fabs(M[i][i])) )
        {
            return 0;
        }
        suma = 0;
    }
    return 1;
}

void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] )
{
    int i;
    int j;
    float suma;
    for ( i = 0; i < N; i++ )
    {
        for ( j = 0; j < N; j++ )
        {
            suma = suma + (M[i][j]*vect[j]);
        }
        vectres[i] = suma;
        suma = 0;
    }
}

int main()
{

    // Funció per inicialitzar els arrays i les matrius amb les quals treballarem

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

    // Cridem la funció per inicialitzar els nostres vectors i matrius

    InitData();

    // Prints per mostrar per pantalla els resultats d'utilitzar les funcions desenvolupades i comparar-los amb els resultats esperats

    // A
    printf("V1 del 0 al 9 i del 256 al 265:\n");
    PrintVect( V1, 0, 9 );
    PrintVect( V1, 256, 265 );
    printf("\n");
    printf("V2 del 0 al 9 i del 256 al 265:\n");
    PrintVect( V2, 0, 9 );
    PrintVect( V2, 256, 265 );
    printf("\n");
    printf("V3 del 0 al 9 i del 256 al 265:\n");
    PrintVect( V3, 0, 9 );
    PrintVect( V3, 256, 265 );
    printf("\n");

    // B
    printf("Mat fila 0 i fila 100 del 0 al 9:\n");
    PrintRow( Mat, 0, 0, 9 );
    PrintRow( Mat, 100, 0, 9 );
    printf("\n");

    // C
    printf("MatDD fila 0 del 0 al 9 i fila 100 del 95 al 104:\n");
    PrintRow( MatDD, 0, 0, 9 );
    PrintRow( MatDD, 100, 95, 104 );
    printf("\n");

    // D
    printf("Infininorma de Mat = %.3f\n", Infininorm(Mat));
    printf("Norma ú de Mat =  %.3f\n", Onenorm(Mat));
    printf("Norma de Frobenius de Mat =  %.3f\n", NormFrobenius(Mat));
    if ( DiagonalDom(Mat) == 1 )
    {
        printf("La matriu Mat és diagonal dominant\n");
    }
    else
    {
        printf("La matriu Mat no és diagonal dominant\n")   ;  
    }
    printf("\n");
    printf("Infininorma de MatDD = %.3f\n", Infininorm(MatDD));
    printf("Norma ú de MatDD =  %.3f\n", Onenorm(MatDD));
    printf("Norma de Frobenius de MatDD =  %.3f\n", NormFrobenius(MatDD));
    if ( DiagonalDom(MatDD) == 1 )
    {
        printf("La matriu MatDD és diagonal dominant\n");
    }
    else
    {
        printf("La matriu MatDD no és diagonal dominant\n")   ;  
    }
    printf("\n");

    // E
    printf("Escalar <V1,V2> = %.6f\n", Scalar( V1, V2 ));
    printf("Escalar <V1,V3> = %.6f\n", Scalar( V1, V3 ));
    printf("Escalar <V2,V3> = %.5f\n", Scalar( V2, V3 ));
    printf("\n");

    // F
    printf("Magnitud V1 = %.6f\n", Magnitude( V1 ));
    printf("Magnitud V2 = %.6f\n", Magnitude( V2 ));
    printf("Magnitud V3 = %.6f\n", Magnitude( V3 ));
    printf("\n");

    // G
    if ( Ortogonal ( V1, V2 ) == 1 )
    {
        printf("V1 i V2 són ortogonals\n");
    }
    else
    {
        printf("V1 i V2 no són ortogonals\n");  
    }
    if ( Ortogonal ( V1, V3 ) == 1 )
    {
        printf("V1 i V3 són ortogonals\n");
    }
    else
    {
        printf("V1 i V3 no són ortogonals\n");  
    }
    if ( Ortogonal ( V2, V3 ) == 1 )
    {
        printf("V2 i V3 són ortogonals\n");
    }
    else
    {
        printf("V2 i V3 no són ortogonals\n");  
    }

    // H
    printf("\n");
    printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3x2.0 són:\n");
    MultEscalar( V3, V1, 2 );
    PrintVect( V1, 0, 9 );
    PrintVect( V1, 256, 265 );

    // I
    printf("\n");
    printf("Els elements 0 a 9 del resultat de la projecció de V2 sobre V3 són:\n");
    Projection( V2, V3, V1 );
    PrintVect( V1, 0, 9 );
    InitData();
    Projection( V1, V2, V1 );
    PrintVect( V1, 0, 9 );

    
    // J
    printf("\n");
    printf("Els elements 0 a 9 del resultat de la multiplicació de Mat per v2 són:\n");
    Matriu_x_Vector( Mat, V2, V1);
    PrintVect( V1, 0, 9 );
}