# Threadpool
A simple threadpool implemented in c++

## Creating a threadpool

To create a threadpool with as many threads as your system can handle:

    Threadpool tp;

To create a threadpool and specify the number of threads to run:

    int num_threads = 4;
    Threadpool tp(num_threads);

## Submitting a simple job

    void print_hello() {
        std::cout << "Hello" << std::endl;
    }
    ...
    tp.submit_task(print_hello);
    tp.wait_for_all_jobs();

## Submitting a job with arguments

    void print_arguments(char* s1, int i, char* s3) {
        std::cout << s1 << " " << i << " " << s3 << std::endl;
    }
    ...
    Threadpool tp;
    tp.submit_task(print_arguments, "Hello", 42, "world");
    tp.wait_for_all_jobs();

## Submitting a job with a future

    int add_two(int a, int b) {
        return a + b;
    }
    ...
    Threadpool tp;
    auto f = tp.submit_contract(add_two, 10, 5);
    assert(f.get() == 15);
    
