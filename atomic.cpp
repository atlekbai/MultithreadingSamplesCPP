#include <iostream>
#include <thread>

std::atomic<size_t> counter(0);

void compute(int begin, int end)
{
	for (int i = begin; i < end; i++)
		counter += i;
}

int main(void)
{
	std::thread t1(compute, 0, 100);
	std::thread t2(compute, 100, 200);
	t1.join();
	t2.join();
	std::cout << counter << std::endl;
	return (0);
}
