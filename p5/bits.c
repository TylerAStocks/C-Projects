/** Supports reading and writing files one bit at a time
* @author Tyler Stocks tastock2
* @file bits.c
  */
  
  
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
  

BitReader *openBitReader ( char const *filename )
{
  FILE *fp = fopen( filename, "rb" );
  
  if ( fp == NULL ) {
    perror( filename );
    exit( 1 );
  }
  
  BitReader *bReader = (BitReader *) malloc( sizeof( BitReader ) );
  bReader->file = fp;
  bReader->buffer = 00000000;
  bReader->count = BUFFER;
  
  return bReader;
  

}



void closeBitReader ( BitReader *reader )
{
  fclose( reader->file );
  free( reader );
  
}



int getBit ( BitReader *reader )
{
  if( reader->count == BUFFER ) {
    if ( fread( &reader->buffer, sizeof( char ), 1, reader->file ) == 0 ) {
      reader->count = BUFFER;
      return EOF;
    }
    reader->count = 0;
  }
  
  
  unsigned char bit = reader->buffer & 0x01 << ( BUFFER - (reader->count) - 1 );
  
  
  
  int val = 0;
  if ( bit ) {
    val = 1;
  }
  
  
  reader->count++;
  
  return val;
}



BitWriter *openBitWriter ( char const *filename )
{
  FILE *out = fopen( filename, "wb" );
  
  BitWriter *writer = (BitWriter *) malloc( sizeof( BitWriter ) );
  writer->file = out;
  writer->buffer = 0x00;
  writer->count = 0;
  
  return writer;
}



void closeBitWriter ( BitWriter *writer )
{
  if ( writer->count > 0 ) {
    for( int i = 0; i < BUFFER; i++ ) {
      putBit( writer, 0 );
    }
  } 
  fclose( writer->file );
  free( writer );

}



void putBit ( BitWriter *writer, int val )
{

  if ( writer->count < BUFFER ) {
    if ( val == 1 ) {  
      writer->count++;
      writer->buffer |= 0x01 << ( BUFFER - (writer->count) );
    } else {
      writer->count++;
    }
  }
  if ( writer->count == BUFFER ) {
    fwrite( &(writer->buffer), sizeof( char ), 1, writer->file );
    writer->count = 0;
    writer->buffer = 0x00;
  }
  
}











