#pragma once
#ifndef CGRAPH_H_
#define CGRAPH_H_
#include <map>
#include <list>
#include <vector>
#include <climits>
#include <string>
using std::list;
using std::map;
using std::pair;
using std::vector;
using std::string;

// ����
class CEdge
{
private:
	int tail;	// β������ID
	int head;	// ͷ������ID
	int weight;	// �߾���
	float rate; // ��ͨ����
	int capacity;   // ����Լ��
public:
	CEdge(int t, int h, int w, int c = 0) { tail = t; head = h; weight = w; capacity = c; rate = 1.0; };	// Ȩ�ر߹��캯��
	CEdge(int t, int h, float r, int c = 0) { tail = t; head = h; rate = r; capacity = c; weight = 0; };  // ͨ���ʱ߹��캯��
	~CEdge() {};	// ��������

	int getWeight() const { return weight; };
	int getHead() const { return head; };
	int getTail() const { return tail; };
	int getCapacity() const { return capacity; };
	float getRate() const { return rate; };

	void setTail(int t) { tail = t; };
	void setHead(int h) { head = h; };
	void setWeight(int w) { weight = w; };
	void setRate(float r) { rate = r; };
	void setCapacity(int c) { capacity = c; };
};

// ������
class CVertex
{
public:
	int d;		// ������ʼ��ľ���
	int d_temp; // �����յ�ľ���,���ڷ���Dijkstra
	int ID;		// �����ID
	int flag;   // ����˫��Dijkstra�㷨����Ƿ��ѱ�����
	float dRate;    // ͨ����"·��"
	CVertex* p;		// ָ��Ŀǰ�����ǰ������
	CVertex* p_rev;     // ����Dijkstraָ��Ŀǰ����ǰ������
	list<CEdge*> VListEdge;     // �ö���ĳ��ȱ��б�

	CVertex(int id) { d = INT_MAX / 10; d_temp = d; p = nullptr; p_rev = nullptr; ID = id; dRate = 0.0; flag = 0; }
	~CVertex() {};	// ��������

	int get_d() const { return d; };
	int get_dtemp() const { return d_temp; };
};

// ͼ��
class CGraph
{
private:
	int numVertex;			// ������Ŀ
	int numEdge;			// ����Ŀ
	list<CEdge*> IncidentList;	// �ߵ��б�
	map<int, CVertex*> mapVID_Vertex;  // ���еĶ���
	list<CVertex*> listTempMark;	// ��ʱ��ǵĶ��㼯��
	map<int, list<CEdge*> > mapVID_listEdge;  // ��¼�붥������ĳ��ȱ�
	map<int, list<CEdge*> > mapVID_listRevEdge; // ��¼�붥���������ȱ�

	void Update(int VID);		// ���¶������
	void UpdateRev(int VID);    // ������¶������
	void Update(int VID, string type);  // ���ͨ���ʰ汾���¶������

	int travel();    // ����Ƿ�Ϊ��ͨͼ

	void initMapVID_listRevEdge();  // ��ʼ��mapVID_listRevEdge
public:
	friend class CPath;

	CGraph(int nVertex = 6, int nEdge = 9); // Ĭ�Ϲ��캯��,�������ͼ
	CGraph(string type, int nVertex = 6, int nEdge = 9); // ���캯��,�������ͨ����ͼ
														 // CGraph(char* inputFile);	// �����ļ�
														 // CGraph(list<CEdge*> listEdge);	// �����ߵ��б�
	CGraph(CGraph &) {};		// ���ƹ��캯��
	~CGraph();			// ��������

	int getNumVertex() { return numVertex; };
	int getNumEdge() { return numEdge; };

	void initVertexMap();   // ��ʼ�����㼯,���ڱȽ��㷨Ч��

	void bandWidthLimit(int bandLimit); // �������ƺ���

	void DijkstraAlg(int VID);  // ����Dijkstra�㷨
	void DijkstraAlg(int sVID, int eVID);   // ��Դ�������·Dijkstra�㷨
	void DijkstraAlg(int VID, string type); // ���ͨ����Dijkstra�㷨
	void BidDijkstraAlg(int sVID, int eVID);    // ˫��Dijkstra�㷨

	void showGraphInConsole();   // ������������ʾ���
	void showDijPathInConsole();    // ���������·��Dijstra�㷨��ͼ·����ʾ��������
};

// ·����
class CPath
{
private:
	list<CVertex*> path;    // ��¼·��
public:
	CPath(CVertex* s, CVertex* e);  // ��ȡ����·��
	~CPath() {};                     // Ĭ����������
	void showPathInConsole();    // ��ʾ����·��
};

#endif