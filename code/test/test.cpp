#include <iostream>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "../pool/threadpool.h"
#include "../pool/sqlconnpool.h"
#include "../pool/sqlconnRAII.h"

using namespace std;

void test01()
{
    Buffer buf(10);
    cout << buf.WritableBytes() << endl;
    cout << buf.ReadableBytes() << endl;

    buf.Append("1234567890");

    cout << buf.WritableBytes() << endl;
    cout << buf.ReadableBytes() << endl;

    cout << buf.WritableBytes() << endl;
    cout << buf.ReadableBytes() << endl;
    cout << buf.PrependableBytes() << endl;
}

void test02()
{
    Log::Instance()->init(DEBUG, "./log", ".log", 12);
    LOG_DEBUG("========== Server init ==========");
    LOG_INFO("========== Server init ==========");
    LOG_WARN("Unexpected event");
    LOG_ERROR("Unexpected event");
}

void ff(int a)
{
    std::cout << "ff" << a << std::endl;
}

void test03()
{
    ThreadPool thread_pool(4);
    int a = 1;
    thread_pool.AddTask(std::bind(&ff, a));
    sleep(1);
}

void test04()
{
    SqlConnPool::Instance()->Init("localhost", 3306, "root", "123", "test", 10);
    MYSQL *sql;
    SqlConnRAII sql_con_raii(&sql, SqlConnPool::Instance());
    sleep(1);
}

#define MY_MACRO           \
    {                      \
        cout << 1 << endl; \
        cout << 1 << endl; \
    }

int main()
{
    // test01();
    // test02();
    // testo3();
    // test04();
    // test05();
    return 0;
}