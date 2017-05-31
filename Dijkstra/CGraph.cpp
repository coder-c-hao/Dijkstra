#include "CGraph.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <climits>

bool pVertexComp(CVertex*, CVertex*);
bool pVertexRevComp(CVertex*, CVertex*);
bool pVertexCompRate(CVertex*, CVertex*);

// Ĭ�Ϲ��캯��,�����������ͼ
CGraph::CGraph(int nVertex, int nEdge)
{
	// ��ʼ�������������
	numVertex = nVertex;
	numEdge = nEdge;

	// ���յ�ǰʱ�����������
	srand((unsigned int)time(0));

	// ����nVertex������,����IDΪi(i=0,1,2,...,nVertex-1)
	for (int i = 0; i < nVertex; i++)
	{
		CVertex * vertex = new CVertex(i);
		mapVID_Vertex.insert(pair<const int, CVertex *>(i, vertex));
	}

	int headID; // �ߵ�ͷ������ID
	int tailID; // �ߵ�β������ID
	int weight; // �ߵ�Ȩ��
	int capacity;   // �ߵĴ�������

					// ����nEdge�������
	for (int i = 0; i < nEdge; i++)
	{
		// β������ID����ΪnVertex-1
		while ((tailID = rand() % nVertex) == nVertex - 1)
		{
			continue;
		}
		// ͷ������ID����β������ID(��ֹ˫���),����ͷ������ID������β������ID��ͬ
		while ((headID = tailID + rand() % (nVertex - tailID)) == tailID)
		{
			continue;
		}

		weight = rand() % 10 + 1;   // �����Ȩ�ط�ΧΪ 1 ~ 10
		capacity = rand() % 20 + 1; // ����Ĵ�������Ϊ 1 ~ 20

		CEdge * edge = new CEdge(tailID, headID, weight, capacity);

		// ����,��ֹ�����ظ���
		bool isExit = false;
		list<CEdge*>::iterator l1;
		if (!IncidentList.empty()) {
			for (l1 = IncidentList.begin(); l1 != IncidentList.end(); l1++) {
				if ((*l1)->getTail() == tailID && (*l1)->getHead() == headID) {
					isExit = true;
					break;
				}
			}
		}
		if (!isExit) {
			IncidentList.push_back(edge);
			mapVID_Vertex[tailID]->VListEdge.push_back(edge);
		}
		else
			i--;
	}

	// ��¼�붥������ĳ��ȱ�
	for (int key = 0; key < nVertex; key++)
	{
		list<CEdge*> edgeList = mapVID_Vertex[key]->VListEdge;
		mapVID_listEdge.insert(pair<const int, list<CEdge*> >(key, edgeList));
	}

	int breakVertex;    // ����ȶ���
						// ѭ�������ʹ������ͨͼ
	while ((breakVertex = travel()) != -1) {
		headID = breakVertex;
		tailID = rand() % headID;
		weight = rand() % 10 + 1;
		capacity = rand() % 20 + 1;
		CEdge * edge = new CEdge(tailID, headID, weight, capacity);
		IncidentList.push_back(edge);   // ���±��б�
		mapVID_Vertex[tailID]->VListEdge.push_back(edge);   // ���¶�������б�
		mapVID_listEdge[tailID].push_back(edge);    // ���³���map��¼
		numEdge++;  // ���±���Ŀ
	}
}

