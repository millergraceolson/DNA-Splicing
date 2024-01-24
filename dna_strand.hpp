// dna_strand.hppMP5!!!:)
#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <stdexcept>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  // Node* CreateNode(char data);

  void PerformSplice(Node* last_occurrence,
                     DNAstrand& to_splice_in,
                     size_t pattern_length);

private:
  Node* head_;
  Node* tail_;

  Node* FindLast(const char* pattern);
  void ClearNodes();
};

#endif
