#include <boost/asio.hpp>
#include <iostream>

namespace Game_elements{
    
    namespace Network_elements{
        
        using namespace boost::asio;
        
        const int send_buffer_size = 2000;
        const int recv_buffer_size = 2000;
        const int useful_data_from_snake = 4; // coordinates(x & y), points, state
        const int useful_data_from_food = 2; // coordinates(x & y)
    
        class Client{
            int send_buff[send_buffer_size];
            int recv_buff[recv_buffer_size];
            
            boost::asio::io_service * service;
            ip::tcp::socket * sock; // the namespace "ip" from boost::asio
            ip::tcp::endpoint * ep;
            
        public:
            Client(std::string addr);
            ~Client();
            
            void sendData();
            void recvData();
            void getData(int * data_from_snake, int * data_from_food);
            int * giveData() { return recv_buff; }
            int available();
        };
        
        
        /* -------------------------------  */
        
        
        class Server{
            int send_buff[send_buffer_size];
            int recv_buff[recv_buffer_size];
            
            boost::asio::io_service * service;
            ip::tcp::endpoint * ep; // the namespace "ip" from boost::asio
            ip::tcp::socket * sock;
            ip::tcp::acceptor * acc;
            
        public:
            Server();
            ~Server();
            
            void sendData();
            void recvData();
            void getData(int * data_from_snake, int * data_from_food);
            int * giveData() { return recv_buff; }
            int available();
        };
        
    }
    
}
