/** Implements the encode and decode programs, using functions provided by 
* the other three programs.
* @author Tyler Stocks tastock2
* @file encode.c
  */
  
#include "j10.h"
/** size of array of chars used to read suffix of args **/
#define SUFFIX 4
/** Number of arguments required for the program **/
#define ARGS 3
  
int main( int argc, char *argv[] )
{
  if ( argc != ARGS ) {
    fprintf( stderr, "usage: encode <input.pgm> <output.j10>\n" );
    exit( 1 );
  }
  
  char suffixA[SUFFIX];
  char suffixB[SUFFIX];
  
  strcpy( suffixA, &argv[1][strlen( argv[1] ) - 3] );
  strcpy( suffixB, &argv[2][strlen( argv[2] ) - 3] );
  
  if ( strcmp( suffixA, "pgm" ) != 0 ) {
    fprintf( stderr, "Invalid image file\n" );
    exit( 1 );
  }
  
  
  
  Image image = readImage( argv[1] );
  BitWriter *writer = openBitWriter( argv[2] );
  encodeImage( &image, writer );

  
  
}