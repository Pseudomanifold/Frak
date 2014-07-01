#include "Block.hh"
#include "Parser.hh"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <stack>
#include <stdexcept>

namespace
{

bool isValidCommand( command_type command )
{
  return    command == '>'
         || command == '<'
         || command == '+'
         || command == '-'
         || command == '.'
         || command == ','
         || command == '['
         || command == ']';
}

typedef std::pair<command_type, std::size_t> paren;

} // anonmyous namespace

commands_type Parser::parse( const std::string& filename ) const
{
  std::ifstream in( filename );
  if( !in )
    throw std::runtime_error( "Unable to open input file" );

  commands_type commands;

  std::copy_if( std::istreambuf_iterator<command_type>( in ),
                std::istreambuf_iterator<command_type>(),
                std::back_inserter( commands ),
                isValidCommand );

  return commands;
}

std::vector<Block> Parser::getBlocks( const commands_type& commands ) const
{
  std::stack<paren> parens;
  std::vector<Block> blocks;

  // FIXME: Requiring knowledge about the implementation of `commands_type`
  // here. This could surely be solved better. I miss Python's `enumerate()`.
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

      blocks.push_back( Block(begin, end) );
    }
  }

  if( !parens.empty() )
    throw std::runtime_error( "Encountered unmatched parenthesis" );

  return blocks;
}
