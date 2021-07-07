

#include <stdlib.h>
#include <stdbool.h>

#define CAP 10
#define TITLE_CAP 38

struct Movie {
  int id;
  char title[ TITLE_CAP ];
  int year;
  int length;
};

typedef struct Movie Movie;


struct Database {
  Movie movies;
  int count;
  int capacity;
};
  
typedef struct Database Database;


Database *makeDatabase();
void freeDatabase( Database *);
void readDatabase( Database *, char const *);