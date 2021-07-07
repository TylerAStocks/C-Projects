#include "stringval.h"

#include <stdlib.h>
#include <string.h> 



/** Representation for a String, a subclass of Value. */
typedef struct {
  void (*print)( Value *value, FILE *stream );
  bool (*equals)( Value *value, Value *other );
  Value *(*copy)( Value *value );
  void (*destroy)( Value *value );
  
  char *val;
} String;



static void printString( Value *value, FILE *stream )
{
  String *this = (String *) value;
  printf( "%s", this->val );

}


static bool equalsString( Value *value, Value *other )
{
  String *this = (String *) value;
  
  if( other->print != printString ) {
    return false;
  }
  
  
  String *that = (String *) other;
  if ( strcmp( this->val, that->val ) == 0 ) {
    return true;
  } else {
    return false;
  }

}


static Value *copyString( Value *value )
{
  String *this = (String *) value;
  return makeString( this->val );
  
}



static void destroyString( Value *value )
{
  free( value );
}




Value *makeString( char *val )
{
  String *this = (String *)malloc( sizeof( String ) );
  
  this->print = printString;
  this->equals = equalsString;
  this->copy = copyString;
  this->destroy = destroyString;
  
  
  this->val = (char *)malloc( strlen( val ) + 1 );
  strcpy( this->val, val );
  
  return (Value *) this;
  
}



typedef struct {
  int (*get)(Value *value);

} Strlen;


static int getStrlen( Value *value)
{
  String *this = (String *) value;
  
  return strlen(this->val);

}


Expr *makeStrlen( Value *value )
{
  Strlen *this = (Strlen *)malloc( sizeof( Strlen ) );
  this->get = getStrlen;
  
  return (Expr *) this;

}





