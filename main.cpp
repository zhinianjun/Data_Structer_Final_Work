#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/*
    List链表节点类
    data用于存储每4位长整数
    next, pre分别为节点的下一个和上一个节点
*/
class Node{
    public:
        int data;
        Node* next;
        Node* pre;
        Node(int data) : data(data), next(nullptr), pre(nullptr){}
};

/*
    自定义List双向链表用于存储一个整数
*/
class List{
    private:
        //整数字符串
        string num;
        //头节点
        Node* head;
        /*  
            Creat方法接受一个字符串并,以","分隔每4位长整数生成一个节点,
            以头插法的方式将每个分割数字插入双向链表
        */
        void Create(string num){
            //申明从最后一个数字开始的迭代器,从最后一位最低位数开始迭代
            string::const_iterator last = num.end() - 1;
            while(last >= num.begin())
            {
                int res = 0;
                //四位数分割
                for(int i = 0; i < 4;i++){
                    if(*last == ',' || *last == '-' || last<num.begin()){
                        last--;
                        break;
                    }
                    res += (*last-'0') * pow(10,i);
                    last--;
                }
                //跳过空格
                last--;
            
                //生成节点并按头插法插入
                Node* newnode = new Node(res);
                if(head->next != nullptr)
                    head->next->pre = newnode;
                newnode->next = head->next;
                head->next = newnode;
                newnode->pre = head;
                }
            
        }
        //add()方法用于计算两数和的情况
        //核心代码时间效率为O(n²)
        void add(List& num2){
            Node* tail = head;
            //end_con存储两数相加截至的情况
            int end_con = 1;
            if(num2.lenth() > this->lenth())
                end_con = num2.lenth()-this->lenth() + 1;

            //如果num2数字长度大于当前数字,将num2未进行加法部分拼接到当前链表
            for(int i = num2.lenth() - this->lenth(); i >= 1; i--){
                Node* newnode = new Node(num2.get_elem(i));
                if(head->next != nullptr)
                    head->next->pre = newnode;
                newnode->next = head->next;
                head->next = newnode;
                newnode->pre = head;
            }
            while(tail->next!= nullptr) tail = tail->next;

            //从两数最低位开始进行相加的情况
            for(int i = num2.lenth(); i >= end_con; i--){
                int temp = tail->data + num2.get_elem(i);
                //处理进位操作,当两低位两束相加超过9999即需要进位
                if(temp > 9999)
                {
                    tail->data = temp % 10000;
                    if(tail->pre == head){
                        Node* newnode = new Node(1);
                        if(head->next != nullptr)
                            head->next->pre = newnode;
                        newnode->next = head->next;
                        head->next = newnode;
                        newnode->pre = head;
                        continue;
                    }else
                        tail->pre->data += 1;
                }else
                    tail->data = temp;
    
                tail = tail->pre;
                
            }
            //当两数相加完毕最后再次处理进位的操作
            tail = head;
            while(tail->next!= nullptr) tail = tail->next;
            while(tail != nullptr){
                if(tail->data >= 10000){
                    tail->data -= 10000;
                    tail->pre->data += 1;
                }
                tail = tail->pre;
            }
        }
        //sub()方法处理两数一正一负两数相减情
        //核心代码时间效率为O(n²)
        void sub(List& num2){
            //两数相减,并且当前数字长度大于另一个数字长度,当前数字符号不变
            if(this->lenth() > num2.lenth()){
                if(this->get_sign() == 0){
                    Node* tail = head;
                    while(tail->next!= nullptr) tail = tail->next;
                    for(int i = num2.lenth(); i >=1 ;i--){
                        int temp = -(tail->data) + num2.get_elem(i);
                        if(temp>0){
                            tail->pre->data -= 1;
                            temp = tail->data + 10000 - num2.get_elem(i);
                        }
                        tail->data = temp;
                        tail = tail->pre;
                    }
                }
                else{
                    Node* tail = head;
                    while(tail->next!= nullptr) tail = tail->next;
                    for(int i = num2.lenth(); i >=1 ;i--){
                        int temp = tail->data - num2.get_elem(i);
                        if(temp < 0){
                            tail->pre->data -= 1;
                            temp = tail->data + 10000 - num2.get_elem(i);
                        }
                        tail->data = temp;
                        tail = tail->pre;
                    }
                }
        //两数相减,并且当前数字长度大于另一个数字长度,当前数字符号变为另一个数字符号
        }else if(this->lenth() < num2.lenth()){
            if(this->get_sign() == 0){
                head->data = 1;
                int origin_len = this->lenth();
                int end_con = num2.lenth() - this->lenth();
                for(int i = num2.lenth() - this->lenth(); i >= 1; i--){
                    Node* newnode = new Node(num2.get_elem(i));
                    if(head->next != nullptr)
                        head->next->pre = newnode;
                    newnode->next = head->next;
                    head->next = newnode;
                    newnode->pre = head;
                }
                Node* tail = head;
                while(tail->next != nullptr) tail = tail->next;
                for(int i = num2.lenth(); i > end_con; i--){
                    int temp = -(tail->data) + num2.get_elem(i);
                    if(temp < 0){
                        if(i - origin_len > 1)
                            tail->pre->data += 1;
                        else
                            tail->pre->data -= 1;
                        temp = num2.get_elem(i) + 10000 - tail->data;
                    }
                    tail->data = temp;
                    tail = tail->pre;
                }
                Node* temp = head;
                while(temp != nullptr){
                    if(temp->data < 0){
                        temp->pre->data -= 1;
                        temp->data = 10000 + temp->data;
                    }
                    temp = temp->next;
                }
                
            }else{
                head->data = 0;
                int end_con = num2.lenth() - this->lenth();
                for(int i = num2.lenth() - this->lenth(); i >= 1; i--){
                    Node* newnode = new Node(num2.get_elem(i));
                    if(head->next != nullptr)
                        head->next->pre = newnode;
                    newnode->next = head->next;
                    head->next = newnode;
                    newnode->pre = head;
                }
                Node* tail = head;
                while(tail->next != nullptr) tail = tail->next;
                for(int i = num2.lenth(); i > end_con; i--){
                    int temp = num2.get_elem(i) - tail->data;
                    if(temp < 0){
                        tail->pre->data -= 1;
                        temp = num2.get_elem(i) + 10000 - tail->data;
                    }
                    tail->data = temp;
                    tail = tail->pre;
                }
            }
            ////两数相减,并且当前数字长度等于另一个数字长度,当前数字符号具体分析
            }else{
                bool is_bigger = true;
                //从头开始判断两数大小,如果从头开始两数均相等,两数相减为0
                for(int i = 1; i <= this->lenth(); i++){
                    if(this->get_elem(i) < num2.get_elem(i))
                    {
                        is_bigger = false;
                        break;
                    }
                    if(i == this->lenth() && this->get_elem(i) == num2.get_elem(i))
                    {
                        head->data = 1;
                        Node* temp = head->next;
                        while(temp){
                            temp->data = 0;
                            temp = temp->next;
                        }
                        return;
                    }
                       
                }
                //当前数字较大,符号不变
                if(is_bigger){
                    Node* tail = head;
                    while(tail->next != nullptr) tail = tail->next;
                    for(int i = this->lenth(); i >= 1; i--){
                        int temp = tail->data - num2.get_elem(i);
                        if(temp < 0){
                            tail->pre->data -= 1;
                        }
                        tail->data = temp;
                        tail = tail->pre;
                    }
                //当前数字小,符号为负号
                }else{
                    head->data = 0;
                    Node* tail = head;
                    while(tail->next != nullptr) tail = tail->next;
                    for(int i = this->lenth(); i >= 1; i--){
                        int temp = tail->data - num2.get_elem(i);
                        if(temp < 0){
                            tail->pre->data -= 1;
                        }
                        tail->data = temp;
                        tail = tail->pre;
                    }
                }
            }
        }
        
