# Pathfinding

Problem 
-------

Input is 10 X 10 array.
 
0 is free space, 1 is obstacle, 2 is start point, 3 is goal. 
Moved trace is indicated by 8.

It is possible to select whether diagonal movement is possible or not.

Input and output should be text files.

Example
-------

Input: 
  1100020111
  1010110001
  0000011100
  0111100010
  0010101000
  1000101011
  1110101010
  1110100110
  1101110100
  1000030000

Output - Right angle case:
  1100028111
  1010118881
  0000011188
  0111188818
  0010181888
  1000181011
  1110181010
  1110188110
  1101118100
  1000038000

Output - Diagonal movement case:
  1100820111
  1018110001
  0000811100
  0111180010
  0010181000
  1000181011
  1110181010
  1110180110
  1101118100
  1000030000

