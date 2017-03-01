#ifndef OPENCV_TUTO_POSTGRE_H
#define OPENCV_TUTO_POSTGRE_H

#include "ConnectionPool.h"
#include <string>
#include <pqxx/pqxx>
#include "../../utils/Common.h"

using boost::shared_ptr;

class PostgresqlConnection : public Connection {

public:

    PostgresqlConnection() {

    };

    ~PostgresqlConnection() {

        if(this->sql_connection) {
            this->sql_connection->disconnect();
            this->sql_connection.reset(); 	// Release and destruct

        }

    };

    boost::shared_ptr<pqxx::connection> sql_connection;

};


class PostgresqlConnectionFactory : public ConnectionFactory {

public:
    PostgresqlConnectionFactory(std::string url) {

        this->url=url;


    };

    // Any exceptions thrown here should be caught elsewhere
    boost::shared_ptr<Connection> create() {


        // Create the connection
        boost::shared_ptr<PostgresqlConnection>conn(new PostgresqlConnection());


        conn->sql_connection = boost::shared_ptr<pqxx::connection>(new pqxx::connection(url));

//        if(conn->sql_connection == NULL){
//            throw  std::exception("Postgresql went to Hell...");
//        }


        return boost::static_pointer_cast<Connection>(conn);
    };

private:
    string url;

};

#endif //OPENCV_TUTO_POSTGRE_H