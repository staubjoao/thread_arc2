#include <iostream>
#include <time.h>
#include <memory>
#include <thread>

// função que calcula o número de fibonacci
int fibonacci(int n)
{
    int x;
    if (n == 1)
        return (1);

    if (n == 2)
        return (1);

    x = fibonacci(n - 1) + fibonacci(n - 2);
    return (x);
}

// multiplica uma linha por uma coluna
int multVetor(int n, int k, int **m1, int **m2)
{
    int i, j, res = 0;
    // é preciso utilizar dois for alinhados, um para linha e outro para coluna
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            res += m1[i][k] * m2[k][j];
    }
    return res;
}

// soma dois vetores das matrizes que deseja
int somaVetor(int n, int *vet1, int *vet2)
{
    int i, soma = 0;
    for (i = 0; i < n; i++)
        soma += (vet1[i] + vet2[i]);
    return soma;
}

// subtrai dois vetores das matrizes que deseja
int subVetor(int n, int *vet1, int *vet2)
{
    int i, sub = 0;
    for (i = 0; i < n; i++)
        sub += (vet1[i] - vet2[i]);
    return sub;
}

// classe das threads
class Worker
{
private:
    int result;

    // funções nescessarias para execução
public:
    Worker();
    void taskSum(int n, int *v1, int *v2);
    void taskSub(int n, int *v1, int *v2);
    void taskMult(int n, int k, int **m1, int **m2);
    void taskFib(int n);
    int getResult();
};

// contrutor, o resultado fica como 0
Worker::Worker()
{
    result = 0;
}

// tarefa responsavel para executar a operação da sequencia de fibonacci
void Worker::taskFib(int n)
{
    result = fibonacci(n);
}

void Worker::taskMult(int n, int k, int **m1, int **m2)
{
    result = multVetor(n, k, m1, m2);
}

// tarefa respomsaveç para executar a operação de soma de dois vetores
void Worker::taskSum(int n, int *v1, int *v2)
{
    result = somaVetor(n, v1, v2);
}

// tarefa respomsaveç para executar a operação de subtração de dois vetores
void Worker::taskSub(int n, int *v1, int *v2)
{
    result = subVetor(n, v1, v2);
}

// função que retorna o resultado
int Worker::getResult()
{
    return result;
}

// soma de matrizes de forma sequencial
int somarMatriz(int n, int **matriz1, int **matriz2)
{
    // dois for alinhados que somam os valores da matrizes
    int i, j, res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            res += (matriz1[i][j] + matriz2[i][j]);
    }
    return res;
}

// subtração de matrizes de forma sequencial
int subtrairMatirz(int n, int **matriz1, int **matriz2)
{
    // dois for alinhados que subtraem os valores da matrizes
    int i, j, res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            res += (matriz1[i][j] - matriz2[i][j]);
    }
    return res;
}

// multiplicação de matrizes de forma sequencial
int multiplicaMatriz(int n, int **matriz1, int **matriz2)
{
    // 3 for alinhados para multiplicar linha por coluna das duas matrizes
    int i, j, k, res = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
                res += matriz1[i][k] * matriz2[k][j];
        }
    }
    return res;
}

// função que gera a matriz
int **gerarMatriz(int n)
{
    int i, j;
    // aloca a memoria para isso
    int **matriz = new int *[n];
    for (i = 0; i < n; i++)
        matriz[i] = new int[n];

    // gera valores aleatorios de 1 a 99
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            matriz[i][j] = rand() % 10 + 1;
    }
    return matriz;
}

// função que apaga a matriz
void apagarMatriz(int n, int **matriz)
{
    int i;
    // desaloca a memoria da matriz
    for (i = 0; i < n; i++)
        delete[] matriz[i];
    delete[] matriz;
}

// soma usando threads
int somaThreads(int n, int **m1, int **m2)
{
    int res = 0, i;
    for (i = 0; i < n; i += 10)
    {
        // são criadas 10 threads
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

        // cada thread soma duas linhas de cada matriz
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

        // inicialização das threads
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

        // os valores são somados e armazenados
        res += w1.getResult() + w2.getResult() + w3.getResult() + w4.getResult() + w5.getResult() + w6.getResult() + w7.getResult() + w8.getResult() + w9.getResult() + w10.getResult();
    }
    // o resultado é retornado
    return res;
}

// sub threads, funciona da mesma forma que a função anterios, só que subtrai os valors de duas matrizes
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

