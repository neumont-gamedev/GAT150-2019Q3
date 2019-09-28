#pragma once

#include "logger.h"

extern Logger<FileLogOutput> g_logger;

#define LOG g_logger.Print< eLogPriority::PRIORITY_VERBOSE >
#define DEBUG1 g_logger.Print< eLogPriority::PRIORITY_DEBUG_1 >
#define DEBUG2 g_logger.Print< eLogPriority::PRIORITY_DEBUG_2 >
#define DEBUG3 g_logger.Print< eLogPriority::PRIORITY_DEBUG_3 >
#define WARNING1 g_logger.Print< eLogPriority::PRIORITY_WARNING_1 >
#define WARNING2 g_logger.Print< eLogPriority::PRIORITY_WARNING_2 >
#define ERR g_logger.Print< eLogPriority::PRIORITY_ERROR >