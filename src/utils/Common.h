#ifndef CPP_SKELETON_COMMON_H
#define CPP_SKELETON_COMMON_H

//Logging with easylogging++
#ifndef ELPP_DEFAULT_LOGGER
#define ELPP_DEFAULT_LOGGER "main"
#endif
#define ELPP_NO_DEFAULT_LOG_FILE
//#define ELPP_ASYNC_LOGGING
#define ELPP_THREAD_SAFE
#define TO_FILE true
#include "log/easylogging++.h"

//Poison protection
//#include "Poison.h"

#include "exception/BasicException.h"
#include "properties/Properties.h"
#include "Utils.h"
#include "thread/Task.h"
#include "thread/ThreadPool.h"

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


#define VERSION_SOFT "2.0.0"

//#define VERSION_MAJOR 
//#define VERSION_MINOR 

const int DEFAULT_POOL_SIZE = 10;
const int STARTED = 0;
const int STOPPED = 1;


#define PI 3.14159265359

#define RADIANS_TO_DEGREES(r) ((r / (2 * PI)) * 360)
#define DEGREES_TO_RADIANS(d) ((d / 360.0) * (2 * PI))
#define ROUND(d)((int)(d + 0.5))

#define ABS(a)	   (((a) < 0) ? -(a) : (a))

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MIN3
#define MIN3(a, b, c) (MIN(MIN(a, b), c))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MAX3
#define MAX3(a, b, c) (MAX(MAX(a, b), c))
#endif



#endif //CPP_SKELETON_COMMON_H
