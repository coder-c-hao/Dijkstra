#include "CGraph.h"
#include <iostream>
#include <ctime>
#define MAXITEM 7
#define VERTEX_NUM  1500
#define EDGE_NUM    1500

int main(int argc, char * argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	int chooseItem;

	cout << "�������к�ִ�ж�Ӧ��Ŀ:\n"
		<< "1. �������������ͨͼ\n"
		<< "2. ��Դ�������·�㷨\n"
		<< "3. ���ͨ����·���㷨\n"
		<< "4. ����Լ�����·�㷨\n"
		<< "5. ˫��Dijkstra�㷨\n"
		<< "6. ����Dijkstra�㷨\n"
		<< "7. �ȽϾ���Dijkstra��˫��Dijkstra\n\n";

	do { cout << "ѡ��: "; cin >> chooseItem; } while (chooseItem < 1 || chooseItem > MAXITEM);

	if (chooseItem == 1)
	{
		cout << "1. �������������ͨͼ\n\n";
		CGraph digraph;
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		cout << "������ɵ�����ͼ������ʽ����:\n";
		digraph.showGraphInConsole();
		cout << endl;
	}
	else if (chooseItem == 2)
	{
		cout << "2. ��Դ�������·�㷨\n\n";
		CGraph digraph;
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		// cout << "������ɵ�����ͼ������ʽ����:\n";
		// digraph.showGraphInConsole();
		// cout << endl;
		int maxVertexID = digraph.getNumVertex() - 1;
		clock_t startTime = clock();    // ��ʼ��ʱ��
		digraph.DijkstraAlg(0, maxVertexID);  // ��Դ�����㷨
		clock_t endTime = clock();  // ������ʱ��
									// cout << "��ڵ㵽�ɴ������··������:\n";
									// digraph.showDijPathInConsole();
									// cout << endl;
		cout << "��Դ����Dijkstra�㷨��ʱ: " << endTime - startTime << " clocks." << endl;
	}
	else if (chooseItem == 3)
	{
		cout << "3. ���ͨ����·���㷨\n\n";
		CGraph digraph("rate");
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		cout << "������ɵ�����ͼ������ʽ����:\n";
		digraph.showGraphInConsole();
		cout << endl;
		digraph.DijkstraAlg(0, "rate"); // ���ͨ�����㷨
		cout << "��ڵ㵽�ɴ������··������:\n";
		digraph.showDijPathInConsole();
		cout << endl;
	}
	else if (chooseItem == 4)
	{
		cout << "4. ����Լ�����·�㷨\n\n";
		CGraph digraph;
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		cout << "������ɵ�����ͼ������ʽ����:\n";
		digraph.showGraphInConsole();
		cout << endl;
		digraph.bandWidthLimit(5);
		digraph.DijkstraAlg(0);
		cout << "��ڵ㵽�ɴ������··������:\n";
		digraph.showDijPathInConsole();
		cout << endl;
	}
	else if (chooseItem == 5)
	{
		cout << "5. ˫��Dijkstra�㷨\n\n";
		CGraph digraph;
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		cout << "������ɵ�����ͼ������ʽ����:\n";
		digraph.showGraphInConsole();
		cout << endl;
		int maxVertexID = digraph.getNumVertex() - 1;
		digraph.BidDijkstraAlg(0, maxVertexID);
		cout << endl;
	}
	else if (chooseItem == 6)
	{
		cout << "6. ��Dijkstra�㷨\n\n";
		CGraph digraph;
		cout << "��������: " << digraph.getNumVertex() << endl;
		cout << "�ߵ�����: " << digraph.getNumEdge() << endl;
		cout << endl;
		cout << "������ɵ�����ͼ������ʽ����:\n";
		digraph.showGraphInConsole();
		cout << endl;
		clock_t startTime = clock();    // ��ʼ��ʱ��
		digraph.DijkstraAlg(0);
		clock_t endTime = clock();      // ������ʱ��
										// cout << "��ڵ㵽�ɴ������··������:\n";
										// digraph.showDijPathInConsole();
		cout << endl;
		cout << "����Dijkstra�㷨��ʱ: " << endTime - startTime << " clocks." << endl;
	}
	else if (chooseItem == 7)
	{
		cout << "7. �ȽϾ���Dijkstra��˫��Dijkstra\n\n" << endl;
		CGraph digraph(VERTEX_NUM, EDGE_NUM);
		int maxVertexID = digraph.getNumVertex() - 1;
		clock_t startTime, endTime;

		cout << "��Դ����:\n";
		startTime = clock();
		digraph.DijkstraAlg(0, maxVertexID);
		endTime = clock();
		cout << "��Դ����Dijkstra�㷨��ʱ: " << (endTime - startTime) * 1000 / CLOCKS_PER_SEC << " ms." << endl;
		digraph.initVertexMap();
		cout << "--------------------------------------------------------------------------" << endl;

		cout << "�����㷨:\n";
		startTime = clock();
		digraph.DijkstraAlg(0);
		endTime = clock();
		cout << "����Dijkstra�㷨��ʱ: " << (endTime - startTime) * 1000 / CLOCKS_PER_SEC << " ms." << endl;
		digraph.initVertexMap();
		cout << "--------------------------------------------------------------------------" << endl;

		cout << "˫���㷨:\n";
		digraph.BidDijkstraAlg(0, maxVertexID);
		digraph.initVertexMap();
	}
	return 0;
}