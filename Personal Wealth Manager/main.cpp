#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Income {
    string description;
    int amount;
};

struct Expense {
    string description;
    int amount;
};

struct Asset {
    string name;
    int value;
    int monthlyIncome;
    int monthlyExpense;
};

struct Liability {
    string name;
    int value;
    int monthlyIncome;
    int monthlyExpense;
};

class FinancialTracker {
private:
    string profession;
    string financialGoal;
    int salary;
    bool salaryEntered;
    vector<Income> incomes;
    vector<Expense> expenses;
    vector<Asset> assets;
    vector<Liability> liabilities;

public:
    FinancialTracker() : salary(0), salaryEntered(false) {}
    void calculateNetIncome();
    void setProfession() {
        cout << "Enter your profession: ";
        cin.ignore();
        getline(cin, profession);
    }

    void setFinancialGoal() {
        cout << "Enter your financial goal (optional): ";
        getline(cin, financialGoal);
    }

    void addIncome() {
        if (salaryEntered) {
            cout << "Salary already entered. Choose an option:\n";
            cout << "1. Update Salary\n";
            cout << "2. Add Other Income\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                cout << "Enter new Salary: ";
                cin >> salary;
                cout << "Salary updated.\n";
                return;
            }
        } else {
            cout << "Enter Salary: ";
            cin >> salary;
            salaryEntered = true;
            cout << "Salary entered.\n";
            return;
        }

