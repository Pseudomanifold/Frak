#include <iostream>
#include <string>

#include "Block.hh"
#include "BlockMap.hh"

#include "Frak.hh"
#include "Parser.hh"

void usage()
{
  // FIXME
  std::cout << "Usage: frak [options] file...\n"
            << "Options:\n";
}

int main(int argc, char* argv[])
{
  if( argc == 1 )
  {
    usage();
    return -1;
  }

  std::string inputFilename = argv[1];

  Parser parser;
  commands_type commands    = parser.parse(inputFilename);
  std::vector<Block> blocks = parser.getBlocks(commands);

  BlockMap blockMap( blocks.begin(), blocks.end() );

  std::size_t ip = 0;
  std::size_t dp = 0;

  std::vector<char> memory( 30000, 0 );

  for( ; ip < commands.size();  )
  {
    command_type command = commands.at( ip );

    if( command == '>' )
      ++dp;
    else if( command == '<' )
      --dp;
    else if( command == '+' )
      ++memory.at( dp );
    else if( command == '-' )
      --memory.at( dp );
    else if( command == '.' )
      std::cout << memory.at( dp );
    else if( command == ',' )
    {
      char c;
      if( std::cin >> c )
        memory.at( dp ) = c;
      else
        throw std::runtime_error( "Unable to obtain input" );
    }
    else if( command == '[' )
    {
      if( memory.at( dp ) == 0 )
      {
        ip = blockMap.getEnd( ip ) + 1;
        continue;
      }
    }
    else if( command == ']' )
    {
      if( memory.at( dp ) != 0 )
      {
        ip = blockMap.getBegin( ip ) + 1;
        continue;
      }
    }

    ++ip;
  }

  return 0;
}
