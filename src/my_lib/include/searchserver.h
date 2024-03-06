#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "invertedindex.h"
#include "structures.h"

/**
 * @brief Класс для обработки поисковых запросов.
 */
class SearchServer {
public:
  /**
   * @brief Конструктор класса.
   * @param idx Ссылка на объект класса InvertedIndex.
   */
  SearchServer(InvertedIndex& idx) : _index(idx) {}

  /**
   * @brief Метод обработки поисковых запросов.
   * @param queries_input Поисковые запросы взятые из файла requests.json.
   * @return Возвращает отсортированный список релевантных ответов для заданных
   * запросов.
   */
  std::vector<std::vector<RelativeIndex>> search(
      const std::vector<std::string>& queries_input);

private:
  InvertedIndex _index;
};

#endif // SEARCHSERVER_H
