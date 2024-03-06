#include "../src/my_lib/src/invertedindex.cpp"
#include <gtest/gtest.h>

using namespace std;
void testInvertedIndexFunctionality(
    const vector<string>& docs, const vector<string>& requests,
    const std::vector<vector<Entry>>& expected) {
  std::vector<std::vector<Entry>> result;
  InvertedIndex idx;
  idx.updateDocumentBase(docs);
  for (auto& request : requests) {
    std::vector<Entry> word_count = idx.getWordCount(request);
    result.push_back(word_count);

    // из-за многопоточности результаты для каждого слова изначально не
    // отсортированы по doc_id
    for (auto& vector : result) {
      std::sort(vector.begin(), vector.end(),
                [](Entry a, Entry b) { return a.doc_id < b.doc_id; });
    }
  }
  ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
  const vector<string> docs = {
      "london is the capital of great britain",
      "big ben is the nickname for the Great bell of the striking clock"};
  const vector<string> requests = {"london", "the"};
  const vector<vector<Entry>> expected = {{{0, 1}}, {{0, 1}, {1, 3}}};
  testInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
  const vector<string> docs = {
      "milk milk milk milk water water water", "milk water water",
      "milk milk milk milk milk water water water water water",
      "americano cappuccino"};
  const vector<string> requests = {"milk", "water", "cappuccino"};
  const vector<vector<Entry>> expected = {
      {{0, 4}, {1, 1}, {2, 5}}, {{0, 3}, {1, 2}, {2, 5}}, {{3, 1}}};
  testInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
  const vector<string> docs = {"a b c d e f g h i j k l", "statement"};
  const vector<string> requests = {"m", "statement"};
  const vector<vector<Entry>> expected = {{}, {{1, 1}}};
  testInvertedIndexFunctionality(docs, requests, expected);
}
