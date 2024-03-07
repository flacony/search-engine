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
   * @param path Строка, содержащая путь к файлу, из которого нужно считать
   * JSON.
   * @return nlohmann::json, представляющий содержимое файла.
   */
  nlohmann::json _getJsonFromFile(const std::string& path);

  /**
   * @brief Метод для записи содержимого из nlohmann::json в файл.
   * @param path Строка, содержащая путь к файлу, в который будет произведена
   * запись.
   * @param json Объект nlohmann::json, содержащий данные для записи в файл.
   */
  void _writeJsonToFile(const std::string& path, const nlohmann::json& json);

  /**
   * @brief Метод для получения содержимого из файла.
   * @param path Строка, содержащая путь к файлу, из которого будет произведено
   * чтение.
   * @return Строка, содержащая содержимое файла.
   */
  std::string _getTextFromFile(const std::string& path);

public:
  /**
   * @brief Конструктор класса.
   * @param path Путь к директории, содержащей файлы config.json и
   * requests.json. По умолчанию установлен на "./config/".
   */
  ConverterJSON(std::string& path = "./config/");

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

  /**
   * @brief Метод для установки пути к файлу config.json.
   * @param path Строка, содержащая абсолютный или относительный путь к файлу
   * config.json.
   */
  void setConfigPath(const std::string& path);

  /**
   * @brief Метод для установки пути к файлу requests.json.
   * @param path Строка, содержащая абсолютный или относительный путь к файлу
   * requests.json.
   */
  void setRequestsPath(const std::string& path);

  /**
   * @brief Метод для установки пути к файлу answers.json.
   * @param path Строка, содержащая абсолютный или относительный путь к файлу
   * answers.json.
   */
  void setAnswersPath(const std::string& path);

  /**
   * @brief Метод для получения списка запросов из файла requests.json.
   * @return Возвращает вектор строк, представляющих запросы.
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
