//
// Created by Igor on 16.10.2018.
//

#include "Server.h"

Server::Server()
{
	clients.clear();
	selector.clear();
	//selector.add(server);
}

Server::Server(size_t port, bool IsAccept, IpAddress ip, bool blocking)
{
	clients.clear();
	selector.clear();
	selector.add(server);
	this->server.setBlocking(blocking);
	if (IsAccept == true)
	{
		this->server.listen(port, ip);
		bool running = true;
		while (running) //ожидание подключения
		{
			TcpSocket *client = new TcpSocket;
			if (this->server.accept(*client) == Socket::Done)
			{
				this->clients.push_back(client);
				running = false;
			}
			else delete client;
		}
	}
	else
	{
		this->server.listen(port, ip);
	}
}

bool Server::Listen(size_t port, IpAddress ip, bool IsAccept)
{
	if (IsAccept)
	{
		this->server.listen(port, ip);
		selector.add(server);
		TcpSocket *client = new TcpSocket;
		cout << "kek" << endl;
			if (this->server.accept(*client) == Socket::Done)
			{
				cout << "have a connect" << endl;
				this->clients.push_back(client);
				selector.add(*client);
				return true;
			}
			else
			{
				delete client;
				return false;
			}

	}
	else
	{
		Socket::Status status = this->server.listen(port, ip);
		if (status == Socket::Status::Done)
		{
			selector.add(server);
			return true;
		}
		else
		{
			switch (status)
			{
				case Socket::Status::Disconnected:
				{
					cout << "The TCP socket has been disconnected." << endl;
					break;
				}
				case Socket::Status::Partial:
				{
					cout << "The socket sent a part of the data." << endl;
					break;
				}
				case Socket::Status::NotReady:
				{
					cout << "The socket is not ready to send / receive data yet." << endl;
					break;
				}
				default:
				{
					cout << "An unexpected error happened." << endl;
					break;
				}
			}
		}
	}
	return false;
}

bool Server::Accept()
{
		TcpSocket *client = new TcpSocket;
		Socket::Status status = this->server.accept(*client);
		if (status == Socket::Status::Done)
		{
			cout << "have a connect" << endl;
			this->clients.push_back(client);
			selector.add(*client);
			return true;
		}
		else
		{
			switch (status)
			{
				case Socket::Status::Disconnected:
				{
					cout << "The TCP socket has been disconnected." << endl;
					break;
				}
				case Socket::Status::Partial:
				{
					cout << "The socket sent a part of the data." << endl;
					break;
				}
				case Socket::Status::NotReady:
				{
					cout << "The socket is not ready to send / receive data yet." << endl;
					break;
				}
				default:
				{
					cout << "An unexpected error happened." << endl;
					break;
				}
			}
			delete client;
			return false;
		}
}

vector <IpAddress> Server::getIpClients()
{
	vector <IpAddress> Ips;
	for (int i = 0; i < this->clients.size(); i++)
	{
		Ips[i] = this->clients[i]->getRemoteAddress();
	}
	return Ips;
}

vector <int> Server::getPortClients()
{
	vector <int> Ports;
	for (int i = 0; i < this->clients.size(); i++)
	{
		Ports[i] = this->clients[i]->getRemotePort();
	}
	return Ports;
}

bool Server::Send(int number, int reciever)
{
	Packet packet;
	packet << number;

	if (reciever == -1)
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			}
			else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{

		}
		else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}

bool Server::Send(string data, int reciever)
{
	Packet packet;
	packet << data;
	if (reciever == -1)
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			}
			else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{
			//continue;
		}
		else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}


bool Server::Send(double number, int reciever)
{
	Packet packet;
	packet << number;

	if (reciever == -1)
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			} else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{
			//continue;
		}
		else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}

bool Server::Send(bool logic, int reciever)
{
	Packet packet;
	packet << logic;

	if (reciever == -1)
	{

		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			}
			else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{
			//continue;
		}
		else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}

bool Server::Send(Packet packet, int reciever)
{
	if (reciever == -1)
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			} else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{
			//continue;
		} else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}

bool Server::Send(Transfer transfer, int reciever)
{
	Packet packet;
	packet << transfer.integer
	       << transfer.data
	       << transfer.f
	       << transfer.d
	       << transfer.logic;

	if (reciever == -1)
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			Socket::Status status = this->clients[i]->send(packet);
			if (status == Socket::Status::Done)
			{
				continue;
			} else
			{
				cout << i << " client ";
				check_status(status, i);
				return false;
			}
		}
	}
	else
	{
		Socket::Status status = this->clients[reciever]->send(packet);
		if (status == Socket::Status::Done)
		{
			//continue;
		}
		else
		{
			cout << reciever << " client ";
			check_status(status, reciever);
			return false;
		}
	}
	return true;
}

