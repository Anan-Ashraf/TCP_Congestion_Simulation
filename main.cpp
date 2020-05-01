#include <iostream>

using namespace std;

class TCP
{
private:
    int MSS,Tresh,cwnd,wndw;
    int SqTripAck;
    int SqTimeOut;
    int packets; //max no of packets
    int counterPackets=0;

public:
     TCP(int lost, int trip,int packets)
    {
        SqTripAck=trip;
        SqTimeOut=lost;
        this->packets=packets;
        cwnd=1;
        wndw=1;
        SS();
    }

    bool connection()
    {
        if(counterPackets>=packets) return false; //terminate
        else
            return true;
    }

    bool TripAck()
    {
        if (counterPackets==SqTripAck)
            return true;
        return false;
    }
    bool TimeOut()
    {
        if (counterPackets==SqTimeOut)
            return true;
        return false;
    }
    void AI()
    {
        cout<<"hi from AI\n";
        while(connection()) //while not terminated connection
        {
            wndw++;
            cout<<"current window size is: "<<wndw<<endl;
            counterPackets+=wndw;
            cout<<counterPackets<<" sent untill now\n";

            if(TripAck()==true)
            {
                Tresh=wndw/2;
                cwnd=Tresh;
            }
            else if (TimeOut())
            {
                cwnd=1;
                Tresh=wndw/2;

            }
        }
        cout<<"connection terminated at window size: "<<wndw<<endl;


    }

    void SS()
    {
        cout<<"hi from SS\n";

        while(wndw<Tresh)
        {
            while(connection()){
            wndw=2*wndw;
            cout<<"current window size is: "<<wndw<<endl;
            counterPackets+=wndw;
            cout<<counterPackets<<"  sent until now\n";
            if(TripAck()==true)
            {
                Tresh=wndw/2;
                cwnd=Tresh;
                AI();
            }
            else if (TimeOut())
            {
                cwnd=1;
                Tresh=wndw/2;
                AI();
            }
        }
        //when reaching threshold
        Tresh=wndw/2;
        cwnd=Tresh;
        AI();
        }
        cout<<"connection terminated\n";

    }
};
int main()
{
    int lost, triple,packets,printSq;
    cout<<"enter total number of packets you want to enter\n";
    cin>>packets;

    cout<<"enter seq no of lost packets\n";
    cin>>lost;
    cout<<"enter seq no of trip ack\n";
    cin>>triple;
    TCP  myTcp(lost, triple,packets);



    return 0;
}