// ���캯��,�������ͨ����ͼ
CGraph::CGraph(string gType, int nVertex, int nEdge)
{
	// ��ʼ�������������
	numVertex = nVertex;
	numEdge = nEdge;

	// ���յ�ǰʱ�����������
	srand((unsigned int)time(0));

	// ����nVertex������,����IDΪi(i=0,1,2,...,nVertex-1)
	for (int i = 0; i < nVertex; i++)
	{
		CVertex * vertex = new CVertex(i);
		mapVID_Vertex.insert(pair<const int, CVertex *>(i, vertex));
	}

	int headID; // �ߵ�ͷ������ID
	int tailID; // �ߵ�β������ID
	float rate; // �ߵ�ͨ����
	int capacity;   // �ߵĴ�������

					// ����nEdge�������
	for (int i = 0; i < nEdge; i++)
	{
		// β������ID����ΪnVertex-1
		while ((tailID = rand() % nVertex) == nVertex - 1)
		{
			continue;
		}
		// ͷ������ID����β������ID(��ֹ˫���),����ͷ������ID������β������ID��ͬ
		while ((headID = tailID + rand() % (nVertex - tailID)) == tailID)
		{
			continue;
		}
		// �����ͨ���ʷ�ΧΪ (0.1,1]
		rate = (rand() % 10 + 1) / 10.0;
		capacity = rand() % 20 + 1;

		CEdge * edge = new CEdge(tailID, headID, rate, capacity);

		// ����,��ֹ�����ظ���
		bool isExit = false;
		list<CEdge*>::iterator l1;
		if (!IncidentList.empty()) {
			for (l1 = IncidentList.begin(); l1 != IncidentList.end(); l1++) {
				if ((*l1)->getTail() == tailID && (*l1)->getHead() == headID) {
					isExit = true;
					break;
				}
			}
		}
		if (!isExit) {
			IncidentList.push_back(edge);
			mapVID_Vertex[tailID]->VListEdge.push_back(edge);
		}
		else
			i--;
	}

	// ��¼�붥������ĳ��ȱ�
	for (int key = 0; key < nVertex; key++)
	{
		list<CEdge*> edgeList = mapVID_Vertex[key]->VListEdge;
		mapVID_listEdge.insert(pair<const int, list<CEdge*> >(key, edgeList));
	}

	int breakVertex;    // ����ȶ���
						// ѭ�����ӱ�������ͨͼ
	while ((breakVertex = travel()) != -1) {
		headID = breakVertex;
		tailID = rand() % headID;
		rate = (rand() % 10 + 1) / 10.0;
		capacity = rand() % 20 + 1;
		CEdge * edge = new CEdge(tailID, headID, rate, capacity);
		IncidentList.push_back(edge);   // ���±��б�
		mapVID_Vertex[tailID]->VListEdge.push_back(edge);   // ���¶�������б�
		mapVID_listEdge[tailID].push_back(edge);    // ���³���map��¼
		numEdge++;  // ���±���Ŀ
	}
}


// ��������,�ͷ�new�����Ķ�����ߵĿռ�
CGraph::~CGraph()
{
	// �ͷŶ���ռ�
	map<int, CVertex*>::iterator i1, iend1;
	iend1 = mapVID_Vertex.end();
	for (i1 = mapVID_Vertex.begin(); i1 != iend1; i1++) {
		delete (*i1).second;
	}
	// �ͷű߿ռ�
	list<CEdge*>::iterator i2, iend2;
	iend2 = IncidentList.end();
	for (i2 = IncidentList.begin(); i2 != iend2; i2++) {
		delete (*i2);
	}
}

// ���¶��㺯��
void CGraph::Update(int v)
{
	list<CEdge*> lEdge = mapVID_listEdge[v];  // ��ȡ����v�����г��ȱ�
	list<CEdge*>::iterator i, iend;
	iend = lEdge.end();
	for (i = lEdge.begin(); i != iend; i++)  // ��������ÿһ������
	{
		int w = (*i)->getWeight();  // ��ȡ��Ȩ��
		CVertex* h = mapVID_Vertex[(*i)->getHead()];    // ��ȡ��ͷ������
		CVertex* t = mapVID_Vertex[v];  // ��ȡ����v
										// �ж�Ȩ���Ƿ��С,���¾���,��ǰ��ָ��ָ��v
		if (t->d + w < h->d)
		{
			h->d = t->d + w;
			h->p = mapVID_Vertex[v];    // ���ñ�ͷ�������ǰ��ָ��
		}
	}
}

// ������¶��㺯��
void CGraph::UpdateRev(int v)
{
	list<CEdge*> lEdge = mapVID_listRevEdge[v]; // ��ȡ����v��������ȱ�
	list<CEdge*>::iterator i, iend;
	iend = lEdge.end();
	for (i = lEdge.begin(); i != iend; i++) {   // ��������ÿһ������
		int w = (*i)->getWeight();  // ��ȡ��Ȩ��
		CVertex* t = mapVID_Vertex[(*i)->getTail()];    // ��ȡ��β������
		CVertex* h = mapVID_Vertex[v];  // ��ȡ����v
										// �ж�Ȩ�ز��Ƿ��С,�����¾���
		if (h->d_temp - w > t->d_temp) {
			t->d_temp = h->d_temp - w;
			t->p_rev = h;
		}
	}
}

