#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory> // Include for std::unique_ptr
#include <string>

// Command to get the IP on cmd terminal : Ip config . Afterwards search for WSL ipv4

//Command to compile the file : g++ Gym_system.cpp -o exe -lmysqlcppconn

// Defining the specifications to connect to the database
// By default, MySQL runs on port 3306

const std::string server = "tcp://172.22.64.1:3306";
const std::string username = "Group4";
const std::string password = "matador123";
const std::string schema = "gym_management";

// Uncomment and implement if needed
// void insertIntoDatabase(const std::string& insertQuery);

void insertIntoUnit(sql::Connection* con, int id_unit, const std::string& name,const std::string& location);
void displayUnitTableContent(sql::Connection* con);
void displayUnitById(sql::Connection* con, int id_unit);
void deleteUnitById(sql::Connection* con, int id_unit);

int main() {
    sql::Driver* driver = get_driver_instance();
    std::unique_ptr<sql::Connection> con(driver->connect(server, username, password));
    con->setSchema(schema);
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 'Hello World!' AS _message"));  // Example query
        while (res->next()) {
            std::cout << "\t... MySQL replies: ";
            std::cout << res->getString("_message") << std::endl;
        }
    } catch (sql::SQLException& e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    std::cout << "You are connected to the database: " << schema << std::endl;

    // For the sake of understanding let's register 3 units on our database 

    for(int i=0;i<3;i++){ 
        int unit;
        std::string name,location;
        std::cout<<"Please , insert the id_unit : ";
        std::cin>>unit;
        std::cout<<"Please insert the name of the unit : ";
        std::cin>>name;
        std::cout<<"Please insert the location of the unit : ";
        std::cin>>location;
        insertIntoUnit(con.get(), unit, name, location); //call the function to insert into unit
    }
    displayUnitTableContent(con.get());
    std::cout<<"Enter the id_unit you are searching for : ";
    int id_example;
    std::cin>>id_example;
    displayUnitById(con.get(), id_example);
    std::cout<<std::endl;

    for(int i=0;i<2;i++){ 
    std::cout<<"Please insert the id_unit you want to delete from your table: ";
    int id_example2;
    std::cin>>id_example2;

    deleteUnitById(con.get(), id_example2);
    std::cout<<std::endl;
    }
    std::cout<<std::endl;
    displayUnitTableContent(con.get());
    
    

    return 0;
}

void insertIntoUnit(sql::Connection* con, int id_unit, const std::string& name,const std::string& location) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO unit (id_unit, name, location) VALUES (?, ?, ?)"));
        pstmt->setInt(1, id_unit);
        pstmt->setString(2, name);
        pstmt->setString(3, location);
        pstmt->executeUpdate();
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException in " << __FILE__;
        std::cerr << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "ERROR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}
void displayUnitTableContent(sql::Connection* con) {
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM unit"));

        std::cout << "Unit Table Content:" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "id_unit\t| name\t| location" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        // Iterate through the result set and display each row
        while (res->next()) {
            std::cout << res->getInt("id_unit") << "\t| "
                      << res->getString("name") << "\t| "
                      << res->getString("location") << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException in " << __FILE__;
        std::cerr << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "ERROR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void displayUnitById(sql::Connection* con, int id_unit) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM unit WHERE id_unit = ?"));
        pstmt->setInt(1, id_unit);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "Unit Table Content for id_unit = " << id_unit << ":" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "id_unit\t| name\t| location" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        // Iterate through the result set and display each row
        while (res->next()) {
            std::cout << res->getInt("id_unit") << "\t| "
                      << res->getString("name") << "\t| "
                      << res->getString("location") << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException in " << __FILE__;
        std::cerr << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "ERROR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void deleteUnitById(sql::Connection* con, int id_unit) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM unit WHERE id_unit = ?"));
        pstmt->setInt(1, id_unit);
        pstmt->executeUpdate();
        std::cout << "Row with id_unit = " << id_unit << " deleted successfully." << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException in " << __FILE__;
        std::cerr << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cerr << "ERROR: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}
