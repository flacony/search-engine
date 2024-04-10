#include <fstream>
#include <iostream>
#include <string>

#include "converterjson.h"

using json = nlohmann::json;

ConverterJSON::ConverterJSON(std::string& path) {
  _configPath = path + "/config.json";
  _requestsPath = path + "/requests.json";
  _answersPath = path + "/answers.json";
  auto json = _getJsonFromFile(_configPath);

  if (!json.contains("config") || !json.contains("files")) {
    std::cerr
        << "File config.json does not contain \"config\" or \"files\" fields.";
    exit(EXIT_FAILURE);
  }
}

void ConverterJSON::setConfigPath(const std::string& path) {
  _configPath = path;
}

void ConverterJSON::setRequestsPath(const std::string& path) {
  _requestsPath = path;
}

void ConverterJSON::setAnswersPath(const std::string& path) {
  _answersPath = path;
}

json ConverterJSON::_getJsonFromFile(const std::string& path) {
  try {
    json configJson;
    std::ifstream inputFile(path);

    if (!inputFile) {
      throw std::runtime_error("Can't open file: " + path);
    } else {
      inputFile >> configJson;
    }

    return configJson;
  } catch (const std::exception& e) {
    std::cerr << "Exception while working with file: " << e.what();
    exit(EXIT_FAILURE);
  }
}

std::string ConverterJSON::_getTextFromFile(const std::string& path) {
  std::string text;
  try {
    std::ifstream inputFile(path);
    if (!inputFile) {
      throw std::runtime_error("Can't open file: " + path);
    } else {
      std::string line;

      while (std::getline(inputFile, line)) {
        text += line + '\n';
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception while working with file: " << e.what() << std::endl;
  }

  return text;
}

void ConverterJSON::_writeJsonToFile(const std::string& path, const json& json) {
  try {
    std::ofstream outputFile(path);

    if (!outputFile) {
      throw std::runtime_error("Can't open file: " + path);
    }

    outputFile << std::setw(4) << json;
  } catch (const std::exception& e) {
    std::cerr << "Exception while working with file: " << e.what() << std::endl;
  }
}

std::vector<std::string> ConverterJSON::getTextDocuments() {
  std::vector<std::string> textDocuments;

  json configJson = _getJsonFromFile(_configPath);

  auto files = configJson["files"];

  for (const auto& path : files) {
    textDocuments.push_back(_getTextFromFile(path));
  }

  return std::move(textDocuments);
}

int ConverterJSON::getResponsesLimit() {
  int responsesLimit{5};
  json configJson = _getJsonFromFile(_configPath);

  if (configJson["config"].contains("max_responses")) {
    responsesLimit = configJson["config"]["max_responses"];
  }

  return responsesLimit;
}

std::vector<std::string> ConverterJSON::getRequests() {
  std::vector<std::string> requests;

  json requestsJson = _getJsonFromFile(_requestsPath);
  auto requestsList = requestsJson["requests"];

  for (const auto& request : requestsList) {
    requests.push_back(request);
  }

  return requests;
}

void ConverterJSON::putAnswers(
    std::vector<std::vector<RelativeIndex>> answersList) {
  json answersJson;

  int responsesLimit = getResponsesLimit();
  int requestCounter{1};

  for (const auto& answer : answersList) {
    json answerJson;
    answerJson["result"] = answer.empty() ? "false" : "true";

    if (!answer.empty()) {
      json relevanceArray;

      for (int i{0};
           i < std::min(responsesLimit, static_cast<int>(answer.size())); ++i) {
        json relevance;
        relevance["doc_id"] = answer[i].doc_id;
        relevance["rank"] = answer[i].rank;
        relevanceArray.push_back(relevance);
      }

      answerJson["relevance"] = relevanceArray;
    }

    std::string name = "request";
    name += (requestCounter < 10 ? "00" : (requestCounter < 100 ? "0" : "")) +
            std::to_string(requestCounter);

    answersJson["answers"][name] = answerJson;
    _writeJsonToFile(_answersPath, answersJson);
    ++requestCounter;
  }
}
