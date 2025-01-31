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

1️⃣ Save the C++ Code
Open a text editor (VS Code, Notepad++, or Sublime Text).
Copy the C++ code you provided.
Save the file as extract_logs.cpp in a folder like:
Windows: C:\Users\YourName\logs_project\
macOS/Linux: ~/logs_project/
2️⃣ Install Necessary Tools
🔹 Windows
Install MinGW-w64 (if not installed):
Download it from MinGW-w64.
Add the bin folder (e.g., C:\mingw-w64\bin) to your System PATH.
Check installation by running:
g++ --version
Install cURL library (needed for downloading logs).
Download from cURL for Windows.
Install it and add its bin folder to System PATH.
🔹 macOS/Linux
Install g++ and cURL (if not installed):
sudo apt update && sudo apt install g++ curl libcurl4-openssl-dev -y  # Ubuntu/Debian  
brew install gcc curl                                                  # macOS  
Check installation:
g++ --version  
3️⃣ Open Terminal or Command Prompt
Windows: Press Win + R, type cmd, and press Enter.
macOS/Linux: Open Terminal (Ctrl + Alt + T for Linux).
Navigate to the folder where your code is saved:
cd C:\Users\YourName\logs_project\   # Windows  
cd ~/logs_project/                    # macOS/Linux  
4️⃣ Download the Log File
Run the following command to download the log file:
curl -L -o test_logs.log "https://limewire.com/d/90794bb3-6831-4e02-8a59-ffc7f3b8b2a3#X1xnzrH5s4H_DKEkT_dfBuUT1mFKZuj4cFWNoMJGX98"
Wait for the download to complete.
5️⃣ Compile the C++ Code
Run this command to compile the program:
g++ extract_logs.cpp -o extract_logs -lcurl  
If no errors appear, your program compiled successfully!
6️⃣ Run the Program
Now, execute the program with a date argument:
./extract_logs 2024-12-01   # macOS/Linux  
extract_logs.exe 2024-12-01  # Windows  
7️⃣ Check the Output File
Once the program runs, it will save logs in a file inside the output/ folder.
To view the extracted logs:
Windows: Open the file in Notepad:
notepad output\output_2024-12-01.txt  
macOS/Linux: Use cat or nano:
cat output/output_2024-12-01.txt  


