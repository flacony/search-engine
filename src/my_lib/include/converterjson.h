#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H
#include "nlohmann/json.hpp"
#include "structures.h"
#include <vector>
/**
 * @brief Class for working with JSON files.
 */
class ConverterJSON {
private:
  std::string _configPath;
  std::string _requestsPath;
  std::string _answersPath;

  /**
   * @brief Method for reading content from a file into nlohmann::json.
   * @param path A string containing the path to the file from which to read
   * JSON.
   * @return nlohmann::json representing the file's content.
   */
  nlohmann::json _getJsonFromFile(const std::string& path);

  /**
   * @brief Method for writing content from nlohmann::json to a file.
   * @param path A string containing the path to the file to which the content
   * will be written.
   * @param json An object of nlohmann::json containing data to be written to
   * the file.
   */
  void _writeJsonToFile(const std::string& path, const nlohmann::json& json);

  /**
   * @brief Method for getting content from a file.
   * @param path A string containing the path to the file from which to read.
   * @return A string containing the file's content.
   */
  std::string _getTextFromFile(const std::string& path);

public:
  /**
   * @brief Class constructor.
   * @param path Path to the directory containing config.json and requests.json
   * files. Default is set to "./config/".
   */
  ConverterJSON(std::string& path);

  /**
   * @brief Method for getting content of text documents from config.json file.
   * @return Returns a list of paths to text documents.
   */
  std::vector<std::string> getTextDocuments();

  /**
   * @brief Method for getting the maximum number of responses for a single
   * request from config.json file.
   * @return Returns the maximum number of responses.
   */
  int getResponsesLimit();

  /**
   * @brief Method for setting the path to the config.json file.
   * @param path A string containing the absolute or relative path to the
   * config.json file.
   */
  void setConfigPath(const std::string& path);

  /**
   * @brief Method for setting the path to the requests.json file.
   * @param path A string containing the absolute or relative path to the
   * requests.json file.
   */
  void setRequestsPath(const std::string& path);

  /**
   * @brief Method for setting the path to the answers.json file.
   * @param path A string containing the absolute or relative path to the
   * answers.json file.
   */
  void setAnswersPath(const std::string& path);

  /**
   * @brief Method for getting a list of requests from the requests.json file.
   * @return Returns a vector of strings representing requests.
   */
  std::vector<std::string> getRequests();

  /**
   * @brief Method for writing search query results to the answers.json file.
   * @param answers A vector of vectors of pairs (document_id, score)
   * representing search query results.
   */
  void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};

#endif // CONVERTERJSON_H
