# Bank Management System

A C++-based Bank Management System that utilizes Object-Oriented Programming (OOP) principles and file handling to manage customer accounts and maintain persistent data storage.

## Features

* **Account Creation:** Create new bank accounts with customer details and an initial balance.
* **Deposit & Withdrawal:** Perform deposit and withdrawal transactions with balance validation.
* **Balance Inquiry:** View account details and current balance information.
* **Account Closure:** Remove existing accounts from the system.
* **Display All Accounts:** List all accounts stored in the database.
* **Data Persistence:** Automatically saves and retrieves account information using file handling.

## Technical Details

* **Programming Language:** C++
* **Object-Oriented Design:** Implemented using classes to encapsulate account and banking operations.
* **Data Structure:** Utilized `std::map` for efficient account storage and retrieval.
* **File Handling:** Used `ifstream` and `ofstream` for persistent data management.
* **Exception Handling:** Incorporated error handling for invalid transactions and insufficient balance scenarios.
* **Operator Overloading:** Overloaded `<<` and `>>` operators to simplify file input/output operations.

## How to Run

### Compile the Program

```bash
g++ banking.cpp -o bank
```

### Run the Application

```bash
./bank
```
