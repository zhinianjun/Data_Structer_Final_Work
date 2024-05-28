#include <iostream>
#include <cmath>
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
        //0
        void Create(string num){
            string::const_iterator last = num.end() - 1;
            
            while(last >= num.begin())
            {
                int res = 0;
                for(int i = 0; i < 4; i++){
                    if(*last == ',' || *last == '-')
                    {
                        last--;
                        break;
                    }
                    res += (*last-'0') * pow(10, i);
                    last--;
                }
                Node* newnode = new Node(res);
                newnode->next = head->next;
                head->next->pre = newnode;
                head->next = newnode;
                newnode->pre = head;
            }
            
        }
    public:
        List(string num) : num(num), head(nullptr){
            //创建头节点,头节点存放数据表示正负 1:正 0:负
            int sign = 1;
            if(num[0] == '-') sign = 0;
            head = new Node(sign);
            Create(num);
        }
        void print(){
            // Node* tail = head;
            // while(tail->next != nullptr)
            //     tail = tail->next;
            // if(head->data == 0)
            //     cout << '-';
            // while(temp->pre != nullptr)
            // {
            //     cout << temp->data << ',';
            //     temp = temp->pre;
            // }
            cout << head->data;
        }
        ~List(){
            Node* temp = head;
            while(temp->next != nullptr){
                Node* t = temp;
                temp = temp->next;
                delete t;
            }
        }
};
int main(){
    string num1;
    cin >> num1;
    List a(num1);
    a.print();
    return 0;
}