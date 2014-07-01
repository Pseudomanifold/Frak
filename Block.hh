#ifndef Block_hh__
#define Block_hh__

#include <cstddef>

struct Block
{
  Block( std::size_t begin_, std::size_t end_ );

  std::size_t begin;
  std::size_t end;
};

#endif
