#include <iostream>
#include <chrono>
#include <atomic>
#include <vector>
#include <utility>

#include "Threadpool.h"

using namespace std;

mutex m;

void hello() {
  static thread_local int i = 0;
  lock_guard<mutex> l(m);
  cout << "Hello: " << i << endl;
  i++;
}

class Tester {
  Threadpool tp;
  mutex m2;

  void run_once() {
    static thread_local int i = 0;
    lock_guard<mutex> l(m2);
    cout << "Hello: " << i << endl;
    i++;
  }

  public:
    Tester() { }

    ~Tester() {
      tp.wait_for_all_jobs();
    }

    void test() {
      for (int i = 0; i < 100000; ++i) {
        tp.submit_task(&Tester::run_once, this);
      }
    }
};

int add_tester(int i, int j) {
  return i + j;
}

template <typename T>
void swap2(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

void my_swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void my_bad_swap(int a, int b) {
  int temp = a;
  a = b;
  b = temp;
}

vector<int> vec_func(int lim) {
  vector<int> v;
  static atomic<int> j(0);
  for (int i = 0; i < lim; ++i) {
    v.push_back(j);
    j++;
  }
  return v;
}

int main() {
  Threadpool tp;
#if 1
  {
    auto f1 = tp.submit_contract(add_tester, 54, 12);
    cout << f1.get() << endl;
  }
#endif
#if 1
  {
    cout << "ACTUAL SWAP" << endl;
    {
      int a = 0;
      int b = 5;
      cout << "BEFORE: a = " << a << ", b = " << b << endl;
      auto f = tp.submit_contract(my_swap, std::ref(a), std::ref(b));
      f.get();
      cout << "AFTER: a = " << a << ", b = " << b << endl;
    }
    cout << "BAD SWAP" << endl;
    {
      int a = 0;
      int b = 5;
      cout << "BEFORE: a = " << a << ", b = " << b << endl;
      auto f = tp.submit_contract(my_bad_swap, a, b);
      f.get();
      cout << "AFTER: a = " << a << ", b = " << b << endl;
    }
  }
#endif

#if 1
#define lim 1000
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

  start = std::chrono::high_resolution_clock::now();
  long k = 0;
  vector<future<vector<int>>> futures;
  for (int i = 1; i < lim; ++i) {
    futures.push_back(tp.submit_contract(vec_func, i));
  }
  for (auto& f: futures) {
    auto v = f.get();
    for (auto& i: v) {
      cout << i << endl;
    }
    k += v[0];
  }
  cout << k << endl;
  end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<chrono::milliseconds> (end-start).count() / 1000.0;
  std::cout << "DURATION: " << time << endl;
#endif

#if 1
  for (int i = 0; i < 100000; ++i) {
    tp.submit_task(hello);
  }
  tp.wait_for_all_jobs();

  Tester t;
  t.test();

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      auto t = tp.submit_contract(add_tester, i, j);
    }
  }
  tp.wait_for_all_jobs();
#endif

#if 1
  for (int i = 0; i < 100000; ++i) {
    submit_task(hello);
  }
  wait_for_all_jobs();

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      auto t = submit_contract(add_tester, i, j);
    }
  }
  wait_for_all_jobs();
#endif
}
