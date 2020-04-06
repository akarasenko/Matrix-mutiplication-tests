#include <iostream>

void production(int M, int K, int N, double* A, double* B, double* prod)
{
    if (M == 0 || K == 0 || N == 0)
        throw std::invalid_argument("Matrix with zero string or column number");

    if (A == NULL || B == NULL)
        throw std::invalid_argument("One of matrices is NULL");

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            prod[i * N + j] = 0;
            for (int k = 0; k < K; k++)
                prod[i * N + j] += A[i * K + k] * B[k * N + j];
        }
    }
};

int main()
{
    return 0;
};