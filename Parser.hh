#ifndef Parser_hh__
#define Parser_hh__

#include <string>
#include <vector>

#include "Frak.hh"

class Block;

class Parser
{
public:
  commands_type parse( const std::string& filename ) const;
  std::vector<Block> getBlocks( const commands_type& commands ) const;
};

#endif
