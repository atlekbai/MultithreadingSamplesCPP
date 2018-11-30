#include <iostream>
#include <future>
#include <list>

template <typename IT, typename Func1, typename Func2>
auto	threaded(IT p, IT q, Func1 f1, Func2 f2) -> decltype(f1(*p))
{
	auto res = f1(*p);
	while (++p != q)
		res = f2(res, f1(*p));
	return (res);
}

template <typename IT, typename Func1, typename Func2>
auto	map_reduce(IT p, IT q, Func1 f1, Func2 f2, size_t threads) -> decltype(f1(*p))
{
	int dif = std::distance(p, q);
	std::future<decltype(f1(*p))> fut[threads];
	for (int i = 0; i < threads; i++)
	{
		auto p1 = p;
		auto q1 = p;
		std::advance(p1, static_cast<int>(i * dif / threads));
		std::advance(q1, static_cast<int>((i + 1) * dif / threads));
		fut[i] = std::async(std::launch::async, &threaded<IT, Func1, Func2>, p1, q1, f1, f2);
	}
	auto res = fut[0].get();
	for (int i = 1; i < threads; i++)
		res = f2(res, fut[i].get());
	return res;
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