// mult threads, funciona da mesma forma que os outros, são 10 threads que operam na matriz multiplicando a linha pela coluna
int multThreads(int n, int **m1, int **m2)
{
    int res = 0, i, j;
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

        // cada thread ira receber as duas matrizes e o valor de k do caso sequencial
        std::thread t1(&Worker::taskMult, &w1, n, i, m1, m2);
        std::thread t2(&Worker::taskMult, &w2, n, i + 1, m1, m2);
        std::thread t3(&Worker::taskMult, &w3, n, i + 2, m1, m2);
        std::thread t4(&Worker::taskMult, &w4, n, i + 3, m1, m2);
        std::thread t5(&Worker::taskMult, &w5, n, i + 4, m1, m2);
        std::thread t6(&Worker::taskMult, &w6, n, i + 5, m1, m2);
        std::thread t7(&Worker::taskMult, &w7, n, i + 6, m1, m2);
        std::thread t8(&Worker::taskMult, &w8, n, i + 7, m1, m2);
        std::thread t9(&Worker::taskMult, &w9, n, i + 8, m1, m2);
        std::thread t10(&Worker::taskMult, &w10, n, i + 9, m1, m2);

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
    // a lógica das funções seguem a mesma, foram criadas funções genericas para que o único valor que mude seja o valor de n
    // dessa forma só será comentado o primeiro caso
    srand(time(NULL));

    // váriaveis para marcar o tempo da execução das funções
    double time_spent, time_spent2;
    // váriaveis para marcar o tempo de inicio e de termino de execução
    clock_t begin, end;

    int n;
    // ponteiro das matrizes e dos resultados
    int **m1, **m2, res, res2;
    n = 10;

    // geração das matrizes
    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    // inicialização da váriavel que marca o tempo
    time_spent = 0.0;
    // armazenagem do inicio da execução
    begin = clock();
    // chamada da função para somar a matriz sequencialmente
    res = somarMatriz(n, m1, m2);
    // armazenagem do fim da execução
    end = clock();
    // conta para armazenar o tempo de execução
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Matriz " << n << " X " << n << std::endl;
    // apresentação do resultadoda soma com o tempo que levou para executar
    std::cout << "Resultado da soma sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    // aqui é feita a operação de soma só que usando threads, as váriaveis begin, end e res armazenam as mesmas coisas
    // que da ultima exeução
    time_spent = 0.0;
    begin = clock();
    res = somaThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // apresentação do resultado com o tempo que levou para executar
    std::cout << "Resultado da soma usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    // para a subtração a ideia é a mesma, primeiro de forma sequencial, com os dados aprsentados na tela
    // depois de forma paralela com os dados na tela tambem
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

    // na multiplicação a ideia segue a mesma, primeiro sequencial depois paralelo
    time_spent = 0.0;
    begin = clock();
    res = multiplicaMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = multThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    // a memoria alocada para as matrizes são desalocadas
    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    // execução identida para 10 só que para 1000 agora
    n = 100;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    res = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "\nMatriz " << n << " X " << n << std::endl;

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

    time_spent = 0.0;
    begin = clock();
    res = multiplicaMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = multThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    // execução identida para 10 e para 100 só que para 10000 agora
    n = 1000;

    m1 = gerarMatriz(n);
    m2 = gerarMatriz(n);
    time_spent = 0.0;
    begin = clock();
    res = somarMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "\nMatriz " << n << " X " << n << std::endl;

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

    time_spent = 0.0;
    begin = clock();
    res = multiplicaMatriz(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação sequencial: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    time_spent = 0.0;
    begin = clock();
    res = multThreads(n, m1, m2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Resultado da multiplicação usando threads: " << res << "\nFeita no tempo: " << time_spent << std::endl;

    apagarMatriz(n, m1);
    apagarMatriz(n, m2);

    // aqui será executado uma função recursiva para calcular um número da sequencia de fibonacci, de forma
    // sequencial e de forma paralela
    int fib1 = 22, fib2 = 30;
    std::cout << "Fibonacci sequencial: " << std::endl;
    // marca o tempo
    time_spent = 0.0;
    begin = clock();
    std::cout << "Iniciado para o valor " << fib1 << std::endl;
    // armazena o resultado
    res = fibonacci(fib1);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    // apresenta o valor do fibonacci e o tempo que levou para executar
    std::cout << "Para o valor fib(" << fib1 << ") = " << res << ", no tempo " << time_spent << std::endl;

    // aqui ocorre a mesma coisa só que para outro valor
    begin = clock();
    std::cout << "Iniciado para o valor " << fib2 << std::endl;
    res = fibonacci(fib2);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Para o valor fib(" << fib2 << ") = " << res << ", no tempo " << time_spent << std::endl;

    // agora utilizando threads
    std::cout << "Fibonacci com threads: " << std::endl;
    time_spent = 0.0, time_spent2 = 0.0;
    begin = clock();
    Worker w1;
    std::thread t1(&Worker::taskFib, &w1, 6);
    std::cout << "Iniciado para o valor " << fib1 << std::endl;
    // inicia a execução de um número em uma thread
    t1.join();
    res = w1.getResult();
    end = clock();
    // calcula o tempo
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock();
    Worker w2;
    std::thread t2(&Worker::taskFib, &w2, 20);
    std::cout << "Iniciado para o valor " << fib2 << std::endl;
    // inica a execução de outro número em outra thread
    t2.join();
    res2 = w2.getResult();
    end = clock();
    // calcula o tempo que levou
    time_spent2 += (double)(end - begin) / CLOCKS_PER_SEC;

    // apresenta o tempo e aqui podemos notar que o tempo de execução é semelhante mesmo a função tendo uma complexidade
    // alta, diferente de quando é executado de forma sequencial, já que é nescessario acabar a execução de uma chamada
    // para inicia a outra
    std::cout << "\nPara o valor fib(" << fib1 << ") = " << res << ", no tempo " << time_spent << std::endl;
    std::cout << "Para o valor fib(" << fib2 << ") = " << res2 << ", no tempo " << time_spent2 << std::endl;

    return 0;
}
