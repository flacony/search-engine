#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "invertedindex.h"
#include "structures.h"

/**
 * @brief Class for processing search queries.
 */
class SearchServer {
private:
  InvertedIndex _index;

public:
  /**
   * @brief Class constructor.
   * @param idx Reference to an object of the InvertedIndex class.
   */
  SearchServer(InvertedIndex& idx) : _index(idx) {}

  /**
   * @brief Method for processing search queries.
   * @param queriesInput A vector of strings representing search queries from
   * the requests.json file.
   * @return Returns a sorted list of relevant responses for the given queries.
   */
  std::vector<std::vector<RelativeIndex>> search(
      const std::vector<std::string>& queriesInput);
};

#endif // SEARCHSERVER_H
