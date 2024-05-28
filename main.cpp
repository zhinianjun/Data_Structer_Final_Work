#include <iostream>
#include <string>

using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node* pre;
        Node(int data) : data(data), next(nullptr), pre(nullptr){}
};

class List{
    private:
        
        string num;
        Node* head;
        Node* tail;
        //
        void Create(string str){
            
        }
    public:
        List(string num) : num(num), head(nullptr), tail(nullptr){
            //创建头节点,头节点存放数据表示正负 1:正 0:负
            int sign = 1;
            if(num[0] == '-') sign = 0;
            head = new Node(sign);
            tail = head;
        }
        ~List(){
            Node* temp = head->next;
            while(temp->next != nullptr){
                Node* t = temp;
                temp = temp->next;
                delete t;
            }
        }
};
int main(){

    return 0;
}