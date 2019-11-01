# Filling Buckets
## Tristan Schieler

## Problem Description

This problem is based on the classic puzzle of how you can measure out a specific amount ofwater using buckets of different sizes. Initially, all of the buckets are empty, and at each point, the only legal moves are: filling up a bucket, dumping out a bucket, or transferring the water in one bucket into another. Note that a transfer will either empty out the bucket it is pouring from or fill up the bucket it is pouring into, whichever happens first.

For example, suppose you want to measure out 4 gallons of water using a 3-gallon bucket and a 5-gallon bucket. You might fill up the 5-gallon bucket (5 gal,  0 gal), transfer the 3 gallons to the 3-gallon bucket (2 gal, 3 gal), dump the 3-gallon bucket (2 gal, 0 gal), transfer 2 gallons to the 3-gallon bucket (0 gal, 2 gal), fill the 5-gallon bucket again (5 gal, 2 gal), transfer 1 gallon to the 3-gallon bucket (4 gal, 3 gal), and finally dump the 3-gallon bucket (4 gal, 0 gal). This is the most efficient solution, which takes 7 moves. 

Instead of describing how to make a given amount of water, we want to identify the amount of water that takes the most moves to make.  The amount of water in a given set of buckets is the sum of the water in all buckets.  In the previous example, the two buckets can have from 0 up to 8 gallons of water between them, and 4 gallons takes the greatest number of moves to make.

### Input Format

`Input.txt, Input2.txt, Input3.txt`

`To pick the file to run the code with change the file to open under the "input" section of the code`

The first line of the input has one positive integer, n, representing the number of buckets. The next line contains n positive integers, representing the size of each bucket. The bucket sizes will be given in decreasing order. The number and size of the buckets will be such that your graph will never have more than 1 million vertices or 10 million edges.

### Output Format

`Output will be put into an Output.txt file`

The first two integers will be the number of vertices and the number of edges in the graph, respectively. The third and fourth integers will be the most difficult amount of water to make and the number of moves that amount takes, respectively. If there is a tie for the amount that takes the greatest number of moves, output will be the smallest amount of water that takes this many moves.

### Compile
* LINUX
    * `g++ bucket.cpp -o buckets`
* WINDOWS
    * `g++ bucket.cpp`

### Run
* LINUX
    * `./buckets`
* WINDOWS
    * `./a.exe`

### Versioning 

The version of this program is purely for testing and education purposes. The maker reserves the right to make updates and bugfixes.