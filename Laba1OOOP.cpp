#include <iostream>
#include "Graph.h"
#include "IPaddress.h"
#include "GraphList.h"
#include "GraphMatrix.h"
void TestIP(){
	IpAddress address;

	address.generateRandomIpV4();

	IpAddress host;

	host.generateRandomIpV4();

	std::cout << address.checkIfInSubnetIpV4(host, 30);
}
void TestGraph() {
	GraphList<int> graph1(10);

	graph1.AddVertex(2);

	graph1.AddVertex(4);

	graph1.AddVertex(7);

	std::cout<<graph1.Distance;

	IpAddress host;

	host.generateRandomIpV6();

	GraphMatrix<IpAddress> graph2(10);

	graph2.AddVertex(host);

}
int main()
{
	//TestGraph();
	//TestGraph();
    
}