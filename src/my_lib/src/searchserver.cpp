#include <unordered_set>

#include "searchserver.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(
    const std::vector<std::string>& queriesInput) {
  std::vector<std::vector<RelativeIndex>> totalResults;

  for (const auto& query : queriesInput) {
    std::vector<RelativeIndex> requestResults;

    std::map<size_t, size_t> docIdCountMap;
    size_t maxCount{0};

    std::unordered_set<std::string> requestWords;

    std::sregex_token_iterator iter(query.begin(), query.end(), _index.pattern);
    std::sregex_token_iterator rend;

    while (iter != rend) {
      requestWords.insert(iter->str());
      ++iter;
    }

    for (const auto& word : requestWords) {
      std::vector<Entry> wordEntries = _index.getWordCount(word);

      for (const auto& entry : wordEntries) {
        docIdCountMap[entry.doc_id] += entry.count;
      }
    }

    for (const auto& result : docIdCountMap) {
      maxCount = std::max(result.second, maxCount);
    }

    for (const auto& result : docIdCountMap) {
      RelativeIndex relativeIndex;
      relativeIndex.doc_id = result.first;
      relativeIndex.rank = static_cast<double>(result.second) / maxCount;
      requestResults.push_back(relativeIndex);
    }

    std::sort(requestResults.begin(), requestResults.end(),
              [](RelativeIndex a, RelativeIndex b) { return a.rank > b.rank; });
    totalResults.push_back(requestResults);
  }

  return totalResults;
}
