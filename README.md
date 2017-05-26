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

Input: <br/>
  1100020111<br/>
  1010110001<br/>
  0000011100<br/>
  0111100010<br/>
  0010101000<br/>
  1000101011<br/>
  1110101010<br/>
  1110100110<br/>
  1101110100<br/>
  1000030000<br/>

Output - Right angle case:<br/>
  1100028111<br/>
  1010118881<br/>
  0000011188<br/>
  0111188818<br/>
  0010181888<br/>
  1000181011<br/>
  1110181010<br/>
  1110188110<br/>
  1101118100<br/>
  1000038000

Output - Diagonal movement case:<br/>
  1100820111<br/>
  1018110001<br/>
  0000811100<br/>
  0111180010<br/>
  0010181000<br/>
  1000181011<br/>
  1110181010<br/>
  1110180110<br/>
  1101118100<br/>
  1000030000<br/>
