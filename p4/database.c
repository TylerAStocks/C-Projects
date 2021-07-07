/** Stores a database of all the given movies
* @file database.c
* @author Tyler Stocks tastock2
  */
  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "database.h"
#include "input.h"






/** Dynamically allocates storage for the database,
* initiallizes its fields, and returns a pointer to it
* @return a pointer to the database
  */
Database *makeDatabase()
{
  Database *database = 
    ( Database *)malloc( sizeof( Database ) );
    
    return database;

}

/** Frees the memory used to store the database, including freeing space for all
* the movies, freeing the resizable array of movie pointers and freeing space for the database
* struct itself
* @param *dat The given database to have memory freed for it
  */
void freeDatabase( Database *dat )
{
  free ( dat );
}

/** Reads all movies from a movie list file with the given name.
* Makes an instance of the Movie struct for each one and stores a pointer to that
* movie in the resizable array.
* @param *dat Pointer to the database
* @param *filename Name of the given file
  */
void readDatabase( Database *dat, char const *filename )
{
  FILE *fp = fopen( filename, "r");
  if ( !fp ) {
    fprintf( stderr, "Can't open file: %s\n", filename );
    exit( 1 );
  }
  
  char *line;
  while ( ( line = readLine( fp ) ) != NULL ) {
    int id;
    char title[ TITLE_CAP ];
    int year;
    int length;
    int pos;
    sscanf( line, "%d%s", &id, &title );
    
    Movie m = { id, title };
    printf( "%d   %s\n", m.id, m.title );
  }
  fclose( fp );
}

/** Lists all movies in the database, sorted by ID number.
* The movies component can call this when the user enters the database command
* @param *dat The given database
  */
void listAll( Database *dat ) 
{

}



/** lists all movies with a year between the given min and max values (inclusive).
* The movies component can call this when the user enters the year command.
* In the output, movies are sorted by year, and by ID if they have the same year.
* @param *dat The given database
* @param min The minimum year value
* @param max The maximum year value
  */
void listYear ( Database *dat, int min, int max )
{

}

/** Lists all movies where the given title string occurs in the movie's title field.
* In the output, the movies are listed in order by ID. 
* @param *dat The given database
* @param *title The given title string
  */
void listTitle( Database *dat, char const *title )
{

}


/** Extra credit function
* Reports all movies where the given genre string occurs in the movie's genre field
* In the output, movies are listed in order by ID
  */
void listGenre( Database *dat, char const *genre )
{

}


/** Static function in the database component
* used by listAll(), listYear(), listTitle(), and listGenre() functions to actually report the list
* of movies in the right format.
* In addition to a pointer to the database, this function also takes a pointer to a function
* (test) and a pointer to an arbitrary block of data (data) to let the caller tell the function
* which particular movies it should print out.
* @param *dat The given database
  */
void listDatabase( Database *dat, bool (*test)( Movie const *movie, void const *data ), void const *data )
{

}

