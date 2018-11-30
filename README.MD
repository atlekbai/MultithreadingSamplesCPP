# Multithreading samples
---
##### atomic.cpp

```std::atomic<typename> variable```

Short program showing, how threads are able to access to an atomic variable.
Atomic variables have only one access at a time, multiple threads can't change an atomic variable simultaneously.
---
##### synchonisation.cpp

```std::mutex```

Program showing simple usage of `std::mutex`. Access to a variable can be temporary locked by `std::lock_guard<std::mutex> lck(mutex_var)`

---
##### parallel_access.cpp

```std::mutex, std::ref```

Code showing how 2 threads (1 for push, 1 for pop) simultaniously change `std::vector` and how correctly mutex can be used to access to a variable.

---
##### this_thread.cpp

```std::this_thread::yield```

Threads race. Each thread is called to count until 1 million. Outputs sequence of finished threads.

---
##### thread_id.cpp

```std::this_thread::get_id()```

Small code showing that each thread has got an id.

---
##### map_reduce.cpp

```std::future, std::async, decltype```

> ***MapReduce*** is a programming model and an associated implementation for processing and generating big data sets with a parallel, distributed algorithm on a cluster.
@wiki

Parallel processing on data using `std::future`

---
##### map_reduce_thread.cpp

```std::thread, decltype```


Parallel processing on data using `std::thread`
