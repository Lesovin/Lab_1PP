
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include "mpi.h"

void Print_Matrix(int* Mat, int size)
{
    std::cout << "Multiplication: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << Mat[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
}

void FillFiles(int size)
{
    int num = size * size;
    std::ofstream Data1("Data1.txt");
    for (size_t i = 0; i < num; i++) Data1 << rand() % 100<<"\t";
    std::ofstream Data2("Data2.txt");
    for (size_t i = 0; i < num; i++) Data2 << rand() % 100 << "\t";
    Data1.close();
    Data2.close();
}

void ReadFile(int* M, const char* str, int size)
{
    int temp;
    size_t i = 0;
    size_t j = 0;
    std::ifstream Data(str);
    while (Data >> temp)
    {
        if (i < size)
        {
            M[i * size + j] = temp;
            j++;
            if (j == size)
            {
                i++;
                j = 0;
            }
        }
    }
    Data.close();
}

int main(int argc, char * argv[])
{
    double start, stop;
    int i, j, k, l;
    int* A, * B, * C, * buffer, * ans;
    int size = 1000;
    int rank, numprocs, line;

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); 

    line = size / numprocs;
    A = new int[size * size];
    B = new int[size * size];
    C = new int[size * size];
    buffer = new int[size * line]; 
    ans = new int[size * line]; 

    if (rank == 0)
    {
        
        for (i = 0; i < size; i++) 
            for (j = 0; j < size; j++)
                A[i * size + j] = 1;

        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                B[i * size + j] = 2;
      
        start = MPI_Wtime();
        
        for (i = 1; i < numprocs; i++) {
            MPI_Send(B, size * size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
        for (l = 1; l < numprocs; l++) {
            MPI_Send(A + (l - 1) * line * size, size * line, MPI_INT, l, 1, MPI_COMM_WORLD);
        }
        
        for (k = 1; k < numprocs; k++) {
            MPI_Recv(ans, line * size, MPI_INT, k, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  
            for (i = 0; i < line; i++) {
                for (j = 0; j < size; j++) {
                    C[((k - 1) * line + i) * size + j] = ans[i * size + j];
                }
            }
        }
       
        for (i = (numprocs - 1) * line; i < size; i++) {
            for (j = 0; j < size; j++) {
                int temp = 0;
                for (k = 0; k < size; k++)
                    temp += A[i * size + k] * B[k * size + j];
                C[i * size + j] = temp;
            }
        }

 
        stop = MPI_Wtime();

        std::cout << "Rank: " << rank << "\nTime: " << stop - start << " s" << std::endl;

        //Print_Matrix(C, size);

        delete[] A;
        delete[] B;
        delete[] C;
        delete[] buffer;
        delete[] ans;
    }

    
    else {
        MPI_Recv(B, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Recv(buffer, size * line, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < line; i++) {
            for (j = 0; j < size; j++) {
                int temp = 0;
                for (k = 0; k < size; k++)
                    temp += buffer[i * size + k] * B[k * size + j];
                ans[i * size + j] = temp;
            }
        }
        MPI_Send(ans, line * size, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
