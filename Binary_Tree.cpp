#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;
struct node
{
    int data;
    struct node *pLeft; // lien ket ben trai
    struct node *pRight;    // lien ket ben phai
};
typedef struct node NODE;
typedef NODE *TREE; //lam viec voi con tro
void InitTree(TREE &t){
    t = NULL;
}
// them phan tu
void Add_Element(TREE &t, int &x){
    if (t == NULL){
        // khi cay chua co phan tu nao thi phan tu nay se la root
        NODE *p = new NODE;
        p->data = x;
        p->pLeft = NULL;
        p->pRight = NULL;
        t = p; // p la root
    }
    else {
        // cay ton tai phan tu
        if (x < t->data){
            Add_Element(t->pLeft, x);
        }
        else if (x > t->data) {
            Add_Element(t->pRight, x);
        }
        else {
            return;
        }
    }
}
void Output_Ro_L_R(TREE t){
    if(t != NULL)
    {
        cout <<t->data<<" "; // xuat root dau tien
        Output_Ro_L_R(t->pLeft);
        Output_Ro_L_R(t->pRight);
    }  
}
void Output_Ro_R_L(TREE t){
    if(t != NULL)
    {
        cout <<t->data<<" "; // xuat root dau tien
        Output_Ro_R_L(t->pRight);
        Output_Ro_R_L(t->pLeft);
    }  
}
void Output_L_Ro_R(TREE t){
    // xuat cac phan tu be den lon
     if(t != NULL)
    {
        Output_L_Ro_R(t->pLeft); // duyet qua ben trai
        cout <<t->data <<" ";
        Output_L_Ro_R(t->pRight); //duyet qua ben phai
    }  
}
void Output_R_Ro_L(TREE t){
    // xuat cac phan tu be den lon
     if(t != NULL)
    {
        Output_R_Ro_L(t->pRight); // duyet qua ben phai
        cout <<t->data <<" ";
        Output_R_Ro_L(t->pLeft); //duyet qua ben trai
    }  
}
void Output_L_R_Ro(TREE t){
    // xuat cac phan tu be den lon
     if(t != NULL)
    {
        Output_L_R_Ro(t->pLeft); // duyet qua ben trai
        Output_L_R_Ro(t->pRight); //duyet qua ben phai
        cout <<t->data <<" ";
    }  
}
void Output_R_L_Ro(TREE t){
    // xuat cac phan tu be den lon
     if(t != NULL)
    {
        Output_R_L_Ro(t->pRight); // duyet qua ben phai
        Output_R_L_Ro(t->pLeft); //duyet qua ben trai
        cout <<t->data <<" ";

    }  
}
bool Check_Prime(int &x){
    if (x < 2) return false;
    if (x == 2) return true;
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
void Prime(TREE t, int &sum){
    if (t != NULL ){
        if( Check_Prime(t->data)){
        sum ++;
        cout<<t->data<<" ";}
        Prime(t->pLeft, sum);
        Prime(t->pRight, sum);
    }
}
void Find_2_branch(TREE &t){
    if (t != NULL){      
    if (t->pLeft != NULL && t->pRight != NULL){
        cout<<t->data<<" ";
    }
    Find_2_branch(t->pLeft);
    Find_2_branch(t->pRight);
    }
}
void Find_1_Branch(TREE &t){
    if (t != NULL){      
    if ((t->pLeft != NULL && t->pRight == NULL) || (t->pLeft == NULL && t->pRight != NULL)){
        cout<<t->data<<" ";
    }
    Find_1_Branch(t->pLeft);
    Find_1_Branch(t->pRight);
    }
}
void Find_leaf(TREE &t){
    if (t != NULL){      
    if (t->pLeft == NULL && t->pRight == NULL){
        cout<<t->data<<" ";
    }
    Find_leaf(t->pLeft);
    Find_leaf(t->pRight);
    }
}
int Max_TREE(TREE &t, int &max){
    if (t != NULL){
     max = Max_TREE(t->pRight, t->data);
    }
       return max;
}
int Min_TREE(TREE &t, int &min){
    if (t != NULL){
     min = Min_TREE(t->pLeft, t->data);
    }
       return min;
}
void DELETE_VALUE(TREE &t, int x){
    if (t != NULL)
    {
        if (x < t->data)
        {
            DELETE_VALUE(t->pLeft, x);
        }
        else if (x > t->data)
        {
            DELETE_VALUE(t->pRight, x);
        }
        else
        {
            // khi x = t->data
            NODE *g = t; // đây là node thế của node t
            // trường hợp dùng cho node là node có 1 con và node là lá
            if (t->pLeft == NULL)
            {
                // cay con phai
                t = t->pRight; // cập nhật mối liên kết node cha và node con sau
                // sau đó xóa node đó đi, tương tự với th dưới
                // trong trường hợp là lá thì cho node cha trỏ đến null
            }
            else if (t->pRight == NULL)
            {
                // cay con trai
                t = t->pLeft;
            }
            else if (t->pLeft != NULL && t->pRight != NULL)
            {
                NODE *h = t->pRight;
                NODE *k = t->pRight;
                while (h->pLeft != NULL)
                {
                    k = h;
                    h = h->pLeft;
                }
                if (k != h)
                {
                    k->pLeft = h->pRight;
                    h->pLeft = t->pLeft;
                    h->pRight = t->pRight;
                    t = h;
                }
                else
                {
                    h->pLeft = t->pLeft;
                    t = h;
                }
            }
            delete (g);
        }
    }
    else
    {
        return;
    }
}
void Menu(TREE &t){
    int choose;
    while (true)
    {
        system("cls");
        cout << "..........................MENU..........................\n";
        cout << " ==> 1.  Add Element\n";
        cout << " ==> 2.  Display the list on screen (Root - Left - Right) \n";
        cout << " ==> 3.  Display the list on screen (Root - Right - Left)\n";
        cout << " ==> 4.  Display the list on screen (Left - Root - Right) \n";
        cout << " ==> 5.  Display the list on screen (Right - Root - Left) \n";
        cout << " ==> 6.  Display the list on screen (Left - Right - Root) \n";
        cout << " ==> 7.  Display the list on screen (Right - Left - Root) \n";
        cout << " ==> 8.  The Number is Prime\n";
        cout << " ==> 9.  Value of NODE have 2 branch\n";
        cout << " ==> 10. Value of NODE have 1 branch\n";
        cout << " ==> 11. Value of leaf\n";
        cout << " ==> 12. Max of TREE\n";
        cout << " ==> 13. Min of TREE\n";
        cout << " ==> 14. Delete a value\n";
        cout << " ==> 0.  End program\n";
        cout << "...........................END..........................\n";
        cout << " => Input your choose : ";
        cin >> choose;
        switch (choose)
        {
        case 0: 
        {
            exit(0); 
            }
        case 1:
        {
            cout<<" - Enter value = ";
            int x;
            cin >> x;
            Add_Element(t,x);
            break;
        }
        case 2 :
        {
            cout<<"List : ";
            Output_Ro_L_R(t);
            cout <<endl;
            system("pause");
            break;
        }       
        case 3 :
        {
            cout<<"List : ";
            Output_Ro_R_L(t);
            cout <<endl;
            system("pause");
            break;
        }
        case 4 :
        {   
            cout<<"List : ";
            Output_L_Ro_R(t);
            cout <<endl;
            system("pause");
            break;
        }
        case 5 :
        {   
            cout<<"List : ";
            Output_R_Ro_L(t);
            cout <<endl;
            system("pause");
            break;
        }
        case 6 :
        {
            cout<<"List : ";
            Output_L_R_Ro(t);
            cout <<endl;
            system("pause");
            break;
        }
        case 7 :
        {
            cout<<"List : ";
            Output_R_L_Ro(t);
            cout <<endl;
            system("pause");
            break;
        }
        case 8 :
        {
              int sum = 0;
            cout<<"List : ";
            Prime(t, sum);
            cout<<endl<<"Sum = "<<sum;
            cout<<endl;
            system("pause");
            break;
        }
        case 9 :
        {
            cout<<"List : ";
            Find_2_branch(t);
            cout<<endl;
            system("pause");
            break;
        }
        case 10 :
        {
            cout<<"List : ";
            Find_1_Branch(t);
            cout<<endl;
            system("pause");
            break;
        }
        case 11 :
        {
            cout<<"List : ";
            Find_leaf(t);
            cout<<endl;
            system("pause");
            break;
        }
        case 12 :
        {
            int max;          
            cout <<"Max of TREE = "<<  Max_TREE(t,max)<<endl;
            system("pause");
            break;
        }
        case 13 :
        {
            int min;          
            cout <<"Min of TREE = "<<Min_TREE(t,min)<<endl;
            system("pause");
            break;
        }
        case 14 :
        {
            int x;
            cout <<" -> Input the value need deleted x = ";
            cin >> x;
            DELETE_VALUE(t,x);
            cout <<" Rest of list : ";
            Output_L_Ro_R(t);
            cout<<endl; 
            system("pause");
            break;
        }
        default: 
        {
            break;
        }
        }
    }
}
int main (){
    TREE t;
    InitTree(t);
    Menu(t);
    system ("pause");
    return 0;
}