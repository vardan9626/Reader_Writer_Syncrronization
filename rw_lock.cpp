#include "reader_writer_lock.h"

ReaderWriterLock::ReaderWriterLock() : readers(0), writers(0), readers_waiting(0), writers_waiting(0) {}

void ReaderWriterLock::acquire_read() {
    std::unique_lock<std::mutex> lock(mtx);
    readers_waiting++;
    readers_condition.wait(lock, [this] { return writers == 0; });
    readers_waiting--;
    readers++;
}

void ReaderWriterLock::release_read() {
    std::unique_lock<std::mutex> lock(mtx);
    readers--;
    if (readers == 0 && writers_waiting > 0) {
        writers_condition.notify_one();
    }
}

void ReaderWriterLock::acquire_write() {
    std::unique_lock<std::mutex> lock(mtx);
    writers_waiting++;
    writers_condition.wait(lock, [this] { return readers == 0 && writers == 0; });
    writers_waiting--;
    writers++;
}

void ReaderWriterLock::release_write() {
    std::unique_lock<std::mutex> lock(mtx);
    writers--;
    if (readers_waiting > 0) {
        readers_condition.notify_all();
    } else if (writers_waiting > 0) {
        writers_condition.notify_one();
    }
}
