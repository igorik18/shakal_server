#include "Server.h"
int main()
{
    Server server;
    server.SetBlock(true);
	bool s = true;
	size_t counter = 0;
    cout << server.Listen(1261, IpAddress::Any, false) << endl;
    while (s)
    {
	    if (server.getSelector().wait())
	    {
		    cout << "hi" << endl;
		    if (server.getSelector().isReady(server.getServer()))
		    {
			    if (server.Accept())
			    {
				    cout << "CONNECTED!!!" << endl;
				    cout << "clients: " << server.getClients().size() << endl;

				    //creating peremennyx
				    vector <bool> check;
				    vector <int> integer;
				    vector <string> stroka;
				    vector <double> doble;
				    vector <bool> bol;
				    vector <Packet> pack;
				    vector <Transfer> trans;



				    // giving mes
				    integer = server.GetIntMessage(check);
				    cout << integer[counter] << endl;
				    stroka = server.GetStringMessage(check);
				    cout << stroka[counter] << endl;
				    doble = server.GetDoubleMessage(check);
				    cout << doble[counter] << endl;
				    bol = server.GetBoolMessage(check);
				    cout << bol[counter] << endl;
				    pack = server.GetPacketMessage(check);
				    int int_for_pack;
				    string str_for_pack;
				    bool bol_for_pack;
				    float flot_for_pack;
				    double dob_for_pack;
				    pack[counter] >> int_for_pack >> str_for_pack >> bol_for_pack >> dob_for_pack;
				    cout << int_for_pack << " "
				         << str_for_pack << " "
				         << bol_for_pack << " "
				         << dob_for_pack << endl;
				    trans = server.GetTransferMessage(check);
				    cout << trans[counter].integer << " "
				         << trans[counter].logic << " "
				         << trans[counter].f << " "
				         << trans[counter].data << " "
				         << trans[counter].d << endl;


				    //sending mes
				    Packet packet;
				    Transfer transer;

				    transer.d = 10.632;
				    transer.data = "vaucher";
				    transer.f = 2.41;
				    transer.integer = 956;
				    transer.logic = true;

				    packet << 2 << "hutok" << true << 29.58;

				    cout << server.Send(4) << endl;
				    cout << server.Send(string("hehe")) << endl;
				    cout << server.Send(7.894) << endl;
				    cout << server.Send(true) << endl;
				    cout << server.Send(packet) << endl;
				    cout << server.Send(transer) << endl;


				    if (server.getClients().size() == 3)
				    {
					    vector <size_t > d = {0, 2};
					    server.Disconnect(d);
				    }


				    cout << "clients: " << server.getClients().size() << endl;
				    counter++;
			    }
		    }
		    else
		    {
		    	// running to all sockets
		    	server.refreash_clients();
		    	cout << "clients: " << server.getClients().size() << endl;
		    }
	    }
    }






    return 0;
}