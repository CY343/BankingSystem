# Banking System Project

![C++](https://img.shields.io/badge/C++-17-blue)
![MySQL](https://img.shields.io/badge/MySQL-8.0-orange)
![License](https://img.shields.io/badge/License-MIT-green)

A comprehensive banking system implementation in C++ with MySQL database integration. This project simulates core banking operations including account management, card processing, and transaction handling.

## Features

- **Customer Management**: Create and manage customer profiles
- **Account Operations**: Support for checking, savings, and credit accounts
- **Card System**: Debit and credit card generation and management
- **Transaction Processing**: Deposit, withdrawal, transfer, and payment operations
- **Database Integration**: MySQL backend for persistent data storage
- **Secure Authentication**: Password hashing for user credentials
- **Comprehensive Testing**: Complete test suite for database operations

## Prerequisites

Before running this project, ensure you have installed:

- **MySQL Server 8.0+** ([Download MySQL](https://dev.mysql.com/downloads/mysql/))
- **MySQL Connector/C++** ([Download Connector](https://dev.mysql.com/downloads/connector/cpp/))
- **C++ Compiler** with C++17 support (GCC 9+ or MSVC 19+)
- **CMake** (version 3.12+)

## Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/CY343/BankingSystem.git
cd banking-system

CREATE DATABASE BankingSystem;
USE BankingSystem;

-- Run the complete schema from schema.sql
SOURCE path/to/schema.sql;

mkdir build
cd build
cmake ..
make

[mysql]
host=localhost
port=3306
database=BankingSystem
username= root
password=wayne970911
```
### project structure
banking-system/
├── include/               # Header files
│   ├── BankingExceptions.hpp
│   ├── Card.hpp
│   ├── CardGenerator.hpp
│   ├── CheckingAccount.hpp
│   ├── CreditCard.hpp
│   ├── Customers.hpp
│   ├── DebtCard.hpp
│   ├── MySQLAccountData.hpp
│   └── MySQLTransactionData.hpp
├── src/                   # Source files
│   ├── BankingExceptions.cpp
│   ├── Card.cpp
│   ├── CardGenerator.cpp
│   ├── CheckingAccount.cpp
│   ├── CreditCard.cpp
│   ├── Customers.cpp
│   ├── DebtCard.cpp
│   ├── MySQLAccountData.cpp
│   ├── MySQLTransactionData.cpp
│   └── main.cpp
├── schema/                # Database scripts
│   └── banking_schema.sql
├── tests/                 # Test programs
│   └── database_test.cpp
├── CMakeLists.txt         # Build configuration
└── config.ini             # Database configuration

### Database Schema
https://docs/db_diagram.png

-The system uses a relational database with 6 core tables:

-Customers: Stores client information

-BankAccounts: Manages account details

-Cards: Handles debit/credit cards

-Transactions: Records financial operations

-CreditAccounts: Stores credit-specific data

-AuthCredentials: Manages user authentication

### Running the Application

# Start the banking system
./build/banking_system

# Run database tests
./build/database_test

### Key Features Implementation
Card Generation

// CardGenerator.cpp
std::string CardGenerator::generateCardNumber(CardType type) {
    std::string prefix = (type == DEBIT) ? "4" : "5";
    // ... generation logic
}

### Transaction Processing

// MySQLTransactionData.cpp
void recordTransaction(int account_id, TransactionType type, double amount) {
    // Insert transaction record
    // Update account balance
}

### Database Connection

// MySQLAccountData.cpp
MySQLAccountData::MySQLAccountData() {
    auto config = ConfigLoader::load("config.ini");
    session = std::make_unique<mysqlx::Session>(
        mysqlx::SessionOption::HOST, config.host,
        mysqlx::SessionOption::PORT, config.port,
        // ... other parameters
    );
}

### Testing
The project includes comprehensive tests for database operations:

# Run database tests
./build/database_test

# Sample output
[==========] Running 6 tests
[ PASSED ] DatabaseConnectionTest
[ PASSED ] CustomerOperationsTest
[ PASSED ] AccountOperationsTest
[ PASSED ] CardOperationsTest
[ PASSED ] TransactionOperationsTest
[ PASSED ] CreditAccountTest

### Contributing
Contributions are welcome! Please follow these steps:

1. Fork the repository

2. Create your feature branch (git checkout -b feature/your-feature)

3. Commit your changes (git commit -am 'Add some feature')

4. Push to the branch (git push origin feature/your-feature)

5. Open a pull request

### License
This project is licensed under the MIT License - see the LICENSE file for details.

Developed by [Cheng Yue]
https://img.shields.io/badge/Contact-email@example.com-blue


## Key Sections Explained:

1. **Shields/Badges**: Visual indicators for language versions and licenses
2. **Features**: Highlights core functionality with emoji icons
3. **Installation**: Step-by-step setup instructions
4. **Project Structure**: Clear directory tree explanation
5. **Database Schema**: Visual representation of tables
6. **Code Snippets**: Key implementation examples
7. **Testing**: Instructions for running tests
8. **Contributing**: Standard GitHub workflow guidelines

The README includes all essential sections for a professional GitHub project while focusing on the banking system specifics. It's structured to help new contributors quickly understand and work with the project.

4. Commit your changes (git commit -am 'Add some feature')

5. Push to the branch (git push origin feature/your-feature)

6. Open a pull request
