#include <iostream>
#include <thread>
#include <mutex>

double shared = 0;
std::mutex mtx;

void compute(int begin, int end)
{
	for (int i = begin; i < end; i++)
	{
		std::lock_guard<std::mutex> lck(mtx);
		shared += i;
	}
}

int main(void)
{
	std::thread t1(compute, 0, 100);
	std::thread t2(compute, 100, 200);
	t1.join();
	t2.join();
	std::cout << shared << std::endl;
	return (0);
}
