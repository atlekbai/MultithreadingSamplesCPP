#include <iostream>
#include <thread>
#include <cstdlib>

class print_number
{
public:
	void operator()(int number, int arr[], int idx)
		{
			int sum = 0;
			for (int i = 0; i < number; i++)
			{
				if (i % 15 == 0) continue;
				if (i % 3 == 0) sum += 3 * i;
				if (i % 5 == 0) sum += 5 * i;
			}
			arr[idx] = sum;
		}
};

int main(void)
{
	const int len = 10;
	std::thread::id id;
	std::thread thread_arr[len];
	int res_arr[len] = {0};
	
	for (int i = 0; i < len; i++)
		thread_arr[i] = std::thread(print_number(), rand(), res_arr, i);
	for (int i = 0; i < len; i++)
		if (thread_arr[i].joinable())
		{
			id = thread_arr[i].get_id();
			thread_arr[i].join();
			std::cout << "Thread with id " <<  id << " finished. With result " << res_arr[i] << std::endl;
		}
	return (0);
}
