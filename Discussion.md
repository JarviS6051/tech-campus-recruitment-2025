The first approach I considered was a basic line-by-line method. 
However, for a 1TB file, this would be very inefficient, as we cannot store the entire file in memory on a typical laptop. 
Then, I thought about an indexing method, similar to how databases work, which would allow the use of binary search.
While this is more efficient, creating the indexes for a 1TB file is time-consuming and requires two passes: one to build the index and another to search through it.

Finally, I opted for a streaming approach with memory optimization. 
This method reads the file line by line, avoiding the need to load the entire file into memory, and it works in a single pass with a time complexity of O(n). 
I implemented this solution in C++.





I chose the streaming approach with memory optimization for a few key reasons:

Memory Efficiency: With a 1TB file, storing the entire file in memory isn't feasible, especially on a typical laptop. The line-by-line streaming approach ensures that we only load a small part of the file at a time into memory, allowing us to process large files without running into memory limitations.

Single Pass Solution: Unlike the indexing approach, which requires two passes (one to build the index and another to search through it), the streaming approach allows us to process the file in a single pass. This simplifies the process and reduces overhead, making it more efficient in terms of both time and resource usage.

Scalability: As the file size increases, the streaming approach remains scalable because we aren't dependent on building large indexes or holding the entire file in memory. This makes it much more adaptable to very large files, like the 1TB one you're working with.

Simplicity: The streaming approach is straightforward to implement and does not require complex data structures like indexes or additional storage. It allows for a simpler, more maintainable solution while still being efficient.



How to run this code :-


