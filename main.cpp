//Made by MinDl
//
//10.12.2021
//
#include <iostream>
#include <string>
#include <jdbc.h>
using namespace std;

//Server data
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "123";

int main(){
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	string str1, str2;
    int id=0;
  //check connection with server
	try {
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e) {
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
  //use database
	con->setSchema("users_log");
	while (true) {
		cout << "Login or sign_up?\n::";
		string signup;
		cin>>signup;
		if (signup=="login"||signup=="Login") {
			string email;
			string password;
			cout << "Your email: ";
			cin >> email;
			cout << "Password: ";
			cin >> password;
			pstmt = con->prepareStatement("SELECT * FROM users WHERE login = ? AND passwd = ?;");
			pstmt->setString(1, email);
			pstmt->setString(2, password);
			result = pstmt->executeQuery();
			while (result->next()) {
                id = result->getInt(1);
				str1 = result->getString(2).c_str();
				str2 = result->getString(3);
			}
			if (str1==email&&str2==password) {
				cout << "Hello "<< str1 <<endl << endl;
				break;
			}
			else {
				cout << "Wrong password or email\n\n";
			}
      delete pstmt;
      delete result;
		}
		else if (signup=="sign_up"|| signup=="Sign_up") {
			string email,password,password_again,name;
			cout << "Your email: ";
			cin >> email;
            cout << "Enter your name";
            cin >> name;
			cout << "Password: ";
			cin >> password;
			cout << "Password again: ";
			cin >> password_again;
			if (password==password_again) {
				pstmt = con->prepareStatement("INSERT INTO users(login, passwd, name) VALUES(?,?,?);");
				pstmt->setString(1, email);
				pstmt->setString(2, password); 
                pstmt->setString(3, name);
				pstmt->execute();
				cout << "Your profile created!\n\n";
                delete pstmt;
			}
			else {
				cout << "Passwords mismatch!\n\n";
			}
		}
		else {
			cout << "Wrong command\n\n";
		}
	}
	while (true) {
		if (str1=="admin") {
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
                        cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3).c_str() << ", " << result->getString(4).c_str() << ", " << result->getString(5) << endl << endl;
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
                        cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3).c_str() << ", " << result->getString(4).c_str() << ", " << result->getString(5) << endl << endl;
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
                        cout << "Reading from table(id,login,password,name) " << result->getInt(1) << ", " << result->getString(2).c_str() << ", " << result->getString(3).c_str() << ", " << result->getString(4).c_str() << ", " << result->getString(5) << endl << endl;
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
            break;
		}
        else {
            string exit;
            while (exit != "exit") {
                cout << "Exit or command\n Commands:\nupdate - update your data\nshow - show your data\nsend_message - send message for martians or update message\n::";
                cin >> exit;
                if (exit=="update") {
                    string update_log, update_pass, update_name;
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
                    pstmt->setInt(4, id);
                    pstmt->execute();
                    cout << "Data updated\n\n";
                    delete pstmt;
                }
                else if (exit=="show") {
                    pstmt = con->prepareStatement("SELECT login, passwd, name , message FROM users WHERE id = ?;");
                    pstmt->setInt(1, id);
                    result = pstmt->executeQuery();
                    while (result->next()) {
                        cout << "Reading from table(login,password,name,message) " << result->getString(1).c_str() << ", " << result->getString(2).c_str() << ", " << result->getString(3) << ", " << result->getString(4) << endl << endl;
                    }
                    delete result;
                    delete pstmt;
                }
                else if (exit=="send_message") {
                    cout << "Enter message for Martians without spaces:\n";
                    string martians;
                    cin>>martians;
                    pstmt = con->prepareStatement("UPDATE users SET message = ? WHERE id = ?;");
                    pstmt->setString(1, martians);
                    pstmt->setInt(2, id);
                    pstmt->execute();
                    cout << "\nMessage created!";
                }
                else {
                    cout << "Wrong command\n\n";
                }
            }
            break;
        }
	}
    delete con;
}
