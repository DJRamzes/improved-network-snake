#include <boost/asio.hpp>
#include <iostream>

namespace Game_elements{
    
    namespace Network_elements{
        
        using namespace boost::asio;
        
        const int send_buffer_size = 2000;
        const int recv_buffer_size = 2000;
        const int useful_data_from_snake = 4; // coordinates(x & y), points, state
        const int useful_data_from_food = 2; // coordinates(x & y)
        
        int server_port = 3025; 
    
        class Client{
            int send_buff[send_buffer_size];
            int recv_buff[recv_buffer_size];
            int size_buff[2]; // rows and cols, size_buff[0] - x, size_buff[1] - y
            
            boost::asio::io_service * service;
            ip::tcp::socket * sock; // the namespace "ip" from boost::asio
            ip::tcp::endpoint * ep;
            
        public:
            Client(std::string addr, int size_x, int size_y);
            ~Client();
            
            void sendData();
            void recvData();
            void getData(int * data_from_snake, int * data_from_food);
            int * giveData() { return recv_buff; }
            int available();
            void sync_screens();
            int * giveSize_buff() { return size_buff; }
        };
        
        void Client::sync_screens()
        {
            send_buff[0] = size_buff[0];
    	    send_buff[1] = size_buff[1];
    	    sendData();
    	    recvData();
    	    size_buff[0] = recv_buff[0];
    	    size_buff[1] = recv_buff[1];
            
            sock->non_blocking(true);
        }
        
        int Client::available()
        {
            return sock->available();
        }
        
        Client::Client(std::string addr, int in_size_x, int in_size_y)
        {
            size_buff[0] = in_size_x;
            size_buff[1] = in_size_y;
            service = new boost::asio::io_service();
            sock = new ip::tcp::socket(*service);
            ep = new ip::tcp::endpoint(ip::address::from_string(addr), server_port);
            sock->connect(*ep);
            //sock->non_blocking(true);
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
            for(int i = 0; i < useful_data_from_snake; ++i, ++j)
                send_buff[j] = data_from_snake[i];
            for(int i = 0; i < useful_data_from_food; ++i, ++j)
                send_buff[j] = data_from_food[i];
        }

        
        /* -------------------------------  */
        
        class Server{
            int send_buff[send_buffer_size];
            int recv_buff[recv_buffer_size];
            int size_buff[2];
            
            boost::asio::io_service * service;
            ip::tcp::endpoint * ep; // the namespace "ip" from boost::asio
            ip::tcp::socket * sock;
            ip::tcp::acceptor * acc;
            
        public:
            Server(int size_x, int size_y);
            ~Server();
            
            void sendData();
            void recvData();
            void getData(int * data_from_snake, int * data_from_food);
            int * giveData() { return recv_buff; }
            int available();
            void sync_screens();
            int * giveSize_buff() { return size_buff; }
        };
        
        void Server::sync_screens()
        {
    	    recvData();
    	    
    	    if(recv_buff[0] <= size_buff[0] && recv_buff[1] <= size_buff[1]){
            	size_buff[0] = recv_buff[0] / 2 - 1;
            	size_buff[1] = recv_buff[1] - 1;
            	
            	send_buff[0] = size_buff[0];
            	send_buff[1] = size_buff[1];
    	    }
    	    else if(recv_buff[0] >= size_buff[1] && recv_buff[1] <= size_buff[0]){
            	size_buff[0] = recv_buff[0] / 2 - 1;
            	size_buff[1] = size_buff[1] - 1;
            	
            	send_buff[0] = size_buff[0];
            	send_buff[1] = size_buff[1];
    	    }    
    	    else if(recv_buff[0] <= size_buff[1] && recv_buff[1] >= size_buff[0]){
            	size_buff[0] = size_buff[0] / 2 - 1;
            	size_buff[1] = recv_buff[1] - 1;
            	
            	send_buff[0] = size_buff[0];
            	send_buff[1] = size_buff[1];
    	    }    
    	    else{
            	size_buff[0] = size_buff[0] / 2 - 1;
            	size_buff[1] = size_buff[1] - 1;
                
            	send_buff[0] = size_buff[0];
            	send_buff[1] = size_buff[1];
    	    }
    	    sendData();	
            
            sock->non_blocking(true);
        }
        
        int Server::available()
        {
            return sock->available();
        }
        
        Server::Server(int in_size_x, int in_size_y)
        {
            size_buff[0] = in_size_x;
            size_buff[1] = in_size_y;
            service = new boost::asio::io_service();
            ep = new ip::tcp::endpoint(ip::tcp::v4(), server_port);
            sock = new ip::tcp::socket(*service);
            acc = new ip::tcp::acceptor(*service, *ep);
            acc->accept(*sock);
            //sock->non_blocking(true);
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
