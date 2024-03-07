#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "invertedindex.h"
#include "structures.h"

/**
 * @brief Класс для обработки поисковых запросов.
 */
class SearchServer {
private:
  InvertedIndex _index;

public:
  /**
   * @brief Конструктор класса.
   * @param idx Ссылка на объект класса InvertedIndex.
   */
  SearchServer(InvertedIndex& idx) : _index(idx) {}

  /**
   * @brief Метод для обработки поисковых запросов.
   * @param queriesInput Вектор строк, представляющих поисковые запросы из файла
   * requests.json.
   * @return Возвращает отсортированный список релевантных ответов для заданных
   * запросов.
   */
  std::vector<std::vector<RelativeIndex>> search(
      const std::vector<std::string>& queriesInput);
};

#endif // SEARCHSERVER_H
