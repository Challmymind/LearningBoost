#define _WIN32_WINNT 0x0501
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>


namespace asio = boost::asio;

int main()
{
    asio::io_service service;
    boost::mutex mtx;

    for (int i = 0; i <20; ++i)
    {
        service.post([i, &mtx]()
        {
            std::cout << boost::this_thread::get_id()<< std::endl;
            boost::this_thread::sleep(
                boost::posix_time::seconds(5)
            );

        }
        );
    }

    boost::thread_group pool;
    for (int i = 0; i < 20; ++i)
    {
        pool.create_thread([&service]() {service.run(); });
    }

    pool.join_all();

    return 1;
}
