#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/**
 * @brief A simple thread pool implementation.
 */
class ThreadPool {
private:
  std::vector<std::thread> _threads;
  std::mutex _tasksMutex;

  /**
   * @brief Determines the number of threads to create based on the number of
   * tasks.
   * @param tasksCount The number of tasks to be executed.
   * @return The number of threads to create.
   */
  int _getThreadsCount(int tasksCount);

public:
  /**
   * @brief Executes the given tasks using the thread pool.
   * @param tasks A queue of tasks represented as std::function<void()>.
   */
  void execute(std::queue<std::function<void()>>& tasks);
};

#endif // THREADPOOL_H
