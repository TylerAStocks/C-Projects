/**
*/

#ifndef _J10_H_
#define _J10_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "bits.h"

/** Size of each image block used in the compressed image. */
#define BLOCK_SIZE 10
/** constant scaling factor value **/
#define S_CONST 0.044997
/** Value of Sm or Sn when m or n equals 0 **/
#define S_ZERO ( 1 / sqrt( 2 ) )

#endif


void encodeImage ( Image *image, BitWriter *writer );
Image *decodeImage ( BitReader *reader );