# Names

Arya More, Michael Chen

# Compilation

If countnames does not exist, first run
```cc countnames.c -o countnames -Wall -Werror```, then run `cc shell1.c -o shell1 -Wall -Werror`
Otherwise, just run `cc shell1.c -o shell1 -Wall -Werror`.
# Running the program

Run ```./shell1``` and then run ```"./countnames <insert text file arguments here>"``` inside shell1.
The output should be in multiple ".out" and ".err" files in the same folder.

# Test Case information
1.) Tests a file with a large amount of empty spaces(about 98 to be exact). 
2.) Tests a file with excessively long names.
3.) Tests a file with a large amount of names occurring with differing amount of whitespaces.

# Lessons Learned

We learned that wait(NULL) > 0 was what we needed in order to wait for all the child processes to finish.

# Acknowledgements

[1]: Advanced Programming in the UNIX Environment 3rd Edition
