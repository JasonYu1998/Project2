#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include <stack>
#include <iomanip>
#include <vector>
#include<fstream>
#include<cstdlib>

using namespace std;

queue<int> q,q1,qi,qc,qc2,tr,td,tl,td1,td2,tl1;
stack<int> s,si,sl;
vector<stack<int>> sU,sD,sL,sR,v1,v0;
vector<queue<int>> qU,qD,qL,qR,v2,qur,qul,qud,qlr,qld,qdr,qur1,qul1,qud1,qlr1,qld1,qdr1;
int T=0;

void change(queue<int> &qc){
    int r=qc.size()/2;
    int *A= new int[r],*B= new int[r],i=0;
    while(!qc.empty()){A[i]=qc.front();qc.pop();B[i]=qc.front();qc.pop();i++;}
    for(int k=r-1;k>=0;k--){qc.push(A[k]);qc.push(B[k]);}
    delete [] A;delete [] B;
}
void change2(queue<int> &qc2,int rx,int ry){
    int r=qc2.size()/2;
    int *A= new int[r],*B= new int[r],i=0;
    while(!qc2.empty()){A[i]=qc2.front();qc2.pop();B[i]=qc2.front();qc2.pop();i++;}
    qc2.push(rx);qc2.push(ry);
    for(int k=r-1;k>=0;k--){qc2.push(A[k]);qc2.push(B[k]);}
    delete [] A;delete [] B;
}

void combine(stack<int> &si,queue<int> &qi,queue<int> &qc){
    int a;
    while(!si.empty()){a=si.top();si.pop();qc.push(a);}
    while(!qi.empty()){a=qi.front();qi.pop();qc.push(a);}
}
void serch1(int **dist,int x,int y,int **visited,stack<int> &si){
    si.push(y);si.push(x);visited[x][y]=true;T++;
    if(dist[x][y]==0) return;
    else if(dist[x][y]>dist[x][y-1] && !visited[x][y-1]){serch1(dist,x,y-1,visited,si);}
    else if(dist[x][y]>dist[x][y+1] && !visited[x][y+1]){serch1(dist,x,y+1,visited,si);}
    else if(dist[x][y]>dist[x-1][y] && !visited[x-1][y]){serch1(dist,x-1,y,visited,si);}
    else if(dist[x][y]>dist[x+1][y] && !visited[x+1][y]){serch1(dist,x+1,y,visited,si);}
    else if(dist[x][y]>dist[x][y-1]  ){serch1(dist,x,y-1,visited,si);}
    else if(dist[x][y]>dist[x][y+1]  ){serch1(dist,x,y+1,visited,si);}
    else if(dist[x][y]>dist[x-1][y]  ){serch1(dist,x-1,y,visited,si);}
    else if(dist[x][y]>dist[x+1][y]  ){serch1(dist,x+1,y,visited,si);}

}
void serch2(int **dist,int x,int y,int **visited,queue<int> &qi,stack<int> &sl,int b){
    qi.push(x);qi.push(y);visited[x][y]=true;T++;sl.push(y);sl.push(x);
    if(dist[x][y]==0) return;
    else if(b>dist[x][y-1] && !visited[x][y-1]){b--;serch2(dist,x,y-1,visited,qi,sl,b);}
    else if(b>dist[x][y+1] && !visited[x][y+1]){b--;serch2(dist,x,y+1,visited,qi,sl,b);}
    else if(b>dist[x-1][y] && !visited[x-1][y]){b--;serch2(dist,x-1,y,visited,qi,sl,b);}
    else if(b>dist[x+1][y] && !visited[x+1][y]){b--;serch2(dist,x+1,y,visited,qi,sl,b);}
    else if(dist[x][y]>dist[x][y-1]  ){b--;serch2(dist,x,y-1,visited,qi,sl,b);}
    else if(dist[x][y]>dist[x][y+1]  ){b--;serch2(dist,x,y+1,visited,qi,sl,b);}
    else if(dist[x][y]>dist[x-1][y]  ){b--;serch2(dist,x-1,y,visited,qi,sl,b);}
    else if(dist[x][y]>dist[x+1][y]  ){b--;serch2(dist,x+1,y,visited,qi,sl,b);}

}
void serch3(int **dist,int x,int y,stack<int> &si){cout<<2;
    si.push(y);si.push(x);
    if(dist[x][y]==0) return;
    else if(dist[x][y]>dist[x][y-1]  ){serch3(dist,x,y-1,si);}
    else if(dist[x][y]>dist[x-1][y]  ){serch3(dist,x-1,y,si);}
    else if(dist[x][y]>dist[x][y+1]  ){serch3(dist,x,y+1,si);}
    else if(dist[x][y]>dist[x+1][y]  ){serch3(dist,x+1,y,si);}

}
void serch4(int **dist,int x,int y,queue<int> &qi,stack<int> &sl){
    qi.push(x);qi.push(y);sl.push(y);sl.push(x);cout<<3;
    if(dist[x][y]==0) return;
    else if(dist[x][y]>dist[x+1][y]  ){serch4(dist,x+1,y,qi,sl);}
    else if(dist[x][y]>dist[x][y+1]  ){serch4(dist,x,y+1,qi,sl);}
    else if(dist[x][y]>dist[x-1][y]  ){serch4(dist,x-1,y,qi,sl);}
    else if(dist[x][y]>dist[x][y-1]  ){serch4(dist,x,y-1,qi,sl);}

}

