#ifndef OPENCV_TUTO_DATABASE_H
#define OPENCV_TUTO_DATABASE_H

#include "PostgresqlConnection.h"

class DatabaseManager {

private:
    static DatabaseManager* m_pInstance;
    DatabaseManager();
    int poolSizeInt;
    std::string url;
    int poolSize;
    boost::shared_ptr<PostgresqlConnectionFactory> connection_factory;
    boost::shared_ptr<ConnectionPool<PostgresqlConnection>> pool;
    //ConnectionPoolStats stats;
public:
    ~DatabaseManager();
    static DatabaseManager* getInstance();
    boost::shared_ptr<PostgresqlConnection> getConnection();
    void releaseConnection(boost::shared_ptr<PostgresqlConnection> conn);
    ConnectionPoolStats getStats();

};


#endif //OPENCV_TUTO_DATABASE_H
