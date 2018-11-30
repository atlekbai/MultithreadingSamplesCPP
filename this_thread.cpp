#include <iostream>
#include <thread>
#include <sstream>

std::atomic<bool> ready(false);

void race(int id)
{
	// threads wait until ready != true
	while (!ready)
		std::this_thread::yield();

	for (int i = 0; i < 1000000; i++){}
	std::cout << id << std::endl;
}

int main(void)
{
	std::thread threads[10];

	for (int i = 0; i < 10; i++)
		threads[i] = std::thread(race, i);
	ready = true;
	for (int i = 0; i < 10; i++)
		if (threads[i].joinable())
			threads[i].join();
	return(0);
}
