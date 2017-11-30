#include <iostream>

#include <cpp_redis/cpp_redis>

using namespace std;

int main() {
    //! Enable logging
    cpp_redis::active_logger = std::make_unique<cpp_redis::logger>();

    cpp_redis::client client;
    client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
            std::cout << "client disconnected from " << host << ":" << port << std::endl;
        }
    });

    return 0;
}
