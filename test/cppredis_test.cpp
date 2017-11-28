#include <cpp_redis/cpp_redis>
#include <tacopie/tacopie>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <csignal>


std::condition_variable should_exit;

void
sigint_handler(int) {
    should_exit.notify_all();
}

int
main() {
    //! Enable logging
    cpp_redis::active_logger = std::make_unique<cpp_redis::logger>();

    cpp_redis::subscriber sub;


    sub.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::subscriber::connect_state status) {
        if (status == cpp_redis::subscriber::connect_state::dropped) {
            std::cout << "client disconnected from " << host << ":" << port << std::endl;
            should_exit.notify_all();
        }
    });

    //! authentication if server-server requires it
    // sub.auth("some_password", [](const cpp_redis::reply& reply) {
    //   if (reply.is_error()) { std::cerr << "Authentication failed: " << reply.as_string() << std::endl; }
    //   else {
    //     std::cout << "successful authentication" << std::endl;
    //   }
    // });

    sub.subscribe("some_chan", [](const std::string& chan, const std::string& msg) {
        std::cout << "MESSAGE " << chan << ": " << msg << std::endl;
    });
    sub.psubscribe("*", [](const std::string& chan, const std::string& msg) {
        std::cout << "MESSAGE " << chan << ": " << msg << std::endl;
    });
    sub.commit();

    signal(SIGINT, &sigint_handler);
    std::mutex mtx;
    std::unique_lock<std::mutex> l(mtx);
    should_exit.wait(l);

    return 0;
}
