#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#include "value.h"
//#include "syntax.h"
#include "parse.h"

/** Print a usage message then exit unsuccessfully. */
void usage()
{
  fprintf( stderr, "usage: interpret <program-file>\n" );
  exit( EXIT_FAILURE );
}

int main( int argc, char *argv[] )
{
  // Open the program's source.
  if ( argc != 2 )
    usage();
  FILE *fp = fopen( argv[ 1 ], "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open file: %s\n", argv[ 1 ] );
    usage();
  }

  // Environment, for storing variable values.
  Environment *env = makeEnvironment();
  
  // Parse one statement at a time, then run each statement
  // using the same Environment.
  char tok[ MAX_TOKEN + 1 ];
  while ( parseToken( tok, fp ) ) {
    // Parse the next input statement.
    Stmt *stmt = parseStmt( tok, fp );

    // Run it.
    stmt->execute( stmt, env );

    // Delete it.
    stmt->destroy( stmt );
  }
  
  // We're done, close the input file and free the environment.
  fclose( fp );
  freeEnvironment( env );

  return EXIT_SUCCESS;
}
