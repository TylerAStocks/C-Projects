#!/bin/bash
FAIL=0

# Function to run the encode program and check its output against expected otuput.
testEncode() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.j10
  
  # Run the encode program, capturing standard output and standard error to files.
  echo "Encode Test $TESTNO : ./encode image-$TESTNO.pgm output.j10 > stdout.txt 2> stderr.txt"
  ./encode image-$TESTNO.pgm output.j10 > stdout.txt 2> stderr.txt
  STATUS="$?"

  # For all these tests, the program shouldn't print anything to standard output.
  if [ -s stdout.txt ]; then
      echo "**** Encode Test $TESTNO FAILED - program shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi
  
  # Make sure the program exited with the right exit status, success for most tests.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Encode Test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # If there's an expected error output message, make sure the program printed it.
  if [ -f estderr-$TESTNO.txt ]; then
      if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
	  echo "**** Encode Test $TESTNO FAILED - output to standard error (stderr.txt) didn't match expected (estderr-$TESTNO.gxt)"
	  FAIL=1
	  return 1
      fi
  else
      if [ -s stderr.txt ]; then
	  echo "**** Encode Test $TESTNO FAILED - program should not have printed output to standard error."
	  FAIL=1
	  return 1
      fi
  fi

  # Make sure the otuput image is right.
  if [ -f encoded-$TESTNO.j10 ] &&
	 ! diff -q encoded-$TESTNO.j10 output.j10 >/dev/null 2>&1 ; then
      echo "**** Encode Test $TESTNO FAILED - encoded image (output.j10) didn't match expected (encoded-$TESTNO.j10)"
      FAIL=1
      return 1
  fi

  echo "Encode Test $TESTNO PASS"
  return 0
}

# Function to run the decode program and check its output against expected otuput.
testDecode() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.pgm

  # Run the decode program, capturing standard output and standard error to files.
  # test 12 uses different command-line arguments.
  if [ "$TESTNO" == "12" ]; then
      echo "Decode Test $TESTNO : ./decode encoded-$TESTNO.j10 output.pgm extra-argument > stdout.txt 2> stderr.txt"
      ./decode encoded-$TESTNO.j10 output.pgm extra-argument > stdout.txt 2> stderr.txt
      STATUS="$?"
  else
      echo "Decode Test $TESTNO : ./decode encoded-$TESTNO.j10 output.pgm > stdout.txt 2> stderr.txt"
      ./decode encoded-$TESTNO.j10 output.pgm > stdout.txt 2> stderr.txt
      STATUS="$?"
  fi

  # For all these tests, the program shouldn't print anything to standard output.
  if [ -s stdout.txt ]; then
      echo "**** Decode Test $TESTNO FAILED - program shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi
  
  # Make sure the program exited with the right exit status, success for most tests.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Decode Test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # If there's an expected error output message, make sure the program printed it.
  if [ -f estderr-$TESTNO.txt ]; then
      if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
	  echo "**** Decode Test $TESTNO FAILED - output to standard error (stderr.txt) didn't match expected (estderr-$TESTNO.gxt)"
	  FAIL=1
	  return 1
      fi
  else
      if [ -s stderr.txt ]; then
	  echo "**** Decode Test $TESTNO FAILED - program should not have printed output to standard error."
	  FAIL=1
	  return 1
      fi
  fi

  # Make sure the otuput image is right.
  if [ -f decoded-$TESTNO.pgm ] &&
	 ! diff -q decoded-$TESTNO.pgm output.pgm >/dev/null 2>&1 ; then
      echo "**** Decode Test $TESTNO FAILED - decoded image (output.pgm) didn't match expected (decoded-$TESTNO.pgm)"
      FAIL=1
      return 1
  fi

  echo "Decode Test $TESTNO PASS"
  return 0
}

# Build a fresh copy of both programs
make clean
make

# Run tests on the encode program.
if [ -x encode ] ; then
    # Tests for valid inputs.
    testEncode 01 0
    testEncode 02 0
    testEncode 03 0
    testEncode 04 0
    testEncode 05 0
    testEncode 06 0
    
    # Tests for invalid inputs.
    testEncode 07 1
    testEncode 08 1
    testEncode 09 1
else
    echo "**** The encode program didn't build successfully"
    FAIL=1
fi

# Run tests on the decode program.
if [ -x decode ] ; then
    # Tests for valid inputs.
    testDecode 01 0
    testDecode 02 0
    testDecode 03 0
    testDecode 04 0
    testDecode 05 0
    testDecode 06 0
    
    # Tests for invalid inputs.
    testDecode 10 1
    testDecode 11 1
    testDecode 12 1
else
    echo "**** The encode program didn't build successfully"
    FAIL=1
fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
