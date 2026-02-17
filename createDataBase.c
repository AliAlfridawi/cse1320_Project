/*
    Author: Ali Alfridawi
    Purpose: Create Database
*/

#include <stdio.h>
#include "sqlite/sqlite3.h"

void createDB() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("dummy.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return; 
    }
    else
    {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Enable Foreign Keys (Crucial for SQLite constraints to work)
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);

    // USERS TABLE
    char *sql = "CREATE TABLE IF NOT EXISTS users (" \
                "user_id INTEGER PRIMARY KEY AUTOINCREMENT," \
                "username VARCHAR(50) UNIQUE NOT NULL," \
                "password_hash VARCHAR(255) NOT NULL," \
                "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Users SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Users table created successfully\n");
    }

    // RESTAURANTS TABLE (Fixed spelling: resturant -> restaurant)
    sql = "CREATE TABLE IF NOT EXISTS restaurants (" \
            "restaurant_id INTEGER PRIMARY KEY AUTOINCREMENT," \
            "restaurant_name VARCHAR(100) NOT NULL," \
            "location VARCHAR(255));";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);   
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Restaurants SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Restaurants table created successfully\n");
    }

    // USER ACCESS TABLE
    sql = "CREATE TABLE IF NOT EXISTS user_access (" \
            "user_id INT," \
            "restaurant_id INT," \
            "can_edit BOOLEAN DEFAULT FALSE," \
            "PRIMARY KEY (user_id, restaurant_id)," \
            "FOREIGN KEY (user_id) REFERENCES users(user_id)," \
            "FOREIGN KEY (restaurant_id) REFERENCES restaurants(restaurant_id));";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);   
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Access SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Access table created successfully\n");
    }

    // INVENTORY TABLE
    sql = "CREATE TABLE IF NOT EXISTS inventory (" \
            "item_id INTEGER PRIMARY KEY AUTOINCREMENT," \
            "restaurant_id INT," \
            "item_name VARCHAR(100) NOT NULL," \
            "quantity INT NOT NULL," \
            "threshold INT NOT NULL," \
            "FOREIGN KEY (restaurant_id) REFERENCES restaurants(restaurant_id));";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);   
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Inventory SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Inventory table created successfully\n");
    }
    
    sqlite3_close(db);      
}

int main() {
    createDB();
    return 0;
}