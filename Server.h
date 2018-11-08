//
// Created by Igor on 16.10.2018.
//

#ifndef ZHAKAL_SERVER_H
#define ZHAKAL_SERVER_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;
using namespace sf;


struct Transfer
{
	int integer;
	string data;
	float f;
	double d;
	bool logic;
};

class Server
{
private:
	TcpListener server;
	vector <TcpSocket *> clients;
	SocketSelector selector;
public:
	Server();
	Server(size_t port, bool IsAccept = true, IpAddress ip = IpAddress::Any,  bool blocking = true);
	bool Listen(size_t port, IpAddress ip, bool IsAccept = true);
	bool Accept();

	vector <IpAddress> getIpClients();
	vector <int> getPortClients();

	bool Send(int number, int reciever = -1);
	bool Send(string data, int reciever = -1);
	bool Send(double number, int reciever = -1);
	bool Send(bool logic, int reciever = -1);
	bool Send(Packet packet, int reciever = -1);
	bool Send(Transfer transfer, int reciever = -1);

	vector <int> GetIntMessage(vector <bool> &check);
	vector <string> GetStringMessage(vector <bool> &check);
	vector <double> GetDoubleMessage(vector <bool> &check);
	vector <bool> GetBoolMessage(vector <bool> &check);
	vector <Packet> GetPacketMessage(vector <bool> &check);
	vector <Transfer> GetTransferMessage(vector <bool> &check);

	bool DisconnectBack();
	bool Disconnect(size_t number);
	bool Disconnect(vector <size_t> numbers);

	void check_status(Socket::Status status, size_t current);

	size_t SizeOfClients();

	void SetBlock(bool blocking);
	bool IsBlocking();

	Packet refreash_clients();

	 TcpListener &getServer();
	 SocketSelector &getSelector();
	 vector <TcpSocket *> &getClients();

};


#endif //ZHAKAL_SERVER_H
