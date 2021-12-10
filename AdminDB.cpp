//Made by MinDl
//%?
//10.12.2021
//
#include <stdlib.h>
#include <iostream>
#include <string>
#include <jdbc.h>

using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "123";

int main() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;
    //check connection
    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    bool bool_base = true;
    while (bool_base) {
        string base;
        cout << "Create new database?(Yes/No): ";
        cin >> base;
        if (base == "Y" || base == "y" || base == "yes" || base == "Yes") {
            stmt = con->createStatement();
            stmt->execute("CREATE DATABASE users_log");
            con->setSchema("users_log");
            stmt->execute("DROP TABLE IF EXISTS users");
            cout << "Created database 'users_log' and table 'users'\nFinished dropping table (if existed)" << endl;
            stmt->execute("CREATE TABLE users (id INT NOT NULL AUTO_INCREMENT, login VARCHAR(20) NOT NULL, passwd VARCHAR(20) NOT NULL, name VARCHAR(20), message VARCHAR(200), PRIMARY KEY(id));");
            cout << "Finished creating table" << endl;
            delete stmt;
            //default admin
            pstmt = con->prepareStatement("INSERT INTO users(login, passwd, name) VALUES(?,?,?);");
            pstmt->setString(1, "admin");
            pstmt->setString(2, "admin");
            pstmt->setString(3, "admin");
            pstmt->execute();
            bool_base = false;
            delete pstmt;
        }
        else if (base == "N" || base == "n" || base == "no" || base == "No") {
            string base_name;
            cout << "The name of existing database to use: ";
            cin >> base_name;
            con->setSchema(base_name);
            bool bool_table = true;
            while (bool_table) {
                string name_table;
                cout << "Create new table 'users'?\nYes - if you haven't this table\nNo - if you have table users with id,login,passwd\n:: ";
                cin >> name_table;
                if (name_table == "Yes" || name_table == "yes" || name_table == "Y" || name_table == "y") {
                    stmt = con->createStatement();
                    stmt->execute("DROP TABLE IF EXISTS users");
                    stmt->execute("CREATE TABLE users (id INT NOT NULL AUTO_INCREMENT, login VARCHAR(20) NOT NULL, passwd VARCHAR(20) NOT NULL, name VARCHAR(20), message VARCHAR(200), PRIMARY KEY(id));");
                    cout << "Finished creating table" << endl;
                    pstmt = con->prepareStatement("INSERT INTO users(login, passwd, name) VALUES(?,?,?);");
                    pstmt->setString(1, "admin");
                    pstmt->setString(2, "admin");
                    pstmt->setString(3, "admin");
                    pstmt->execute();
                    delete stmt;
                    delete pstmt;
                    bool_table = false;
                }
                else if (name_table == "No" || name_table == "no" || name_table == "N" || name_table == "n") {
                    cout << "Ok\n";
                    bool_table = false;
                }
                else {
                    cout << "Wrong enter\n\n";
                }
            }
            bool_base = false;
        }
        else {
            cout << "Wrong enter\n\n";
        }
    }
    //User chooses commands 
    string exit;
    while (exit != "exit") {
        cout << "Exit or command\nCommands:\nnew - create row\nshow - show all from the table\nsearch_login - search in the table with login\nsearch_id - search in the table with id\nupdate - change login, password and name following the id\ndelete - delete row following the id\n::";
        cin >> exit;
        if (exit == "new") {
            string log, pas, name;
            cout << "Enter ur login: ";
            cin >> log;
            cout << "Enter ur password: ";
            cin >> pas;
            cout << "Enter ur name: ";
            cin >> name;
            pstmt = con->prepareStatement("INSERT INTO users(login, passwd, name) VALUES(?,?,?)");
            pstmt->setString(1, log);
            pstmt->setString(2, pas);
            pstmt->setString(3, name);
            pstmt->execute();
            cout << "User created!\n\n";
            delete pstmt;
        }
        else if (exit == "show") {
            pstmt = con->prepareStatement("SELECT * FROM users;");
            result = pstmt->executeQuery();
            while (result->next()) {
                cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3) << ", " << result->getString(4) << endl << endl;
            }
            delete result;
            delete pstmt;
        }
        else if (exit == "search_login") {
            string search;
            cout << "Enter Login: ";
            cin >> search;
            pstmt = con->prepareStatement("SELECT * FROM users WHERE login = ?;");
            pstmt->setString(1, search);
            result = pstmt->executeQuery();
            while (result->next()) {
                cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3) << ", " << result->getString(4) << endl << endl;
            }
            delete result;
            delete pstmt;
        }
        else if (exit == "search_id") {
            int search;
            cout << "Enter Login: ";
            cin >> search;
            pstmt = con->prepareStatement("SELECT * FROM users WHERE id = ?;");
            pstmt->setInt(1, search);
            result = pstmt->executeQuery();
            while (result->next()) {
                cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3) << ", " << result->getString(4) << endl << endl;
            }
            delete result;
            delete pstmt;
        }
        else if (exit == "update") {
            string update_log, update_pass, update_name;
            int idd;
            cout << "Enter id: ";
            cin >> idd;
            cout << "Enter new login: ";
            cin >> update_log;
            cout << "Enter new password: ";
            cin >> update_pass;
            cout << "Enter new name: ";
            cin >> update_name;
            pstmt = con->prepareStatement("UPDATE users SET login = ? , passwd = ? , name = ? WHERE id = ?");
            pstmt->setString(1, update_log);
            pstmt->setString(2, update_pass);
            pstmt->setString(3, update_name);
            pstmt->setInt(4, idd);
            pstmt->execute();
            cout << "Row updated\n\n";
            delete pstmt;
        }
        else if (exit == "delete") {
            int idd;
            cout << "Enter id: ";
            cin >> idd;
            pstmt = con->prepareStatement("DELETE FROM users WHERE id = ?");
            pstmt->setInt(1, idd);
            result = pstmt->executeQuery();
            cout << "Row deleted\n\n";
            delete result;
            delete pstmt;
        }
        else if (exit == "exit") {}
        else {
            cout << "Wrong command\n\n";
        }
    }
    delete con;
    system("pause");
    return 0;
}
