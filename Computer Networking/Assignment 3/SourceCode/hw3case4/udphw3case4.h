#pragma
#include "UdpSocket.h"
#include "Timer.h"

class udphw3case4
{
public:
    int clientSlidingWindow( UdpSocket &sock, const int max, int message[], int windowSize );
    void serverEarlyRetrans( UdpSocket &sock, const int max, int message[], int windowSize ,int dropChance);
};