#include"SIMPLE-LOG.hpp"
#include<limits>
using namespace std;
bool should_exit = false;
int main()
{
	srand(time(NULL));
	Log LOG("gamelog.log");
	LOG.set_ERROR_Callback([](const string& msg){
        cerr<<"ERROR:"<< msg;
        should_exit = true;
    });
    LOG.Write(LogLevel::INFO,"Game Start Successful\n");
    int num = rand()%100 + 1;
    int current_num = 0;
    long long buffer = 0;
    while(!should_exit){
        buffer = 0,current_num = 0;
        cin>>buffer;
        if(buffer > 2147483647 || buffer < 0)LOG.Write(LogLevel::ERROR,"Current_num is out of range\n");
        current_num = buffer;
        string msg_str = "Player Guess:" + to_string(current_num) + "\n";
        LOG.Write(LogLevel::INFO,msg_str);
        if(current_num != num){
            if(current_num > num){
                cout<<"too big!"<<endl;
            }
            else{
                cout<<"too small!"<<endl;
            }
        }else{
            cout<<"You guessed it!"<<endl;
            break;
        }
    }
    LOG.Write(LogLevel::INFO,"Game Exit Successful\n");
	return 0;
}
