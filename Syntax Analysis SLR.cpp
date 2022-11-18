#include "Lexical Analyzer.cpp" 
#include<iostream> 
#include <iomanip> 
#include <bits/stdc++.h> 
#include<string>
#include<set>
#include<map>
#include <Windows.h>
#include <fstream> 
using namespace std;
 
typedef struct StackNode{ 
string data; 
StackNode *next; 
}StackNode, *LinkStack; 
bool InitStack(LinkStack &S); 
bool Push(LinkStack &S, string e); 
bool Pop(LinkStack &S, string &e); 
string GetTop(LinkStack S); 
string out(LinkStack S); 
int GetNum(LinkStack S); 
bool SLR1(); 
int is_Ter(string s); 
int is_Non_Ter(string s); 
int isStat(string s); 
string charToStr(char a);int check_gram(string s); 
string swap(string s); 
string G[10] ={"S->E","E->TA","A->+TA","A->","F->(E)","F->i","T->FB","B->*FB","B->"}; 
string ACTION[16][6]; 
string GOTO[16][5]; 
bool SLR1(){ 
bool flag = false; 
cout << "Enter a string ending with # :" << endl; 
string input="" ; 
cin >> input; 
int input_len = input.length(); 
text=input; 
while(pText<text.length()) 
{
LexicalAnalyzer(); 
} 
LinkStack sy;//symbol stack 
LinkStack st;//status stack 
InitStack(sy);// initialize symbol and state 
InitStack(st); 
cout << "Parsing Process:" << endl; 
cout <<"Steps\tState\t Symbol Input\t Action Goto Production" << endl; 
Push(st, "0"); 
Push(sy,"#"); 
int steps = 0; 
int i = 0; 
while (i<input_len){ 
cout << setw(8) << left << (steps+1);//output steps 
cout << setw(10) << left << out(st); //outpur state stack 
cout << setw(10) << left << out(sy);//output symbol stackcout << setw(15) << left << 
input.substr(i,input_len); //output input string 
string fir = charToStr(input[i]); 
int a = isStat(GetTop(st)); 
int b = is_Ter(fir); 
string act = ACTION[a][b]; 
if (act[0] == 's'){ 
cout << setw(10) << left << act << setw(10) << left << "0" << 
setw(5) << left <<"shift";
string z = charToStr(act[1]); 
Push(sy,fir); 
Push(st,z); 
i++; 
} 
else if (act[0] == 'r'){ 
string z = charToStr(act[1]); 
string gram = G[(z[0]-'0')]; 
int x = check_gram(gram); 
for (int q = 0; q < x; q++){ 
string toF = GetTop(sy); 
string toZ = GetTop(st); 
Pop(sy,toF); 
Pop(st,toZ); 
}
Push(sy, charToStr(gram[0])); 
string go = 
GOTO[isStat(GetTop(st))][is_Non_Ter(charToStr(gram[0]))]; 
char u=act[1]; 
cout << setw(10) << left << act << setw(10) << left << go<<setw(5) 
<< left <<G[u-'0']; 
if (go.length() == 1){ 
Push(st, go); } 
if (go.length() == 2){ 
Push(st, swap(go)); 
} 
} 
else if (act == "acc"){ 
if ((fir == "#") && (GetNum(sy) == 2) && (GetTop(sy) == "E")){ 
flag = true; 
cout << setw(10) << left << act << setw(10) << left << 
"0"<< setw(10) << endl; 
i++; 
break;} 
} 
else { 
cout<<"Error!"; 
break; 
}
cout << endl; 
steps++; 
} 
return flag; 
}
string swap(string s){ 
string ss; 
ss = charToStr(s[1]) + charToStr(s[0]); 
return ss; 
}
//change char to string 
string charToStr(char a){ 
char x[] = "1"; 
x[0] = a; 
return x; 
}
//Look how many digits are on the right of the production 
int check_gram(string s){ 
int x = 0; 
for (unsigned int i = 3; i < s.length(); i++){ 
x++; 
}
return x; 
}
int is_Ter(string s){ 
int x = -1; 
if (s == "i"){ 
x = 0; 
}
if (s == "+"){ 
x = 1; 
}
if (s == "*"){ 
x = 2; 
}
if (s == "("){ 
x = 3; 
}
if (s == ")"){x = 4; 
}
if (s == "#"){ 
x = 5; 
}
return x; 
}
int is_Non_Ter(string s){ 
int x = -1; 
if (s == "E"){ 
x = 0; 
}
if (s == "A"){ 
x = 1; 
}
if (s == "F"){ 
x = 2; 
}
if (s == "T"){ 
x = 3; 
}
if (s == "B"){ 
x = 4; 
}
return x; 
}
int isStat(string s){ 
int x = 0; 
if (s.length() == 1){ 
x = (s[0] - '0'); 
}
if (s.length() == 2){ 
x = (s[1] - '0') * 10 + (s[0] - '0'); 
}
return x; 
}
bool InitStack(LinkStack &S){ 
S = NULL; 
return true; 
}
bool Push(LinkStack &S, string e){StackNode *p; 
p = new StackNode; 
p->data = e; 
p->next = S; 
S = p; 
return true; 
}
bool Pop(LinkStack &S, string &e){ 
StackNode *p; 
if (S == NULL){ return false; } 
e = S->data; 
p = S; 
S = S->next; 
delete p; 
return true; 
}
//Take the top element of the stack 
string GetTop(LinkStack S){ 
if (S != NULL) 
{ 
return S->data; 
}
else{ 
return 0; 
} 
}
int GetNum(LinkStack S){ 
int num = 0; 
num++; 
while (S->next != NULL) 
{ 
num++; 
S = S->next; 
}
return num; 
}

