The first approach I considered was a basic line-by-line method. 
However, for a 1TB file, this would be very inefficient, as we cannot store the entire file in memory on a typical laptop. 
Then, I thought about an indexing method, similar to how databases work, which would allow the use of binary search.
While this is more efficient, creating the indexes for a 1TB file is time-consuming and requires two passes: one to build the index and another to search through it.

Finally, I opted for a streaming approach with memory optimization. 
This method reads the file line by line, avoiding the need to load the entire file into memory, and it works in a single pass with a time complexity of O(n). 
I implemented this solution in C++.

