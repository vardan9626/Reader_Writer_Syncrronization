#ifndef READER_WRITER_LOCK_H
#define READER_WRITER_LOCK_H

#include <mutex>
#include <condition_variable>

class ReaderWriterLock {
private:
    std::mutex mtx;
    std::condition_variable readers_condition;
    std::condition_variable writers_condition;
    int readers;
    int writers;
    int readers_waiting;
    int writers_waiting;

public:
    ReaderWriterLock();
    void acquire_read();
    void release_read();
    void acquire_write();
    void release_write();
};

#endif // READER_WRITER_LOCK_H
