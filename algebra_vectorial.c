#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define N 512

void PrintVect( float vect[N], int from, int numel) 
{
    int i;
    for ( i = from; i <= numel; i++ ) // Bucle for que recorre des d'una posició donada fins a una altre posició també donada
    {
        printf("%f ", vect[i]); // Imprimim la posició i del vector per a cada iteració
    }
    printf("\n");
}

void PrintRow( float mat[N][N], int row, int from, int numel )
{
    int i;
    for ( i = from; i <= numel; i++ ) // Bucle for que recorre des d'una posició donada fins a una posició final també donada
    {
        printf("%f ", mat[row][i]); // Imprimim la columna i d'una fila pasada com a paràmetre per a cada iteració
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa )
{
    int i;
    for ( i = 0; i < N; i++ ) // Bucle for que recorre tot el vector pasat com a paràmetre
    {
        vectres[i] = vect[i]*alfa; // Assignem al vector resultant passat com a paràmetre el producte entre el valor de la posició i del vector i la constant passat com a paràmetre per a cada iteració 
    }
}

float Scalar( float vect1[N], float vect2[N] )
{
    int i;
    float suma = 0;
    for ( i = 0; i < N; i++ ) // Bucle for que recorre tot el vector passat com a paràmetre
    {
        suma = suma + (vect1[i]*vect2[i]); // Sumem a una variable declarada el producte del valor de la posició i del primer vector amb el valor de la mateixa posició del segon vector, vectors els quals estan passats com a paràmetre 
    }
    return suma; // Retornem el valor de la variable suma que surt com a resultat del bucle anterior
}

float Magnitude( float vect[N] )
{
    float result;
    result = sqrt(Scalar( vect, vect )); // A una variable declarada li assignem el resultat de fer l'arrel quadrada del producte escalar de dos vectors (aquests sent el mateix vector, el qual està passat com a paràmetre)
    return result; // Retornem el resultat del valor de la variable declarada després d'haver fet el bucle anterior
}

int Ortogonal( float vect1[N], float vect2[N] )
{
    if ( Scalar( vect1, vect2 ) == 0 ) // Comprovem si el resultat de fer l'escalar entre els dos vectors passats com a paràmetre és igual a 0
    {
        return 1; // Si és igual a zero la funció retorna 1
    }
    else
    {
        return 0; // Si no és igual a zero la funció retorna 0
    }
}

void Projection( float vect1[N], float vect2[N], float vectres[N] )
{
    float alfa = (( Scalar( vect1, vect2 ) / Magnitude( vect2 ) )); // Declarem una variable i li assignem el resultat de fer la divisió entre el producte escalar de dos vectors passats com a paràmetre i la magnitud del segon vector
    return MultEscalar( vect2, vectres, alfa ); // Retornem el resultat de multiplicar cada component d'un vector per una constant. La constant serà la variable d'abans i per fer aquesta operació fem servir una funció ja programada anteriorment i només hem de pasar-li tres paràmetres: el vector a operar, el vector per afegir el resultat i la constant
}

float Infininorm( float M[N][N] )
{
    float max = 0;
    float suma = 0;
    int i;
    int j;
    for ( i = 0; i < N; i++ ) // Bucle for que recorre cada fila (per recórrer la següent fila s'ha de recórrer totes les columnes de la fila anterior)
    {
        for ( j = 0; j < N; j++ ) // Bucle for que recorre cada columna 
        {
            suma = suma + fabs(M[i][j]); // A una variable declarada li sumem el valor absolut de la posició actual on estem de la matriu 
        }
        if ( max < suma ) // Quan acabem d'iterar una fila observem si el resultat de les sumes anteriors és més gran que una variable declarada per guardar el valor més gran.
        {
            max = suma; // Si és compleix l'anterior assignem el valor del resultat de les sumes actuals a la variable per guardar el valor més gran.  
        }
        suma = 0; // Reiniciem la variable suma a zero per tal de calcular el resultat de les sumes de la següent fila
    }
    return max;
}

float Onenorm( float M[N][N] ) // Fa el mateix que a la funció anterior, però en comptes de sumar valors d'una fila suma els valors d'una columna.
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
    for ( i = 0; i < N; i++ ) // Bucle for que recorre cada fila de la matriu
    {
        for ( j = 0; j < N; j++ ) // Bucle for que recorre cada columna de la matriu
        {
            suma = suma + (M[i][j]*M[i][j]); // A una variable declarada li sumem el resultat de multiplicar la posició actual on estem per si mateix o sigui el quadrat de la posició
        }
    }
    return sqrt(suma); // Retornem l'arrel quadrada de la variable declarada després de les iteracions anteriors
}

