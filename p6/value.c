#include "value.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Value Subclasses

/** Representation for an Integer, a subclass of Value. */
typedef struct {
  void (*print)( Value *value, FILE *stream );
  bool (*equals)( Value *value, Value *other );
  Value *(*copy)( Value *value );
  void (*destroy)( Value *value );

  /** Integer value contained in this Value subclass. */
  int val;
} Integer;

/** Implementation of print for Integer */
static void printInteger( Value *value, FILE *stream )
{
  // If this function gets called, value must really be an Integer.
  Integer *this = (Integer *) value;
  printf( "%d", this->val );
}

/** Implementation of equals for Integer */
static bool equalsInteger( Value *value, Value *other )
{
  // If this function gets called, value must really be an Integer.
  Integer *this = (Integer *) value;
  
  // If they're not the same type, then theyre not equal. We can use
  // one of the function poitners to make sure other is an Integer.  It is
  // if it has the right print function for an int.
  if ( other->print != printInteger )
    return false;

  // If they're both integers, return true if they contain the same value.
  Integer *that = (Integer *) other;
  return this->val == that->val;
}

/** Implementation of copy for Integer */
static Value *copyInteger( Value *value )
{
  return makeInteger( ((Integer *) value)->val );
}

/** Implementation of destroy for Integer */
static void destroyInteger( Value *value )
{
  free( value );
}

Value *makeInteger( int val )
{
  // Allocate space for an Integer object.
  Integer *this = (Integer *) malloc( sizeof( Integer ) );

  // Record pointers to the right functions for working with this object.
  this->print = printInteger;
  this->equals = equalsInteger;
  this->copy = copyInteger;
  this->destroy = destroyInteger;

  // Record a copy of the given integer value.
  this->val = val;

  return (Value *) this;
}

/** Documented in the header. */
int toInt( Value *value )
{
  // We can use one of the function poitners to make sure this is an
  // Integer.
  if ( value->print != printInteger ) {
    fprintf( stderr, "Expected Integer value\n" );
    exit( EXIT_FAILURE );
  }

  // Get a copy of the value, then free the value that contained it.
  int val = ((Integer *) value)->val;
  value->destroy( value );

  // Return the int value that was inside.
  return val;
}

//////////////////////////////////////////////////////////////////////
// Environment.

// Define your own Environment struct to hold the values of all
// variables.

typedef struct {
  char *name;
  Value *value;
  
} Variable;

struct EnvironmentStruct {
  Value *(*lookup) ( Environment *env, char const *name );
  void (*set)( Environment *env, char const *name, Value *value );
  void (*free)( Environment *env );
  
  Variable *var;
  int len;
  
};



Environment *makeEnvironment()
{
  Environment *this = (Environment *)malloc( sizeof( Environment ) );
  this->lookup = lookupVariable;
  this->set = setVariable;
  this->free = freeEnvironment;
  
  this->var = (Variable *)malloc( sizeof( Variable ) );
  this->len = 0;
  
  
  return this;
}

Value *lookupVariable( Environment *env, char const *name )
{
  Environment *this = (Environment *) env;
  
  for( int i = 0; i < this->len; i++ ) {
    if ( strcmp( this->var[i].name, name ) == 0 ) {
      return this->var[i].value;
    }
  }
  return NULL;
  
}

void setVariable( Environment *env, char const *name, Value *value )
{
  Environment *this = (Environment *) env;
  bool inUse = false;
  
  for( int i = 0; i < this->len; i++ ) {
    if ( strcmp( this->var[i].name, name ) == 0 ) {
      inUse = true;
      this->var[i].value = value;
    }
  }
  if ( !inUse ) {
    this->len++;
  
    this->var = (Variable *)realloc(this->var, this->len * sizeof( Variable ) );
    this->var[this->len - 1].name = (char *)malloc( strlen( name ) + 1 );
    
    this->var[this->len - 1].value = value;
    strcpy(this->var[this->len - 1].name, name );
  }
}

void freeEnvironment( Environment *env )
{
  for ( int i = 0; i < env->len; i++ ) {
    env->var[i].value->destroy( env->var[i].value );
  }
  free( env );
}

