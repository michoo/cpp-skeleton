#include "main.h"



using namespace cv;
using namespace std;

INITIALIZE_EASYLOGGINGPP

void Main::start(){
    //log config
    el::Configurations conf("../conf/log.conf");
    el::Loggers::reconfigureLogger("main", conf);
    el::Loggers::reconfigureAllLoggers(conf);

    //logo style
    printf( "                                       __          .__          __                 \n"
                    "  ____ ______ ______             _____|  | __ ____ |  |   _____/  |_  ____   ____  \n"
                    "_/ ___\\\\____ \\\\____ \\   ______  /  ___/  |/ // __ \\|  | _/ __ \\   __\\/  _ \\ /    \\ \n"
                    "\\  \\___|  |_> >  |_> > /_____/  \\___ \\|    <\\  ___/|  |_\\  ___/|  | (  <_> )   |  \\\n"
                    " \\___  >   __/|   __/          /____  >__|_ \\\\___  >____/\\___  >__|  \\____/|___|  /\n"
                    "     \\/|__|   |__|                  \\/     \\/    \\/          \\/                 \\/ \n\n");
    printf(VERSION_SOFT);
    printf("\n\n");

    LOG(DEBUG) << "---- Debug mode ----";
}




int main() {

    Main::start();

    //start all singleton
    Properties::Instance()->print();
    ThreadPool::Instance()->start();



    sleep(4);

    return 0;
}

