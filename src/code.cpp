#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <curl/curl.h>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

class LogExtractor {
private:
    static constexpr const char* LOG_FILE_PATH = "test.logs.log";
    static constexpr const char* OUTPUT_DIR = "output";
    static constexpr const char* LOG_FILE_URL = "https://limewire.com/d/0c95044f-d489-4101-bf1a-ca48839eea86#cVKnm0pKXpN6pjsDwav4f5MNssotyy0C8Xvaor1bA5U";

    // Improved write data function using size_t
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, FILE* userp) {
        return fwrite(contents, size, nmemb, userp);
    }

    // Optimized date validation with regex
    static bool validateDate(const std::string& date) {
        static const std::regex DATE_REGEX(R"(^\d{4}-\d{2}-\d{2}$)");
        if (!std::regex_match(date, DATE_REGEX)) return false;

        try {
            int year = std::stoi(date.substr(0, 4));
            int month = std::stoi(date.substr(5, 2));
            int day = std::stoi(date.substr(8, 2));

            // Basic month and day range check
            return (month >= 1 && month <= 12 && day >= 1 && day <= 31);
        } catch (...) {
            return false;
        }
    }

    // Optimized file download
    static bool downloadFile() {
        if (fs::exists(LOG_FILE_PATH)) {
            std::cout << "Log file already exists." << std::endl;
            return true;
        }

        CURL* curl = curl_easy_init();
        if (!curl) {
            std::cerr << "CURL initialization failed" << std::endl;
            return false;
        }

        FILE* file = fopen(LOG_FILE_PATH, "wb");
        if (!file) {
            std::cerr << "File creation error" << std::endl;
            curl_easy_cleanup(curl);
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, LOG_FILE_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        
        CURLcode res = curl_easy_perform(curl);
        
        fclose(file);
        curl_easy_cleanup(curl);

        return (res == CURLE_OK);
    }

    // Optimized log extraction with vector
    static void extractMatchingLogs(const std::string& targetDate) {
        std::ifstream logFile(LOG_FILE_PATH);
        if (!logFile) {
            std::cerr << "Cannot open log file" << std::endl;
            return;
        }

        // Ensure output directory exists
        fs::create_directories(OUTPUT_DIR);

        // Prepare output file path
        std::string outputPath = std::string(OUTPUT_DIR) + "/output_" + targetDate + ".txt";
        std::ofstream outFile(outputPath);

        if (!outFile) {
            std::cerr << "Cannot create output file" << std::endl;
            return;
        }

        std::string logLine;
        std::vector<std::string> matchedLogs;

        // Single pass through the file
        while (std::getline(logFile, logLine)) {
            if (logLine.find(targetDate) != std::string::npos) {
                matchedLogs.push_back(logLine);
                std::cout << logLine << std::endl;
                outFile << logLine << std::endl;
            }
        }

        std::cout << "Extracted " << matchedLogs.size() << " log entries for " << targetDate << std::endl;
    }

public:
    static int run(const std::string& date) {
        // Validate input
        if (!validateDate(date)) {
            std::cerr << "Invalid date format. Use YYYY-MM-DD" << std::endl;
            return 1;
        }

        // Download log file
        if (!downloadFile()) {
            std::cerr << "Log file download failed" << std::endl;
            return 1;
        }

        // Extract logs
        extractMatchingLogs(date);

        return 0;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " YYYY-MM-DD" << std::endl;
        return 1;
    }

    return LogExtractor::run(argv[1]);
}
