
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

void PrintMatrix(const std::vector<std::vector<int>>& M)
{
    for (size_t i = 0; i < 400; i++)
    {
        for (size_t j = 0; j < 400; j++)
        {
            std::cout << M[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void FillFiles()
{
    std::ofstream Data1("Data1.txt");
    for (size_t i = 0; i < 160000; i++) Data1 << rand() % 100<<"\t";
    std::ofstream Data2("Data2.txt");
    for (size_t i = 0; i < 160000; i++) Data2 << rand() % 100 << "\t";
    Data1.close();
    Data2.close();
}

void ReadFile(std::vector<std::vector<int>>& M, const char* str)
{
    int temp;
    size_t i = 0;
    size_t j = 0;
    std::ifstream Data(str);
    while (Data >> temp)
    {
        if (i < 400)
        {
            M[i][j] = temp;
            j++;
            if (j == 400)
            {
                i++;
                j = 0;
            }
        }
    }
    Data.close();
}

std::vector<std::vector<int>> MatrixMul(const std::vector<std::vector<int>>& M1, const std::vector<std::vector<int>>& M2)
{
    std::vector<std::vector<int>> Res(400, std::vector<int>(400));
    std::ofstream Results("Result.txt", std::ios::app);
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 400; i++)
    {
        for (size_t j = 0; j < 400; j++)
        {
            for (size_t k = 0; k < 400; k++)
                Res[i][j] += M1[i][k] * M2[k][j];
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    Results << "Размер матрицы: " << 400 << "x" << 400 << std::endl;
    Results << "Время выполнения: " << elapsed.count() << std::endl;
    Results << "**********************"<<"\n";
    return Res;
}

int main()
{
    std::vector<std::vector<int>> M1(400, std::vector<int>(400));
    std::vector<std::vector<int>> M2(400, std::vector<int>(400));
    std::vector<std::vector<int>> Res(400, std::vector<int>(400));
    FillFiles();
    ReadFile(M1, "Data1.txt");
    ReadFile(M2, "Data2.txt");
    Res=MatrixMul(M1, M2);
    std::ofstream MulRes("Res_Matrix.txt");
    for (size_t i = 0; i < 400; i++)
    {
        for (size_t j = 0; j < 400; j++)
        {
            MulRes << Res[i][j]<<"\t";
        }
    }
    return 0;
}
