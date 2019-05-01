#!/bin/sh
./lightDB.exe <1.sql >1_cp.out
./lightDB.exe <2.sql >2_cp.out
./lightDB.exe <3.sql >3_cp.out
./lightDB.exe <4.sql >4_cp.out
./lightDB.exe <5.sql >5_cp.out
./lightDB.exe <6.sql >6_cp.out
./lightDB.exe <7.sql >7_cp.out
./lightDB.exe <8.sql >8_cp.out
./lightDB.exe <9.sql >9_cp.out
./lightDB.exe <10.sql >10_cp.out

echo "1"
diff --strip-trailing-cr 1_cp.out 1.out
echo "2"
diff --strip-trailing-cr 2_cp.out 2.out
echo "3"
diff --strip-trailing-cr 3_cp.out 3.out
echo "4"
diff --strip-trailing-cr 4_cp.out 4.out
echo "5"
diff --strip-trailing-cr 5_cp.out 5.out
echo "6"
diff --strip-trailing-cr 6_cp.out 6.out
echo "7"
diff --strip-trailing-cr 7_cp.out 7.out
echo "8"
diff --strip-trailing-cr 8_cp.out 8.out
echo "9"
diff --strip-trailing-cr 9_cp.out 9.out
echo "10"
diff --strip-trailing-cr 10_cp.out 10.out
