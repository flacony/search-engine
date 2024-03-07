#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "structures.h"

/**
 * @brief Класс для работы с обратным индексом.
 */
class InvertedIndex {
private:
  std::vector<std::string> _docs;
  std::map<std::string, std::vector<Entry>> _freqDictionary;

  /**
   * @brief Метод для обновления инвертированного индекса с учетом содержимого
   * документа.
   * @param document Строка, содержащая текст документа.
   * @param id Уникальный идентификатор документа.
   * @note Метод использует статический мьютекс для обеспечения
   * потокобезопасности при обновлении общего частотного словаря
   * _freqDictionary.
   */
  void _invertDocument(const std::string& document, size_t id);

public:
  /**
   * @brief Конструктор по умолчанию.
   */
  InvertedIndex() = default;

  /**
   * @brief Метод для обновления или заполнения базы документов.
   * @param inputDocs Вектор строк, содержащих текст документов.
   */
  void updateDocumentBase(const std::vector<std::string>& inputDocs);

  /**
   * @brief Метод для определения количества вхождений слова в базе документов.
   * @param word Слово, частоту вхождений которого необходимо определить.
   * @return Возвращает подготовленный список с частотой слов.
   */
  std::vector<Entry> getWordCount(const std::string& word);

  /** @brief Регулярное выражение для распознования отдельных слов в тексте. В
   * том числе считает за слова числа с точкой, слова или числа через дефис.
   */
  std::regex pattern = std::regex(R"(\d+(\.\d+)?|\w([\w-]*\w)?)");
};

#endif // INVERTEDINDEX_H
