#include "converterjson.h"
#include "invertedindex.h"
#include "searchserver.h"
#include "structures.h"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc > 4) {
    std::cerr << "Usage: Too many command-line arguments provided."
              << std::endl;
    return 1;
  }

  std::string pathToFolder = "./config";

  if (argc == 2) {
    pathToFolder = argv[1];
  }

  ConverterJSON converterJson(pathToFolder);

  if (argc > 2) {
    converterJson.setConfigPath(argv[1]);
    converterJson.setRequestsPath(argv[2]);
  }
  if (argc == 4) {
    converterJson.setAnswersPath(argv[3]);
  }

  InvertedIndex invertedIndex;
  invertedIndex.updateDocumentBase(converterJson.getTextDocuments());
  SearchServer searchServer(invertedIndex);
  auto results = searchServer.search(converterJson.getRequests());
  converterJson.putAnswers(results);
}
