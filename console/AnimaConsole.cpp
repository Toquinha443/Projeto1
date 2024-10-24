#include <chrono>
#include <iostream>
#include <thread>
#include <string>

void clearLastLine() { 
    std::cout << "\r" << std::string(50, ' ') << "\r"; 
}

void sleep(float tempo) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(static_cast<int>(tempo * 1000))
    );
}

void animateChange(int iterations = 5) {
    std::cout << std::endl;
    for (int i = iterations; i > 0; --i) {
        std::cout << "\rLIMPANDO EM " << i << "s ." << std::flush;
        sleep(0.3);

        clearLastLine();
        std::cout << "\rLIMPANDO EM " << i << "s .." << std::flush;
        sleep(0.3);

        clearLastLine();
        std::cout << "\rLIMPANDO EM " << i << "s ..." << std::flush;
        sleep(0.4);

        clearLastLine();
    }
}
