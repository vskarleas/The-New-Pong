#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <SDL_net.h>
#include <string>

struct PaddleState {
    float y_position;
    bool up_pressed;
    bool down_pressed;
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    
    bool init_as_host(int port = 1234);
    bool init_as_client(const char* host, int port = 36000);
    void send_paddle_state(const PaddleState& state);
    bool receive_paddle_state(PaddleState& state);
    void close();

private:
    UDPsocket socket;
    IPaddress peer_address;
    UDPpacket* send_packet;
    UDPpacket* receive_packet;
    bool is_host;
};

#endif