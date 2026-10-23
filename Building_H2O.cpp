
class H2O {
    mutex m;
    condition_variable cv;
    int h=0,o=0;

public:
    H2O() {}

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lock(m);
        cv.wait(lock,[&]{return h<2;});
        h++;
        releaseHydrogen();
        if(h==2&&o==1){
            h=0;
            o=0;
            cv.notify_all();
        }
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(m);
        cv.wait(lock,[&]{return o<1;});
        o++;
        releaseOxygen();
        if(h==2&&o==1){
            h=0;
            o=0;
            cv.notify_all();
        }
    }
};