// ���ͨ���ʰ汾,���¶��㺯��
void CGraph::Update(int v, string type)
{
	list<CEdge*> lEdge = mapVID_listEdge[v];  // ��ȡ����v���������ڱ�
	list<CEdge*>::iterator i, iend;
	iend = lEdge.end();
	for (i = lEdge.begin(); i != iend; i++)  // �������ڵ�ÿһ������
	{
		float r = (*i)->getRate();  // ��ȡ��ͨ����
		CVertex* h = mapVID_Vertex[(*i)->getHead()];    // ��ȡͷ������
		CVertex* t = mapVID_Vertex[v];  // ��ȡ����v
										// �ж�ͨ�����Ƿ����,����ͨ����,��ǰ��ָ��ָ��v
		if (t->dRate * r > h->dRate)
		{
			h->dRate = t->dRate * r;
			h->p = mapVID_Vertex[v];
		}
	}
}

// �������ƺ���,ɾ��С��bandLimit�ı�,����mapVID_listEdge
void CGraph::bandWidthLimit(int limit)
{
	int tempTail, tempHead; // ��ʱ��¼Ҫɾ���ıߵ�ͷβ����
	list<CEdge*>::iterator lc, lct;
	for (lc = IncidentList.begin(); lc != IncidentList.end(); lc++) {
		// �����ߵļ���,ɾ�����д���С��limit�ı�,����mapVID_listEdge�и���
		if ((*lc)->getCapacity() < limit) {
			tempTail = (*lc)->getTail();
			tempHead = (*lc)->getHead();
			for (lct = mapVID_listEdge[tempTail].begin(); lct != mapVID_listEdge[tempTail].end(); lct++) {
				if ((*lct)->getHead() == tempHead) {
					mapVID_listEdge[tempTail].remove(*lct);
					break;
				}
			}
		}
	}
}

// Ȩ��Dijkstra�㷨����
void CGraph::DijkstraAlg(int s)
{
	// Ѱ���㷨����ڶ��㲢��ʼ����ʱ����б�
	map<int, CVertex*>::iterator i, iend;
	iend = mapVID_Vertex.end();
	for (i = mapVID_Vertex.begin(); i != iend; i++)
	{
		if (i->second->ID == s)
			i->second->d = 0;
		listTempMark.push_back(i->second);
	}

	Update(s);	// ���³���ڶ��������������

	while (!listTempMark.empty())
	{
		listTempMark.sort(pVertexComp);	 // ��ʣ�ඥ�㰴d��������
		int j = (*listTempMark.begin())->ID;  // ��ȡ��̶����ID
		listTempMark.pop_front();  // ����̶����Ƴ���ʱ�б�
		Update(j);  // ������һ�ָ���
	}

	// ����CPath����,�����·����Ϣ
	CVertex* sVertex = mapVID_Vertex[0];
	CVertex* eVertex = mapVID_Vertex[numVertex - 1];
	CPath path(sVertex, eVertex);
	path.showPathInConsole();
	std::cout << std::endl;
}

// ��Դ�������·Ȩ��Dijkstra�㷨
void CGraph::DijkstraAlg(int s, int e)
{
	// Ѱ���㷨����ڶ��㲢��ʼ����ʱ����б�
	map<int, CVertex*>::iterator i, iend;
	iend = mapVID_Vertex.end();
	for (i = mapVID_Vertex.begin(); i != iend; i++)
	{
		if (i->second->ID == s)
			i->second->d = 0;
		listTempMark.push_back(i->second);
	}

	Update(s);	// ���³���ڶ��������������

	while (!listTempMark.empty())
	{
		listTempMark.sort(pVertexComp);	 // ��ʣ�ඥ�㰴d��������
		int j = (*listTempMark.begin())->ID;  // ��ȡ��̶����ID
		listTempMark.pop_front();  // ����̶����Ƴ���ʱ�б�
								   // �ҵ��޵�,ֹͣ����
		if (j == e) {
			std::cout << "�ҵ��޵� " << j << " , ����·������:" << std::endl;
			break;
		}
		Update(j);  // ������һ�ָ���
	}

	// ����CPath����,�����·����Ϣ
	CVertex* sVertex = mapVID_Vertex[s];
	CVertex* eVertex = mapVID_Vertex[e];
	CPath path(sVertex, eVertex);
	path.showPathInConsole();
	std::cout << std::endl;
}

