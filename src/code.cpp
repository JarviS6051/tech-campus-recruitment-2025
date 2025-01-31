
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <curl/curl.h>

using namespace std;
namespace fs = std::filesystem;

const string LOG_FILE_PATH = "test.logs.log";
const string OUTPUT_DIR = "output";
const string LOG_FILE_URL = "https://limewire.com/d/0c95044f-d489-4101-bf1a-ca48839eea86#cVKnm0pKXpN6pjsDwav4f5MNssotyy0C8Xvaor1bA5U";

// Function to write downloaded data into a file
size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// Function to download log file if not present
bool downloadLogFile() {
    if (fs::exists(LOG_FILE_PATH)) {
        cout << "Log file already exists." << endl;
        return true;
    }

    cout << "Downloading log file..." << endl;
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize CURL" << endl;
        return false;
    }

    FILE* file = fopen(LOG_FILE_PATH.c_str(), "wb");
    if (!file) {
        cerr << "Failed to open file for writing: " << LOG_FILE_PATH << endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, LOG_FILE_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    CURLcode res = curl_easy_perform(curl);
    fclose(file);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        cerr << "Download failed: " << curl_easy_strerror(res) << endl;
        return false;
    }

    cout << "Download complete." << endl;
    return true;
}

// Function to extract logs of a specific date
void extractLogs(const string& date) {
    if (!fs::exists(LOG_FILE_PATH)) {
        cerr << "Log file not found. Please ensure it is downloaded." << endl;
        return;
    }

    if (!fs::exists(OUTPUT_DIR)) {
        fs::create_directories(OUTPUT_DIR);
    }

    string outputFilePath = OUTPUT_DIR + "/output_" + date + ".txt";
    
    // Check if output file exists
    if (fs::exists(outputFilePath)) {
        cout << "Output file for " << date << " already exists. Overwrite? (y/n): ";
        char response;
        cin >> response;
        if (response != 'y' && response != 'Y') {
            cout << "Operation aborted." << endl;
            return;
        }
    }

    ifstream logFile(LOG_FILE_PATH);
    ofstream outFile(outputFilePath);
    if (!logFile || !outFile) {
        cerr << "Error opening files!" << endl;
        return;
    }

    cout << "Extracting logs for " << date << "..." << endl;
    string logLine;
    while (getline(logFile, logLine)) {
        if (logLine.find(date) != string::npos) { // Check if the line contains the date
            outFile << logLine << endl;
            cout << "Matched: " << logLine << endl;
        }
    }

    logFile.close();
    outFile.close();

    cout << "Logs for " << date << " saved to " << outputFilePath << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " YYYY-MM-DD" << endl;
        return 1;
    }

    string date = argv[1];
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        cerr << "Invalid date format. Use YYYY-MM-DD." << endl;
        return 1;
    }

    if (!downloadLogFile()) {
        return 1;
    }

    extractLogs(date);
    return 0;
}
