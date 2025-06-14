#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <memory>

int main() {
    try {
        // Create driver instance
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        
        // Create connection using unique_ptr for automatic cleanup
        std::unique_ptr<sql::Connection> conn(driver->connect(
            "tcp://127.0.0.1:3306", "root", "wayne970911"));
        
        // Set the database schema
        conn->setSchema("BankingSystem");
        
        // Create statement
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        
        // Execute query
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM accounts"));
        
        // Process results
        std::cout << "Accounts in BankingSystem:\n";
        std::cout << "--------------------------\n";
        while (res->next()) {
            std::cout << "Account Number: " << res->getInt("account_number")
                      << " | Balance: " << res->getDouble("balance")
                      << " | Type: " << res->getString("account_type") << "\n";
        }
        std::cout << "--------------------------\n";
        
        return 0;
    } catch (const sql::SQLException &e) {
        std::cerr << "MySQL Error: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "System Error: " << e.what() << std::endl;
        return 2;
    }
}