void bfs_table(int **dist,int n,int m,int x,int y){ // target = 'd', 'u', 'r', 'l'
    int **visit = new int*[n+2];
    int *tmp = new int[(n+2)*(m+2)];
    for(int i=1;i<=n;i++) visit[i] = &(tmp[i*(m+2)]);
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			visit[i][j]=false;
		}
    }
    q1.push(x);q1.push(y);visit[x][y]=true;
    while(!q1.empty()){
        x=q1.front();q1.pop();y=q1.front();q1.pop();
        s.push(y);s.push(x);
        q.push(x);q.push(y);
        if(dist[x][y-1]==0 && !visit[x][y-1]){q1.push(x);q1.push(y-1);visit[x][y-1]=true;dist[x][y-1]=dist[x][y]+1;}
        if(dist[x][y+1]==0 && !visit[x][y+1]){q1.push(x);q1.push(y+1);visit[x][y+1]=true;dist[x][y+1]=dist[x][y]+1;}
        if(dist[x+1][y]==0 && !visit[x+1][y]){q1.push(x+1);q1.push(y);visit[x+1][y]=true;dist[x+1][y]=dist[x][y]+1;}
        if(dist[x-1][y]==0 && !visit[x-1][y]){q1.push(x-1);q1.push(y);visit[x-1][y]=true;dist[x-1][y]=dist[x][y]+1;}

            }
    delete [] tmp; delete [] visit;

}
int ti,tj,r1,r2;
bool found=false,turn[6];
stack<int> tmpr,tmpc;

/*void go(int ti, int tj, int r1, int r2, int B, int **dist, stack<int> &tmpr, stack<int> &tmpc, bool &found,int m,int n){

	if(found == false){
		if(ti == r1 && tj == r2 && dist[ti][tj] == 0){
			tmpr.push(ti); tmpc.push(tj);
			found = true;
		}
		else if(dist[ti][tj] == 0 && tmpr.size() < B)
		{
			dist[ti][tj] = m*n;
			tmpr.push(ti); tmpc.push(tj);

			go(ti+1,tj,r1,r2,B,dist,tmpr,tmpc,found,m,n);
			go(ti,tj+1,r1,r2,B,dist,tmpr,tmpc,found,m,n);
			go(ti,tj-1,r1,r2,B,dist,tmpr,tmpc,found,m,n);
			go(ti-1,tj,r1,r2,B,dist,tmpr,tmpc,found,m,n);

			dist[ti][tj] = 0;
			if(found == false){
				tmpr.pop();tmpc.pop();
			}
		}
	}
}*/