string out(LinkStack S){ 
string str = ""; 
str += S->data; 
while (S->next != NULL) 
{ 
str += S->next->data; 
S = S->next; 
}reverse(str.begin(), str.end()); 
return str; 
}

class FF {
public:
 string fileName = "productions.txt";
 set<string> productions;//?????
 map<string, set<string>> split_productions;//?????????
 set<string> Vt;//?????
 set<string> Vn;//??????
 map<string, set<string>> first;//First?
 map<string, set<string>> follow;//Follow?

 void init();//????????
 void splitProductions();//?????
 void findVtAndVn();//??????????
 bool isVn(string s);
 bool isVt(string s);
 set<string> getOneFirst(string s);//????????first?
 void getFirst();//????????first?
 void getFollow();//????????follow?
 void SSS();//?folloe????3
};

void FF::init() {
 string line;
 ifstream in(fileName);
 if (in) {
  //???????follow????#
  getline(in, line);
  productions.insert(line);
  follow[line.substr(0, 1)].insert("#");
  cout << line << endl;
  while (getline(in, line)) {
   productions.insert(line);
   cout << line << endl;
  }
 }
}
void FF::splitProductions() {
 int position = 0;
 for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
  string temp = *it;
  for (int i = 0; i < temp.length(); i++) {
   position = temp.find("->");
   string s = temp.substr(0, position);
   string ss = temp.substr(position + 2);
   set<string>sss;
   string t;
   for (int j = 0; j < ss.length(); j++) {
    if (ss[j] == '|') {
     sss.insert(t);
     t = "";
    }
    else
    {
     t.append(ss.substr(j,1));
    }
    
   }
   sss.insert(t);
   split_productions.insert(pair<string, set<string>>(s, sss));
  }
 }
 for (map<string, set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
  cout << it->first << "    ";
  for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++) {
   cout << *ii << "    ";
  }
  cout << endl;
 }


}
void FF::findVtAndVn() {
 for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
  string temp = *it;
  for (int i = 0; i < temp.length(); i++) {
   if (temp[i] == '-' || temp[i] == '>' || temp[i] == '|')
    continue;
   //?????
   if (temp[i] >= 'A' && temp[i] <= 'Z') {
    //???'
    if (temp[i + 1] == '\'') {
     Vn.insert(temp.substr(i, 2));
     i++;
    }
    else {
     Vn.insert(temp.substr(i, 1));
    }
   }
   //????
   else
   {
    Vt.insert(temp.substr(i, 1));
   }
  }
 }

 cout << "????" << endl;
 for (set<string>::iterator it = Vn.begin(); it != Vn.end(); it++) {
  cout << *it << endl;
 }

 cout << "???" << endl;
 for (set<string>::iterator it = Vt.begin(); it != Vt.end(); it++) {
  cout << *it << endl;
 }
}
bool FF::isVn(string s) {
 if (Vn.find(s) != Vn.end()) {
  return true;
 }
 return false;
}
bool FF::isVt(string s) {
 if (Vt.find(s) != Vt.end()) {
  return true;
 }
 return false;
}
set<string> FF::getOneFirst(string s) {
 if (split_productions.count(s)>0) {
  set<string>temp = split_productions[s];
  for (set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
   string stemp = *it;
   if (stemp == "#") {
    first[s].insert("#");
   }
   else {
    int flagAll = 0;//????????first???#;
    for (int i = 0; i < stemp.length(); i++) {
     int flag = 0;//????????first??#;
     if (stemp[i+1] == '\'') {//?'?????
      set<string>t1 = getOneFirst(stemp.substr(i, 2));
      for (set<string>::iterator ii = t1.begin(); ii !=  t1.end(); ii++) {
       if (*ii == "#") {//????????
        flag = 1;
       }
       else {
        first[s].insert(*ii);
       }
      }
      i++;
     }
     else if(isVn(stemp.substr(i,1)))//??????
     {
      set<string>t2 = getOneFirst(stemp.substr(i, 1));
      for (set<string>::iterator ii = t2.begin(); ii != t2.end(); ii++) {
       if (*ii == "#") {//????????
        flag = 1;
       }
       else {
        first[s].insert(*ii);
       }
      }
     }
     else {//???
      first[s].insert(stemp.substr(i, 1));
     }
     if (i == stemp.length() - 1 && flag==1) {
      flagAll = 1;
     }
     if (flag == 0)
      break;

    }
    if (flagAll == 1) {
     first[s].insert("#");
    }
   }
  }
 }
 return first[s];
}
void FF::getFirst() {
 for (map<string, set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
  getOneFirst(it->first);
 }
 cout << "First?" << endl;
 for (map<string, set<string>>::iterator it = first.begin(); it != first.end(); it++) {
  cout << it->first << "  :  "  ;
  for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
  {
   cout << *ii << "    ";
  }
  cout << endl;
 }

}
void FF::getFollow() {
 for (map<string, set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
  string left = it->first;
  set<string>right = it->second;
  for (set<string>::iterator ii = right.begin(); ii != right.end(); ii++) {
   string temp = *ii;
   
   for (int i = 0; i < temp.length(); i++) {
    if (isVt(temp.substr(i, 1))) {//???
     continue;
    }
    else if (i+1<temp.length()&&temp[i + 1] == '\'') {//??’?????
     if (isVt(temp.substr(i + 2, 1))) {//??????????
      follow[temp.substr(i, 2)].insert(temp.substr(i + 2, 1));
      i++;
     }
     else {//???????????s
      //????????first?ff??follow??
      string s;
      if (i+3<temp.length()&& temp[i + 3] == '\'') {
       s = temp.substr(i + 2, 2);
      }
      else {
       s = temp.substr(i + 2, 1);
      }
      set<string> ff = first[s];
      for (set<string>::iterator nn = ff.begin(); nn != ff.end(); nn++) {
       if (*nn != "#")
        follow[temp.substr(i, 2)].insert(*nn);
      }
     }
    }
    else {//??’?????
     
     if (i+1<temp.length() && isVt(temp.substr(i + 1, 1))) {//??????????
      follow[temp.substr(i, 1)].insert(temp.substr(i + 1, 1));
      i++;
     }
     else {//???????????s
      //????????first?ff??follow??
      string s;
      if (i+2<temp.length() && temp[i + 2] == '\'') {
       s = temp.substr(i + 1, 2);
      }
      else {
       s = temp.substr(i + 1, 1);
      }
      set<string> ff = first[s];
      for (set<string>::iterator nn = ff.begin(); nn != ff.end(); nn++) {
       if (*nn != "#")
        follow[temp.substr(i, 1)].insert(*nn);
      }
     }
    }
   }
  }
 }
 //??????????,??follow??????
 SSS();
 SSS();

 cout << "Follow?" << endl;
 for (map<string, set<string>>::iterator it = follow.begin(); it != follow.end(); it++) {
  cout << it->first << "  :  ";
  for (set<string>::iterator ii = it->second.begin(); ii != it->second.end(); ii++)
  {
   cout << *ii << "    ";
  }
  cout << endl;
 }
}
void FF::SSS() {
 for (map<string, set<string>>::iterator it = split_productions.begin(); it != split_productions.end(); it++) {
  string left = it->first;
  set<string>right = it->second;
  for (set<string>::iterator ii = right.begin(); ii != right.end(); ii++) {
   string temp = *ii;
   for (int j = temp.length() - 1; j > 0; j--) {
    string now;
    if (temp[j] == '\'') {
     now = temp.substr(j - 1, 2);
     j--;
    }
    else now = temp.substr(j, 1);
    if (isVt(now)) {//?????????
     break;
    }
    else {//??????????
     set<string>aa = follow[left];
     for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
      follow[now].insert(*pp);
     }
    }
    if (first[now].find("#") == first[now].end())
     break;
   }
  }
 }
}

