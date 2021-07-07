/** Parses command line arguments, opens the input and output files and uses the 
* text and operations components to read the input, carry out the encryption
* operations, then write out the result text.
* @file encrypt.c
* @author Tyler Stocks tastock2
  */
  
  
#include <stdlib.h>
#include <stdio.h>
#include "operations.h"
#include "text.h"
  
int main( int argc, char *argv[] )
{
  FILE *out;
  FILE *fp;
  
  if ( strcmp( argv[ argc - 2 ], "-" ) == 0 ) {
    fp = NULL;
  } else {
    fp = fopen ( argv[ argc - 2 ], "r" );
    if ( !fp ) {
      fprintf( stderr, "Can't open file: %s\n", argv[ argc - 2 ] );
      exit( 1 );
    } 
  }

  readFile( fp );
  

  for ( int i = 1; i < argc - 2; i++ ) {
    if ( strcmp( argv[ i ], "shift" ) == 0 ) {
      int m = atoi( argv[ i + 1 ] );
      shiftLetters( m );
    } else if ( strcmp( argv[ i ], "reverse" ) == 0 ) {
      reverseLines();
    } else if ( strcmp( argv[ i ], "swap" ) == 0 ) {
      int m = atoi( argv[ i + 1 ] );
      int n = atoi( argv[ i + 2 ] );
      if ( n == 0 || m == 0 ) {
        fprintf( stderr, "invalid arguments\nusage: encrypt operation* (infile|-) (outfile|-)\n" );
        exit( 1 );
    }
    m--;
    n--;
    if ( n >= lineCount || m >= lineCount ) {
      fprintf( stderr, "invalid arguments\nusage: encrypt operation* (infile|-) (outfile|-)\n" );
      exit( 1 );
    }
      swapLines( m, n );
    } else if ( strcmp( argv[ i ], "left" ) == 0 ) {
      rotateLinesLeft();
    } else if ( strcmp( argv[ i ], "right" ) == 0 ) {
      rotateLinesRight();
    } else {
      if ( atoi ( argv[ i ] ) == 0 ) {
        fprintf( stderr, "invalid arguments\nusage: encrypt operation* (infile|-) (outfile|-)\n" );
        exit( 1 );
      }
    }
  }
  
  if ( strcmp( argv[ argc - 1 ], "-" ) == 0 ) {
    out = NULL;
  } else {
    out = fopen( argv[ argc - 1 ], "w" );
  }
  
  writeFile( out );
  
}