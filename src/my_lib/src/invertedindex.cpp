#include "invertedindex.h"
#include <mutex>
#include <thread>

void InvertedIndex::updateDocumentBase(
    const std::vector<std::string>& inputDocs) {
  _freqDictionary.clear();
  _docs = inputDocs;

  std::vector<std::thread> threads;
  size_t id{0};

  for (const auto& document : inputDocs) {
    threads.emplace_back(&InvertedIndex::_invertDocument, this, document, id);
    id++;
  }

  for (auto& thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void InvertedIndex::_invertDocument(const std::string& document, size_t id) {
  static std::mutex _freqDictionaryMutex;

  std::sregex_token_iterator iter(document.begin(), document.end(), pattern);
  std::sregex_token_iterator rend;

  std::map<std::string, size_t> localMap;

  while (iter != rend) {
    localMap[iter->str()] += 1;
    ++iter;
  }
  std::lock_guard<std::mutex> lock(_freqDictionaryMutex);
  for (const auto& el : localMap) {
    Entry entry{id, el.second};
    _freqDictionary[el.first].push_back(entry);
  }
}

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word) {
  auto it = _freqDictionary.find(word);
  if (it != _freqDictionary.end()) {
    return it->second;
  } else
    return {};
}
