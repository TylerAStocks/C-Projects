/** Contains support for encoding and decoding images in our j10 format.
* @author Tyler Stocks tastock2
* @file j10.c
  */
  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "j10.h"
/** Amount of bits used to define the rows and columns **/
#define SIZE_BITS 12

/** Computes the Discrete Cosine Transform, reading pixel intensities from the X array and 
* storing the result of the DCT in Y. To use this, you'll need to copy individual blocks of 
* pixel data from the input image into a 10x10 array of doubles.
  */
void DCTBlock ( double X[ BLOCK_SIZE ][ BLOCK_SIZE ], double Y[ BLOCK_SIZE ][ BLOCK_SIZE ] )
{
  double sM;
  double sN;
  for ( int m = 0; m < BLOCK_SIZE; m++ ) {
    if ( m == 0 ) {
      sM = S_ZERO;
    } else {
      sM = 1.0;
    }
    for ( int n = 0; n < BLOCK_SIZE; n++ ) {
      if ( n == 0 ) {
        sN = S_ZERO;
      } else {
        sN = 1.0;
      }
      
      
      
      
      for ( int i = 0; i < BLOCK_SIZE; i++ ) {
        for ( int j = 0; j < BLOCK_SIZE; j++ ) {
          double mCos = cos( ( M_PI / (double)BLOCK_SIZE ) * ( i + 0.5 ) * m );
          double nCos = cos( ( M_PI / (double)BLOCK_SIZE ) * ( j + 0.5 ) * n );
          
          
          Y[ m ][ n ] += S_CONST * ( 2 /(double) BLOCK_SIZE ) * sM * sN * mCos * nCos * X[ i ][ j ];
        
        }
      }
      
      Y[m][n] = round( Y[m][n] );
      
    } 
  }
}


/** Computes the inverse DCT, reading from the Y array and writing pixel intensity values to X.
  */
void IDCTBlock ( double Y[ BLOCK_SIZE ][ BLOCK_SIZE ], double X[ BLOCK_SIZE ][ BLOCK_SIZE ] )
{
  double sM;
  double sN;
  for ( int i = 0; i < BLOCK_SIZE; i++ ) {
    for ( int j = 0; j < BLOCK_SIZE; j++ ) {
      
      
      for ( int m = 0; m < BLOCK_SIZE; m++ ) {
        if ( m == 0 ) {
          sM = S_ZERO;
        } else {
          sM = 1.0;
        }
        for ( int n = 0; n < BLOCK_SIZE; n++ ) {
          if ( n == 0 ) {
            sN = S_ZERO;
          } else {
            sN = 1.0;
          }
          
          double mCos = cos( ( M_PI / (double)BLOCK_SIZE ) * ( i + 0.5 ) * m );
          double nCos = cos( ( M_PI / (double)BLOCK_SIZE ) * ( j + 0.5 ) * n );
          X[ i ][ j ] += ( 1 / S_CONST ) * ( 2 /(double) BLOCK_SIZE ) * sM * sN * mCos * nCos * Y[ m ][ n ];
          
        }
      }
    }
  }
  
}


/** Encodes the given image in the j10 format. Writes bits using the given BitWriter struct.
  */
void encodeImage ( Image *image, BitWriter *writer )
{
  double *X[ BLOCK_SIZE ][ BLOCK_SIZE ] = {};
  
  for( int i = SIZE_BITS - 1; i >= 0; i-- ) {
    putBit( writer, image->rows & ( 0x01 << i ) ? 1 : 0 );
  }
  
  for ( int i = SIZE_BITS - 1; i >= 0; i-- ) {
    putBit( writer, image->cols & ( 0x01 << i ) ? 1 : 0 );
  }
  
  for ( int i = 0; i < ( image->rows) / BLOCK_SIZE; i++ ) {
    for ( int j = 0; j < ( image->cols ) / BLOCK_SIZE; j++ ) {
      
      for ( int m = 0; m < BLOCK_SIZE; m++ ) {
        for ( int n = 0; n < BLOCK_SIZE; n++ ) {
          X[ m ][ n ] = image->pix[ ( i * BLOCK_SIZE ) + m ][ ( j * BLOCK_SIZE ) + n ];
        }
      }
      double *Y[ BLOCK_SIZE ][ BLOCK_SIZE ] = {};
      DCTBlock( X, Y );
      
      for( int m = 6; m >= 0; m-- ) {
        putBit( writer, (int)Y[0][0] & ( 0x01 << m ) ? 1 : 0 );
      }
      
      for ( int m = 0; m < BLOCK_SIZE; m++ ) {
        for ( int n = 0; n < BLOCK_SIZE; n++ ) {
          if ( m > 0 || n > 0 ) {
            if ( Y[ m ][ n ] != 0 ) {
              putBit( writer, 1 );
            } else {
              putBit( writer, 0 );
            }
            
          }
        }
      }
      
      for ( int m = 0; m < BLOCK_SIZE; m++ ) {
        for ( int n = 0; n < BLOCK_SIZE; n++ ) {
          if ( n > 0 && m > 0 ) {
            
            if ( Y[ m ][ n ] > 0 ) {
              putBit( writer, 0 );
              for( int b = 6; b >= 0; b-- ) {
                putBit( writer, ( int )Y[ m ][ n ] & ( 0x01 << b ) ? 1 : 0 );
              }
            } else if ( Y[m][n] < 0 ) {
              putBit( writer, 1 );
              int yAbs = fabs( (int) Y[m][n] );
              for( int b = 6; b >= 0; b-- ) {
                putBit( writer, yAbs & (0x01 << b ) ? 1 : 0 );
              }
            
            }
            
          }
        }
      }
      
    }
  }
  closeBitWriter( writer );
  freeImage( image );
  
}


/** Creates a new image and returns a pointer to it, decoding the j10 format to fill in the image pixels.
* It uses the given BitReader to extract individual bits from the encoded image
  */
Image *decodeImage ( BitReader *reader )
{
  int rows = 0;
  int cols = 0;
  
  for ( int i = 0; i < SIZE_BITS; i++ ) {
    rows += fgetc( &reader->file ) * exp2( i );
  }
  
  for ( int i = 0; i < SIZE_BITS; i++ ) {
    cols += fgetc( &reader->file ) * exp2( i );
  }
  
  
}