int main(void){
    int i,j,B,co=0;
    int n,m,rx,ry;
    char c;
    queue<int> point;
    fstream data;
    data.open ("floor.data", ios::in );
    data>>n>>m>>B;
    int **dist = new int*[n+2];
    int *tmp = new int[(n+2)*(m+2)];
    for(i=0;i<n+2;i++) dist[i] = &(tmp[i*(m+2)]);

    int **dist_l = new int*[n+2];
    int *tmp_l = new int[(n+2)*(m+2)];
    for(i=0;i<n+2;i++) dist_l[i] = &(tmp_l[i*(m+2)]);

    int **dist_u = new int*[n+2];
    int *tmp_u = new int[(n+2)*(m+2)];
    for(i=0;i<n+2;i++) dist_u[i] = &(tmp_u[i*(m+2)]);

    int **dist_d = new int*[n+2];
    int *tmp_d = new int[(n+2)*(m+2)];
    for(i=0;i<n+2;i++) dist_d[i] = &(tmp_d[i*(m+2)]);

    int **dist_r = new int*[n+2];
    int *tmp_r = new int[(n+2)*(m+2)];
    for(i=0;i<n+2;i++) dist_r[i] = &(tmp_r[i*(m+2)]);


    for(i=0;i<n+2;i++) for(j=0;j<m+2;j++) dist[i][j]=0;
    for(j=1;j<=m;j++) { dist[0][j] = n*m; dist[n+1][j] = n*m; }
    for(i=1;i<=n;i++) {
        dist[i][0] = n*m;
        for(j=1;j<=m;j++){
            data>>c;
            if(c=='1') dist[i][j]=m*n;
            else if(c=='R'){dist[i][j]=0;rx=i;ry=j;}
            else dist[i][j]=0;
        }
        dist[i][m+1] = n*m;
    }
    data.close();

    for(i=0;i<n+2;i++) {
        for(j=0;j<m+2;j++) {
            dist_l[i][j]=dist[i][j];
            dist_r[i][j]=dist[i][j];
            dist_u[i][j]=dist[i][j];
            dist_d[i][j]=dist[i][j];
        }
    }


     if(dist[rx-1][ry]==m*n && dist[rx+1][ry]==m*n && dist[rx][ry-1]==m*n && dist[rx][ry+1]==m*n){
            ofstream peak("final.path");
            peak << "0" <<endl;
    peak.close();
		return 0;}

    dist[rx][ry]=0;
    bfs_table(dist,n,m,rx,ry);
    dist_l[rx][ry] = n*m;
    dist_l[rx][ry-1] = 1;
    dist_u[rx][ry] = n*m;
    dist_u[rx-1][ry] = 1;
    dist_d[rx][ry] = n*m;
    dist_d[rx+1][ry] = 1;
    dist_r[rx][ry] = n*m;
    dist_r[rx][ry+1] = 1;

    bfs_table(dist_l,n,m,rx,ry-1);
    bfs_table(dist_u,n,m,rx-1,ry);
    bfs_table(dist_d,n,m,rx+1,ry);
    bfs_table(dist_r,n,m,rx,ry+1);

    /* up to left */
/**
      r l u d
    r 1 1 0 1
    l 1 1 0 1
    u 0 0 1 1
    d 1 1 1 1
**/
    vector<int> path_up_to_left, path_left_to_down, path_down_to_right;

    path_up_to_left.push(rx);path_up_to_left.push(ry);
    if (dist[rx-1][ry] != n*m && dist[rx][ry-1] != n*m) {
        if (B >= dist_l[rx-1][ry]) { // up->left

        } else if (B >= dist_r[rx-1][ry]) { // up->right
        } else if (B >= dist_d[rx-1][ry]) {
        }
            x = rx-1;
            y = ry;
            path_up_to_left.push(x);path_up_to_left.push(y);
            while(x != rx && y != ry-1) {
                if (dist_l[x+1][y] < dist_l[x][y]) {x++; path_up_to_left.push(x);path_up_to_left.push(y);}
                if (dist_l[x-1][y] < dist_l[x][y]) {x--; path_up_to_left.push(x);path_up_to_left.push(y);}
                if (dist_l[x][y+1] < dist_l[x][y]) {y++; path_up_to_left.push(x);path_up_to_left.push(y);}
                if (dist_l[x][y-1] < dist_l[x][y]) {y--; path_up_to_left.push(x);path_up_to_left.push(y);}
            }
        }

    }

    /* left to down */
    path_left_to_down.push(rx);path_left_to_down.push(ry);
    if (dist[rx][ry-1] != n*m && dist[rx+1][ry] != n*m) {

    }

    /* down to right */
    if (dist[rx+1][ry] != n*m && dist[rx][ry+1] != n*m) {

    }

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            printf("%2d ", dist_l[i][j]);
        }
        cout << endl;
    }
    return 0;



    int **visited = new int*[n+2];
    int *tmp1 = new int[(n+2)*(m+2)];
    for(int g=1;g<=n;g++) visited[g] = &(tmp1[g*(m+2)]);
    for(int g=1;g<=n;g++){
		for(int h=1;h<=m;h++){
			visited[g][h]=false;
		}
    }
    while(!s.empty()){
        int x,y;
        x=s.top(); s.pop();
        y=s.top(); s.pop();
        if(!visited[x][y]){
          int b=B-dist[x][y];
          serch1(dist,x,y,visited,si);
          serch2(dist,x,y,visited,qi,sl,b);
          qi.pop();qi.pop();
          int a1=si.top();si.pop();int a2=si.top();si.pop();int ax=si.top();si.pop();int ay=si.top();si.push(ax);si.push(a2);si.push(a1);
          int b1=sl.top();sl.pop();int b2=sl.top();sl.pop();int bx=sl.top();sl.pop();int by=sl.top();sl.push(bx);sl.push(b2);sl.push(b1);
          if(ax==bx && ay==by){
            if(ax==rx-1 && ay==ry) {sU.push_back(si);qU.push_back(qi);}//UU
            else if(ax==rx && ay==ry+1) {sR.push_back(si);qR.push_back(qi);}//RR
            else if(ax==rx+1 && ay==ry) {sD.push_back(si);qD.push_back(qi);}//DD
            else if(ax==rx && ay==ry-1) {sL.push_back(si);qL.push_back(qi);}//LL
          }
          else if(ax==rx-1 && ay==ry){//UX
            if(bx==rx && by==ry+1){combine(si,qi,qc);qur.push_back(qc);}
            if(bx==rx && by==ry-1){combine(si,qi,qc);qul.push_back(qc);}
            if(bx==rx+1 && by==ry){combine(si,qi,qc);qud.push_back(qc);}
          }
          else if(ax==rx && ay==ry-1){//L
            if(bx==rx && by==ry+1){combine(si,qi,qc);qlr.push_back(qc);}
            if(bx==rx-1 && by==ry){combine(si,qi,qc);change(qc);qul.push_back(qc);}
            if(bx==rx+1 && by==ry){combine(si,qi,qc);qld.push_back(qc);}
          }
          else if(ax==rx+1 && ay==ry){//D
            if(bx==rx && by==ry+1){combine(si,qi,qc);qdr.push_back(qc);}
            if(bx==rx-1 && by==ry){combine(si,qi,qc);change(qc);qud.push_back(qc);}
            if(bx==rx && by==ry-1){combine(si,qi,qc);change(qc);qld.push_back(qc);}
          }
          else if(ax==rx && ay==ry+1){//R
            if(bx==rx && by==ry-1){combine(si,qi,qc);change(qc);qlr.push_back(qc);}
            if(bx==rx-1 && by==ry){combine(si,qi,qc);change(qc);qur.push_back(qc);}
            if(bx==rx+1 && by==ry){combine(si,qi,qc);change(qc);qdr.push_back(qc);}
          }
          //v0.push_back(sl);
          //v1.push_back(si);
          //v2.push_back(qi);
          while(!si.empty()){si.pop();}
          while(!qi.empty()){qi.pop();}
          while(!qc.empty()){qc.pop();}

        }
        else continue;

    }
    stack<int> ss;


    bool finish[6]={!qul.empty(),!qld.empty(),!qdr.empty(),false,false,false};
    //finish ul ld dr ur ud lr
        while(!q.empty()){
        if(finish[0]==1 && finish[1]==1 && finish[2]==1) {cout<<1;break;}
        else{
        int x,y;
        q.pop();q.pop();
        x=q.front(); q.pop();
        y=q.front(); q.pop();
          serch3(dist,x,y,si);
          serch4(dist,x,y,qi,sl);
          qi.pop();qi.pop();
          int a1=si.top();si.pop();int a2=si.top();si.pop();int ax=si.top();si.pop();int ay=si.top();si.push(ax);si.push(a2);si.push(a1);
          int b1=sl.top();sl.pop();int b2=sl.top();sl.pop();int bx=sl.top();sl.pop();int by=sl.top();sl.push(bx);sl.push(b2);sl.push(b1);
          if(ax==rx-1 && ay==ry){//UX
            if(bx==rx && by==ry+1){if(finish[3]==0){combine(si,qi,qc);qur1.push_back(qc);finish[3]=true;}else continue;}
            if(bx==rx && by==ry-1){if(finish[0]==0){combine(si,qi,qc);qul1.push_back(qc);finish[0]=true;}else continue;}
            if(bx==rx+1 && by==ry){if(finish[4]==0){combine(si,qi,qc);qud1.push_back(qc);finish[4]=true;}else continue;}
          }
          else if(ax==rx && ay==ry-1){//L
            if(bx==rx && by==ry+1){if(finish[5]==0){combine(si,qi,qc);qlr1.push_back(qc);finish[5]=true;}else continue;}
            if(bx==rx-1 && by==ry){if(finish[0]==0){combine(si,qi,qc);change(qc);qul1.push_back(qc);finish[0]=true;}else continue;}
            if(bx==rx+1 && by==ry){if(finish[1]==0){combine(si,qi,qc);qld1.push_back(qc);finish[1]=true;}else continue;}
          }
          else if(ax==rx+1 && ay==ry){//D
            if(bx==rx && by==ry+1){if(finish[2]==0){combine(si,qi,qc);qdr1.push_back(qc);finish[2]=true;}else continue;}
            if(bx==rx-1 && by==ry){if(finish[4]==0){combine(si,qi,qc);change(qc);qud1.push_back(qc);finish[4]=true;}else continue;}
            if(bx==rx && by==ry-1){if(finish[1]==0){combine(si,qi,qc);change(qc);qld1.push_back(qc);finish[1]=true;}else continue;}
          }
          else if(ax==rx && ay==ry+1){//R
            if(bx==rx && by==ry-1){if(finish[5]==0){combine(si,qi,qc);change(qc);qlr1.push_back(qc);finish[5]=true;}else continue;}
            if(bx==rx-1 && by==ry){if(finish[3]==0){combine(si,qi,qc);change(qc);qur1.push_back(qc);finish[3]=true;}else continue;}
            if(bx==rx+1 && by==ry){if(finish[2]==0){combine(si,qi,qc);change(qc);qdr1.push_back(qc);finish[2]=true;}else continue;}
          }
          else continue;

          while(!si.empty()){si.pop();}
          while(!qi.empty()){qi.pop();}
          while(!qc.empty()){qc.pop();}

    }
        }
