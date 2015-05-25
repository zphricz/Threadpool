# SingletonThreadpool
The same threadpool, but using a singleton pattern

## Starting the threadpool

To start the threadpool with as many threads as your system can handle:

    start_threadpool();

To start the threadpool and specify the number of threads to run:

    int num_threads = 4;
    set_num_threads(num_threads);
    start_threadpool();

## Submitting a simple job

    void print_hello() {
        std::cout << "Hello" << std::endl;
    }
    ...
    submit_task(print_hello);
    wait_for_all_jobs();

## Submitting a job with arguments

    void print_arguments(char* s1, int i, char* s3) {
        std::cout << s1 << " " << i << " " << s3 << std::endl;
    }
    ...
    submit_task(print_arguments, "Hello", 42, "world");
    wait_for_all_jobs();

## Submitting a job with a future

    int add_two(int a, int b) {
        return a + b;
    }
    ...
    auto f = submit_contract(add_two, 10, 5);
    assert(f.get() == 15);
    
