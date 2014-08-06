#pragma once
#include "common/scale.h"
#include "common/nvector.h"
#include "dag/physical_dag.h"
#include "op/closure.h"

namespace minerva {

class Chunk {
  friend class ChunkElewise;

 public:
  static Chunk Constant(const Scale&, float);
  static Chunk Randn(const Scale&, float, float);
  Chunk();
  Chunk(PhysicalDataNode* node);
  Chunk(const Chunk& other);
  PhysicalDataNode* data_node() const { return data_node_; }
  Chunk& operator=(const Chunk& other);

  friend Chunk operator + (Chunk, Chunk);
  friend Chunk operator - (Chunk, Chunk);
  friend Chunk operator / (Chunk, Chunk);
  friend Chunk operator + (Chunk, float);
  friend Chunk operator - (Chunk, float);
  friend Chunk operator * (Chunk, float);
  friend Chunk operator / (Chunk, float);
  friend Chunk operator + (float, Chunk);
  friend Chunk operator - (float, Chunk);
  friend Chunk operator * (float, Chunk);
  friend Chunk operator / (float, Chunk);
  void operator += (Chunk );
  void operator -= (Chunk );
  void operator /= (Chunk );
  void operator += (float );
  void operator -= (float );
  void operator *= (float );
  void operator /= (float );
  Chunk operator - ();
  // Matrix multiplication
  friend Chunk operator * (Chunk, Chunk); // Matrix multiplication
  // reduction
  Chunk Reduce(const Scale& dims_to_reduce, ReductionType );
  // shape
  Scale Size() const;
  int Size(int) const;
  Chunk Trans();

  static Scale ComputeOffset(NVector<Chunk> ); // return merged size
  static Chunk Merge(NVector<Chunk> );
  NVector<Chunk> Split(const NVector<Scale>& partsizes);

  // customized operations
  static std::vector<Chunk> Compute(const std::vector<Chunk>& params,
      const std::vector<Scale>& result_sizes, PhysicalComputeFn* fn);

 private:
  PhysicalDataNode* data_node_; // Set up in constructor
};

class ChunkElewise {
 public:
  static Chunk Exp(Chunk);
  static Chunk Ln(Chunk);
  static Chunk Sigmoid(Chunk);
  static Chunk Mult(Chunk, Chunk);
};

} // end of namespace minerva