// ���ͨ����Dijkstra�㷨����
void CGraph::DijkstraAlg(int s, string type)
{
	// Ѱ���㷨����ڶ��㲢��ʼ����ʱ����б�
	map<int, CVertex*>::iterator i, iend;
	iend = mapVID_Vertex.end();
	for (i = mapVID_Vertex.begin(); i != iend; i++)
	{
		if (i->second->ID == s)
			i->second->dRate = 1;
		listTempMark.push_back(i->second);
	}

	Update(s, "rate");	// ���³���ڶ��������������

	while (!listTempMark.empty())
	{
		listTempMark.sort(pVertexCompRate);	 // ��ʣ�ඥ�㰴dRate��������
		int j = (*listTempMark.begin())->ID;  // ��ȡ���ͨ���ʶ����ID
		listTempMark.pop_front();  // �����ͨ���ʶ����Ƴ���ʱ�б�
		Update(j, "rate");  // ������һ�ָ���
	}
}

// ������ʽ��ʾͼ����Ϣ
void CGraph::showGraphInConsole()
{
	using std::cout;
	using std::endl;
	list<CEdge*>::iterator lc;
	for (int key = 0; key < getNumVertex(); key++) {
		cout << key;
		if (!mapVID_listEdge[key].empty()) {
			for (lc = mapVID_listEdge[key].begin(); lc != mapVID_listEdge[key].end(); lc++) {
				cout << "-->" << (*lc)->getHead();
			}
		}
		cout << endl;
	}
}

// ����ͼ,�鿴�Ƿ���ͨͼ,˼·:��ڵ�ɵ�������ȫ������
int CGraph::travel()
{
	list<CEdge*>::iterator lc;
	map<int, list<CEdge*> >::iterator mi, ml;
	// ���ÿһ������������ȱ�
	for (int key = 1; key < numVertex; key++) {
		bool hasInDegree = false;
		// ������������ڽӱ������޸ö���
		for (ml = mapVID_listEdge.begin(); ml != mapVID_listEdge.end(); ml++) {
			if (!(*ml).second.empty()) {
				for (lc = (*ml).second.begin(); lc != (*ml).second.end(); lc++) {
					if ((*lc)->getHead() == key) {
						hasInDegree = true;
						break;
					}
				}
			}
			// ����ѭ���ҵ��ö������˳�ѭ��
			if (hasInDegree)
			{
				break;
			}
		}
		// ����û����ȱ�,������IDֵ
		if (!hasInDegree)
		{
			return key;
		}
	}
	// ÿһ�����㶼����ȱ�,����-1��ʾͼ��ͨ
	return -1;
}

// ��ʾ����Dijstra�㷨��ͼ����ڵ㵽�������ȫ��·��
void CGraph::showDijPathInConsole()
{
	CVertex* sVertex = mapVID_Vertex[0];
	CVertex* eVertex;
	for (int key = 1; key < numVertex; key++) {
		eVertex = mapVID_Vertex[key];
		CPath path(sVertex, eVertex);
		path.showPathInConsole();
	}
}

// listTempMark.sort(pVertexComp) ��ָ���б�dֵ��С��������
bool pVertexComp(CVertex* x, CVertex* y)
{
	if (x->d < y->d)
		return true;
	else
		return false;
}

// listTempMark.sort(pVertexComp) ��ָ���б�dֵ��С��������
bool pVertexRevComp(CVertex* x, CVertex* y)
{
	if (x->d_temp < y->d_temp)
		return true;
	else
		return false;
}

// listTempMark.sort(pVertexCompRate) ��ָ���б�dRateֵ�Ӵ�С����
bool pVertexCompRate(CVertex* x, CVertex* y)
{
	if (x->dRate > y->dRate)
		return true;
	else
		return false;
}

// ��ʼ��mapVID_listRevEdge()����
void CGraph::initMapVID_listRevEdge()
{
	int tempHead;
	list<CEdge*> tempCEdge;
	list<CEdge*>::iterator lc;
	for (int id = 0; id < numVertex; id++)
		mapVID_listRevEdge.insert(pair<const int, list<CEdge*> >(id, tempCEdge));
	for (lc = IncidentList.begin(); lc != IncidentList.end(); lc++) {
		tempHead = (*lc)->getHead();
		mapVID_listRevEdge[tempHead].push_back(*lc);
	}
}

