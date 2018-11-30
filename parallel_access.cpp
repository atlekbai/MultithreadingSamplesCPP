#include <iostream>
#include <thread>
#include <cstdlib>
#include <vector>
#include <mutex>

const int elem_count = 10;

void push(std::vector<int> &arr, std::mutex &m_arr, std::mutex &m_out)
{
	int num;
	for (int i = 0; i < elem_count; i++)
	{
		m_arr.lock();
		num = rand();
		arr.push_back(num);
		m_arr.unlock();
		m_out.lock();
		std::cout << "Push " << num << std::endl;
		m_out.unlock();
	}
}

void pop(std::vector<int> &arr, std::mutex &m_arr, std::mutex &m_out)
{
	int i = 0;
	int num;
	while (i < elem_count)
	{
		m_arr.lock();
		if (arr.size() > 0)
		{
			num = arr.back();
			arr.pop_back();
			m_out.lock();
			std::cout << "Pop " << num << std::endl;
			m_out.unlock();
			i++;
		}
		m_arr.unlock();
	}
}

int main(void)
{
	std::mutex m_arr;
	std::mutex m_out;
	std::vector<int> vec;
	std::thread push_thread(push, std::ref(vec), std::ref(m_arr), std::ref(m_out));
	std::thread pop_thread(pop, std::ref(vec), std::ref(m_arr), std::ref(m_out));
	if (push_thread.joinable()) push_thread.join();
	if (pop_thread.joinable()) pop_thread.join();
	return (0);
}
