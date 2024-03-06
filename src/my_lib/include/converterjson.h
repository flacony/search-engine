#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H
#include "nlohmann/json.hpp"
#include "structures.h"
#include <vector>
/**
 * @brief Класс для работы с JSON-файлами.
 */
class ConverterJSON {
private:
  std::string _configPath;
  std::string _requestsPath;
  std::string _answersPath;

  /**
   * @brief Метод для записи содержимого из файла в nlohmann::json.
   * @return Возвращает nlohmann::json с содержимым файла.
   */
  nlohmann::json _getJsonFromFile(const std::string& path);

  /**
   * @brief Метод для записи содержимого из nlohmann::json в файл.
   */
  void _writeJsonToFile(const std::string& path, const nlohmann::json& json);

  std::string _getTextFromFile(const std::string& path);

public:
  /**
   * @brief Конструктор класса.
   * @param path Путь к файлам config.json и requests.json.
   */
  ConverterJSON(std::string path = "./config/");

  /**
   * @brief Метод для получения содержимого текстовых документов из файла
   * config.json.
   * @return Возвращает список путей к текстовым документам.
   */
  std::vector<std::string> getTextDocuments();

  /**
   * @brief Метод для получения предельного количества ответов на один запрос из
   * файла config.json.
   * @return Возвращает предельное количество ответов.
   */
  int getResponsesLimit();

  void setConfigPath(const std::string& path);
  void setRequestsPath(const std::string& path);
  void setAnswersPath(const std::string& path);

  /**
   * @brief Метод для получения списка запросов из файла requests.json.
   * @return Возвращает список запросов.
   */
  std::vector<std::string> getRequests();

  /**
   * @brief Метод для записи результатов поисковых запросов в файл answers.json.
   * @param answers Вектор векторов пар (document_id, score) - результаты
   * поисковых запросов.
   */
  void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};

#endif // CONVERTERJSON_H
