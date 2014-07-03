#include "BlockMap.hh"

#include <stack>
#include <stdexcept>

BlockMap::BlockMap( const std::vector<char>& commands )
{
  typedef std::pair<char, std::size_t> paren;
  std::stack<paren> parens;

  for( std::size_t i = 0; i < commands.size(); i++ )
  {
    if( commands[i] == '[' )
      parens.push( std::make_pair( commands[i], i ) );
    else if( commands[i] == ']' )
    {
      if( parens.empty() || parens.top().first != '[' )
        throw std::runtime_error( "Encountered unmatched parenthesis" );

      paren p = parens.top();
      parens.pop();

      std::size_t begin = p.second;
      std::size_t end   = i;

      // Store the block; I am aware that this is rather wasteful as the same
      // information is stored twice...
      _addressMap.insert( std::make_pair( begin, end   ) );
      _addressMap.insert( std::make_pair( end,   begin ) );
    }
  }

  if( !parens.empty() )
    throw std::runtime_error( "Encountered unmatched parenthesis" );
}

std::size_t BlockMap::getMatchingAddress( std::size_t address ) const
{
  return _addressMap.at( address );
}
