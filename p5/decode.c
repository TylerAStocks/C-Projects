/** Implements the encode and decode programs, using functions provided by 
* the other three programs.
* @author Tyler Stocks tastock2
* @file decode.c
  */
  
#include <errno.h>
#include "j10.h"
  
/** size of array of chars used to read suffix of args **/
#define SUFFIX 4
/** Number of arguments required for the program **/
#define ARGS 3
  
int main( int argc, char *argv[] )
{
  errno = 0;
  if ( argc != ARGS ) {
    fprintf( stderr, "usage: decode <input.j10> <output.pgm>\n" );
    exit( 1 );
  }
  
  
  BitReader *reader = openBitReader( argv[1] );
  
  
  Image *image = decodeImage( &reader );
  //writeImage( &image, &reader );
  
  
  
  
}