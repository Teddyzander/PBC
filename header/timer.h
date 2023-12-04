#include <string>

#ifdef TIMERLOG
namespace GlobalTimer {
    inline std::map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> activeTimers{};

    void set(const std::string& timerName) {
        assert(!activeTimers.count(timerName));
        activeTimers[timerName] = std::chrono::high_resolution_clock::now();
        std::cout << "[" << UnixColours::YELLOW << "Begin"
            << UnixColours::RESET << "] "
            << UnixColours::GREEN << timerName
            << "." << UnixColours::RESET << std::endl;
    }

    void stop(const std::string& timerName) {
        assert(activeTimers.count(timerName));
        auto start = activeTimers[timerName];
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "[" << UnixColours::BLUE << duration
            << "µs" << UnixColours::RESET << "] "
            << UnixColours::RED << timerName << "."
            << UnixColours::RESET << std::endl;
        activeTimers.erase(timerName);
    }

};

#else
namespace GlobalTimer {
    void set(const std::string& timerName) {}
    void stop(const std::string& timerName) {}
};
#endif 
