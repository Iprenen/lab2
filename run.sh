#!bin/bash

make clean
make

clear

echo "Pthreads tests"
echo "critical"
./lab2 -t critical -c pthreads
./lab2 -t critical4 -c pthreads
./lab2 -t critical8 -c pthreads
echo "incdec"
./lab2 -t incdec_no_atomic -c pthreads
./lab2 -t incdec_atomic -c pthreads
echo "cmpxchg"
./lab2 -t cmpxchg_atomic -c pthreads
./lab2 -t cmpxchg_no_atomic -c pthreads


echo ""

echo "Dekker tests"

echo "critical"
./lab2 -t critical -c dekker

echo "incdec"
./lab2 -t incdec_no_atomic -c dekker
./lab2 -t incdec_atomic -c dekker
echo "cmpxchg"
./lab2 -t cmpxchg_atomic -c dekker
./lab2 -t cmpxchg_no_atomic -c dekker

echo ""

echo "CLH tests"

echo "critical"
./lab2 -t critical -c queue
./lab2 -t critical4 -c queue
./lab2 -t critical8 -c queue

echo "incdec"
./lab2 -t incdec_no_atomic -c queue
./lab2 -t incdec_atomic -c queue
echo "cmpxchg"
./lab2 -t cmpxchg_atomic -c queue
./lab2 -t cmpxchg_no_atomic -c queue
