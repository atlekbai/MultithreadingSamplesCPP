#include <iostream>
#include <thread>
#include <list>

template<typename it, typename ft1, typename ft2>
void threaded(it p, it q, ft1 f1, ft2 f2, decltype(f1(*p)) &elem)
{
	auto res = f1(*p);
	while (++p != q)
		res = f2(res, f1(*p));
	elem = res;
}

template<typename it, typename ft1, typename ft2>
auto map_reduce(it p, it q, ft1 f1, ft2 f2, size_t threads) -> decltype(f1(*p))
{
	int dif = std::distance(p, q);
	std::thread thr[threads];
	decltype(f1(*p)) arr[threads];
	for (int i = 0; i < threads; i++)
	{
		auto p1 = p;
		auto q1 = p;
		std::advance(p1, static_cast<int>(i * dif / threads));
		std::advance(q1, static_cast<int>((i + 1) * dif / threads));
		thr[i] = std::thread(threaded<it, ft1, ft2>, p1, q1, f1, f2, std::ref(arr[i]));
	}
	for (int i = 0; i < threads; i++)
		if (thr[i].joinable()) thr[i].join();
	auto res = arr[0];
	for (int i = 1; i < threads; i++)
		res = f2(res, arr[i]);
	return (res);
}

int main(void)
{
	std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto sum = map_reduce(l.begin(), l.end(), [](int i){return i;}, std::plus<int>(), 3);
	std::cout << "sum :" <<  sum << std::endl;

	auto has_even = map_reduce(l.begin(), l.end(), [](int i){return i % 2 == 0;}, std::logical_or<bool>(), 4);
	std::cout << "has even: " << has_even << std::endl;
	return (0);
}
