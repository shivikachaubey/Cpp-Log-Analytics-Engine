#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

struct LogEntry {
    std::string timestamp;
    std::string logLevel;
    std::string message;
};

class LogAnalyticsEngine {
private:
    std::unordered_map<std::string, std::size_t> levelCounts;
    std::unordered_map<std::string, std::size_t> errorFrequency;

public:
    void processLogLine(const std::string& line) {
        std::stringstream ss(line);
        std::string timestamp, level, message;

        if (ss >> timestamp >> level) {
            std::getline(ss, message);
            if (!message.empty() && message.front() == ' ')
                message.erase(0, 1);

            ++levelCounts[level];

            if (level == "[ERROR]" || level == "[CRITICAL]")
                ++errorFrequency[message];
        }
    }

    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open log file: " << filename << '\n';
            return;
        }

        std::string line;
        while (std::getline(file, line))
            processLogLine(line);
    }

    void generateReport(double executionMs) const {
        std::cout << "\n========== LOG ANALYTICS SUMMARY ==========\n";

        std::vector<std::pair<std::string, std::size_t>> levels(
            levelCounts.begin(), levelCounts.end());

        std::sort(levels.begin(), levels.end(),
                  [](const auto& a, const auto& b) {
                      return a.first < b.first;
                  });

        for (const auto& [level, count] : levels)
            std::cout << std::left << std::setw(12)
                      << level << " Count: " << count << '\n';

        std::vector<std::pair<std::string, std::size_t>> errors(
            errorFrequency.begin(), errorFrequency.end());

        std::sort(errors.begin(), errors.end(),
                  [](const auto& a, const auto& b) {
                      return a.second > b.second;
                  });

        std::cout << "\n--- Top Critical Errors ---\n";
        if (errors.empty()) {
            std::cout << "No critical errors found.\n";
        } else {
            for (const auto& [message, count] : errors)
                std::cout << "Frequency " << count << "x -> " << message << '\n';
        }

        std::cout << "\nExecution Time: " << executionMs << " ms\n";
        std::cout << "===========================================\n";
    }
};

int main(int argc, char* argv[]) {
    LogAnalyticsEngine engine;

    auto start = std::chrono::high_resolution_clock::now();

    if (argc > 1) {
        engine.processFile(argv[1]);
    } else {
        const std::vector<std::string> sampleLogs = {
            "2026-09-19T10:00:01 [INFO] Server started on port 8080",
            "2026-09-19T10:00:05 [WARN] High memory usage detected: 85%",
            "2026-09-19T10:00:12 [ERROR] Database connection timeout: DB_HOST_1",
            "2026-09-19T10:00:15 [ERROR] Database connection timeout: DB_HOST_1",
            "2026-09-19T10:00:20 [CRITICAL] Out of Memory Exception in WorkerThread-4",
            "2026-09-19T10:00:25 [INFO] User session authenticated ID:99201"
        };

        for (const auto& log : sampleLogs)
            engine.processLogLine(log);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    engine.generateReport(duration.count());
    return 0;
}