        Income inc;
        cout << "Enter Income Description: ";
        cin.ignore();
        getline(cin, inc.description);
        cout << "Enter Income Amount: ";
        cin >> inc.amount;
        incomes.push_back(inc);
    }

    void addExpense() {
        cout << "Choose Expense Type:\n";
        cout << "1. Taxes\n";
        cout << "2. Home Mortgage Payment\n";
        cout << "3. School Loan Payment\n";
        cout << "4. Car Loan Payment\n";
        cout << "5. Credit Card Payment\n";
        cout << "6. Retail Payment\n";
        cout << "7. Other Expenses\n";
        cout << "8. Child Expenses\n";
        cout << "9. Loan Payment\n";
        cout << "10. Other\n";
        int choice;
        cin >> choice;

        Expense exp;
        switch (choice) {
            case 1: exp.description = "Taxes"; break;
            case 2: exp.description = "Home Mortgage Payment"; break;
            case 3: exp.description = "School Loan Payment"; break;
            case 4: exp.description = "Car Loan Payment"; break;
            case 5: exp.description = "Credit Card Payment"; break;
            case 6: exp.description = "Retail Payment"; break;
            case 7: exp.description = "Other Expenses"; break;
            case 8: exp.description = "Child Expenses"; break;
            case 9: exp.description = "Loan Payment"; break;
            case 10:
                cout << "Enter Expense Description: ";
                cin.ignore();
                getline(cin, exp.description);
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
        cout << "Enter Expense Amount: ";
        cin >> exp.amount;
        expenses.push_back(exp);
    }

    void addAsset() {
        Asset ast;
        cout << "Enter Asset Name: ";
        cin.ignore();
        getline(cin, ast.name);
        cout << "Enter Asset Value: ";
        cin >> ast.value;
        cout << "Enter Monthly Income from Asset: ";
        cin >> ast.monthlyIncome;
        cout << "Enter Monthly Expense for Asset: ";
        cin >> ast.monthlyExpense;

        if (ast.monthlyIncome <= ast.monthlyExpense) {
            liabilities.push_back({ast.name, ast.value, ast.monthlyIncome, ast.monthlyExpense});
        } else {
            assets.push_back(ast);
        }
    }

    void addLiability() {
        Liability lib;
        cout << "Enter Liability Name: ";
        cin.ignore();
        getline(cin, lib.name);
        cout << "Enter Liability Value: ";
        cin >> lib.value;
        cout << "Enter Monthly Income from Liability: ";
        cin >> lib.monthlyIncome;
        cout << "Enter Monthly Expense for Liability: ";
        cin >> lib.monthlyExpense;

        if (lib.monthlyIncome <= lib.monthlyExpense) {
            liabilities.push_back(lib);
        } else {
            assets.push_back({lib.name, lib.value, lib.monthlyIncome, lib.monthlyExpense});
        }
    }

    void generateReport(const std::string& filePath) {
    ofstream file(filePath);
    if (!file) {
        cerr << "Unable to open file";
        return;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<style>\n";
    file << "table { width: 100%; border-collapse: collapse; }\n";
    file << "table, th, td { border: 1px solid black; }\n";
    file << "th, td { padding: 8px; text-align: left; }\n";
    file << "th { background-color: #f2f2f2; }\n";
    file << "</style>\n";
    file << "<title>Financial Report</title>\n";
    file << "</head>\n<body>\n";
    file << "<h1>Financial Statement</h1>\n";
    file << "<p>Profession: " << profession << "</p>\n";
    if (!financialGoal.empty()) {
        file << "<p>Financial Goal: " << financialGoal << "</p>\n";
    }

    // Income Statement
    file << "<h2>Income Statement</h2>\n";
    file << "<table>\n<tr><th>Income Description</th><th>Amount</th></tr>\n";
    file << "<tr><td>Salary</td><td>" << salary << "</td></tr>\n";
    for (const auto& inc : incomes) {
        file << "<tr><td>" << inc.description << "</td><td>" << inc.amount << "</td></tr>\n";
    }
    for (const auto& ast : assets) {
        if (ast.monthlyIncome > ast.monthlyExpense) {
            file << "<tr><td>" << ast.name << "</td><td>" << (ast.monthlyIncome - ast.monthlyExpense) << "</td></tr>\n";
        }
    }
    file << "</table>\n";

    // Expenses
    file << "<h2>Expenses</h2>\n";
    file << "<table>\n<tr><th>Expense Description</th><th>Amount</th></tr>\n";
    for (const auto& exp : expenses) {
        file << "<tr><td>" << exp.description << "</td><td>" << exp.amount << "</td></tr>\n";
    }
    for (const auto& ast : assets) {
        if (ast.monthlyExpense > ast.monthlyIncome) {
            file << "<tr><td>" << ast.name << "</td><td>" << (ast.monthlyExpense - ast.monthlyIncome) << "</td></tr>\n";
        }
    }
    for (const auto& lib : liabilities) {
        if (lib.monthlyExpense > lib.monthlyIncome) {
            file << "<tr><td>" << lib.name << "</td><td>" << (lib.monthlyExpense - lib.monthlyIncome) << "</td></tr>\n";
        }
    }
    file << "</table>\n";

    // Balance Sheet
    file << "<h2>Balance Sheet</h2>\n";
    file << "<h3>Assets</h3>\n";
    file << "<table>\n<tr><th>Asset Name</th><th>Value</th><th>Monthly Income</th><th>Monthly Expense</th></tr>\n";
    for (const auto& ast : assets) {
        file << "<tr><td>" << ast.name << "</td><td>" << ast.value << "</td><td>" << ast.monthlyIncome << "</td><td>" << ast.monthlyExpense << "</td></tr>\n";
    }
    file << "</table>\n";

    file << "<h3>Liabilities</h3>\n";
    file << "<table>\n<tr><th>Liability Name</th><th>Value</th><th>Monthly Income</th><th>Monthly Expense</th></tr>\n";
    for (const auto& lib : liabilities) {
        file << "<tr><td>" << lib.name << "</td><td>" << lib.value << "</td><td>" << lib.monthlyIncome << "</td><td>" << lib.monthlyExpense << "</td></tr>\n";
    }
    file << "</table>\n";

    // Passive Income and Total Expenses from Balance Sheet
    int totalPassiveIncome = 0;
    int totalAssetExpense = 0;
    for (const auto& ast : assets) {
        if (ast.monthlyIncome > ast.monthlyExpense) {
            totalPassiveIncome += (ast.monthlyIncome - ast.monthlyExpense);
        } else {
            totalAssetExpense += (ast.monthlyExpense - ast.monthlyIncome);
        }
    }
    for (const auto& lib : liabilities) {
        if (lib.monthlyIncome <= lib.monthlyExpense) {
            totalAssetExpense += (lib.monthlyExpense - lib.monthlyIncome);
        }
    }

    // Monthly Cash Flow
    int totalIncome = salary;
    for (const auto& inc : incomes) {
        totalIncome += inc.amount;
    }
    int totalExpense = 0;
    for (const auto& exp : expenses) {
        totalExpense += exp.amount;
    }
    totalExpense += totalAssetExpense;
    int monthlyCashFlow = totalIncome - totalExpense;

    file << "<h3>Summary</h3>\n";
    file << "<p>Passive Income: " << totalPassiveIncome << "</p>\n";
    file << "<p>Total Expenses: " << totalExpense << "</p>\n";
    file << "<p>Monthly Cash Flow: " << monthlyCashFlow << "</p>\n";

    file << "</body>\n</html>";
    file.close();

    cout << "Report generated and saved as " << filePath << "\n";
}
};
void FinancialTracker::calculateNetIncome() {
    int totalIncome = salary;
    for (const auto& inc : incomes) {
        totalIncome += inc.amount;
    }
    int totalExpense = 0;
    for (const auto& exp : expenses) {
        totalExpense += exp.amount;
    }
    for (const auto& ast : assets) {
        totalExpense += ast.monthlyExpense;
    }
    for (const auto& lib : liabilities) {
        totalExpense += lib.monthlyExpense;
    }
    int netIncome = totalIncome - totalExpense;
    cout << "Monthly Net Income: " << netIncome << "\n";
}



int main() {
    FinancialTracker tracker;
    int choice;
    std::string filePath = "FinancialReport.html";
    
    do {
        cout << "\n--- Monthly Financial Tracker ---\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. Add Asset\n";
        cout << "4. Add Liability\n";
        cout << "5. Generate Report\n";
        cout << "6. Calculate Net Income\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                tracker.addIncome();
                break;
            case 2:
                tracker.addExpense();
                break;
            case 3:
                tracker.addAsset();
                break;
            case 4:
                tracker.addLiability();
                break;
            case 5:
                tracker.generateReport(filePath);
                break;
            case 6:
                tracker.calculateNetIncome();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
    
    return 0;
}
