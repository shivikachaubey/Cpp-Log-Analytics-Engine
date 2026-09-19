# C++ Log Analytics Engine

A lightweight, high-performance C++ log analytics engine that parses application logs, counts log levels, detects recurring errors, and reports execution time.

## Features

- Fast line-by-line log processing
- Supports `INFO`, `WARN`, `ERROR`, and `CRITICAL` levels
- Frequency analysis for errors and critical events
- Optional log-file input
- Uses C++17 STL containers such as `unordered_map` and `vector`
- Measures processing time with `std::chrono`
- Zero external dependencies

## Project Structure

```text
Cpp-Log-Analytics-Engine/
├── main.cpp
├── sample_logs.txt
├── README.md
├── CMakeLists.txt
└── .gitignore
```

## Requirements

- C++17-compatible compiler
- GCC, Clang, or MSVC
- CMake 3.10+ (optional)

## Compile and Run

### Linux / macOS

```bash
g++ -std=c++17 -O2 main.cpp -o log_analyzer
./log_analyzer
```

Run against a log file:

```bash
./log_analyzer sample_logs.txt
```

### Windows with MinGW

```bash
g++ -std=c++17 -O2 main.cpp -o log_analyzer.exe
log_analyzer.exe sample_logs.txt
```

## Example Output

```text
========== LOG ANALYTICS SUMMARY ==========
[CRITICAL]   Count: 1
[ERROR]      Count: 2
[INFO]       Count: 2
[WARN]       Count: 1

--- Top Critical Errors ---
Frequency 2x -> Database connection timeout: DB_HOST_1
Frequency 1x -> Out of Memory Exception in WorkerThread-4

Execution Time: ... ms
===========================================
```

## How It Works

Each log line is split into:

1. Timestamp
2. Log level
3. Message

`unordered_map` stores the frequency of each log level and recurring error message.

For error and critical entries, the message becomes a key in `errorFrequency`, allowing repeated incidents to be identified.

The optional file-input mode processes logs sequentially, so memory usage does not depend on the total number of log lines.

## Complexity

For `n` log lines, average-case processing is approximately **O(n)**.

Hash-map operations are average **O(1)**, while memory usage is **O(k)** where `k` is the number of distinct log levels and error messages retained.

## Skills Demonstrated

- C++
- Object-oriented programming
- STL
- Hash maps
- File I/O
- String parsing
- Algorithmic complexity
- Performance measurement
- Systems-oriented programming

## Future Improvements

- Multithreaded log ingestion
- Configurable alert thresholds
- CSV/JSON export
- Real-time streaming input
- Date/time range filtering
- More robust log-format validation
- Benchmarking with millions of log entries

## Author

**Shivika**

B.Tech CSE — Big Data Analytics
