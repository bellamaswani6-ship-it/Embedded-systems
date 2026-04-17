#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

struct SensorConfig {
    int id;
    SensorConfig(int i) : id(i) {
        std::cout << "SensorConfig created\n";
    }
    ~SensorConfig() {
        std::cout << "SensorConfig destroyed\n";
    }
};

void fastTask(std::shared_ptr<SensorConfig> cfg) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "[Fast Task] ID=" << cfg->id
              << " use_count=" << cfg.use_count() << "\n";
}

void mediumTask(std::shared_ptr<SensorConfig> cfg) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::cout << "[Medium Task] ID=" << cfg->id
              << " use_count=" << cfg.use_count() << "\n";
}

void slowTask(std::shared_ptr<SensorConfig> cfg) {
    std::this_thread::sleep_for(std::chrono::milliseconds(15000));
    std::cout << "[Slow Task] ID=" << cfg->id
              << " use_count=" << cfg.use_count() << "\n";
}

int main() {
    std::shared_ptr<SensorConfig> config = std::make_shared<SensorConfig>(42);

    std::cout << "[Main] Initial use_count = "<< config.use_count() << "\n"; //1

    std::thread t1(fastTask, config); //fun_name,parameter
    std::thread t2(mediumTask, config);
    std::thread t3(slowTask, config);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "[Main] Final use_count = " << config.use_count() << "\n";
}