//ul
queue<int> q_ul,q_tmp,q_ud,q_ur,q_ld,q_lr,q_dr;
        if (finish[0]) { //ul
                q_ul = qul1[0];

        } else if (finish[3] && finish[5]) { //url
                q_ul = qur1[0];q_tmp = qlr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}
        } else if (finish[1] && finish[2] && finish[3]) { //urdl
                q_ul = qur1[0];q_tmp = qdr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qld1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}
        } else if (finish[4] && finish[1]) { //udl
                q_ul = qud1[0];q_tmp = qld1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}
        } else if (finish[2] && finish[4] && finish[5]) { //udrl
                q_ul = qud1[0];q_tmp = qdr1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qlr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        }
//ud
        if (finish[4]) { //ud
                q_ud = qud1[0];

        } else if (finish[3] && finish[2]) { //urd
                q_ud = qur1[0];q_tmp = qdr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        }
//ur
        if (finish[3]) { //ur
                q_ur = qur1[0];
        }
//ld

        /**       0  1  2  3  4  5  **/
        /**finish ul ld dr ur ud lr **/
        if (finish[1]) {
                q_ld = qld1[0];
        } else if (finish[2] && finish[5]) { //lrd
                q_ld = qlr1[0];q_tmp = qdr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[0] && finish[3] && finish[2]) { //lurd
                q_ld = qul1[0];change(q_ld);q_tmp = qur1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qdr1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[0] && finish[4]) { //lud
                q_ld = qul1[0];change(q_ld);q_tmp = qud1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[5] && finish[3] && finish[4]) { //lrud
                q_ld = qlr1[0];q_tmp = qur1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qud1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        }
