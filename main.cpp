#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;
bool isonediff(string s1, string s2, string &returnstring){
    int returnval;
    int count=0;
    returnstring=s1;
    for(int i=0; i<s1.length(); i++){
        if(s1[i]!=s2[i]){
            count++;
            returnval=i;
        }
    }
    if(count==1){
        returnstring[returnval]='8';
        return true;
    }
    else return false;
    
}
struct implicants{
    set<string>primeimplicants;
    unordered_map<int, set<string>>checkessential;
    set<string>essentialprime;
    unordered_map<int, bool>doesithave;
    unordered_map<int, vector<string>>nonessprint;
    set<string>needednoness;
};
struct step1{
    vector<pair<string, string>>group0;
    vector<pair<string, string>>group1;
    vector<pair<string, string>>group2;
    vector<pair<string, string>>group3;
    unordered_map<string, bool>newmin;
};
struct step2{
    vector<pair<string, string>>group0;
    vector<pair<string, string>>group1;
    vector<pair<string, string>>group2;
    unordered_map<string, bool>newmin;
};
struct step3{
    vector<pair<string, string>>group0;
    vector<pair<string, string>>group1;
};
void assignstep1(implicants &iprime, step1 &istep1, set<int>minterms, unordered_map<int, bool>&newmin){
    unordered_map<int, pair<int, string>>findgroup;
    set<int>::iterator itty=minterms.begin();

    findgroup[0]=make_pair(0, "000"); findgroup[1]=make_pair(1,"001"); findgroup[2]=make_pair(1,"010"); findgroup[3]=make_pair(2, "011"); findgroup[4]=make_pair(1,"100"); findgroup[5]=make_pair(2, "101"); findgroup[6]=make_pair(2, "110"); findgroup[7]=make_pair(3, "111");
    for(int i=0; i<minterms.size(); i++){
        if(findgroup[*itty].first==0){
            istep1.group0.push_back(make_pair(to_string(*itty), findgroup[*itty].second));
        }
        if(findgroup[*itty].first==1){
            //cout<<"the iterator is "<<*itty<<endl;
            istep1.group1.push_back(make_pair(to_string(*itty), findgroup[*itty].second));
        }
        if(findgroup[*itty].first==2){
            istep1.group2.push_back(make_pair(to_string(*itty), findgroup[*itty].second));
        }
        if(findgroup[*itty].first==3){
            istep1.group3.push_back(make_pair(to_string(*itty), findgroup[*itty].second));
        }
        itty++;
    }
}
void assignstep2(implicants &iprime, step1 &istep1, step2 &istep2){
    string returnstring;
    bool lestry=false;
    for(int i=0; i<istep1.group0.size();i++){
        for(int j=0; j<istep1.group1.size(); j++){
            lestry=true;
            if(isonediff(istep1.group0[i].second, istep1.group1[j].second, returnstring)){
                istep1.newmin[istep1.group0[i].second]=true;
                istep1.newmin[istep1.group1[j].second]=true;
                istep2.group0.push_back(make_pair(istep1.group0[i].first+","+istep1.group1[j].first, returnstring));
            }
            else{
                if(istep1.newmin.find(istep1.group0[i].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group0[i].second]=false;
                }
                    
                if(istep1.newmin.find(istep1.group1[j].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group1[j].second]=false;
                }
            }
        }
    }
    if(lestry==false){
        for(int i=0; i<istep1.group0.size();i++){
            if(istep1.newmin.find(istep1.group0[i].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group0[i].second]=false;
            }
        }
        for(int j=0; j<istep1.group1.size(); j++){
            if(istep1.newmin.find(istep1.group1[j].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group1[j].second]=false;
            }
        }
    }
    lestry=false;
    for(int i=0; i<istep1.group1.size();i++){
        for(int j=0; j<istep1.group2.size(); j++){
            lestry=true;
            if(isonediff(istep1.group1[i].second, istep1.group2[j].second, returnstring)){
                istep1.newmin[istep1.group1[i].second]=true;
                istep1.newmin[istep1.group2[j].second]=true;
                istep2.group1.push_back(make_pair(istep1.group1[i].first+","+istep1.group2[j].first, returnstring));
            }
            else{
                if(istep1.newmin.find(istep1.group1[i].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group1[i].second]=false;
                }
                    
                if(istep1.newmin.find(istep1.group2[j].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group2[j].second]=false;
                }
            }
        }
    }
    if(lestry==false){
        for(int i=0; i<istep1.group1.size();i++){
            if(istep1.newmin.find(istep1.group1[i].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group1[i].second]=false;
            }
        }
        for(int j=0; j<istep1.group2.size(); j++){
            if(istep1.newmin.find(istep1.group2[j].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group2[j].second]=false;
            }
        }
    }
    lestry=false;
    for(int i=0; i<istep1.group2.size();i++){
        for(int j=0; j<istep1.group3.size(); j++){
            lestry=true;
            if(isonediff(istep1.group2[i].second, istep1.group3[j].second, returnstring)){
                istep1.newmin[istep1.group2[i].second]=true;
                istep1.newmin[istep1.group3[j].second]=true;
                istep2.group2.push_back(make_pair(istep1.group2[i].first+","+istep1.group3[j].first, returnstring));
            }
            else{
                if(istep1.newmin.find(istep1.group2[i].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group2[i].second]=false;
                }
                    
                if(istep1.newmin.find(istep1.group3[j].second)==istep1.newmin.end()){
                    istep1.newmin[istep1.group3[j].second]=false;
                }
            }
        }
    }
    if(lestry==false){
        for(int i=0; i<istep1.group2.size();i++){
            if(istep1.newmin.find(istep1.group2[i].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group2[i].second]=false;
            }
        }
        for(int j=0; j<istep1.group3.size(); j++){
            if(istep1.newmin.find(istep1.group3[j].second)==istep1.newmin.end()){
                istep1.newmin[istep1.group3[j].second]=false;
            }
        }
    }
}
void assignstep3(implicants &iprime, step1 &istep1,step2 &istep2, step3 &istep3){
    set<string>displaystring;
    string returnstring;
    bool lestry=false;
    //cout<<"why do you hate me "<<endl;
    for(int i=0; i<istep2.group0.size();i++){
        for(int j=0; j<istep2.group1.size(); j++){
            lestry=true;
            if(isonediff(istep2.group0[i].second, istep2.group1[j].second, returnstring)){
                istep2.newmin[istep2.group0[i].second]=true;
                istep2.newmin[istep2.group1[j].second]=true;
                istep3.group0.push_back(make_pair(istep2.group0[i].first+","+istep2.group1[j].first, returnstring));
                displaystring.insert(returnstring);
            }
            else{
                if(istep2.newmin.find(istep2.group0[i].second)==istep2.newmin.end()){
                    istep2.newmin[istep2.group0[i].second]=false;
                }
                    
                if(istep2.newmin.find(istep2.group1[j].second)==istep2.newmin.end()){
                    istep2.newmin[istep2.group1[j].second]=false;
                }
            }
        }
    }
    if(lestry==false){
        for(int i=0; i<istep2.group0.size();i++){
            if(istep2.newmin.find(istep2.group0[i].second)==istep2.newmin.end()){
                istep2.newmin[istep2.group0[i].second]=false;
            }
        }
        for(int j=0; j<istep2.group1.size(); j++){
            if(istep2.newmin.find(istep2.group1[j].second)==istep2.newmin.end()){
                istep2.newmin[istep2.group1[j].second]=false;
            }
        }
    }
    lestry=false;
    //cout<<"i love you babey "<<endl;
    for(int i=0; i<istep2.group1.size();i++){
        for(int j=0; j<istep2.group2.size(); j++){
            lestry=true;
            if(isonediff(istep2.group1[i].second, istep2.group2[j].second, returnstring)){
                istep2.newmin[istep2.group1[i].second]=true;
                istep2.newmin[istep2.group2[j].second]=true;
                istep3.group1.push_back(make_pair(istep2.group1[i].first+","+istep2.group2[j].first, returnstring));
                displaystring.insert(returnstring);
            }
            else{
                if(istep2.newmin.find(istep2.group1[i].second)==istep2.newmin.end()){
                    istep2.newmin[istep2.group1[i].second]=false;
                }
                if(istep2.newmin.find(istep2.group2[j].second)==istep2.newmin.end()){
                    istep2.newmin[istep2.group2[j].second]=false;
                }
            }
        }
    }
    if(lestry==false){
        for(int i=0; i<istep2.group1.size();i++){
            if(istep2.newmin.find(istep2.group1[i].second)==istep2.newmin.end()){
                istep2.newmin[istep2.group1[i].second]=false;
            }
        }
        for(int j=0; j<istep2.group2.size(); j++){
            if(istep2.newmin.find(istep2.group2[j].second)==istep2.newmin.end()){
                istep2.newmin[istep2.group2[j].second]=false;
            }
        }
    }

    unordered_map<int, char>getletter;
        set<string>::iterator displayitty=displaystring.begin();
        getletter[0]='A'; getletter[1]='B'; getletter[2]='C';
        
    for(displayitty; displayitty!=displaystring.end(); displayitty++){
            iprime.primeimplicants.insert(*displayitty);
    }
        
        bool addzero=false;
        int counter=1;
        unordered_map<string, bool>::iterator ittybool;

    for(ittybool=istep2.newmin.begin(); ittybool!=istep2.newmin.end(); ittybool++){
            if(ittybool->second==false)
                iprime.primeimplicants.insert((*ittybool).first);
        }
        
        counter=1;
        addzero=false;
        for(ittybool=istep1.newmin.begin(); ittybool!=istep1.newmin.end(); ittybool++){
            if(ittybool->second==false)
                iprime.primeimplicants.insert((*ittybool).first);
        }
    set<string>::iterator itty=iprime.primeimplicants.begin();
    
    for(int i=0; i<iprime.primeimplicants.size(); i++){
        for(int j=0; j<(*itty).length(); j++){
            if((*itty)[j]=='0'){
                //cout<<"the letter is "<<(*itty)[j]<<endl;
                cout<<"~"<<getletter[j];
            }else if((*itty)[j]=='1'){
                //cout<<"the letter is "<<(*itty)[j]<<endl;
                cout<<getletter[j];
            }
        }
        itty++;
        if(i<iprime.primeimplicants.size()-1)
        cout<<" + ";
    }
    cout<<endl;
}
void validateinput(set<int>&mintermsinput, int &numofvar){
    int tempvar, numofmin, maxmins;
    numofvar=3;
    bool numofminn=false;
    do{
    cout<<"How many minterms is your function?"<<endl;
        cin>>numofmin;
        
        maxmins=pow(2, numofvar);
        int i=0;
        bool repeat=false;
        bool continuee=true;
        if(numofmin>0&&numofmin<=maxmins){
            numofminn=false;
            do {
                i=0;
                tempvar=0;
                mintermsinput.clear();
        cout<<"Please enter the minterms as decimals, press enter after each digit: ";
        while(i<numofmin&&tempvar>=0&&tempvar<maxmins){
            continuee= false;
            cin>>tempvar;
            if(mintermsinput.find(tempvar)==mintermsinput.end()){
            if(tempvar<0||tempvar>=maxmins){
                cout<<"invalid minterm, try again"<<endl;
                continuee=false;
                i=0;
            }else{
            mintermsinput.insert(tempvar);
                i++;
                continuee=true;
            }
                repeat=false;
            }
            else {cout<<"You repeated a minterm, try again"<<endl;
                repeat=true;
                i=0;
                break;
            }
        }
            }while(continuee==false||repeat==true);
        }
        else{
            cout<<"invalid number of minterms"<<endl;
            numofminn=true;
        }
    }while(numofminn==true);
    
}
void printkmap(set<int>minterms, int numofvars){
       unordered_map<int, pair<int,int>>umap;
       umap[0]=make_pair(0,0); umap[1]=make_pair(0, 1); umap[2]=make_pair(0,3); umap[3]=make_pair(0, 2);
       umap[4]=make_pair(1,0); umap[5]=make_pair(1,1); umap[6]=make_pair(1,3); umap[7]=make_pair(1,2);
       
       // set<int>::iterator itty=minterms.begin();

       int printarray2[1][4]={0};
       int printarray3[2][4]={0};
       
       for(auto it : minterms){
           // printarray2[umap[it].first][umap[it].second]=1;
           printarray3[umap[it].first][umap[it].second]=1;
       }
       
       if(numofvars==2){
           for(int i=0; i<1; i++){
               for(int j=0; j<4; j++){
                   cout<<printarray2[i][j]<<" ";
               }
               cout<<endl;
           }
           
       }
       else if(numofvars==3){
           for(int i=0; i<2; i++){
               for(int j=0; j<4; j++){
                   cout<<printarray3[i][j]<<" ";
               }
               cout<<endl;
           }
       }
}
int main() {
    set<int>mintermsinput;
    int numofvar=0;
    
    implicants instprime;
    step1 inststep1;
    step2 inststep2;
    step3 inststep3;
    unordered_map<int, bool>newmin;
    validateinput(mintermsinput, numofvar);
    set <int>::iterator itty=mintermsinput.begin();
    
    for(int i=0; i<mintermsinput.size(); i++){
        newmin[*itty]=false;
        itty++;
    }
    printkmap(mintermsinput, numofvar);
    assignstep1(instprime, inststep1, mintermsinput, newmin);
    assignstep2(instprime, inststep1, inststep2);
    assignstep3(instprime, inststep1, inststep2, inststep3);
    
    return 0;
}
