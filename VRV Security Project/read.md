# Log Analysis Script

## Objective
This project aims to develop a Python script for analyzing log files, focusing on file handling, string manipulation, and data analysis.

## Features
1. **Count Requests per IP Address:**
   - Parse log files to count requests per IP and display results in descending order.
2. **Identify Most Frequently Accessed Endpoint:**
   - Extract and count endpoint accesses, identify the most accessed endpoint.
3. **Detect Suspicious Activity:**
   - Flag IPs with failed login attempts exceeding a configurable threshold.
4. **Output Results:**
   - Display results in the terminal and save to `log_analysis_results.csv`.

## Usage
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/log-analysis-script.git
   cd log-analysis-script
