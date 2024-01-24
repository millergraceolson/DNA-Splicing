// dna_strand.ccMP5!!:)
#include "dna_strand.hpp"

#include <stdexcept>

// DNAstrand::DNAstrand(): head_(nullptr), tail_(nullptr) {}

DNAstrand::~DNAstrand() { ClearNodes(); }

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr || *pattern == '\0' || to_splice_in.head_ == nullptr ||
      this == &to_splice_in) {
    return;
  }

  size_t pattern_length = 0;
  const char* p = pattern;
  while (*p != '\0') {
    pattern_length++;
    p++;
  }

  Node* last_occurrence = FindLast(pattern);
  if (last_occurrence != nullptr) {
    PerformSplice(last_occurrence, to_splice_in, pattern_length);
  } else {
    throw std::runtime_error("");
  }
}
void DNAstrand::ClearNodes() {
  Node* current = head_;
  while (current != nullptr) {
    Node* to_delete = current;
    current = current->next;
    delete to_delete;
  }
  head_ = tail_ = nullptr;
}

Node* DNAstrand::FindLast(const char* pattern) {
  Node* last_occurrence = nullptr;
  Node* current = head_;
  while (current != nullptr) {
    Node* check = current;
    const char* p = pattern;
    while (check != nullptr && *p != '\0' && check->data == *p) {
      check = check->next;
      p++;
    }
    if (*p == '\0') {
      last_occurrence = current;
    }
    current = current->next;
  }
  return last_occurrence;
}

void DNAstrand::PerformSplice(Node* last_occurrence,
                              DNAstrand& to_splice_in,
                              size_t pattern_length) {
  if (last_occurrence == nullptr || to_splice_in.head_ == nullptr) {
    return;
  }
  Node* prev = nullptr;
  if (last_occurrence != head_) {
    prev = head_;
    while (prev != nullptr && prev->next != last_occurrence) {
      prev = prev->next;
    }
  }
  Node* pattern_end = last_occurrence;
  for (size_t i = 0; i < pattern_length && pattern_end != nullptr; i++) {
    pattern_end = pattern_end->next;
  }

  if (last_occurrence == head_) {
    head_ = to_splice_in.head_;
  } else {
    prev->next = to_splice_in.head_;
  }
  Node* last_node = to_splice_in.head_;
  while (last_node->next != nullptr) {
    last_node = last_node->next;
  }
  last_node->next = pattern_end;
  if (pattern_end == nullptr) {
    tail_ = last_node;
  }

  while (last_occurrence != pattern_end) {
    Node* temp = last_occurrence;
    last_occurrence = last_occurrence->next;
    delete temp;
  }
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}
