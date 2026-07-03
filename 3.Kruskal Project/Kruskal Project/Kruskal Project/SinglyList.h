#pragma once
#include<assert.h>
template<typename T>
class  SNode {
private:
	T data;
	SNode<T>* next;
	
public:
	SNode(const T & data, SNode<T>* next=nullptr) {
		this->data = data;
		this->next = next;
	}
	SNode<T> * getNext() const { return next; }
	const T& getData() const { return data; }
	void  setData(const T & d) { data = d; }
	void setNext(SNode<T> * N) { next = N; }

	template<typename T> friend class SinglyList;
};

template<typename T>
class SinglyList
{
private:
	SNode<T>* head;
	SNode<T>* tail;
	int n; 

public:
	void   copyList(const SinglyList<T>& obj);

	SinglyList() :head(nullptr), tail(nullptr),n(0) { }
	SinglyList(const SinglyList<T>& obj):head(nullptr) {
		this->copyList(obj);
		}
	SinglyList<T>& operator=(const SinglyList<T>& obj) {

		if (this != &obj)
			copyList(obj);

		return *this;
	}
	~SinglyList() {	while (!empty()) removeFront(); head = nullptr; tail = nullptr;	}

	bool empty() const { return head == nullptr && n <= 0;  }
	int size() const { return n; }

	SNode<T>* getHead() const { return head; }
	SNode<T>* getTail() const { return tail; }

	T    front() const {
	//	if (empty())  exit(20);
		assert(!empty());
		return head->data;
	}
	//T(n) = 1
	T   back()const {
		if (empty())  exit(20);
	
		return tail->data;
	}

	SNode<T>* createNode(const T & item) {
	//Node preparation
	//1. memory allocation
		SNode<T> * N = new  SNode<T>(item);
		//2. Data storage
		N->data = item;
		//3. Nullification
		N->next = nullptr;
		return N;
	}
	void  addFront(const T &  item) {
		SNode<T> * _newNode = createNode(item);

		if (head == nullptr) {
			head = _newNode;
			tail = _newNode;
			++n;
			return;
		}
		_newNode->next = head;
		head = _newNode;
		++n;
	}

	//running time without tail sentinel  = O(n) , but with T(n) = c or 1
	void  addBack(const T &  item) {
		if (empty()) { addFront(item); return; }
		SNode<T>* _newNode = createNode(item);
		
		tail->next = _newNode;
		tail = tail->next;
		++n;
	}


	bool   remove(const T & elem) {
		if (empty()) return false;
		if (head->data == elem) {
			removeFront();
			return true;
		}
		if (tail->data == elem) {
			removeBack();
			return true;
		}
		SNode<T>* p = head, * q = head;
		while (p && p->data != elem)
		{
			q = p;
			p = p->next;

		}
		//if the elem isn't exist
		if (!p) return false;
		// element is found to remove
		q->next = p->next;
		p->next = nullptr;
		delete p;
		
		--n;
		return true;

	 }
	bool  removeFront() {
		if (empty()) return false;
		SNode<T>* p = head;
		head = head->next;
		p->next = nullptr;
		delete p;
		--n;
		if (n == 0)  tail = head = nullptr;
		return true;
	}
	bool  removeBack() {
		if (empty()) return false;
		if (n == 1 || head == tail) {
			delete head;
			--n;
			head = tail = nullptr;
			return true; // ← أضف هذا
		}
		SNode<T>* p = head;
		while (p && p->next != tail) p = p->next;
		p->next = nullptr;
		delete tail;
		tail = p;
		--n;
		if (n == 0)  tail = head = nullptr;
		return true;
	}
	//return the address of the first occurence element found
	SNode<T>* searchFirst(const T& elem) {
		SNode<T>* p = head;
		while (p && p->data != elem) p = p->next;
		return p;
	}
	//count how many elem is found in the list (search for all occurrences)
	int   countAll(const T& elem) {
		SNode<T>* p = head;  int count = 0;
		while (p != nullptr) {
			if (p->data == elem)
				count++;
			p = p->next;
		}
		return count;
	}
	//return the address of the  last occurrence (don't use extra ds)
	SNode<T>* searchLast(const T& elem) {
		SNode<T>* p = head,*f = nullptr;
		while (p ) {
			if (p->data == elem)
				f = p;
			p = p->next;
		}
		return f;
	}
	//return all occurrences 
	SNode<T>* searchAll(const T & elem) {
		SNode<T> * p = head, * f = nullptr;
		SNode<T> ** a = new SNode<T> * [countAll(elem)];
		int i = 0;
		while (p) {
			if (p->data == elem)
				a[i++] = p;
			p = p->next;
		}
		return f;
	}
	void clear();

};
template<typename T>
void  SinglyList<T>::clear() {
	if (this->empty())  return;

		
		while (!empty()) {
		
			this->removeFront();
			
		}
}

template<typename T>
void   SinglyList<T>::copyList(const SinglyList<T>& obj) {
	if (obj.empty()) return;

	if(!this->empty() ) this->clear();

	if (this->empty()) {
		SNode<T>* p = obj.head;
		while (p) {
			this->addBack(p->data);
			p = p->next;
		}
	}
	
}