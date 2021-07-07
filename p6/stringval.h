/**
  @file stringval.h
  @author Tyler Stocks tastock2

  Support for values that contain strings.
*/
#include <stdio.h>
#include <stdbool.h>
#include "syntax.h"



/** Make a String object out of a Value
    @param val The value of the string
    @return pointer to a new, dynamically allocated value
 */
Value *makeString( char *val );




/** Make a Strlen object out of a Expr
    @param value the value being evaluated
    @return pointer to a new, dynamically allocated value
 */
Expr *makeStrlen( Value *value );