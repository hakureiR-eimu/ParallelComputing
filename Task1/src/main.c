#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int A_length;
int B_length;
int A[ 100 ] = { 0 };
int B[ 100 ] = { 0 };
//使用OpenMP指令并行化计算过程实现卷积
void matrix_multiply( int A[], int B[] ) {
    // A = (int **) A;
    // B = (int **) B;
    int n = sqrt( A_length );
    int m = sqrt( B_length );

    int *res = (int *) malloc( 100 * sizeof( int ) );
    int res_length = n - m + 1;

    // #pragma omp parallel for collapse( 2 )
    for ( int i = 0; i < res_length; ++i ) {
        for ( int j = 0; j < res_length; ++j ) {
            int val = 0;
            for ( int Bi = 0; Bi < m; Bi++ ) {
                for ( int Bj = 0; Bj < m; Bj++ ) {
                    val += A[ ( i + Bi ) * n + ( j + Bj ) ] * B[ Bi * m + Bj ];
                }
            }
            res[ i * res_length + j ] = val;
        }
    }
    printf( "Res is below:\n" );
    for ( int i = 0; i < res_length; ++i ) {
        for ( int j = 0; j < res_length; ++j ) {
            printf( "%d ", res[ i * res_length + j ] );
        }
        printf( "\n" );
    }
}
// Input:1 2 3 4 5 6 7 8 9
//       0 0 0 1
void input() {
    char ch;
    while ( 1 ) {
        scanf( "%d", &A[ A_length ] );
        A_length++;

        ch = getchar();
        if ( ch == '\n' ) {
            break;
        } else if ( ch != ' ' && ch != '\t' ) {
            ungetc( ch, stdin );
        }
    }
    while ( 1 ) {
        if ( scanf( "%d", &B[ B_length ] ) == 1 ) B_length++;

        ch = getchar();
        if ( ch == EOF ) {
            break;
        }
        if ( ch == '\n' ) {
            break;
        } else if ( ch != ' ' && ch != '\t' ) {
            ungetc( ch, stdin );
        }
    }
    printf( "A_len:%d,B_len:%d\n", A_length, B_length );
    // for ( int i = 0; i < A_length; ++i ) {
    //     printf( "%d ", A[ i ] );
    // }
    // printf( "\n" );
    // B_length = 4;
    // for ( int i = 0; i < B_length; ++i ) {
    //     printf( "%d ", B[ i ] );
    // }
    printf( "\n" );
}
int main( int argc, char **argv ) {
    clock_t start;
    clock_t end;

    A_length = 0;
    B_length = 0;
    int val;
    int res;

    int isChangeLine = 0;

    // int *A = (int *) malloc( 100 * sizeof( int ) );
    // int *B = (int *) malloc( 100 * sizeof( int ) );
    input();
    start = clock();
    matrix_multiply( A, B );
    end = clock();

    clock_t time_used_in_circles = end - start;
    printf( "Excuted time :%d circles\n", time_used_in_circles );
    return 0;
}
