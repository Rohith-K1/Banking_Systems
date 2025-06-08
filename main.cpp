#include<bits/stdc++.h>
using namespace std;

class bankaccount {
private:
  unsigned int accno;//account number of the bank account
  int currentbalance;
  bankaccount *next;

public:
  bankaccount() {
    accno = 0;
    currentbalance = 0;
    next = nullptr;
  }
 bankaccount(int k) {
    accno = k;
    currentbalance = 1000;//initially each account has 1000 in it.
    next = nullptr;
  }
  friend class SingleLinkedList;
  friend class DoubleLinkedList;
};
class SingleLinkedList {
private:
  bankaccount *first;
  bankaccount *last;
  int len;

public:
  SingleLinkedList() {
    first = nullptr;
    last = nullptr;
    len = 0;
  }
  void insertbankacc(int k) {
    bankaccount *toadd = new bankaccount(k);
    if (first == nullptr) {
      first = toadd;
      last = toadd;
      len++;
    } else {
      bankaccount *temp = first;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = toadd;
      last = toadd;
      len++;
    }
    
  }
  void print1() {
    bankaccount *temp = first;
    while (temp != nullptr) {
      cout << temp->accno << " "<<temp->currentbalance<<" ";
      temp = temp->next;
    }
    cout << endl;
  }
  bankaccount *getfirst() { return first; }
  friend class DoubleLinkedList;
};
class transaction {
private:
  int acno;
  char dorw;
  int amount;
  transaction *prev;
  transaction *next;

public:
  transaction() {
    acno = -1;
    dorw = '\0';//deposit or withdrawl
    amount = 0;
    prev = nullptr;
    next = nullptr;
  }
  transaction(int ac2, char dorw2, int amount1) {
    acno = ac2;
    dorw = dorw2;
    amount = amount1;
    prev = nullptr;
    next = nullptr;
  }
  friend class DoubleLinkedList;
  friend class SingleLinkedList;
  friend class bankaccount;
};
int N;
int NN;
class DoubleLinkedList {
private:
  transaction *head;
  transaction *tail;

public:
  transaction *cursor;
  DoubleLinkedList() {
    head = new transaction();
    tail = new transaction();
    head->next = tail;
    head->prev = nullptr;
    tail->prev = head;
    tail->next = nullptr;
    cursor = head;
  }
  void inserttransaction(int ac2, char c2, int amount1) {
    transaction *toadd = new transaction(ac2, c2, amount1);
    transaction *temp = head;
    while (temp->next != tail) {
      temp = temp->next;
    }
    temp->next = toadd;
    toadd->prev = temp;
    toadd->next = tail;
    tail->prev = toadd;
  }
  void printalltransaction() {
    transaction *temp = head->next;
    while (temp != tail) {
      cout << temp->acno << " " << temp->dorw << " " << temp->amount << " ";
      temp = temp->next;
    }
    cout << endl;
  }
  transaction *gethead() { return head; }
  void processnextxtransactions(int x, SingleLinkedList &list1) {
    int e;
    if (N >= x) {
      e = x;
    } else {
      e = N;
    }
    for (int i = 0; i < e; i++) {
        cursor=cursor->next;
       bankaccount *temp2 =list1.first;
      while (temp2 != nullptr) {
        if (temp2->accno == cursor->acno) {
          if (cursor->dorw == 'W') {
            temp2->currentbalance = temp2->currentbalance - cursor->amount;
          } else {
            temp2->currentbalance = temp2->currentbalance + cursor->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
    }
    return;
  }
  void undoytransactions(int y, SingleLinkedList &list1) {
    if(cursor==head){
      return;
    }
    for (int i = 0; i < y; i++) {
      bankaccount *temp2 = list1.first;
        while(cursor->acno!=temp2->accno) {
          temp2=temp2->next;
        }
          if (cursor->dorw == 'W') {//for withdrawl
            temp2->currentbalance = temp2->currentbalance + cursor->amount;
          } else {//for deposit
            temp2->currentbalance = temp2->currentbalance - cursor->amount;
          }
          N++;
      if(cursor->prev==head){break;}
     else {
       if(i!=y){
         cursor=cursor->prev;
       }
     }
    }
  }
  void insertkpos(transaction *t, int k,SingleLinkedList& list1) {
    transaction *temp = head->next;
    for (int i = 0; i <= k - 2; i++) {
      temp = temp->next;
    }
    transaction *temp2 = temp->next;
    temp->next = t;
    t->prev = temp;
    t->next = temp2;
    temp2->prev = t;
    N++;
    NN++;
    if(k<=NN-N){
         bankaccount *temp2 =list1.first;
      while (temp2 != nullptr) {
        if (temp2->accno == t->acno) {
          if (t->dorw == 'W') {
            temp2->currentbalance = temp2->currentbalance - t->amount;
          } else {
            temp2->currentbalance = temp2->currentbalance + t->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
    }
  }
  void printalltransactionsofy(int y,SingleLinkedList& list1) {
    transaction *temp = head->next;
    while (temp!= cursor->next) {
      if (temp->acno == y) {
        cout << temp->acno << " " << temp->dorw << " " << temp->amount << endl;
      }
      temp=temp->next;
    }
  }
void processallfurthertransactions(SingleLinkedList& list1){
  while(cursor->next!=tail){
      cursor=cursor->next;
    bankaccount* temp2=list1.first;
    while (temp2 != nullptr) {
        if (temp2->accno == cursor->acno) {
          if (cursor->dorw == 'W') {
            temp2->currentbalance = temp2->currentbalance - cursor->amount;
          } else {
            temp2->currentbalance = temp2->currentbalance + cursor->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
  }
}
void printcurrentbalance_of_x(int x,SingleLinkedList& list1){
    bankaccount* temp=list1.first;
    while(temp!=nullptr){
        if(temp->accno==x){
            cout<<temp->currentbalance<<endl;
            break;
        }
        temp=temp->next;
    }
}
void print_no_of_accounts_with_currentbalance_morethan_or_equal_to_x(int x,SingleLinkedList& list1){
    bankaccount* temp=list1.first;
    int count=0;
    while(temp!=nullptr){
        if(temp->currentbalance>=x){
            count++;
        }
        temp=temp->next;
    }
    cout<<count<<endl;
}
void printaccounts_with_highestbalance(SingleLinkedList& list1){
    bankaccount* temp=list1.first;
    vector<int>v;
    int max=0;
    while(temp!=nullptr){
        if(temp->currentbalance>max){
            max=temp->currentbalance;
            v.clear();
            v.push_back(temp->accno);
        }
        else if(temp->currentbalance==max){
            v.push_back(temp->accno);
        }
        temp=temp->next;
    }
   sort(v.begin(), v.end(), greater<int>());
   for(int i=0;i<v.size();i++){
       cout<<v[i]<<" ";
   }
   cout<<endl;
}
void deletetransaction(int ac,int M,SingleLinkedList& list1){
    if(M>0){
        int i=0;
           transaction*temp=cursor->next;
            while((temp!=tail)&&(i<M)){
        if(temp->acno==ac){
            transaction*temp1=temp;
            (temp1->prev)->next=temp1->next;
            (temp1->next)->prev=temp1->prev;
            delete temp1;
            N--;
          i++;
          break;
        }
        temp=temp->next;
        }
    }
    else{
        int i=0;
           transaction*temp=cursor->prev;
      while((temp!=head)&&(i<abs(M))){
        if(temp->acno==ac){
            bankaccount *temp2 = list1.first;
      while (temp2->accno!=temp->acno) {
        temp2=temp2->next;
      }
          if (temp->dorw == 'W') {
            temp2->currentbalance = temp2->currentbalance + temp->amount;
          } else {
            temp2->currentbalance = temp2->currentbalance - temp->amount;
          }

             transaction*temp1=temp;
            (temp1->prev)->next=temp1->next;
            (temp1->next)->prev=temp1->prev;
            delete temp1;
          N--;
          i++;
        }
        temp=temp->prev;
        }
}
}

  friend class SingleLinkedList;
  friend class bankaccount;
  friend class transaction;
};

int main() {
  cout << "Enter the number of bank accounts: ";
  int C;
  cin >> C;
  SingleLinkedList list1;
  int k;
  cout << "Enter the account numbers:" << endl;
  for (int i = 0; i < C; i++) {
    cin >> k;
    list1.insertbankacc(k);
  }
  cout << "Enter the number of transactions: ";
  cin >> N;
  NN=N;
  DoubleLinkedList list2;
  int acno;
  char dorw1;
  int amount1;
  cout << "Enter the transactions (account_number direction amount):" << endl;
  for (int i = 0; i < N; i++) {
    cin >> acno >> dorw1 >> amount1;
    list2.inserttransaction(acno, dorw1, amount1);
  }
   // list1.print1();
   // list2.print2();
  string s;
  int x;
  cout << "Enter the operations (F, R, I, S, C, G, M, V, D) or END to exit:" << endl;
  cin >> s;
  while (s != "END") {
    if (s == "F") {
      cout << "Enter the number of transactions to process: ";
      cin >> x;
      list2.processnextxtransactions(x, list1);
      // list1.print1();
    }
     else if (s == "R") {
       cout << "Enter the number of transactions to undo: ";
      cin >> x;
      list2.undoytransactions(x, list1);
      // list1.print1();
    }
     else if (s == "I") {
      int acno;
      char c3;
      int amount3;
      int k;
       cout << "Enter the transaction details (account_number direction amount position): ";
      cin >> acno >> c3 >> amount3 >> k;
      transaction *t = new transaction(acno, c3, amount3);
      list2.insertkpos(t, k,list1);
      // list2.print2();
      // list1.print1();
    } 
    else if (s == "S") {// DISPLAYS ALL TRANSACTIONS OF ACCOUNT y
       cout << "Enter the account number to display transactions: ";
      int y;
      cin >> y;
      list2.printalltransactionsofy(y,list1);
    }
    else if(s=="C"){//PROCESSES ALL FURTHER TRANSACTIONS
       list2.processallfurthertransactions(list1); 
       // list1.print1();
    }
    else if(s=="G"){//PRINTS THE ACCOUNT NUMBERS WHICH HAVE CURRENT BALANCE GREATER THAN r
      cout << "Enter the minimum balance: ";
      int r;
      cin>>r;
      list2.print_no_of_accounts_with_currentbalance_morethan_or_equal_to_x(r,list1);
    }
    else if(s=="M"){//PRINTS THE ACCOUNT NUMBERS WHOSE BALANCE IS HIGHEST
        list2.printaccounts_with_highestbalance(list1);
    }
    else if(s=="V"){//PRINTS THE CURRENT BALANCE OF ACCOUNT NUMBER x
      cout << "Enter the account number to display current balance: ";
        cin>>x;
        list2.printcurrentbalance_of_x(x,list1);
    }
    else if(s=="D"){//DELETES M TRANSACTIONS OF A
      cout << "Enter the account number and number of transactions to delete: ";
        int A;
        cin>>A;
        int M;
        cin>>M;
        list2.deletetransaction(A,M,list1);
        // list2.print2();
        // list1.print1();
    }
    cout << "Enter the next operation or END to exit: ";
    cin >> s;
  }
  return 0;
}
