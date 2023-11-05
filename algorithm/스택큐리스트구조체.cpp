#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
//202221106 임세현 코드작성

using namespace std;

template <class T> struct Node {
	T data;
	Node* next;
	Node(T d = 0) :next(nullptr), data(d) {}
};
template <class T> struct List {
	Node<T>* head = nullptr;
	void pop_front() { //리스트 맨앞 삭제 
		if (head == nullptr)return;
		auto next = head->next;
		delete head;
		head = next;
	}
	void push_front(const T& d) { //리스트의 앞에 삽입
		auto newNode = new Node<T>(d);
		newNode->next = head;
		head = newNode;
	}
	bool IsEmpty() const {
		return head == nullptr;
	}
	void push_back(T d) { //리스트의 끝에 삽입
		auto cur = head;
		if (cur == nullptr) {  //head가 널인경우 맨앞에 새로운 노드 
			auto newNode = new Node<T>(d);
			head = newNode;
			return;
		}
		while (cur != nullptr) {//마지막 위치 찾음
			if (cur->next == nullptr) { //맨마지막 노드 위치 cur  
				auto newNode = new Node<T>(d); 
				cur->next = newNode;
				return;
			}
			cur = cur->next;
		}
	}
	void pop_back() {//마지막 노드 삭제 
		if (head == nullptr) return;  //빈노드인경우 종료
		if (head->next == nullptr) {  //노드 하나인경우
			delete head;    //head지우기
			head = nullptr;
			return;
		}
		auto cur = head;
		while (cur->next != nullptr) {  //현재 노드의 다음노드가 널이아닐때
			if (cur->next->next == nullptr) { //다음다음 노드가 널이면
				delete cur->next;  //삭제할 대상은 다음노드
				cur->next = nullptr;
				return;
			}
			cur = cur->next;   //노드 한칸 이동 
		}
		printf("Something is wrong!!!\n");
	}

};
template<class T>
std::ostream& operator <<(std::ostream& os, List<T> list)//list 전용 출력
{
	auto cur = list.head;
	while (cur != nullptr) { //리스트 목록 전부 출력
		os << cur->data << " ";
		cur = cur->next;
	}
	return os;
}

template<class T> struct Queue {// 선입선출
	List<T> list;
	void pop() {
		list.pop_front(); //맨앞에 노드 삭제 
	}
	void push(const T& data) {//뒤에 삽입 
		list.push_back(data);
	}
	T front() { //맨앞 리스트 출력 
		if (list.head == nullptr) {
			printf("No data to print exit program");
			exit(-1);
		}
		return list.head->data;
	}
	bool empty()const {
		return list.IsEmpty();
	}
};
template<class T> struct Stack {//선입후출
	List<T> list;
	void pop() {  //앞에놈 pop
		list.pop_front();
	}
	void push(const T& data) {//앞에 push
		list.push_front(data);
	}
	T top() {
		if (list.head == nullptr) {
			printf("No data to print exit program");
			exit(-1);
		}
		return list.head->data;
	}
	bool empty() const {
		return list.IsEmpty();
	}
};


int main() {
	printf("test stack int\n");
	Stack<int> stack;
	stack.push(1); stack.push(2);
	stack.push(3); stack.push(4);
	stack.push(5);
	cout << stack.top() << endl;
	stack.pop(); stack.pop(); stack.pop(); stack.pop(); stack.pop();
	if (stack.empty())
		printf("stack is empty\n");
	else printf("stack is not empty\n");
	printf("test queue int\n");
	Queue<int> queue;
	queue.push(1); queue.push(2);
	queue.push(3); queue.push(4);
	queue.push(5);

	cout << queue.front() << endl;
	queue.pop(); queue.pop(); queue.pop(); queue.pop(); queue.pop();
	if (queue.empty())
		printf("queue is empty\n");
	else printf("queue is not empty\n");
	queue.push(1);	queue.push(2);	queue.push(3);	queue.push(4);
	cout << queue.front() << endl;
	printf("test stack char\n");
	Stack<char> stack2;
	stack2.push('a'); stack2.push('b');
	stack2.push('c'); stack2.push('d');
	stack2.push('e');
	cout << stack2.top() << endl;
	stack2.pop();
	cout << stack2.top() << endl;
	stack2.pop();
	cout << stack2.top() << endl;
	stack2.pop();
	cout << stack2.top() << endl;
	if (stack2.empty())
		printf("stack is empty\n");
	else printf("stack is not empty\n");

	printf("test queue char\n");
	Queue<char> queue2;
	queue2.push('a'); queue2.push('b');
	queue2.push('c'); queue2.push('d');
	queue2.push('e');

	cout << queue2.front() << endl;
	queue2.pop(); queue2.pop(); queue2.pop(); queue2.pop(); queue2.pop();
	if (queue2.empty())
		printf("queue is empty\n");
	else printf("queue is not empty\n");
	queue2.push('a');	queue2.push('b');	queue2.push('c');	queue2.push('d');
	cout << queue2.front() << endl;
	queue2.pop();
	cout << queue2.front() << endl;
	queue2.pop();
	cout << queue2.front() << endl;
	queue2.pop();
	cout << queue2.front() << endl;

	return 0;
}
