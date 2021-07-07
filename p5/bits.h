
#include <stdio.h>
#include <stdlib.h>

/** amount of bits held in the buffer element **/
#define BUFFER 8




/** Responsible for reading in binary values **/
typedef struct {
  /** the file being read from **/
  FILE *file;
  /** holds up to 8 bits before reading in more **/
  unsigned char buffer;
  /** how many bit values currently in the buffer **/
  int count;


} BitReader;

/** Responsible for writing bit values to a file **/
typedef struct {
  /** the file being written to **/
  FILE *file;
  /** holds up to 8 bits before writing them to the file **/
  unsigned char buffer;
  /** how many bit values currently in the buffer **/
  int count;


} BitWriter;


/** Opens the given file for reading and dynamically allocates a new BitReader struct for it,
* intializes it and returns a pointer to it
* @param filename The given input file
  */ 
BitReader *openBitReader ( char const *filename );

/** Frees any resources used by the given BitReader, closes the file it's reading from and
* frees any memory the reader was using
* @param reader The BitReader object
  */
void closeBitReader ( BitReader *reader );

/** Client code calls this function to get the next bit from the file the reader is reading from.
* If the buffer contains any bits that haven't been returned yet, it returns the next bit from
* the buffer. If the buffer is empty, it reads the next byte from the input file and returns
* the high-order bit from that byte. If there are no more bits left, returns EOF
* @param reader The BitReader object
  */
int getBit ( BitReader *reader );

/** Creates a new BitWriter struct, opening a file with the given name, allocating space
* for the BitWriter and initializing is fields as needed.
* Returns a pointer to the new BitWriter struct
* @param filename The name of the given file
  */
BitWriter *openBitWriter ( char const *filename );

/** Frees all resources for the given BitWriter.
* If there are some buffered bits, they will be written out to the output file before it is closed,
* with zero bits used to fill in any low-order bits that were never used.
* @param writer The given writer object to be closed
  */
void closeBitWriter ( BitWriter *writer );

/** Writes a bit to the output file.
* The val parameter will be 0 for writing a 0 bit, or 1 for writing a 1 bit.
* Bits are stored internally in the BitWriter struct until there are 8 of them,
* then they can be written to the output file as a single byte.
* @param writer The given writer object that holds the bit
* @param val The given bit value to be put in the writer
  */
void putBit ( BitWriter *writer, int val );