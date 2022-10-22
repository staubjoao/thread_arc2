#include <iostream>
#include <time.h>
#include <memory>
#include <thread>

int somaVetor(int n, int *vet1, int *vet2)
{
    int i, soma = 0;
    for (i = 0; i < n; i++)
        soma += (vet1[i] + vet2[i]);
    return soma;
}

class Worker
{
private:
    int result;

public:
    Worker();
    void taskSum(int n, int *v1, int *v2);
    int getResult();
};

Worker::Worker()
{
    result = 0;
}

void Worker::taskSum(int n, int *v1, int *v2)
{
    result = somaVetor(n, v1, v2);
}

int Worker::getResult()
{
    return result;
}

int somarMatriz(int n, int **matriz1, int **matriz2)
{
    int i, j, res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            res += (matriz1[i][j] + matriz2[i][j]);
    }
    return res;
}

int **gerarMatriz(int n)
{
    int i, j;
    int **matriz = new int *[n];
    for (i = 0; i < n; i++)
        matriz[i] = new int[n];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            matriz[i][j] = rand() % 99 + 1;
    }
    return matriz;
}

void apagarMatriz(int n, int **matriz)
{
    int i;
    for (i = 0; i < n; i++)
        delete[] matriz[i];
    delete[] matriz;
}

int somaThreads(int n, int **m1, int **m2)
{
    int res = 0, i;
    for (i = 0; i < n; i += 5)
    {
        Worker w1;
        Worker w2;
        Worker w3;
        Worker w4;
        Worker w5;

        std::thread t1(&Worker::taskSum, &w1, n, m1[i], m2[i]);
        std::thread t2(&Worker::taskSum, &w2, n, m1[i + 1], m2[i + 1]);
        std::thread t3(&Worker::taskSum, &w3, n, m1[i + 2], m2[i + 2]);
        std::thread t4(&Worker::taskSum, &w4, n, m1[i + 3], m2[i + 3]);
        std::thread t5(&Worker::taskSum, &w5, n, m1[i + 4], m2[i + 4]);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();

        res += w1.getResult() + w2.getResult() + w3.getResult() + w4.getResult() + w5.getResult();
    }
    return res;
}

int main()
{
    srand(time(NULL));

    double time_spent;
    clock_t begin, end;

    int n, i;
    n = 10;
    int **m1, **m2;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    int somam1 = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da soma sequencial: " << somam1 << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    int somat = somaThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da soma usando threads: " << somat << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    // n = 100;
    // int **m2 = new int *[n];
    // for (i = 0; i < n; i++)
    //     m2[i] = new int[n];

    // gerarMatriz(n, m2);
    // int somam2 = somarMatriz(n, m2);
    // int subm2 = subtrairMatriz(n, m2);

    // n = 1000;
    // int **m3 = new int *[n];
    // for (i = 0; i < n; i++)
    //     m3[i] = new int[n];

    // gerarMatriz(n, m3);
    // int somam3 = somarMatriz(n, m3);
    // int subm3 = subtrairMatriz(n, m3);

    // n = 10;
    // for (i = 0; i < n; i++)
    //     delete[] m1[i];
    // delete[] m1;

    // n = 100;
    // for (i = 0; i < n; i++)
    //     delete[] m2[i];
    // delete[] m2;

    // n = 1000;
    // for (i = 0; i < n; i++)
    //     delete[] m3[i];
    // delete[] m3;

    return 0;
}
