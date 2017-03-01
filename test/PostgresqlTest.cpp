#include "gtest/gtest.h"
#include "../src/utils/Common.h"
#include <pqxx/pqxx>
#include <boost/shared_ptr.hpp>
#include "../src/controller/database/PostgresqlConnection.h"
#include "../src/controller/database/DatabaseManager.h"



INITIALIZE_EASYLOGGINGPP

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    //log config
    el::Configurations conf("../conf/log.conf");
    el::Loggers::reconfigureLogger("main", conf);
    el::Loggers::reconfigureAllLoggers(conf);

    printf("cpp-skeleton ");
    printf(VERSION_SOFT);
    printf("\n");

    LOG(DEBUG) << "---- Test Postgresql----\n";
    return RUN_ALL_TESTS();
}


TEST(Postgresql, libversion)
{
    LOG(DEBUG) << "---- first Test Postgresql----\n";
    try{

        std::string url = Properties::Instance()->find("postgresql.url");
        pqxx::connection C(url);
        if (C.is_open()) {
            LOG(TRACE) << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            LOG(TRACE) << "Can't open database" ;
            return ;
        }
        C.disconnect();
    }catch (const std::exception &e){
        LOG(ERROR) << e.what() ;
        return ;
    }


EXPECT_EQ(1, 1);
}

TEST(Postgresql2, testDatabaseManager)
{
    LOG(DEBUG) << "---- second Test Postgresql----\n";
// Create a pool of 2 dummy connections
    std::string url = Properties::Instance()->find("postgresql.url");
    std::string poolSize = Properties::Instance()->find("postgresql.pool.size");
    int poolSizeInt = atoi(poolSize.c_str());
    LOG(TRACE) <<"Creating connections..." ;
    boost::shared_ptr<PostgresqlConnectionFactory>connection_factory(new PostgresqlConnectionFactory(url));
    boost::shared_ptr<ConnectionPool<PostgresqlConnection> >pool(new ConnectionPool<PostgresqlConnection>(poolSizeInt, connection_factory));
    ConnectionPoolStats stats=pool->get_stats();
    EXPECT_EQ(stats.pool_size, 3);
    {

        // Get both available connections
        boost::shared_ptr<PostgresqlConnection> conn1=pool->borrow();
        boost::shared_ptr<PostgresqlConnection> conn2=pool->borrow();
        boost::shared_ptr<PostgresqlConnection> conn3=pool->borrow();

        // Trying to get a third should throw
        LOG(TRACE) <<"Checking for exception when pool is empty..." ;
        bool exception_thrown=false;
        try {

            boost::shared_ptr<PostgresqlConnection> conn4=pool->borrow();

        } catch (std::exception& e) {

            LOG(TRACE) << "Exception thrown (intentional)" ;
            exception_thrown=true;
        }
        EXPECT_EQ(exception_thrown,true);


        // Release one, and make sure it was repatriated (no exception)
        LOG(TRACE) <<"Clean relase and re-borrow 1 connection" ;
        pool->unborrow(conn1);
        conn1=pool->borrow();		// Should not throw

        if (conn1->sql_connection->is_open()) {
            LOG(TRACE) << "Opened database successfully: " << conn1->sql_connection->dbname() << std::endl ;
        } else {
            LOG(TRACE) << "Can't open database" ;
        }

    }

    // We never released pool 2, but it went out of scope.  2 connections should once again be available...
    LOG(TRACE) <<"Dirty relase and re-borrow 2 connections.  Will cause destruction of old connections" ;
    boost::shared_ptr<PostgresqlConnection> conn1=pool->borrow();
    boost::shared_ptr<PostgresqlConnection> conn2=pool->borrow();

    stats=pool->get_stats();

    LOG(TRACE) << "Clean release all connections " << stats.pool_size << std::endl;


    EXPECT_EQ(stats.pool_size, 0);
}

TEST(Postgresql3, DatabaseManagerR)
{
    LOG(DEBUG) << "---- third Test Postgresql----\n";

    boost::shared_ptr<PostgresqlConnection> conn1 = DatabaseManager::getInstance()->getConnection();
    if (conn1->sql_connection->is_open()) {
        LOG(TRACE) << "Opened database successfully: " << conn1->sql_connection->dbname() << std::endl ;
    } else {
        LOG(TRACE) << "Can't open database" ;
    }

    ConnectionPoolStats stats=DatabaseManager::getInstance()->getStats();

    LOG(TRACE) << "Pool size before releasing " << stats.pool_size << std::endl;

    DatabaseManager::getInstance()->releaseConnection(conn1);
    stats=DatabaseManager::getInstance()->getStats();

    LOG(TRACE) << "Pool size after releasing " << stats.pool_size << std::endl;

}
