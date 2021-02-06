#include <boost/asio.hpp>
#include <iostream>

namespace Game_elements{
    
    namespace Network_elements{
        
        using namespace boost::asio;
        
        const int send_buffer_size = 3000;
        const int recv_buffer_size = 3000;
        const int useful_data_from_snake = 4; // coordinates(x & y), points, state
        const int useful_data_from_food = 2; // coordinates(x & y)
        
        int server_port = 3025; 
    
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
        
        int Client::available()
        {
            return sock->available();
        }
        
        Client::Client(std::string addr)
        {
            service = new boost::asio::io_service();
            sock = new ip::tcp::socket(*service);
            ep = new ip::tcp::endpoint(ip::address::from_string(addr), server_port);
            sock->connect(*ep);
            sock->non_blocking(true);
        }
        
        Client::~Client()
        {
            delete ep;
            sock->close();
            delete sock;
            delete service;
        }
        
        void Client::sendData()
        {
            sock->write_some(boost::asio::buffer(send_buff, send_buffer_size));
        }
        
        void Client::recvData()
        {
            sock->read_some(boost::asio::buffer(recv_buff, recv_buffer_size));
        }
        
        void Client::getData(int * data_from_snake, int * data_from_food)
        {
            int j = 0;
            //int * tmp = send_buff;
            for(int i = 0; i < useful_data_from_snake; ++i, ++j)
                send_buff[j] = data_from_snake[i];
            for(int i = 0; i < useful_data_from_food; ++i, ++j)
                send_buff[j] = data_from_food[i];
        }

        
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
        
        int Server::available()
        {
            return sock->available();
        }
        
        Server::Server()
        {
            service = new boost::asio::io_service();
            ep = new ip::tcp::endpoint(ip::tcp::v4(), server_port);
            sock = new ip::tcp::socket(*service);
            acc = new ip::tcp::acceptor(*service, *ep);
            acc->accept(*sock);
            sock->non_blocking(true);
        }
        
        Server::~Server()
        {
            delete service;
            delete ep;
            sock->close();
            delete sock;
            delete acc;
        }
        
        void Server::sendData()
        {
            sock->write_some(boost::asio::buffer(send_buff, send_buffer_size));
        }
        
        void Server::recvData()
        {
            sock->read_some(boost::asio::buffer(recv_buff, recv_buffer_size));
        }
        
        void Server::getData(int * data_from_snake, int * data_from_food)
        {
            int j = 0; // Why must I to initialize exactly here?
            for(int i = 0; i < useful_data_from_snake; ++i, ++j)
                send_buff[j] = data_from_snake[i];
            for(int i = 0; i < useful_data_from_food; ++i, ++j)
                send_buff[j] = data_from_food[i];
        }
    }
    
}
