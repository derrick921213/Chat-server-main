#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

const string SERVER_IP = "server"; // 服务器的IP地址
const int PORT = 8080;                // 服务器的端口

int main()
{
    try
    {
        // 创建io_context对象，用于处理异步操作
        boost::asio::io_context io_context;

        // 创建一个tcp::resolver对象，解析服务器的IP地址和端口
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(SERVER_IP, to_string(PORT));

        // 创建并连接到服务器的socket
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        cout << "Connected to server " << SERVER_IP << " on port " << PORT << endl;

        // 准备要发送的消息
        const string msg = "Hello from DATA client!";
        boost::system::error_code error;

        // 发送消息到服务器
        boost::asio::write(socket, boost::asio::buffer(msg), error);

        if (!error)
        {
            cout << "Message sent: " << msg << endl;
        }
        else
        {
            cout << "Failed to send message: " << error.message() << endl;
        }

        // 接收服务器的响应
        char reply[1024];
        size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, msg.size()), error);

        if (!error)
        {
            cout << "Reply received: ";
            cout.write(reply, reply_length);
            cout << endl;
        }
        else
        {
            cout << "Failed to receive reply: " << error.message() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
