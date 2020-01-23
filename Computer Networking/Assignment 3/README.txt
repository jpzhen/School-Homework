How to compile and run:
- The assignment page only told us to include our write-up, hw3.cpp, udphw3.cpp, udphw3case4.cpp, and hw3case3.cpp
- To able to run, the problem needs the provided code: Time.cpp, Time.h, UdpSocket.cpp, UdpSocket.cpp,
- Please put those files inside directory: hw3 and hw3case4 (each directory require a copy!)
- I noticed timeout time the assignment ask us to set (1500 user) is too long for any packet to drop for me, if you don't see any retransmission, please lower the time out time in udphw3.cpp and udphw3case4.cpp. This may vary from hardware to hardware. 
- Please enter these commands to compile and run:
    - hw3:
            (machine 1) $ g++ Time.cpp UdpSocket.cpp hw3.cpp udphw3.cpp -o hw3
            (machine 1) $ ./hw3
            (machine 2) $ ./hw3 127.0.0.1 #I used local network, if you use different ip address please make sure its local
            (machine 1 and 2) $ #enter test 1, 2, or 3

    - hw3case4:
            (machine 1) $ g++ Time.cpp UdpSocket.cpp hw3case4.cpp udphw3case4.cpp -o hw3case4
            (machine 1) $ ./hw3case4
            (machine 2) $ ./hw3case4 127.0.0.1 #I used local network, if you use different ip address please make sure its local
            (machine 1 and 2) $ #Please enter test 4 only! 