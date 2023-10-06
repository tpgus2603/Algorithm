#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include<string>


//뉴욕 길찾기 프로그램 각 노드는 지역 간선의 가중치가 이동 거리
//두 개의 노드번호를 입력하면 최단거리로 이동하여 방문한 노드번호 출력 
using namespace std;

struct Edge {
	int to;  //도착 위치의 인덱스(도착지역)
	int  dst;  //간선의 거리   cf텍스트파일의 거리가 모두 정수형이기에 가중치(노드사이의 거리)를 float가 아닌 int형으로함 
};
struct Node {   //노드(위치) 마다 연결된 엣지의 리스트를 표현함 
	int  data;  //노드의 인덱스 
	vector<Edge> adList;  //각각의 노드와 연결된 간선들 나타내는 리스트

};

struct Graph {
	vector<Node> nodes;
	void addNode(int data) {  //노드 추가 
		nodes.push_back({ data });
	}
	void addEdge(int from, int to, int dst) {  //
		nodes[from].adList.push_back({ to,dst });
		//nodes[to].adList.push_back({ from,dst });  // 방향그래프인경우 from-to 간선만 인접리스트에 추가함 
	}
	void ShortPath(int start, int end) const { // 데이크스트라 알고리즘으로
		//미방문 지역중 시작 노드와 거리가 가까운 노드를 차례차례 방문
		struct NodeInfo { //노드의 인덱스와 해당 노드거리정보(루트노드로 부터거리) 저장된 노드정보 
			int node;
			int dst;
		};
		struct NodeInfoCompare {
			bool operator() (const  NodeInfo& a, const NodeInfo& b) {
				return a.dst > b.dst;
			}
		};
		priority_queue<NodeInfo, vector<NodeInfo>, NodeInfoCompare> open;  //열린상태(방문의 후보군) 최소힙에 넣음  
		vector<bool> closed(nodes.size(), false);	//부울 타입으로 닫힌상태 판정 해당 노드번호가 true이면 이미 방문한 노드임 
		vector<int> dList(nodes.size(), INT_MAX); //특정 노드번호에서 시작노드와의 최소거리가 담긴 정보 
		vector<int>parents(nodes.size(), -1);  // 부모노드 즉 방향그래프에서 to와 연결된 from노드가 담긴 배열 
		open.push({ start,0 });
		dList[start] = 0;
		while (!open.empty() && !closed[end]) { // 방문할 노드가 없을때 +end지점이 닫히지 않을때 반복 
			NodeInfo info = open.top();  //최소거리 정보 
			open.pop();
			if (closed[info.node]) continue; // 방문한 노드인경우 넘어감
			closed[info.node] = true;   //방문플래그
			for (auto edge : nodes[info.node].adList) { //edge=방문한 노드와 연결된 간선 
				int to = edge.to; //노드와 연결된 간선의 도착노드 정보
				if (closed[to])continue; //해당 노드가 방문한 노드인경우 넘어감 
				if (dList[to] > dList[info.node] + edge.dst) {//현재까지 시작노드와의 최소 거리(큐에서 팝한 노드+간선거리)보다 작은 경우
					parents[to] = info.node; //도착노드와 연결한 부모 노드 목록 추가 
					dList[to] = dList[info.node] + edge.dst;
					open.push({ to,dList[to] });//최소거리 노드 오픈목록에 넣기
				}//최소거리 갱신 
			}
		}
		if (!closed[end]) //최종 목적지가 방문되지 않는경우 (dest로 가는길이 없는경우)
			cout << "No path " << endl;
		else {
			cout << "Shortest path:" << endl;
			vector<int> Shortpath; //최단거리 경로 배열 
			int temp = end;
			while (temp != -1) { //부모노드가 없을떄까지 즉 temp가 -1이 아닐때까지 반복
				Shortpath.push_back(temp);  // 종착지 삽입 
				temp = parents[temp];   //종착지의 부모노드 
			}
			for (int i = Shortpath.size() - 1; i >= 0; i--)
				cout << Shortpath[i] << " "; // 해당경로는 끝에서 부터 시작까지의 순서로 배열에 삽입 됐으므로 끝에서부터 반대로 출력 
		}
	}
};

int main() {
	Graph loadMap;
	ifstream NewYork("USA-road-d.NY.gr.txt"); //텍스트 파일의 이름
	int nodeSize, edgeSize; //텍스트파일에 적힌 노드와 간선 크기 읽기 
	int start, end;
	cout << "enter start point and end point: "; //시작지점 끝지점 입력
	cin >> start >> end;
	if (NewYork.is_open()) { //성공적으로 열렸는지 확인 +열렸으면 노드 개수 와 엣지 개수 정보 받기 
		NewYork >> nodeSize;
		NewYork >> edgeSize;
	}
	else {
		cout << "File open failed";  //파일 여는데 실패한경우 프로그램 종료 
		return 0;
	}

	loadMap.nodes = vector<Node>(nodeSize + 1); //노드 크기 정해줌 (텍스트파일은 1번부터 시작이기떄문에 0번인덱스를 뺴고 1만큼 크게 노드 사이즈를 정함)
	cout << "wait for load txt...." << endl; //모든 텍스트파일의 모든edge를 추가하는데 시간이 오래걸림 
	while (NewYork.peek() != EOF) {    //텍스트파일의 끝(EOF)만나기 전까지 반복 
		char flag; //텍스트 파일에 a가 적힌경우
		NewYork >> flag;
		if (flag == 'a') { // add 플래그 a인경우 edge추가 
			int n1, n2, n3;
			NewYork >> n1 >> n2 >> n3;
			loadMap.addEdge(n1, n2, n3);
		}
		else {
			string line;
			getline(NewYork, line); //a가 아닌경우 건너뜀 ->제공된 텍스트파일은 모두a가 있는것 같으나 a가없는 경우를 추가로 설정
		}
	}
	loadMap.ShortPath(start, end); //start와 end의 최소경로 출력 
	NewYork.close(); //파일닫기 

	return 0;
}
