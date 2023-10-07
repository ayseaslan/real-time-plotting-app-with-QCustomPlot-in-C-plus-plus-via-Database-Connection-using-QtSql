#include <iostream>
#include <sqlite3.h>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>

int main() {
    sqlite3* db;
    char* errMsg = 0;

    // Open or create a SQLite database file
    int rc = sqlite3_open("studentage_database.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // SQL statement to create a table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Students("
        "ID INT PRIMARY KEY NOT NULL,"
        "SCORE INT NOT NULL,"
        "NAME TEXT NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Table created successfully" << std::endl;
    }

  

    int terminate = 0;
    int id = 1;

    while (terminate!=1)
    {
        // Define the duration for 2 minutes
        std::chrono::seconds duration(2);

        // Sleep for the specified duration
        std::this_thread::sleep_for(duration);

        // Set up a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Set the mean and standard deviation for the normal distribution
        double mean = 5.5;  // Mean of the distribution (average of 1 and 10)
        double stddev = 2.5; // Standard deviation of the distribution

        // Create a normal distribution object
        std::normal_distribution<double> distribution(mean, stddev);

        // Generate a normally distributed number
        double result = distribution(gen);

        // Ensure the result is within the desired range [1, 10]
        int grade = static_cast<int>(std::max(1.0, std::min(result, 10.0)));


        std::cout << grade;

        // Generate a random letter (lowercase)
        const char letter = 'a' + (std::rand() % 26);    

        std::cout << ","<<letter<<std::endl;

       
        std::stringstream s; 
        s << "INSERT INTO Students(ID, SCORE, NAME) VALUES(" << id << "," << grade << ",'" << letter << "');";

        std::string sql = s.str();

        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        else {
            std::cout << "Data inserted successfully" << std::endl;

        }
            
        // SQL statement to retrieve data from the table
        const char* selectDataSQL = "SELECT * FROM Students;";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, selectDataSQL, -1, &stmt, nullptr);

        if (rc == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

                std::cout << "ID: " << id << ", Name: " << name << std::endl;
            }

            sqlite3_finalize(stmt);
        }
        else {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }

        id++; 

       
         

    }

    // Close the database
    sqlite3_close(db);

  

    return 0;
}



