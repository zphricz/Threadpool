#include <iostream>
#include <chrono>

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
    Tester() :
      tp(4) {
    }

    ~Tester() {
      tp.wait_for_all_jobs();
    }

    void test() {
      for (int i = 0; i < 100000; ++i) {
        tp.submit_job(&Tester::run_once, this);
      }
    }
};

int add_tester(int i, int j) {
  return i + j;
}

void my_swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  Threadpool tp(4);
  int a = 4;
  int b = 6;
  cout << "BEFORE: a = " << a << ", b = " << b << endl;
  tp.submit_job(my_swap, a, b);
  cout << "AFTER NO REF: a = " << a << ", b = " << b << endl;
  tp.submit_job(my_swap, std::ref(a), std::ref(b));
  cout << "AFTER REF: a = " << a << ", b = " << b << endl;
#if 0
  for (int i = 0; i < 100000; ++i) {
    tp.submit_job(hello);
  }
  tp.wait_for_all_jobs();

  Tester t;
  t.test();

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      auto t = tp.submit_job(add_tester, i, j);
      t.get();
    }
  }
  tp.wait_for_all_jobs();
#endif
}
