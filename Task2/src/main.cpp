#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_PATH_LENGTH 256
#define NUM_THREADS 4

typedef struct {
    char file_path[ MAX_PATH_LENGTH ];
    char target_string[ MAX_LINE_LENGTH ];
    // 补全结构体
} ThreadData;
void *search_file( void *arg ) {
    ThreadData *data = (ThreadData *) arg;
    char line[ MAX_LINE_LENGTH ];

    FILE *file = fopen( data->file_path, "r" );
    if ( file == NULL ) {
        perror( "Error opening file" );
        pthread_exit( NULL );
    }

    int line_number = 1;

    // 执行文本搜素
    while ( fgets( line, MAX_LINE_LENGTH, file ) != NULL ) {
        printf( "%s", line );
    }
    // 文件关闭&线程退出
    fclose( file );
    pthread_exit( NULL );
}

void search_files( const char *folder_path, const char *target_string ) {
    DIR *directory;
    struct dirent *entry;

    directory = opendir( folder_path );
    if ( directory == NULL ) {
        perror( "Error opening directory" );
        return;
    }

    pthread_t threads[ 256 ];
    ThreadData thread_data[ 256 ];
    int num_threads = 0;

    //执行搜索任务
    while ( ( entry = readdir( directory ) ) != NULL ) {
        if ( entry->d_type == DT_REG ) {
            strcpy( thread_data[ num_threads ].file_path, folder_path );
            strcat( thread_data[ num_threads ].file_path, "/" );
            strcat( thread_data[ num_threads ].file_path, entry->d_name );
            strcpy( thread_data[ num_threads ].target_string, target_string );
        }
        //为每个线程分配任务
    }
    closedir( directory );

    //线程同步
}

int main() {
    char folder_path[ 256 ] =
        "/home/usami/workU/ParallelComputing/OpenMP/Task2/texts";
    char target_string[ 256 ];

    scanf( "%s", target_string );

    search_files( folder_path, target_string );

    return 0;
}