#include "gtest/gtest.h"
#include "../src/utils/thread/Task.h"
#include "../src/utils/thread/ThreadPool.h"
#include "../src/utils/Common.h"

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

    LOG(DEBUG) << "---- Test  ----\n";
    return RUN_ALL_TESTS();
}

// Simple test, does not use gmock
TEST(Dummy, foobar)
{
EXPECT_EQ(1, 1);
}


TEST(ThreadTest, TestName) {
    Task jobtask(10);
    Task jobtask1(11);
    Task jobtask2(12);



    ThreadPool::Instance()->produce(jobtask);
    ThreadPool::Instance()->produce(jobtask1);
    ThreadPool::Instance()->produce(jobtask2);

    ThreadPool::Instance()->start();
    sleep(1);

    ThreadPool::Instance()->stop();
    sleep(10);
    EXPECT_EQ(1, 1);
}
