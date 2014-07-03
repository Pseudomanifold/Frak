#ifndef BlockMap_hh__
#define BlockMap_hh__

#include <map>
#include <vector>
#include <utility>

class BlockMap
{
public:

  /**
    Creates a new block map from a vector of Brainf*ck commands.

    @param commands Vector of commands
  */
  
  BlockMap( const std::vector<char>& commands );

  /**
    Creates a new block map from an arbitrary range of commands.

    @param begin Input iterator to begin of range
    @param end   Input iterator to end of range
  */

  template <class InputIterator> BlockMap( InputIterator begin, InputIterator end )
    : BlockMap( std::vector<char>( begin, end ) )
  {
  }

  /** @returns The matching address for the start or end of a block */
  std::size_t getMatchingAddress( std::size_t address ) const;

private:

  /**
    Maps matching addresses to each other. Each block [a,b] in the program will
    result in the entries a->b and b->a being made.

    This is not optimal and could be solved more easily with Boost's bimap.
  */

  std::map<std::size_t, std::size_t> _addressMap;
};

#endif
