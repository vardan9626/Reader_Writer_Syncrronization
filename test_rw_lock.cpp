#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "reader_writer_lock.h"

ReaderWriterLock rwl;
int shared_resource = 0;

void reader(int id) {
    for (int i = 0; i < 3; ++i) {
        rwl.acquire_read();
        std::cout << "Reader " << id << " reads: " << shared_resource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rwl.release_read();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void writer(int id) {
    for (int i = 0; i < 2; ++i) {
        rwl.acquire_write();
        shared_resource++;
        std::cout << "Writer " << id << " writes: " << shared_resource << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        rwl.release_write();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<std::thread> threads;

    // Create reader threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(reader, i);
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, i);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
