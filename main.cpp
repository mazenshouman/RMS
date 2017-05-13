#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iomanip>

typedef struct {
    int p_Id;
    int ex;
    int pr;
    int rt;
    int ready;
}Process;

using namespace std;

bool cmp (Process a , Process b){
    return(a.pr < b.pr);
}

int find_lcm(vector <Process> data , int limit){
    int maax1 , maax2 , counter=1;
    bool notfound=true;
    maax2=maax1=data[limit-1].pr;
    while(notfound){
        for(int j=0 ; j<limit-1 ; j++){
            if(!(maax2%data[j].pr));
            else break;
            if(j==(limit-2)){
                notfound=false;
                break;
            }
        }
        if(!notfound)
            break;
        else{
           maax2 = maax1*(++counter);
        }
    }
    return maax2;
}
int main()
{
    int no , ex , pr , lcm;
    double utilization=0;
    int totalExecutionTime=0;
    vector <Process> data;
    Process temp;
    cout << "please enter number of processes " << endl;
    cin >> no;
    cout << "please enter the data for each process" << endl;

    for(int i=1 ; i<=no ; i++){
        cout << "P" << i << " \n" << "Execution time : ";
        cin >> ex ;
        cout << "Period : ";
        cin >> pr;
        cout << endl;
        temp.p_Id=i;
        temp.ex=ex;
        temp.pr=pr;
        temp.ready=1;
        temp.rt=ex;
        data.push_back(temp);
    }

    sort(data.begin() , data.end() , cmp);
    lcm=find_lcm(data , no);

    cout << "Process No.\t\tExecution time \t\t Period" << endl;
    for(int i=0 ; i<no ; i++){
        totalExecutionTime+=(lcm/data[i].pr)*data[i].ex;
        cout <<"    "<< data[i].p_Id << "\t\t\t\t" << data[i].ex << "\t\t    " << data[i].pr<< endl;
    }

    if(totalExecutionTime > lcm){
        cout <<"\n\nTotal execution time is more than LCM so RMS is not feasible here" << endl;
        return 0;
    }

    utilization=(totalExecutionTime*1.0/lcm) *100;
    cout << setprecision(4)<<"\n\nUtilization = " << utilization << "%\n";

    cout << "\n\nLCM = " << lcm << endl;
    cout <<"\n  Time" << "\t\t Running Process\n";
    for(int i=0 ; i<lcm ; i++){
        if(i>=data[0].pr)//re-new process at each period
            for(int j=0 ; j<no ; j++){
                if(!(i%data[j].pr))//if period re-newed
                    data[j].ready=1;//set it ready
            }
        for(int j=0 ; j<no ; j++){
            if(data[j].ready){//ready
                if(data[j].rt){//has remaining execution time
                    if(!(--(data[j].rt))){//reduce remaining execution time and check it
                        data[j].ready=0;//put status waiting
                        data[j].rt=data[j].ex;//reset remaining time
                    }
                }
                cout << "   " << i << "\t\t\tP" << data[j].p_Id<< endl;
                break;
            }
        }
    }
    return 0;
}
