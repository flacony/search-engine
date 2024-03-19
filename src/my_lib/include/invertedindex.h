#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "structures.h"

/**
 * @brief Class for working with an inverted index.
 */
class InvertedIndex {
private:
  std::vector<std::string> _docs;
  std::map<std::string, std::vector<Entry>> _freqDictionary;

  /**
   * @brief Method for updating the inverted index considering the content of
   * the document.
   * @param document A string containing the text of the document.
   * @param id Unique identifier of the document.
   * @note The method uses a static mutex to ensure thread safety when updating
   * the shared frequency dictionary _freqDictionary.
   */
  void _invertDocument(const std::string& document, size_t id);

public:
  /**
   * @brief Default constructor.
   */
  InvertedIndex() = default;

  /**
   * @brief Method for updating or populating the document base.
   * @param inputDocs A vector of strings containing the text of the documents.
   */
  void updateDocumentBase(const std::vector<std::string>& inputDocs);

  /**
   * @brief Method for determining the frequency of occurrence of a word in the
   * document base.
   * @param word The word whose frequency of occurrence needs to be determined.
   * @return Returns a prepared list with word frequency.
   */
  std::vector<Entry> getWordCount(const std::string& word);

  /** @brief Regular expression for recognizing individual words in the text.
   * Also considers numbers with a dot, words or numbers separated by a hyphen
   * as words.
   */
  std::regex pattern = std::regex(R"(\d+(\.\d+)?|\w([\w-]*\w)?)");
};

#endif // INVERTEDINDEX_H
