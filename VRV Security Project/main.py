import csv
from collections import Counter

# File path
log_file_path = 'sample.log'

# Function to parse the log file
def parse_log(file_path):
    with open(file_path, 'r') as file:
        log_entries = file.readlines()
    return log_entries

# Function to count requests per IP address
def count_requests(log_entries):
    ip_addresses = [line.split()[0] for line in log_entries]
    counter = Counter(ip_addresses)
    return counter

# Function to count requests per endpoint
def count_endpoints(log_entries):
    endpoints = [line.split()[6] for line in log_entries]
    counter = Counter(endpoints)
    return counter

# Function to detect suspicious activity (failed login attempts)
def detect_suspicious_activity(log_entries, threshold=10):
    failed_logins = [line.split()[0] for line in log_entries if '401' in line or 'Invalid credentials' in line]
    counter = Counter(failed_logins)
    suspicious_ips = {ip: count for ip, count in counter.items() if count > threshold}
    return suspicious_ips

# Function to save results to CSV
def save_to_csv(request_counts, endpoint_counts, suspicious_ips):
    with open('log_analysis_results.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        
        # Write Requests per IP
        writer.writerow(['IP Address', 'Request Count'])
        for ip, count in request_counts.items():
            writer.writerow([ip, count])
        
        # Write Most Accessed Endpoint
        writer.writerow([])
        writer.writerow(['Endpoint', 'Access Count'])
        for endpoint, count in endpoint_counts.most_common():
            writer.writerow([endpoint, count])
        
        # Write Suspicious Activity
        writer.writerow([])
        writer.writerow(['IP Address', 'Failed Login Count'])
        for ip, count in suspicious_ips.items():
            writer.writerow([ip, count])

# Function to display the results
def display_results(request_counts, endpoint_counts, suspicious_ips):
    sorted_requests = sorted(request_counts.items(), key=lambda x: x[1], reverse=True)
    print(f"{'IP Address':<18}{'Request Count':<14}")
    for ip, count in sorted_requests:
        print(f"{ip:<18}{count:<14}")

    most_common_endpoint, access_count = endpoint_counts.most_common(1)[0]
    print(f"\nMost Frequently Accessed Endpoint:\n{most_common_endpoint} (Accessed {access_count} times)")

    print("\nSuspicious Activity Detected:")
    if suspicious_ips:
        print(f"{'IP Address':<18}{'Failed Login Attempts':<21}")
        for ip, count in suspicious_ips.items():
            print(f"{ip:<18}{count:<21}")
    else:
        print("No suspicious activity detected.")

# Main script
log_entries = parse_log(log_file_path)
request_counts = count_requests(log_entries)
endpoint_counts = count_endpoints(log_entries)
suspicious_ips = detect_suspicious_activity(log_entries)

display_results(request_counts, endpoint_counts, suspicious_ips)
save_to_csv(request_counts, endpoint_counts, suspicious_ips)