int DiagonalDom( float M[N][N] )
{
    int i;
    int j;
    float suma = 0;
    for ( i = 0; i < N; i++ ) // Bucle for que recorre cada fila
    {
        for ( j = 0; j < N; j++ ) // Bucle for que recorre cada columna
        {
            suma = suma + fabs(M[i][j]); // A una variable declarada li sumem el valor absolut de la posició actual de la matriu
        }
        if ( fabs(M[i][i]) < (suma - fabs(M[i][i])) ) // Quan acaba el bucle anterior, acabem d'iterar tota una fila sencera i observem si el valor absolut de la posició de la diagonal és més petit que la suma dels valors absoluts de totes les altres posicions de la fila 
        {
            return 0; // Si es compleix la condició anterior retornem 0 i acabem els bucles
        }
        suma = 0; // Reiniciem la variable declarada per tal de sumar els valors de la següent fila sense tenir en compte valors d'altres files
    }
    return 1; // Si iterem tota la matriu i mai es compleix la condició dins dels bucles, retornem 1
}

void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] )
{
    int i;
    int j;
    float suma;
    for ( i = 0; i < N; i++ ) // Bucle for que recorre cada fila
    {
        for ( j = 0; j < N; j++ ) // Bucle for que recorre cada columna
        {
            suma = suma + (M[i][j]*vect[j]); // A una variable declarada li sumem el producte entre el valor de la posició actual on estem de la matriu i el valor de la posició de columna on estem actualment del vector
        }
        vectres[i] = suma; // El resultat de les sumes anteriors l'afegim a un vector resultant passat com a paràmetre
        suma = 0; // Reiniciem la variable declarada per tal d'iterar la següent fila sense tenir en compte les sumes d'altres files
    }
}

//    int Jacobi ( float M[N][N], float vect[N], float vectres[N], unsigned iter )
//    {
//        float S[N][N]; // Matriu amb tots els valors de la matriu passada com a paràmtre menys els valors dins de la diagonal
//        float T[N][N]; // Matriu amb només els valors de la diagonal de la matriu passada com a paràmetre
//        int i;
//        int j;
//        int a;
//        float suma = 0;
//        if ( DiagonalDom(M) == 0 ) // Observem si la matriu és diagonal dominant o sigui en fer DiagonalDom(Matriu) ens ha de donar 1
//        {
//            return 0; // Si no dona 1 sinó 0 retornem 0
//        }
//        for ( i = 0; i < N; i++ ) // Bucle for que recorre les files de la matriu passada com a paràmetre
//        {
//           for ( j = 0; j < N; j++ ) // Bucle for que recorre les columnes de la matriu passada com a paràmetre
//            {
//                if ( j == i ) // Si estem en la diagonal
//                {
//                    T[i][j] = M[i][j]; // Afegim a la matriu declarada pels valors de la diagonal el valor de la diagonal el valor de la diagonal de la matriu passada com a paràmetre
//                    S[i][i] = 0; // Afegim a la matriu declarada per la resta dels valors el valor de zero
//                }
//                else // Si no estem en la diagonal
//                {
//                    S[i][j] = M[i][j]; // Afegim a la matriu declarada per la resta dels valors el valor de la posició actual de la matriu que estem iterant
//                    T[i][i] = 0; // Afegim a la matriu declarada per els valors de la diagonal el valor de zero
//                }
//            }
//        }
//        for ( a = 0; a < iter; a++ ) // Anem iterant tantes vegades com ens indica el paràmetre de iteracions
//        {
//            for ( i = 0; i < N; i++ ) // Bucle for per les files
//            {
//                for ( j = 0; j < N; j++ ) // Bucle for per les columnes
//                {
//                  asdas
//                }
//            }
//        }
//    }

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