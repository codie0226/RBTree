#include <iostream>
#include <string>
using namespace std;

// 노드 객체
class Node {
    private:
        int sid;
        string sname;
        string subject;
        string phone;
        int timestamp;
        int depth;
        char color;

        Node* lchild;
        Node* rchild;
        Node* parent;
    public:
        // 생성자. 노드의 정보를 초기화한다. 여기서 자식노드와 부모노드는 nullptr로 초기화한다.
        Node(int sid, string sname, string subject, string phone, int timestamp, char color) {
            this->sid = sid;
            this->sname = sname;
            this->subject = subject;
            this->phone = phone;
            this->timestamp = timestamp;
            this->color = color;
            this->depth = 0;
            lchild = nullptr;
            rchild = nullptr;
            parent = nullptr;
        }

        // 연산자 오버로딩. sid를 먼저 비교하고 subject를 사전순으로 비교한다.
        friend bool operator < (const Node &a, const Node &b) {
            if(a.sid < b.sid) {
                return true;
            } else if (a.sid == b.sid) {
                return a.subject < b.subject;
            } else {
                return false;
            }
        }

        // 기본적인 getter setter 함수들
        string getSname() {
            return sname;
        }

        void setLchild(Node* lchild) {
            this->lchild = lchild;
        }

        void setRchild(Node* rchild) {
            this->rchild = rchild;
        }

        void setParent(Node* parent) {
            this->parent = parent;
        }

        void setColor(char color) {
            this->color = color;
        }

        Node* getLchild() {
            return lchild;
        }

        Node* getRchild() {
            return rchild;
        }

        Node* getParent() {
            return parent;
        }

        int getSid() {
            return sid;
        }

        char getColor() {
            return color;
        }
};

// leaf 노드로 사용할 nil 노드
Node* nil = new Node(0, "", "", "", 0, 'B');

// 레드 블랙 트리
class RBTree {
    private:
        Node* root;

    public:
        // 생성자. root를 nil로 초기화한다.
        RBTree() {
            root = nil;
        }

        // 노드 삽입 함수.
        void insert(Node* newNode) {
            // root가 nil일 경우 트리가 비어있으므로 새로운 노드를 root로 정의한다.
            if(root == nil){
                root = newNode;
                root->setColor('B');
                return;
            }

            // curNode는 현재 노드를 가리키고 root부터 시작한다. parent는 부모노드를 가리킨다.
            Node* curNode = root;
            Node* parent = nullptr;

            // curNode가 nil이 아닐 때까지 newNode의 위치를 찾는다.
            // parent는 curNode를 가리키고 curNode는 하나씩 내려가면서 newNode의 위치를 찾는다.
            // newNode가 curNode보다 작으면 왼쪽 자식으로 내려가고, 크면 오른쪽 자식으로 내려간다.
            while(curNode != nil) {
                parent = curNode;
                if(newNode < curNode) {
                    curNode = curNode->getLchild();
                }else{
                    curNode = curNode->getRchild();
                }
            }

            // newNode의 부모를 parent로 설정하고, newNode가 parent보다 작으면 왼쪽 자식으로, 크면 오른쪽 자식으로 설정한다.
            newNode->setParent(parent);
            if(newNode < parent) {
                parent->setLchild(newNode);
            } else {
                parent->setRchild(newNode);
            }

            // newNode의 자식으로 nil을 설정한다.
            // newNode는 삽입된 노드이므로 레드로 설정한다.
            newNode->setLchild(nil);
            newNode->setRchild(nil);
            newNode->setColor('R');

            // newNode에 대해 더블 레드 체크를 수행한다.
            checkDoubleRed(newNode);
        }

        void checkDoubleRed(Node* newNode) {
            Node* parent = newNode->getParent();
            Node* grandParent = parent->getParent();
            if(parent == nullptr || grandParent == nullptr){
                return;
            }

            // 더블 레드가 아닐 경우 종료
            if(parent->getColor() == 'B') {
                return;
            }

            Node* uncle = nullptr;
            if(parent == grandParent->getLchild()) {
                uncle = grandParent->getRchild();
            } else {
                uncle = grandParent->getLchild();
            }

            if(uncle->getColor() == 'R'){
                parent->setColor('B');
                uncle->setColor('B');
                grandParent->setColor('R');
                checkDoubleRed(grandParent);
            }else{
                
            }
        }

        void restructure(Node* node, Node* uncle, Node* parent){

        }
};

int main() {
    RBTree tree;

    int t;
    cin >> t;

    while(t--){

    }

    return 0;
}