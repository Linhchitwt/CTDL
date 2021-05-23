// bài này là mình tự code dựa theo thuật toán có sẵn, sử dụng thư viện stack và queue cho nhanh
#include <iostream>
#include <string.h>
#include <string>
#include <stack>
#include <queue>
#include <math.h>
#include <conio.h>
#include <climits>
using namespace std;
bool Calculation(char s) {
    // Kiểm tra xem phải phép tính (toán tử) không 
    if (s == '+' || s == '-' || s == '*' || s == '/' || s == '%' || s == '^') {
        return true;
    }
    return false;
}
bool TestOperand(char s) {
    // Kiểm tra xem có phải toán hạng không
    if ((s >= '0' && s <= '9') || (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z')) {
        return true;
    }
    return false;
}
int TestPrioritize_Calculation(char s) {
    // Xét độ ưu tiên của phép tính (toán tử)
    if (s == '+' || s == '-') {
        return 1;
    }
    if (s == '*' || s == '/' || s == '%') {
        return 2;
    }
    if (s == '^') {
        return 3;
    }
    return -1;
}
bool Compare_Prioritize(int& c1, int& c2) {
    //So sánh độ ưu tiên của các toán tử để push cho đúng
    if (c1 == c2) {
        return false;
    }
    if (c1 > c2) {
        return true;
    }
    return false;
}
void Infix_to_Postfix(string s, string &ss) {
    stack <char> sta;
    queue <char> que;
    ss = ""; // ss để tính giá trị biểu thức trong hàm sau
    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (s[i] == ' ') {
            continue;
            // gặp khoảng trắng thì bỏ qua
        }
        if (s[i] == '(') {
            // gặp dấu ( thì push vào stack
            sta.push(s[i]);
        }
        if (TestOperand(s[i])) {
            // nếu là toán hạng thì push vào trong queue
            que.push(s[i]);
        }
        if (s[i] == ')') {
            char k;
            // khi gặp dấu đóng ngoặc, ta push tất cả các phần tử trong stack qua queue cho đến khi gặp dấu (
            while (sta.top() != '(') {
                k = sta.top();
                que.push(k);
                sta.pop();
            }
            // và bỏ luôn dấu mở ngoặc đi
            sta.pop();
        }
        if (Calculation(s[i])) { //là toán tử
            if (sta.empty()) {
                // stack rỗng thì push vào stack
                sta.push(s[i]);
            }
            else {
                /*
                Ngược lại, ta xét các trường hợp :
                - Nếu phần tử đầu stack là k phải toán tử thì push vào stack
                (đây là dùng trong trường hợp các dấu () )
                */
                if (!Calculation(sta.top())) {
                    sta.push(s[i]);
                }
                else {
                    /*
                    - Nếu phần tử đầu stack là toán tử thì :
                    + Xét độ ưu tiên của toán tử :
                        * nếu độ ưu tiên của phần tử lớn hơn độ ưu tiên của toán tử đầu stack thì
                        ta push vào stack
                        * nếu độ ưu tiên của phần tử nhỏ hơn hoặc bằng độ ưu tiên của toán tử đầu stack thì
                        ta thực hiện vòng lặp push phần tử đầu của stack vào queue cho đến khi stack rỗng hoặc
                        phần tử đầu stack không phải là toán tử nữa
                            Trong trường hợp trong stack có các độ ưu tiên mữa độ khác nhau thì chỉ push toán tử nào
                            có độ ưu tiên cao hơn phần tử đang xét.
                    */
                    int c1, c2;
                    c1 = TestPrioritize_Calculation(s[i]);
                    c2 = TestPrioritize_Calculation(sta.top());
                    if (Compare_Prioritize(c1, c2)) {
                        sta.push(s[i]);
                    }
                    else {
                        while (!Compare_Prioritize(c1, c2)) {
                            if (!sta.empty() && Calculation(sta.top())) {
                                // xét riêng là để không bị lỗi chương trình vì tính độ ưu tiên (trường hợp stack rỗng)
                                if (!Compare_Prioritize(c1, c2)) {
                                    que.push(sta.top());
                                    sta.pop();
                                    if (!sta.empty()) {
                                        /* sở dĩ xét rỗng mà không để luôn ngoài vòng vì
                                        nếu trong trường hợp đã push hết phần tử trong stack thì
                                        sẽ hết phần tử để tính độ ưu tiên => lỗi chương trình
                                        */
                                        c1 = TestPrioritize_Calculation(s[i]);
                                        c2 = TestPrioritize_Calculation(sta.top());
                                    }
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        // sau đó push luôn phần tử vào stack
                        sta.push(s[i]);
                    }
                }
            }
        }
    }
    while (!sta.empty()) {
        que.push(sta.top());
        sta.pop();
    }
    //Postfix đã được lưu trong queue

 //  hàm này chỉ mang tính chất check lại kết quả hậu tố
    while (!que.empty()) {
        cout << que.front() << " ";
        ss += que.front(); // ss để tính giá trị biểu thức trong hàm sau
        que.pop();
    }
}
int Char_Int(char c) {
    // Chuyển kí tự trong string thành kiểu Int
    int k;
    k = c;
    return int(k - '0');
    // vì 0 đại diện cho 48 ở bảng mã ASCII
}
int Operation(int a, int b, char op) {
    // hàm tính toán giá trị
    if (op == '+') {
        return b + a;
    }
    else if (op == '-') {
        return b - a;
    }
    else if (op == '*') {
        return b * a;
    }
    else if (op == '/') {
        return b / a;
    }
    else if (op == '%') {
        return b % a;
    }
    else if (op == '^') {
        return pow(b, a);
    }
    else {
        return INT_MIN;
    }
}
// đây là cách thông thường, vẫn có thể sử dụng STL iterators để xác định vị trí của các toán tử
int Calculate_Expression(string &ss) {
    queue <char> que1; // Lưu các phần tử nên để kiểu char
    stack <int> st2; // chỉ để lưu các số
    int a, b;
    for (int i = 0; i < ss.length(); i++) {
        que1.push(ss[i]);
    }
    for (int i = 0; i < ss.length(); i++) {
        // trường hợp là toán hạng push vào stack
        if (TestOperand(ss[i])) {
            st2.push(Char_Int(ss[i])); // lúc này toán hạng đã được chuyển qua kiểu int
        }
        else if (TestPrioritize_Calculation(ss[i]) > 0 && !st2.empty()) { // điều kiện sau chỉ để cho chắc
            // trường hợp là toán tử thì lấy 2 toán hạng trước đó ra để tính toán
            a = st2.top(); //a và b bây giờ đã là kiểu int
            st2.pop();
            b = st2.top();
            st2.pop();
            // sau đó push kết quả vào stack và tiếp tục tính
            st2.push(Operation(a, b, ss[i]));
        }
    }
    return st2.top(); // kết quả cuối cùng là phần tử cuối cùng trong stack
}
struct node
{
    char data;
    struct node *pLeft; // lien ket ben trai
    struct node *pRight;    // lien ket ben phai
};
typedef struct node NODE;
typedef NODE *TREE; //lam viec voi con tro
void InitTree(TREE &t){
    t = NULL;
}
NODE *Create_p(char data){
    // tạo 1 node mới 
    NODE *p = new NODE;
    if (p == NULL){
        cout <<"Error!!! Memory isn't enough";
        return NULL;
    }
    p->data = data;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}
void Output_L_R_Ro(TREE t){
    // xuat cac phan tu be den lon
     if(t != NULL)
    {
        cout <<t->data <<" ";
        Output_L_R_Ro(t->pLeft); // duyet qua ben trai
        Output_L_R_Ro(t->pRight); //duyet qua ben phai
    }  
}
void Create_Expression_Tree(string &ss, TREE &t){
    stack <TREE> st;
    for (int i = 0; i <ss.length(); i++){
            t = Create_p(ss[i]);
        if (!Calculation(ss[i])){
            st.push(t);
        }
        else {
            t->pRight = st.top();
            st.pop();
            t->pLeft = st.top();
            st.pop();
            st.push(t);
        }
    }
    t = st.top();
    st.pop();
}
int main() {
    TREE t;
    InitTree(t);
    string s,ss;
    int choose;
    queue <char> que;
    while (true) {
        system("cls");
        cout << "======= Enter your choose ======\n";
        cout << "==> 1. Input the expression\n";
        cout << "==> 2. Infix to Postfix\n";
        cout << "==> 3. Calculate expression\n";
        cout << "==> 4. Output TREE (Prefix)\n";
        cout << "==> 0. End program\n";
        cout << " Your choose is : ";
        cin >> choose;
        switch (choose)
        {
        case 1: {
            fflush(stdin);
            cout << "Input your Expression : ";
            getline(cin, s);
            break;
        }
        case 2:
        {
            cout << "Postfix is : ";
            Infix_to_Postfix(s, ss);
            cout << endl;
            system("pause");
            break;
        }
        case 3:
        {
            // trong trường hợp đã choose = 2 thì không cần 3 dòng này mà vẫn có thể in ra kết quả
            cout << "Postfix is : ";
            Infix_to_Postfix(s, ss);
            cout << endl; 

            cout << "Value of expression = ";
            cout << Calculate_Expression(ss) << endl;
            system("pause");
            break;
        }
        case 4: {
            Create_Expression_Tree(ss,t);
            cout << "Tree : ";
            Output_L_R_Ro(t);
            cout<< endl;
            system("pause");
            break;
        }
        case 0:
        {
            exit(0);
        }
        default: {
            system("pause");
            break;
        }
        }
    }
}