vector <int> Server::GetIntMessage(vector <bool>& check)
{
	Packet packet;
	vector <int> integer;
	check.clear();

	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			integer.push_back(0);
			check.push_back(false);
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet >> integer[i])
					{
						check.push_back(true);
					}
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
	return integer;
}

vector <string> Server::GetStringMessage(vector <bool> &check)
{
	Packet packet;
	vector <string> data;
	check.clear();

	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			data.push_back("");
			check.push_back(false);
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet >> data[i])
					{
						cout << "ura2" << endl;
						check[i] = true;
					}
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
	return data;
}


vector <double> Server::GetDoubleMessage(vector <bool> &check)
{
	Packet packet;
	vector <double> d;
	check.clear();
	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			d.push_back(0);
			check.push_back(false);
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet >> d[i])
					{
						check[i] = true;
					}
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
	return d;
}

vector <bool> Server::GetBoolMessage(vector <bool> &check)
{
	Packet packet;
	bool *b = new bool[this->clients.size()];
	check.clear();
	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			b[i] = 0;
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet >> b[i])
					{
						check.push_back(true);
					}
					else
					{
						b[i] = 0;
						check.push_back(false);
					}
				} else
				{
					check.push_back(false);
					b[i] = 0;
					check_status(status, i);
				}
			}
		}
	}

	vector <bool> result;
	for (int i = 0; i < this->clients.size(); i++)
		result.push_back(b[i]);

	return result;
}

vector <Packet> Server::GetPacketMessage(vector <bool> &check)
{
	Packet packet;
	vector <Packet> packets;
	check.clear();

	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			packets.push_back(packet);
			check.push_back(false);
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet)
					{
						packets[i] = packet;
						check[i] = true;
					}
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
	return packets;
}

vector <Transfer> Server::GetTransferMessage(vector <bool> &check)
{
	Packet packet;
	vector <Transfer> transfers;
	Transfer tr;
	tr.d = 0;
	tr.data = " ";
	tr.f = 0;
	tr.logic = false;
	tr.integer = 0;
	check.clear();

	if (selector.wait())
	{
		for (int i = 0; i < this->clients.size(); i++)
		{
			transfers.push_back(tr);
			check.push_back(false);
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = this->clients[i]->receive(packet);
				if (status == Socket::Status::Done)
				{
					if (packet >> transfers[i].integer
					           >> transfers[i].data
					           >> transfers[i].f
					           >> transfers[i].d
					           >> transfers[i].logic)
					{
						check[i] = true;
					}
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
	return transfers;
}

bool Server::DisconnectBack()
{
	if (this->clients.size() == 0)
		return false;
	selector.remove(*clients[clients.size()-1]);
	this->clients.back()->disconnect();
	this->clients.pop_back();
	return true;
}

bool Server::Disconnect(size_t number)
{
	if (number >= this->clients.size())
		return false;
	auto it = this->clients.begin();
	it += number;
	selector.remove(*this->clients[number]);
	this->clients[number]->disconnect();
	this->clients.erase(it);
	return true;
}

size_t Server::SizeOfClients()
{
	return this->clients.size();
}

void Server::SetBlock(bool blocking)
{
	this->server.setBlocking(blocking);
}

bool Server::IsBlocking()
{
	return this->server.isBlocking();
}

Packet Server::refreash_clients() //rewrite
{
	Packet packet;
	if (selector.wait())
	{
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (selector.isReady(*clients[i]))
			{
				Socket::Status status = clients[i]->receive(packet);
				if (status == Socket::Done)
				{
					return packet;
				}
				else
				{
					check_status(status, i);
				}
			}
		}
	}
}

bool Server::Disconnect(vector <size_t> numbers)
{
	for (size_t k = 0; k < numbers.size(); k++)
	{
		if (numbers[k] >= clients.size())
		{
			return false;
		}
	}
	sort(numbers.begin(), numbers.end());

	for (size_t k = 0; k < numbers.size(); k++)
	{
		Disconnect(numbers[k]);
		for (size_t i = k+1; i < numbers.size(); i++)
			numbers[i]--;
	}
	return true;
}

TcpListener &Server::getServer()
{
	return server;
}

SocketSelector &Server::getSelector()
{
	return selector;
}

vector <TcpSocket *> &Server::getClients()
{
	return clients;
}

void Server::check_status(Socket::Status status, size_t current)
{
	switch (status)
	{
		case Socket::Status::Disconnected:
		{
			Disconnect(current);
			cout << "The TCP socket has been disconnected." << endl;
			break;
		}
		case Socket::Status::Partial:
		{
			cout << "The socket sent a part of the data." << endl;
			break;
		}
		case Socket::Status::NotReady:
		{
			cout << "The socket is not ready to send / receive data yet." << endl;
			break;
		}
		default:
		{
			cout << "An unexpected error happened." << endl;
			break;
		}
	}
}





