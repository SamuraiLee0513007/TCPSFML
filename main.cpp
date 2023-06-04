#include <iostream>
#include <string>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
int main(){
    TcpSocket socket;
    IpAddress ip = IpAddress::getLocalAddress();
    char connectionType, mode;
    char buffer[2000];
    size_t received;
    string text = "connected to: ";
    cout << "Enter (s) for server, c for client: " << endl;
    cin >> connectionType;
    if(connectionType == 's'){
    	TcpListener listener;
    	listener.listen(2000);
    	listener.accept(socket);
    	text+="Server";
    	mode = 's';
    }
    else if(connectionType == 'c'){
    	socket.connect(ip,2000);
    	text += "Client";
    	mode = 'r';
    }
    socket.send(text.c_str(),text.length()+1);
    socket.receive(buffer,sizeof(buffer),received);
    cout << buffer <<endl;
    bool done = false;
    while(!done){
    	if(mode == 's'){
    		getline(cin,text);
            socket.send(text.c_str(),text.length()+1);
            mode = 'r';
    	}else if(mode == 'r'){
    	     socket.receive(buffer,sizeof(buffer),received);
    		if(received>0){
    			cout<<"Received: "<<buffer<<endl;
    			mode = 's';
    		}

    	}
    }
}




