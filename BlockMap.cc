#include "BlockMap.hh"

std::size_t BlockMap::getBegin( std::size_t address ) const
{
  return _mapEnd.at( address );
}

std::size_t BlockMap::getEnd( std::size_t address ) const
{
  return _mapBegin.at( address );
}