int main() {
cout <<"\n" ; 
cout << "Grammar:" << endl; 
cout << " S->E\nE->TA\nA->+TA\nA->\nF->(E)\nF->i\nT->FB\nB->*FB\nB->\n "<< endl;
cout << "Terminals: + , * , ( , ) , i" << endl; 
cout << "Nonterminals: S , E , A , F , T , B" << endl; 
cout << "First and Follow Sets:" << endl;
	FF ff;
	ff.init();
	ff.splitProductions();
	ff.findVtAndVn();
	ff.getFirst();
	ff.getFollow();
	cout << "..........................."<<endl;
	
//cout << "Follow S ={ # };" << endl; 
//cout << "Follow E ={ # , ) };" << endl; 
//cout << "Follow A ={ # , ) };" << endl; 
//cout << "Follow T ={ # , + , )};" << endl; 
//cout << "Follow B ={ # , + , )};" << endl; 
//cout << "Follow F ={ # , + , ) , * };" << endl; 
for (int i = 0; i < 16; i++){ 
for (int j = 0; j < 6; j++){ 
ACTION[i][j] = " "; 
}
for (int m = 0; m < 5; m++){ 
GOTO[i][m] = " "; 
} 
}
ACTION[0][0] = "s5"; 
ACTION[0][3] = "s4"; 
ACTION[1][5] = "acc"; 
ACTION[2][1] = "s7"; 
ACTION[2][4] = "r3"; 
ACTION[2][5] = "r3"; 
ACTION[3][1] = "r8"; 
ACTION[3][2] = "s9"; 
ACTION[3][4] = "r8"; 
ACTION[3][5] = "r8"; 
ACTION[4][0] = "s5"; 
ACTION[4][3] = "s4"; 
ACTION[5][1] = "r5"; 
ACTION[5][2] = "r5"; 
ACTION[5][4] = "r5"; 
ACTION[5][5] = "r5"; 
ACTION[6][4] = "r1"; 
ACTION[6][5] = "r1";ACTION[7][0] = "s5"; 
ACTION[7][3] = "s4"; 
ACTION[8][1] = "r6"; 
ACTION[8][4] = "r6"; 
ACTION[8][5] = "r6"; 
ACTION[9][0] = "s5"; 
ACTION[9][3] = "s4"; 
ACTION[10][4]= "s13"; 
ACTION[11][1]= "s7"; 
ACTION[11][4] = "r3"; 
ACTION[11][5] = "r3"; 
ACTION[12][1]= "r8"; 
ACTION[12][2] = "s9"; 
ACTION[12][4] = "r8"; 
ACTION[12][5] = "r8"; 
ACTION[13][1]= "r4"; 
ACTION[13][2] = "r4"; 
ACTION[13][4] = "r4"; 
ACTION[13][5] = "r4"; 
ACTION[14][4] = "r2"; 
ACTION[14][5] = "r2"; 
ACTION[15][1] = "r7"; 
ACTION[15][4] = "r7"; 
ACTION[15][5] = "r7"; 
GOTO[0][0] = "1"; 
GOTO[0][2] = "3"; 
GOTO[0][3] = "2"; 
GOTO[2][1] = "6"; 
GOTO[3][4] = "8"; 
GOTO[4][0] = "8"; 
GOTO[4][2] = "3"; 
GOTO[4][3] = "2"; 
GOTO[7][2] = "3"; 
GOTO[7][3] = "11"; 
GOTO[9][2] = "12"; 
GOTO[11][1] = "14"; 
GOTO[12][4] = "15"; 
cout << "Parsing Table:" << endl; 
cout << " i\t+\t*\t(\t)\t#\tE\tA\tF\tT\tB" << endl; 
for (int i = 0; i < 16; i++){ 
cout << i << " "; 
for (int j = 0; j < 6; j++){ 
cout << ACTION[i][j] << "\t"; 
if (j == 5){ 
for (int m = 0; m < 5; m++){ 
cout << GOTO[i][m]<< "\t"; 
}cout << endl; 
} 
} 
}
bool flag = false; 
flag=SLR1(); 
if (flag == true){ 
cout << endl << "Parsing Successful!" << endl; 
}
else{ 
cout << endl << "Parsing Failed!" << endl; 
} 
}


