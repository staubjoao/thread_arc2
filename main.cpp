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

int subVetor(int n, int *vet1, int *vet2)
{
    int i, sub = 0;
    for (i = 0; i < n; i++)
        sub += (vet1[i] - vet2[i]);
    return sub;
}

class Worker
{
private:
    int result;

public:
    Worker();
    void taskSum(int n, int *v1, int *v2);
    void taskSub(int n, int *v1, int *v2);
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

void Worker::taskSub(int n, int *v1, int *v2)
{
    result = subVetor(n, v1, v2);
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

int subtrairMatirz(int n, int **matriz1, int **matriz2)
{
    int i, j, res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            res += (matriz1[i][j] - matriz2[i][j]);
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
    for (i = 0; i < n; i += 10)
    {
        Worker w1;
        Worker w2;
        Worker w3;
        Worker w4;
        Worker w5;
        Worker w6;
        Worker w7;
        Worker w8;
        Worker w9;
        Worker w10;

        std::thread t1(&Worker::taskSum, &w1, n, m1[i], m2[i]);
        std::thread t2(&Worker::taskSum, &w2, n, m1[i + 1], m2[i + 1]);
        std::thread t3(&Worker::taskSum, &w3, n, m1[i + 2], m2[i + 2]);
        std::thread t4(&Worker::taskSum, &w4, n, m1[i + 3], m2[i + 3]);
        std::thread t5(&Worker::taskSum, &w5, n, m1[i + 4], m2[i + 4]);
        std::thread t6(&Worker::taskSum, &w6, n, m1[i + 5], m2[i + 5]);
        std::thread t7(&Worker::taskSum, &w7, n, m1[i + 6], m2[i + 6]);
        std::thread t8(&Worker::taskSum, &w8, n, m1[i + 7], m2[i + 7]);
        std::thread t9(&Worker::taskSum, &w9, n, m1[i + 8], m2[i + 8]);
        std::thread t10(&Worker::taskSum, &w10, n, m1[i + 9], m2[i + 9]);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();

        res += w1.getResult() + w2.getResult() + w3.getResult() + w4.getResult() + w5.getResult() + w6.getResult() + w7.getResult() + w8.getResult() + w9.getResult() + w10.getResult();
    }
    return res;
}

int subsThreads(int n, int **m1, int **m2)
{
    int res = 0, i;
    for (i = 0; i < n; i += 10)
    {
        Worker w1;
        Worker w2;
        Worker w3;
        Worker w4;
        Worker w5;
        Worker w6;
        Worker w7;
        Worker w8;
        Worker w9;
        Worker w10;

        std::thread t1(&Worker::taskSub, &w1, n, m1[i], m2[i]);
        std::thread t2(&Worker::taskSub, &w2, n, m1[i + 1], m2[i + 1]);
        std::thread t3(&Worker::taskSub, &w3, n, m1[i + 2], m2[i + 2]);
        std::thread t4(&Worker::taskSub, &w4, n, m1[i + 3], m2[i + 3]);
        std::thread t5(&Worker::taskSub, &w5, n, m1[i + 4], m2[i + 4]);
        std::thread t6(&Worker::taskSub, &w6, n, m1[i + 5], m2[i + 5]);
        std::thread t7(&Worker::taskSub, &w7, n, m1[i + 6], m2[i + 6]);
        std::thread t8(&Worker::taskSub, &w8, n, m1[i + 7], m2[i + 7]);
        std::thread t9(&Worker::taskSub, &w9, n, m1[i + 8], m2[i + 8]);
        std::thread t10(&Worker::taskSub, &w10, n, m1[i + 9], m2[i + 9]);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();

        res += w1.getResult() + w2.getResult() + w3.getResult() + w4.getResult() + w5.getResult() + w6.getResult() + w7.getResult() + w8.getResult() + w9.getResult() + w10.getResult();
    }
    return res;
}

int main()
{
    srand(time(NULL));

    double time_spent;
    clock_t begin, end;

    int n, i;
    int **m1, **m2, res;
    n = 10;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    res = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Matriz " << n << " X " << n << std::endl;

    std::cout << "Resultado da soma sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = somaThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da soma usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subtrairMatirz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subsThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    n = 100;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    res = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Matriz " << n << " X " << n << std::endl;

    std::cout << "Resultado da soma sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = somaThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da soma usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subtrairMatirz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subsThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    n = 1000;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    res = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Matriz " << n << " X " << n << std::endl;

    std::cout << "Resultado da soma sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = somaThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da soma usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subtrairMatirz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = subsThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da subtração usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    return 0;
}