// ˫��Dijkstra�㷨
void CGraph::BidDijkstraAlg(int s, int e)
{
	using std::cout;
	using std::endl;

	// ��ʼ��������ȱ�mapVID_listRevEdge
	initMapVID_listRevEdge();

	clock_t startTime = clock();    // ��ʼ��ʱ��

									// Ѱ���㷨����ڶ�������ڶ��㲢��ʼ����ʱ����б�
	list<CVertex*> listTempRevMark;
	map<int, CVertex*>::iterator i, iend;
	iend = mapVID_Vertex.end();
	for (i = mapVID_Vertex.begin(); i != iend; i++)
	{
		if (i->second->ID == s)
		{
			i->second->d = 0;
			i->second->flag = 1;
		}
		else if (i->second->ID == e)
		{
			i->second->d_temp = INT_MAX / 2;
			i->second->flag = 2;
		}
		listTempMark.push_back(i->second);
		listTempRevMark.push_back(i->second);
	}

	Update(s);  // ������ڵ��ڽӵ�
	UpdateRev(e);   // ���³��ڵ��ڽӵ�

	bool flag = true;   // ��������Dijkstra�㷨���л�
	list<CEdge*>::iterator lc;

	while (!listTempMark.empty())
	{
		if (flag)
		{
			listTempMark.sort(pVertexComp);
			int j = (*listTempMark.begin())->ID;
			listTempMark.pop_front();   // �̶�����j
										// ������ʵ�����������̶��Ķ���,��������
			if (mapVID_Vertex[j]->flag == 2)
			{
				break;
			}
			Update(j);
			mapVID_Vertex[j]->flag = 1;
		}
		else
		{
			listTempRevMark.sort(pVertexRevComp);   // �˴�Ӧ��d_temp��С��������
			int j = (*(--listTempRevMark.end()))->ID;
			listTempRevMark.pop_back(); // �̶�����j
										// ������ʵ�����������̶��Ķ���,��������
			if (mapVID_Vertex[j]->flag == 1)
			{
				break;
			}
			UpdateRev(j);
			mapVID_Vertex[j]->flag = 2;
		}
		flag = !flag;
	}

	// ö��·����ȡ�ؾ��ı�,Ѱ�Ҹñߵ�β��ansTail��ͷ��ansHead
	int temp = INT_MAX;
	int ansTail = -1, ansHead = -1;
	for (lc = IncidentList.begin(); lc != IncidentList.end(); lc++)
	{
		CVertex* tempHead = mapVID_Vertex[(*lc)->getHead()];
		CVertex* tempTail = mapVID_Vertex[(*lc)->getTail()];
		int d_rev = (INT_MAX / 10 == tempHead->get_dtemp() ? INT_MAX / 10 : INT_MAX / 10 - tempHead->get_dtemp());
		if (temp > (tempTail->get_d() + (*lc)->getWeight() + d_rev)) {
			temp = tempTail->get_d() + (*lc)->getWeight() + d_rev;
			ansTail = tempTail->ID;
			ansHead = tempHead->ID;
		}
	}


	clock_t endTime = clock();      // ������ʱ��

									// ���·����Ϣ
	list<CVertex*> path;
	list<CVertex*>::iterator l;
	CVertex* ansTailVertex = mapVID_Vertex[ansTail];
	CVertex* ansHeadVertex = mapVID_Vertex[ansHead];
	CVertex* tempVertexPointer = ansTailVertex;
	do {
		path.push_back(tempVertexPointer);
		tempVertexPointer = tempVertexPointer->p;
	} while (tempVertexPointer != nullptr);
	path.reverse();
	tempVertexPointer = ansHeadVertex;
	do {
		path.push_back(tempVertexPointer);
		tempVertexPointer = tempVertexPointer->p_rev;
	} while (tempVertexPointer != nullptr);
	cout << "Vertex(" << (*path.begin())->ID << ")";
	for (l = ++path.begin(); l != path.end(); l++) {
		cout << "-->Vertex(" << (*l)->ID << ")";
	}
	cout << endl;
	std::cout << "˫��Dijkstra�㷨��ʱ: " << (endTime - startTime) * 1000 / CLOCKS_PER_SEC << " ms." << std::endl;
	std::cout << std::endl;
}

void CGraph::initVertexMap()
{
	listTempMark.clear();
	CVertex* tempVertex;
	for (int key = 0; key < numVertex; key++) {
		tempVertex = mapVID_Vertex[key];
		tempVertex->d = INT_MAX / 10;
		tempVertex->d_temp = tempVertex->d;
		tempVertex->flag = 0;
		tempVertex->dRate = 0.0;
		tempVertex->p = nullptr;
		tempVertex->p_rev = nullptr;
	}
}