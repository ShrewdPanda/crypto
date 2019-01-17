hashi.py

This program creates a 'hash tree' for file integrity verification. 

Each file in a given directory is hashed. For every pair of hashes, 
there is a parent hash generated. This is continued until there are no 
more pairs found, and the remaining structure is a binary hash tree. 

Now, to verify the integrity of all of the files, one only needs to 
ascend the hash tree (rather than linearly verify each file). This 
reduces the time complexity of verification from O(n) to ~O(log n).

This is currently incomplete, as I have not yet made it scalable -- it 
currently only works for a total of four files --, so I will have to find
a way to make it scale dynamically. This will most likely occur by me setting
a hard limit of 'levels' that can be created (meaning also a hard limit on
the number of files which can be incorporated into the tree). 


ATTEMPT #1:

I plan on doing this by creating an imported module where I can define the
levels as class instances containing arrays which will be dynamically populated
-- this may or may not work --