//lr
        if (finish[5]) { //lr
                q_lr = qlr1[0];
        } else if (finish[0] && finish[3]) { //lur
                q_lr = qul1[0];change(q_ld);q_tmp = qur1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        }
//dr
        /**       0  1  2  3  4  5  **/
        /**finish ul ld dr ur ud lr **/
        if (finish[2]) {
                q_dr = qdr1[0];
        } else if (finish[4] && finish[3]) { //dur
                q_dr = qud1[0];change(q_dr);q_tmp = qur1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[4] && finish[0] && finish[5]) { //dulr
                q_dr = qud1[0];change(q_dr);q_tmp = qul1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qlr1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[1] && finish[5]) { //dlr
                q_dr = qld1[0];change(q_dr);q_tmp = qlr1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        } else if (finish[1] && finish[0] && finish[3]) { //dlur
                q_dr = qld1[0];change(q_dr);q_tmp = qul1[0];change(q_tmp);while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);} q_tmp = qur1[0];while(!q_tmp.empty()){int w=q_tmp.front();q_tmp.pop();q_ul.push(w);}

        }

    //while(!qur.empty()){for(int i=qur.size()-1;i>=0 ;i--){change2(qur[i],rx,ry);qU.push_back(qc2);while(!qc2.empty()){qc2.pop();}}}
    //for(i=1;i<=n;i++) { for(j=1;j<=m-1;j++) cout<<setw(2)<<dist[i][j]<<" "; cout<<setw(2)<<dist[i][j]<<endl;}

    //for(int i=0;i<v1.size();i++){
            //cout<<T<<endl;
            //while(!v1[i].empty()){int t=v1[i].top();v1[i].pop();cout<<t<<" ";t=v1[i].top();v1[i].pop();cout<<t<<endl;}
            //while(v2[i].size()!=2){int t=v2[i].front();v2[i].pop();cout<<t<<" ";t=v2[i].front();v2[i].pop();cout<<t<<endl;}
            //v2[i].pop();v2[i].pop();
    //}
        for(int i=0;i<qU.size();i++){//UU
        //if(i==0){sU[i].pop();sU[i].pop();}
        while(!sU[i].empty()){int t=sU[i].top();sU[i].pop();point.push(t);co++;t=sU[i].top();sU[i].pop();point.push(t);}
        while(qU[i].size()!=2){int t=qU[i].front();qU[i].pop();point.push(t);co++;t=qU[i].front();qU[i].pop();point.push(t);}
        qU[i].pop();qU[i].pop();
    }

        for(int i=0;i<qur.size();i++){while(!qur[i].empty()){int t1=qur[i].front();qur[i].pop();point.push(t1);co++;int t2=qur[i].front();qur[i].pop();point.push(t2);ss.push(t2);ss.push(t1);}ss.pop();ss.pop();while(ss.size()!=2){int t=ss.top();ss.pop();point.push(t);co++;t=ss.top();ss.pop();point.push(t);}ss.pop();ss.pop();} //RIGHT
        for(int i=0;i<qud.size();i++){while(!qud[i].empty()){int t1=qud[i].front();qud[i].pop();point.push(t1);co++;int t2=qud[i].front();qud[i].pop();point.push(t2);ss.push(t2);ss.push(t1);}ss.pop();ss.pop();while(ss.size()!=2){int t=ss.top();ss.pop();point.push(t);co++;t=ss.top();ss.pop();point.push(t);}ss.pop();ss.pop();} //LEFT

        if(!qul.empty()){for(int i=0;i<qul.size();i++){while(qul[i].size()!=2){int t1=qul[i].front();qul[i].pop();point.push(t1);co++;int t2=qul[i].front();qul[i].pop();point.push(t2);} }}//LEFT
        else if(dist[rx][ry-1]!=1 && dist[rx+1][ry]!=1){while(q_ur.size()!=2){int t1=q_ur.front();q_ur.pop();point.push(t1);co++;int t2=q_ur.front();q_ur.pop();point.push(t2);}}
        else if(dist[rx][ry-1]!=1){while(q_ud.size()!=2){int t1=q_ud.front();q_ud.pop();point.push(t1);co++;int t2=q_ud.front();q_ud.pop();point.push(t2);}}
        else {while(q_ul.size()!=2){int t1=q_ul.front();q_ul.pop();point.push(t1);co++;int t2=q_ul.front();q_ul.pop();point.push(t2);}}

        for(int i=0;i<qL.size();i++){//LL
        while(!sL[i].empty()){int t=sL[i].top();sL[i].pop();point.push(t);co++;t=sL[i].top();sL[i].pop();point.push(t);}
        while(qL[i].size()!=2){int t=qL[i].front();qL[i].pop();point.push(t);co++;t=qL[i].front();qL[i].pop();point.push(t);}
        qL[i].pop();qL[i].pop();
    }

        for(int i=0;i<qlr.size();i++){while(!qlr[i].empty()){int t1=qlr[i].front();qlr[i].pop();point.push(t1);co++;int t2=qlr[i].front();qlr[i].pop();point.push(t2);ss.push(t2);ss.push(t1);}ss.pop();ss.pop();while(ss.size()!=2){int t=ss.top();ss.pop();point.push(t);co++;t=ss.top();ss.pop();point.push(t);}ss.pop();ss.pop();} //LEFT

        if(!qld.empty()){for(int i=0;i<qld.size();i++){while(qld[i].size()!=2){int t1=qld[i].front();qld[i].pop();point.push(t1);co++;int t2=qld[i].front();qld[i].pop();point.push(t2);}}}
        else if(dist[rx+1][ry]!=1){while(q_lr.size()!=2){int t1=q_lr.front();q_lr.pop();point.push(t1);co++;int t2=q_lr.front();q_lr.pop();point.push(t2);}}
        else {while(q_ld.size()!=2){int t1=q_ld.front();q_ld.pop();point.push(t1);co++;int t2=q_ld.front();q_ld.pop();point.push(t2);}}
        		//if(dist[rx][ry+1]!=1 && dist[rx+1][ry]!=1){while(!td2.empty()){point.push(td2.front());co++;td2.pop();point.push(td2.front());td2.pop();}}
                //else if(dist[rx][ry+1]!=1){while(!td1.empty()){point.push(td1.front());co++;td1.pop();point.push(td1.front());td1.pop();}}
                //else{while(!tr.empty()){point.push(tr.front());co++;tr.pop();point.push(tr.front());tr.pop();}}
        for(int i=0;i<qD.size();i++){//DD
        while(!sD[i].empty()){int t=sD[i].top();sD[i].pop();point.push(t);co++;t=sD[i].top();sD[i].pop();point.push(t);}
        while(qD[i].size()!=2){int t=qD[i].front();qD[i].pop();point.push(t);co++;t=qD[i].front();qD[i].pop();point.push(t);}
        qD[i].pop();qD[i].pop();
    }

        if(!qld.empty()){for(int i=0;i<qdr.size();i++){while(!qdr[i].empty()){int t1=qdr[i].front();qdr[i].pop();point.push(t1);co++;int t2=qdr[i].front();qdr[i].pop();point.push(t2);}}} //RIGHT
        else {while(q_dr.size()!=2){int t1=q_dr.front();q_dr.pop();point.push(t1);co++;int t2=q_dr.front();q_dr.pop();point.push(t2);}}


        for(int i=0;i<qR.size();i++){//RR
        while(!sR[i].empty()){int t=sR[i].top();sR[i].pop();point.push(t);co++;t=sR[i].top();sR[i].pop();point.push(t);}
        while(qR[i].size()!=2){int t=qR[i].front();qR[i].pop();point.push(t);co++;t=qR[i].front();qR[i].pop();point.push(t);}
        qR[i].pop();qR[i].pop();
    }
             //   if(dist[rx+1][ry]!=1){while(!tl1.empty()){point.push(tl1.front());co++;tl1.pop();point.push(tl1.front());tl1.pop();}}
              //   else{while(!td.empty()){point.push(td.front());co++;td.pop();point.push(td.front());td.pop();}}


                //while(!tl.empty()){point.push(tl.front());co++;tl.pop();point.push(tl.front());tl.pop();}



    point.push(rx);point.push(ry);co++;
    ofstream peak("final.path");
	peak << co <<endl;
	point.pop();point.pop();
	while(!point.empty()){
		peak << point.front()-1 << " ";
		point.pop();
		peak << point.front()-1 << endl;
		point.pop();
	}
    peak.close();
		return 0;

    //cout<<v1.size()<<endl<<sU.size()<<endl<<sR.size()+sD.size()+sL.size()<<endl<<qur.size()<<endl<<qul.size()<<endl<<qud.size()<<endl<<qlr.size()<<endl<<qld.size()<<endl<<qdr.size();

    delete [] dist; delete [] tmp;
    return 0;
}

