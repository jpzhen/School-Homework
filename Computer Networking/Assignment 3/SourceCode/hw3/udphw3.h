#include <iostream>
#include "UdpSocket.h"
#include "Timer.h"
using namespace std;

class udphw3 
{
    public:
        int clientStopWait( UdpSocket &sock, const int max, int message[] );
        int clientSlidingWindow( UdpSocket &sock, const int max, int message[], int windowSize );
        void serverReliable( UdpSocket &sock, const int max, int message[] );
        void serverEarlyRetrans( UdpSocket &sock, const int max, int message[], int windowSize );
};