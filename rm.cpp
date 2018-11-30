#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
#include <math.h>

#define VMAX 1000
using namespace std;

typedef struct{
  int id;
  float e,p,d;
}task;
/*
class Comparator{
  public:
    bool operator()(const task& t1,const task& t2){
      return t1.p < t2.p;
    }
};*/

struct Comparator{
    bool operator()(const task& t1,const task& t2){
      return t2.p < t1.p;
    }
};


typedef long long int ll; 

bool isSchedulable(int n);
void grafico(int ap);

bool verify(const task& t1,const task& t2) {
   return t1.p < t2.p; 
}

int gcd(int a, int b){
  for (;;){
    if (a == 0) return b;
      b %= a;
    if (b == 0) return a;
      a %= b;
  }
}

int lcm(int a, int b){
  int temp = gcd(a, b);
  return temp ? (a / temp * b) : 0;
}

ll findlcm(int arr[], int n) 
{ 
    // Initialize result 
    ll ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / 
                (gcd(arr[i], ans))); 
  
    return ans; 
} 

vector<task> tasks;

int main(const int argc,const char *argv[]) {
  int n;
  int i=0;
  float ut,u,x,y;
  float e,p,d;
  ifstream input;

    if(argc!=2){
    cout << "Usage: ./rm <scheld> \n";
    return(-20);
  }

  input.open(argv[1]);
  if(!input){
    std::cerr << "Unable to open file" << std::endl;
  }else{
    while(input >> e >> p >> d){
      task temptask;
      temptask.e = e;//Execution Time
      temptask.p = p;//Period
      temptask.d = d;//Deadline
      temptask.id = i;
      tasks.push_back(temptask);
      i++;
    }
  }
  n = i;
  ut = 0;
  //calculate the utilization
  for(i=0;i<n;i++) {
    x=tasks[i].e/tasks[i].p;
    ut+=x;
  }

  //calculate value of U
  y=(float)n;
  y=y*((pow(2.0,1/y))-1);
  u=y;

  sort(tasks.begin(),tasks.end(),verify);

cout << endl;
  if(ut<u) {
    cout << "As " << ut << " < " << u;
    cout << "\nThe System is surely Schedulable\nScale:" << endl;
    for(i =0; i< tasks.size();i++){
      cout << "P" << tasks[i].id;
      if(i != (tasks.size()-1)) {
        cout << " => ";
      }
    }
    cout << endl;
  } else {
    cout << "As " << ut << " > " << u;
    cout << "\nNot Sure\nScale: \n";
    for(i =0; i < tasks.size();i++){
      cout << "P" << tasks[i].id;
      if(i != (tasks.size()-1)) {
          cout << " => ";
      }
    }
    cout << endl;
  }
  cout << endl;
  grafico(ut*100);

  do {
    cout << '\n' << "Press Enter to continue...\n\r";
   } while (cin.get() != '\n');

  if(isSchedulable(n)){
    cout << "\nThe System is Schedulable\n";
  }else{
    cout << "\nThe System isn't Schedulable\n";
  }

  return 0;
}

void grafico(int ap){
  int i,j,k=10;
  for(i=0;i<=10;i++){
    for(j=1;j<=28;j++){
      if(j==1 && i!=0){
        if(k<10){
          printf("%d0 ",k);
        }else{ 
          printf("%d0",k);
        }
        k--;
      }else if((j==2 || j==28) && i!=0){
        printf("|");
      }else if(i==(10-(ap/10)) && j==15){
          if(ap<10)printf("0%d%%",ap);
          else printf("%d%%",ap);
      }else if(i>(10-(ap/10)) && j>10 && j < 20){
          if(i < 3){cout << "\033[1;31m"; }else if(i < 5){cout << "\033[1;33m"; }else{ cout << "\033[1;32m"; }
          printf("*");
          cout << "\033[0m";
      }else if(!((i==(10-(ap/10)) && j==16) || (i==(10-(ap/10)) && j==17))){
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("   +-------------------------+\n");
  printf("        RateComputational\t\t\t\t \n\n");
  
}

bool isSchedulable(int n){
  int arr[n];
  priority_queue<task,vector<task>,Comparator> pq;

  for(int i=0;i<tasks.size();i++){
    arr[i] = tasks[i].p;
  }


  int size = sizeof(arr)/sizeof(arr[0]);
  int mmc = findlcm(arr,size);

  for(int i=0;i<mmc;i++){
      cout << "\nTime = " << i << endl;

    for(int j=0;j<n;j++){
      if((i % int(tasks[j].p)) == 0){
        task newtask = tasks[j];
        newtask.d += i;
        pq.push(newtask);
      }
    }

    if(!pq.empty()){
      task temptask = pq.top();
      temptask.e--;
      pq.pop();
      if(temptask.e != 0){
        pq.push(temptask);
      }else{
        cout << "\nRemoveu a task " << temptask.id << endl;
      }
    }
      vector<task> vtask;
      if(!pq.empty()){
      auto tempqueue = pq;
      while(!tempqueue.empty()){
        vtask.push_back(tempqueue.top());
        tempqueue.pop();
      }
}
      if(vtask.size()){
        for(int ak=0;ak < vtask.size();ak++){
          cout << "\nTask " << vtask[ak].id << " Tempo de execução "<< vtask[ak].e << " Periodo " << vtask[ak].p << " Deadline " << vtask[ak].d << endl;;
        }
      }

    for(int j=0;j<vtask.size();j++){
      if((vtask[j].d) < i){
        cout << "\nTask " << vtask[j].id << " Deadline " << vtask[j].d << " Expirado" <<endl;
        return false;
      }
    }
  }
  return true;
}
