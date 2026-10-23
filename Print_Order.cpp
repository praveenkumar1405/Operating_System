class Foo {
    mutex m;
    condition_variable cv;
    int state=0;

public:
    Foo() {}

    void first(function<void()> printFirst) {
        printFirst();
        {
            lock_guard<mutex> lock(m);
            state=1;
        }
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);
        cv.wait(lock,[&]{return state==1;});
        printSecond();
        state=2;
        lock.unlock();
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(m);
        cv.wait(lock,[&]{return state==2;});
        printThird();
    }
};
