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
            //11,1111
            string::const_iterator last = num.end() - 1;
            while(last >= num.begin())
            {
                int res = 0;
                for(int i = 0; i < 4;i++){
                    if(*last == ',' || *last == '-' || last<num.begin()){
                        last--;
                        break;
                    }
                    res += (*last-'0') * pow(10,i);
                    last--;
                }
                last--;
                Node* newnode = new Node(res);
                if(head->next != nullptr)
                    head->next->pre = newnode;
                newnode->next = head->next;
                head->next = newnode;
                newnode->pre = head;
                }
            
        }
        void add(List& num2){
            Node* tail = head;
            while(tail->next!= nullptr) tail = tail->next;
            if()
            for(int i = num2.lenth(); i >=1; i--){
                int temp = tail->data + num2.get_elem(i);
                //处理进位操作
                
                    }
                    tail->pre->data += 1;
                }else{
                    tail->data = temp;
                }
                tail = tail->pre;

            }
        }
        void sub(List& num2){

        }
    public:
        List(string num) : num(num), head(nullptr){
            //创建头节点,头节点存放数据表示正负 1:正 0:负
            int sign = 1;
            if(num[0] == '-') sign = 0;
            head = new Node(sign);
            Create(num);
        }
        int lenth(){
            Node* temp = head;
            int len = 0;
            while(temp->next != nullptr){
                len++;
                temp = temp->next;
            }
            return len;
        }
        int get_elem(int pos){
            if(pos < 0 || pos > this->lenth())
                return -1;
            Node* temp = head;
            for(int i = 1; i <= pos; i++) temp = temp->next;;
            return temp->data;
        }
        void calc(List& num2){
            // 判断两个数符号,同号加法,异号减法
            if(this->get_sign() == num2.get_sign())
                this->add(num2);
            else
                this->sub(num2);
            // cout << num2.get_elem(1) << endl;
        }
        //返回该数的符号
        int get_sign(){
            return head->data;
        }
        void print(){
            Node* temp = head->next;
            if(head->data == 0)
                cout << '-';

           while(temp != nullptr)
           {
            cout << temp->data;
            if(temp->next!=nullptr)
                cout << ',';
            temp = temp->next;
           }
           
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
    string num1, num2;
    cin >> num1 >> num2;
    List a(num1);
    List b(num2);
    a.calc(b);
    a.print();
    return 0;
}