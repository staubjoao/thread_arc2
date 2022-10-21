#include <iostream>
#include <memory>
#include <thread>

int fibo(int n)
{
    if (n <= 2)
        return 1;
    else
        return fibo(n - 1) + fibo(n - 2);
}

class Worker
{
private:
    int result;

public:
    Worker();
    void task(int parameter);
    void dump();
};

Worker::Worker()
{
    result = 0;
}

void Worker::task(int parameter)
{
    result = fibo(parameter);
}

void Worker::dump()
{
    std::cout << result << std::endl;
}

int main()
{
    Worker w1;
    std::shared_ptr<Worker> w2(new Worker);

    std::thread t1(&Worker::task, &w1, 30);
    std::thread t2(&Worker::task, w2, 20);

    t1.join();
    t2.join();

    w1.dump();
    w2->dump();
    return 0;
}
