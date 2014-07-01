#ifndef BlockMap_hh__
#define BlockMap_hh__

#include <map>

#include "Block.hh"

class BlockMap
{
public:
  template <class InputIterator> BlockMap( InputIterator begin, InputIterator end )
  {
    for( InputIterator it = begin; it != end; ++it )
    {
      const Block& block = *it;

      _mapBegin[block.begin] = block.end;
      _mapEnd[block.end]     = block.begin;
    }
  }

  std::size_t getBegin( std::size_t address ) const;
  std::size_t getEnd( std::size_t address ) const;

private:
  std::map<std::size_t, std::size_t> _mapBegin;
  std::map<std::size_t, std::size_t> _mapEnd;
};

#endif