    public:
        //构造函数:构造双向链表头节点并构造整个链表
        List(string num) : num(num), head(nullptr){
            //创建头节点,头节点存放数据表示正负 1:正 0:负
            int sign = 1;
            if(num[0] == '-') sign = 0;
            head = new Node(sign);
            Create(num);
        }
        //返回整个双向链表长度,用于辅助计算
        int lenth(){
            Node* temp = head;
            int len = 0;
            while(temp->next != nullptr){
                len++;
                temp = temp->next;
            }
            return len;
        }
        //返回双向链表第n个元素的值,辅助计算
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
                
        }
        //返回当前整数的符号,用于计算的判断
        int get_sign(){
            return head->data;
        }
        
        //按照数据的不同类型打印数据
        void print(){
            if(head->data == 0)
                cout << '-';

            if(head->next->data == 0 && this->lenth() == 1){
                cout << 0;
                return;
            }
            int real_len = 0;
            for(int i = 1; i <= this->lenth();i++){
                if(this->get_elem(i) != 0){
                    real_len++;
                }
            }
            if((real_len == 1 && head->next->data == 0) || real_len == 0){
                cout << this->get_elem(this->lenth());
                return;
            }

            Node* temp = head->next;
            while(temp != nullptr)
            {
                if(temp->data == 0 && temp == head->next){
                    temp = temp->next;
                    continue;
                }
                if(temp->data != 0 && temp->pre != head){
                    if(temp->data > 0 && temp->data < 10)
                        cout << "000";
                    else if(temp->data >= 10 && temp->data < 100)
                        cout << "00";
                    else if(temp->data >= 100 && temp->data < 1000)
                        cout << "0";
                }
                cout << temp->data;
                if(temp->data == 0 && temp->pre != head)
                    cout << "000";
                if(temp->next!=nullptr)
                    cout << ',';
                
                temp = temp->next;
           }
           
        }
        //析取函数用于销毁申请的节点空间,避免内存溢出
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