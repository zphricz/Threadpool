# Threadpool
A simple threadpool implemented in c++

## Threadpool object
The Threadpool class can be instantiated and used as an object.

### Creating a threadpool

To create a threadpool with std::thread::hardware::concurrency() many threads:

    Threadpool tp;

To create a threadpool and specify the number of threads to run:

    int num_threads = 4;
    Threadpool tp(num_threads);

### Submitting a simple job

    void print_hello() {
        std::cout << "Hello" << std::endl;
    }
    ...
    tp.submit_task(print_hello);
    tp.wait_for_all_jobs();

### Submitting a job with arguments

    void print_arguments(char* s1, int i, char* s3) {
        std::cout << s1 << " " << i << " " << s3 << std::endl;
    }
    ...
    tp.submit_task(print_arguments, "Hello", 42, "world");
    tp.wait_for_all_jobs();

### Submitting a job with a future

    int add_two(int a, int b) {
        return a + b;
    }
    ...
    auto f = tp.submit_contract(add_two, 10, 5);
    assert(f.get() == 15);

## Threadpool singleton
The Threadpool class' functionality is duplicated with a series of functions
that can be used without manually instantiating a threadpool object. All of
these operations will be handled by a singleton instantiation of a Threadpool
that has std::thread::hardware::concurrency() many threads.

### Submitting a simple job

    void print_hello() {
        std::cout << "Hello" << std::endl;
    }
    ...
    submit_task(print_hello);
    wait_for_all_jobs();

### Submitting a job with arguments

    void print_arguments(char* s1, int i, char* s3) {
        std::cout << s1 << " " << i << " " << s3 << std::endl;
    }
    ...
    submit_task(print_arguments, "Hello", 42, "world");
    wait_for_all_jobs();

### Submitting a job with a future

    int add_two(int a, int b) {
        return a + b;
    }
    ...
    auto f = submit_contract(add_two, 10, 5);
    assert(f.get() == 15);
    
