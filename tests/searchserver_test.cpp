#include "../src/my_lib/src/searchserver.cpp"
#include <gtest/gtest.h>

TEST(TestCaseSearchServer, TestSimple) {
  const std::vector<std::string> docs = {
      "milk milk milk milk water water water", "milk water water",
      "milk milk milk milk milk water water water water water",
      "americano cappuccino"};
  const std::vector<std::string> request = {"milk water", "sugar"};
  const std::vector<std::vector<RelativeIndex>> expected = {
      {{2, 1}, {0, 0.7}, {1, 0.3}}, {}};
  InvertedIndex idx;
  idx.updateDocumentBase(docs);
  SearchServer srv(idx);
  std::vector<std::vector<RelativeIndex>> result = srv.search(request);

  ASSERT_EQ(result, expected);
}
