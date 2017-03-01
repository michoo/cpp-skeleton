#include "DatabaseManager.h"
#include "../../utils/Common.h"
#include "PostgresqlConnection.h"

DatabaseManager* DatabaseManager::m_pInstance = NULL;

DatabaseManager* DatabaseManager::getInstance()
{
    if (!m_pInstance){
        // Only allow one instance of class to be generated.
        m_pInstance = new DatabaseManager;
        LOG(TRACE) << "DatabaseManager instanciation";
    }
    return m_pInstance;

}

DatabaseManager::DatabaseManager():url(Properties::Instance()->find("postgresql.url")),poolSize(atoi(Properties::Instance()->find("postgresql.pool.size").c_str())),
                                   connection_factory(new PostgresqlConnectionFactory(url)),
                                   pool(new ConnectionPool<PostgresqlConnection>(poolSize, connection_factory))
{

}


DatabaseManager::~DatabaseManager(){


}

boost::shared_ptr<PostgresqlConnection> DatabaseManager::getConnection() {
    return pool->borrow();
}


void DatabaseManager::releaseConnection(boost::shared_ptr<PostgresqlConnection> conn){
    pool->unborrow(conn);
}

ConnectionPoolStats DatabaseManager::getStats(){
    return pool->get_stats();
}




