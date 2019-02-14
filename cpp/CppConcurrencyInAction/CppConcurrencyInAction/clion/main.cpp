#include <iostream>
#include <thread>
#include "Func21.h"
#include "Demo24.h"
#include "Demo27.h"
#include "Demo28.h"
#include "Demo281.h"
#include "Demo31.h"
#include "windows.h"
#include "Demo39.h"
#include "Demo43.h"

using namespace std;

class background_task {
public:
    void operator()() const {
        std::cout << " dosome" << std::endl;
    }
};

void demo211() {
    int someloacal = 0;
    Func21 func21(someloacal);
    std::thread myThread(func21);
    myThread.detach();

}

void demo22() {
    Demo24 demo24;
    demo24.run();
}

/**
 * p63
 * @return
 */
int main() {
//   demo211();
//    Abstruct *abstruct = new Demo27();
//    Abstruct *abstruct = new Demo28();
//    Abstruct *abstruct = new Demo281();
//    Abstruct *abstruct = new Demo31();
//    BigObj tmp({0, 0});
//    Abstruct *abstruct = new Demo39(tmp);
    Abstruct *abstruct = new Demo43();
    abstruct->run();
    delete abstruct;
    return 0;
}