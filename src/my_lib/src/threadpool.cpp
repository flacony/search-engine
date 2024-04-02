#include "threadpool.h"

int ThreadPool::_getThreadsCount(int tasksCount) {
  int coresCount = std::thread::hardware_concurrency();
  coresCount = coresCount ? coresCount : 4;
  return std::min(coresCount, tasksCount);
}

void ThreadPool::execute(std::queue<std::function<void()>>& tasks) {
  int threadsCount = _getThreadsCount(tasks.size());

  for (int i{0}; i < threadsCount; ++i) {
    _threads.emplace_back([this, &tasks]() {
      while (true) {
        std::function<void()> task;

        _tasksMutex.lock();
        if (tasks.empty()) {
          _tasksMutex.unlock();
          return;
        }
        task = std::move(tasks.front());
        tasks.pop();
        _tasksMutex.unlock();

        task();
      }
    });
  }

  for (auto& thread : _threads) {
    thread.join();
  }
}
