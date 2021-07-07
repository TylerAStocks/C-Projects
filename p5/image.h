/**
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _IMAGE_H_
#define _IMAGE_H_

/** Magic number for the raw PGM format. */
#define PGM_MAGIC "P5"

/** Maximum intensity value expected for images. */
#define STD_RANGE 255
/** Maximum number of pixels supported by the program **/
#define MAX_PIX 4096

/** Representation for the contents of an image file. */
typedef struct {
  /** number of rows */
  int rows;
  
  /** pixels per row */
  int cols;
  
  /** Dynamically allocated pixel data, rows * cols pixels, each with
      an intensity value in the range 0..255.  This is stored as an array
      of pointers, each one pointing to a row of pixel data. */
  unsigned char **pix;
} Image;

#endif

/** Creates an image of the given size. Allocates spaces for all image pixels, 
* but the intensity values don't need to be initialized
* @param rows The height value of the image
* @param cols The width value of the image
  */
Image *makeImage( int rows, int cols );

/** Creates an image, reading its contents from the given file (as a raw, PGM format image)
* @param filename The given name of the file
  */
Image readImage( char const *filename );
/** Writes the given image (in raw, PGM format) to the file with the given name
* @param image The given image being written
* @param filename The name of the file being written to
  */
void writeImage( Image *image, char const *filename );

/** Frees any memory used by the given image
* @param image The given image being freed
  */
void freeImage( Image *image );
