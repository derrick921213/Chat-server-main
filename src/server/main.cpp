
// #include <iostream>
// #include <boost/asio.hpp>
// #include <mysql.h>
// #include <unistd.h>
// using namespace std;
// // 使用 boost::asio::ip::tcp 命名空间
// using boost::asio::ip::tcp;

// const int PORT = 8080;

// // // 定義一個函數get_ip_address()，用於獲取本機IPv4地址
// std::string get_ip_address()
// {
//     // 創建一個asio的io_context物件，用於處理網絡操作
//     boost::asio::io_context io_context;
//     // 創建一個resolver物件，用於解析本機主機名
//     tcp::resolver resolver(io_context);
//     // 解析本機主機名到IP地址列表
//     auto endpoints = resolver.resolve(boost::asio::ip::host_name(), "");
//     // 使用range-based for loop遍歷IP地址列表，找到第一個IPv4地址，並回傳，range-based for loop可以用來遍歷物件或向量
//     for (const auto &endpoint : endpoints)
//     {
//         // 判斷IP地址是否是IPv4地址
//         if (endpoint.endpoint().address().is_v4())
//         {
//             // 回傳IP地址的字符串形式
//             return endpoint.endpoint().address().to_string();
//         }
//     }
//     // 如果沒有找到IPv4地址就回傳
//     return "0.0.0.0";
// }

// int main()
// {
//     // try
//     // {
//     //     // 創建資料庫連接
//     //     mariadb::conncpp::Connection connection("tcp://localhost:3307", "root", "rootpassword", "database_name");

//     //     // // 執行 SQL 查詢
//     //     // mariadb::conncpp::Statement statement(&connection);
//     //     // statement.execute("INSERT INTO users (username, password) VALUES (?, ?)", "user1", "password1");

//     //     // std::cout << "User registered successfully." << std::endl;
//     // }
//     // catch (const mariadb::conncpp::Exception &e)
//     // {
//     //     std::cerr << "Error: " << e.what() << std::endl;
//     // }
//     char hostname[256];
//     if (gethostname(hostname, sizeof(hostname)) == 0)
//     {
//         cout << "Hostname: " << hostname << endl;
//     }
//     else
//     {
//         perror("gethostname");
//     }
//     MYSQL *mysql = new MYSQL;
//     if (mysql_init(mysql) == 0)
//     {
//         cout << mysql_error(mysql) << endl;
//     }
//     else
//     {
//         cout << "mysql init success####" << endl;
//     }
//     mysql_set_character_set(mysql, "utf8");

//     char szIP[256] = "database";
//     char szUser[256] = "root";
//     char szPassword[256] = "rootpassword";
//     char szDBName[256] = "database_name";

//     if (mysql_real_connect(mysql, szIP, szUser, szPassword, szDBName, 0, NULL, 0) == 0)
//     {
//         cout << mysql_error(mysql) << endl;
//     }
//     else
//     {
//         cout << "mysql connect success" << endl;
//     }
//     try
//     {
//         // 創建一個asio的io_context物件，用於處理網絡操作
//         boost::asio::io_context io_context;
//         // 創建一個acceptor物件，用於監聽本機的PORT端口定義在上面的const int PORT = 8080;
//         tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
//         // 獲取本機的IPv4地址
//         std::string ip_address = get_ip_address();
//         // 輸出本機的IPv4地址和PORT
//         std::cout << "Server is listening on IP " << ip_address << " and port " << PORT << std::endl;

//         for (;;)
//         {
//             // 創建一個socket物件，接受客戶端的連接
//             tcp::socket socket(io_context);
//             // 等待客戶端的連接
//             acceptor.accept(socket);
//         }
//     }
//     catch (std::exception &e)
//     {
//         std::cerr << "Exception: " << e.what() << "\n";
//     }
//     return 0;
// }

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

const int PORT = 8080;  // 服务器监听的端口

int main()
{
    try
    {
        // 创建io_context对象，用于处理异步操作
        boost::asio::io_context io_context;

        // 创建一个tcp::acceptor对象，用于监听连接
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));

        cout << "Server is listening on port " << PORT << endl;

        for (;;)
        {
            // 创建一个socket对象，用于与客户端通信
            tcp::socket socket(io_context);

            // 等待并接受一个客户端连接
            acceptor.accept(socket);

            cout << "Client connected" << endl;

            // 创建一个缓冲区来存储接收到的数据
            char data[1024];

            // 读取数据
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (!error)
            {
                cout << "Received message: ";
                cout.write(data, length);
                cout << endl;

                // 发送回复给客户端
                string reply = "Hello from DATA server!";
                boost::asio::write(socket, boost::asio::buffer(reply), error);

                if (!error)
                {
                    cout << "Reply sent: " << reply << endl;
                }
                else
                {
                    cout << "Failed to send reply: " << error.message() << endl;
                }
            }
            else
            {
                cout << "Failed to receive message: " << error.message() << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}