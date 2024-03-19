#ifndef STRUCTURES_H
#define STRUCTURES_H

struct RelativeIndex {
  size_t doc_id;
  double rank;

  bool operator==(const RelativeIndex& other) const {
    return (doc_id == other.doc_id && rank == other.rank);
  }
};

struct Entry {
  size_t doc_id, count;

  bool operator==(const Entry& other) const {
    return (doc_id == other.doc_id && count == other.count);
  }
};

#endif // STRUCTURES_H
