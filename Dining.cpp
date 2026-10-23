
class DiningPhilosophers {
    mutex forks[5];

public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left=(philosopher+1)%5;
        int right=philosopher;

        unique_lock<mutex> l(forks[left],defer_lock);
        unique_lock<mutex> r(forks[right],defer_lock);
        std::lock(l,r);

        pickRightFork();
        pickLeftFork();
        eat();
        putLeftFork();
        putRightFork();
    }
};
