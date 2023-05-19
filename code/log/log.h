/*
 * @Author       : mark
 * @Date         : 2020-06-16
 * @copyleft Apache 2.0
 */
#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <string>
#include <thread>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h> // vastart va_end
#include <assert.h>
#include <sys/stat.h> //mkdir
#include "blockqueue.h"
#include "../buffer/buffer.h"

#define DEBUG 0
#define INFO 1
#define WARN 2
#define ERROR 3

class Log
{
public:
    void init(int level, const char *path = "./log",
              const char *suffix = ".log",
              int maxQueueCapacity = 1024);

    static Log *Instance();
    static void FlushLogThread();

    void write(int level, const char *format, ...);
    void flush();

    int GetLevel();
    void SetLevel(int level);
    bool IsOpen() { return isOpen_; }

private:
    Log();
    void AppendLogLevelTitle_(int level);
    virtual ~Log();
    void AsyncWrite_();

private:
    static const int LOG_PATH_LEN = 256;
    static const int LOG_NAME_LEN = 256;
    static const int MAX_LINES = 50000;

    const char *path_;
    const char *suffix_;

    int MAX_LINES_;

    int lineCount_;
    int toDay_;

    bool isOpen_;

    Buffer buff_;
    int level_;
    bool isAsync_;

    FILE *fp_;
    std::unique_ptr<BlockDeque<std::string>> deque_;
    std::unique_ptr<std::thread> writeThread_;
    std::mutex mtx_;
};

#define LOG_BASE(level, format, ...)                   \
    do                                                 \
    {                                                  \
        Log *log = Log::Instance();                    \
        if (log->IsOpen() && log->GetLevel() <= level) \
        {                                              \
            log->write(level, format, ##__VA_ARGS__);  \
            log->flush();                              \
        }                                              \
    } while (0);

#define LOG_DEBUG(format, ...)                 \
    do                                         \
    {                                          \
        LOG_BASE(DEBUG, format, ##__VA_ARGS__) \
    } while (0);

#define LOG_INFO(format, ...)                 \
    do                                        \
    {                                         \
        LOG_BASE(INFO, format, ##__VA_ARGS__) \
    } while (0);

#define LOG_WARN(format, ...)                 \
    do                                        \
    {                                         \
        LOG_BASE(WARN, format, ##__VA_ARGS__) \
    } while (0);

#define LOG_ERROR(format, ...)                 \
    do                                         \
    {                                          \
        LOG_BASE(ERROR, format, ##__VA_ARGS__) \
    } while (0);

#endif // LOG_H