#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <stack>
#include <utility>

// ---------------------------------------------------------------------

namespace Parser
{

/**
  Checks whether a given command is a valid Brainf*ck command. This auxiliary
  function is used to parse input files.
  
  @param c Character whose validity is going to be determined
  @returns true if \c c is a valid command
*/

bool isValid( char command )
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

/**
  Parse a given input file an stores a stream of valid Brainf*ck commands in an
  output iterator.

  @param[in]  filename Input filename
  @param[out] result   Output iterator for storing the commands
*/

template <class OutputIterator> void parse( const std::string& filename,
                                            OutputIterator result )
{
  std::ifstream in( filename );
  if( !in )
    throw std::runtime_error( "Unable to open input file" );

  std::copy_if( std::istreambuf_iterator<char>( in ),
                std::istreambuf_iterator<char>(),
                result,
                isValid );
}

/**
  Sets up a map of matching block statements. Assuming that the blocks are
  valid, this function will return a map for looking up the respective matching
  address of a given block.

  @param commands Vector of Brainf*ck commands
  @returns Map for finding matching blocks
*/

std::map<std::size_t, std::size_t> getBlockAddresses( const std::vector<char>& commands )
{
  typedef std::pair<char, std::size_t> paren;

  std::stack<paren> parens;
  std::map<std::size_t, std::size_t> addressMap;

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
      //
      // FIXME: Use a bimap?
      addressMap.insert( std::make_pair( begin, end   ) );
      addressMap.insert( std::make_pair( end,   begin ) );
    }
  }

  if( !parens.empty() )
    throw std::runtime_error( "Encountered unmatched parenthesis" );

  return addressMap;
}

} // namespace "Parser"

// ---------------------------------------------------------------------

void usage()
{
  // FIXME
  std::cout << "Usage: frak [options] file...\n"
            << "Options:\n";
}

// ---------------------------------------------------------------------

int main(int argc, char* argv[])
{
  if( argc == 1 )
  {
    usage();
    return -1;
  }

  std::string inputFilename = argv[1];

  std::vector<char> commands;

  Parser::parse( inputFilename,
                 std::back_inserter( commands ) );

  std::map<std::size_t, std::size_t> addressMap = Parser::getBlockAddresses( commands );

  std::size_t ip = 0;
  std::size_t dp = 0;

  std::vector<char> memory( 30000, 0 );

  for( ; ip < commands.size();  )
  {
    char command = commands.at( ip );

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
        ip = addressMap.at( ip ) + 1;
        continue;
      }
    }
    else if( command == ']' )
    {
      if( memory.at( dp ) != 0 )
      {
        ip = addressMap.at( ip ) + 1;
        continue;
      }
    }

    ++ip;
  }

  return 0;
}
