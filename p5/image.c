/** Provides a struct for representing the contents of a PGM image.
* Provides functions for reading and writing an image from a file.
* The pixels of each image will be stored with each row in a dynamically allocated array.
* @author Tyler Stocks tastock2
* @file image.c
  */
  
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
  
  

Image *makeImage( int rows, int cols )
{
  Image *image = (Image *)malloc( sizeof( Image ) );
  
  image->rows = rows;
  image->cols = cols;
  return image;
}



Image readImage( char const *filename )
{
  FILE *fp = fopen( filename, "rb" );
  if ( !fp ) {
    perror( filename );
    exit( 1 );
  }
  char head[ 2 ];
  int rows;
  int cols;
  int intensity;
  fscanf( fp, "%s", head );
  if ( strcmp( head, PGM_MAGIC ) != 0 ) {
    fprintf( stderr, "Invalid image file\n" );
    exit( 1 );
  }
  
  fscanf( fp, "%d", &cols );
  fscanf( fp, "%d", &rows );
  fscanf( fp, "%d", &intensity);
  
  
  if ( intensity < STD_RANGE || rows > MAX_PIX || cols > MAX_PIX ) {
    fprintf( stderr, "Invalid image file\n" );
    exit( 1 );
  }
  
  Image *image = makeImage( rows, cols );
  
  image->pix = (unsigned char **)malloc( rows * sizeof( unsigned char * ) );
  for ( int i = 0; i < rows; i++ ) {
    image->pix[i] = (unsigned char *)malloc( cols * sizeof( unsigned char ) );
    fread( image->pix[i], sizeof( char ), cols, fp );
    if ( feof( fp ) ) {
      fprintf( stderr, "Invalid image file\n" );
      exit( 1 );
    }
  }
  
  fclose( fp );
  return *image;
  
}



void writeImage( Image *image, char const *filename )
{
  FILE *out = fopen( filename, "wb" );
  
  fprintf( out, "%s\n", PGM_MAGIC );
  fprintf( out, "%d ", image->cols );
  fprintf( out, "%d\n", image->rows );
  fprintf( out, "%d\n", STD_RANGE );
  
  for ( int i = 0; i < image->rows; i++ ) {
    fwrite( image->pix, 1, sizeof( image->pix ), out );
    fprintf( out, "\n" );
  }
  
  fclose( out );
}



void freeImage( Image *image )
{
  free( image->pix );
}