#include "network.hpp"

NetworkManager::NetworkManager() : socket(nullptr), send_packet(nullptr), receive_packet(nullptr), is_host(false)
{
    if (SDLNet_Init() < 0)
    {
        SDL_Log("SDLNet_Init failed: %s", SDLNet_GetError());
        return;
    }

    send_packet = SDLNet_AllocPacket(sizeof(PaddleState));
    receive_packet = SDLNet_AllocPacket(sizeof(PaddleState));
}

NetworkManager::~NetworkManager()
{
    close();
}

bool NetworkManager::init_as_host(int port)
{
    is_host = true;
    socket = SDLNet_UDP_Open(port);
    if (!socket)
    {
        SDL_Log("SDLNet_UDP_Open failed: %s", SDLNet_GetError());
        return false;
    }
    return true;
}

bool NetworkManager::init_as_client(const char *host, int port)
{
    is_host = false;
    socket = SDLNet_UDP_Open(0);
    if (!socket)
    {
        SDL_Log("SDLNet_UDP_Open failed: %s", SDLNet_GetError());
        return false;
    }

    if (SDLNet_ResolveHost(&peer_address, host, port) < 0)
    {
        SDL_Log("SDLNet_ResolveHost failed: %s", SDLNet_GetError());
        return false;
    }
    return true;
}

void NetworkManager::send_paddle_state(const PaddleState &state)
{
    memcpy(send_packet->data, &state, sizeof(PaddleState));
    send_packet->len = sizeof(PaddleState);
    send_packet->address = peer_address;

    SDLNet_UDP_Send(socket, -1, send_packet);
}

bool NetworkManager::receive_paddle_state(PaddleState &state)
{
    if (SDLNet_UDP_Recv(socket, receive_packet))
    {
        memcpy(&state, receive_packet->data, sizeof(PaddleState));
        if (!is_host)
        {
            peer_address = receive_packet->address;
        }
        return true;
    }
    return false;
}

void NetworkManager::close()
{
    if (send_packet)
    {
        SDLNet_FreePacket(send_packet);
        send_packet = nullptr;
    }
    if (receive_packet)
    {
        SDLNet_FreePacket(receive_packet);
        receive_packet = nullptr;
    }
    if (socket)
    {
        SDLNet_UDP_Close(socket);
        socket = nullptr;
    }
    SDLNet_Quit();
}