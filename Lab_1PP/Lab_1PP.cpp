
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
/*
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
*/

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

void ReadFile(std::vector<std::vector<int>>& M, const char* str, int size)
{
    int temp;
    size_t i = 0;
    size_t j = 0;
    std::ifstream Data(str);
    while (Data >> temp)
    {
        if (i < size)
        {
            M[i][j] = temp;
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

std::vector<std::vector<int>> MatrixMul(const std::vector<std::vector<int>>& M1, const std::vector<std::vector<int>>& M2, int size)
{
    std::vector<std::vector<int>> Res(size, std::vector<int>(size));
    std::ofstream Results("Result.txt", std::ios::app);
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            for (size_t k = 0; k < size; k++)
                Res[i][j] += M1[i][k] * M2[k][j];
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    Results << "Размер матрицы: " << size << "x" << size << std::endl;
    Results << "Время выполнения: " << elapsed.count() << std::endl;
    Results << "**********************"<<"\n";
    return Res;
}

int main()
{
    int m_size = 400;
    std::vector<std::vector<int>> M1(m_size, std::vector<int>(m_size));
    std::vector<std::vector<int>> M2(m_size, std::vector<int>(m_size));
    std::vector<std::vector<int>> Res(m_size, std::vector<int>(m_size));
    FillFiles(m_size);
    ReadFile(M1, "Data1.txt", m_size);
    ReadFile(M2, "Data2.txt", m_size);
    Res=MatrixMul(M1, M2, m_size);
    std::ofstream MulRes("Res_Matrix.txt");
    for (size_t i = 0; i < m_size; i++)
    {
        for (size_t j = 0; j < m_size; j++)
        {
            MulRes << Res[i][j]<<"\t";
        }
    }
    return 0;
}
