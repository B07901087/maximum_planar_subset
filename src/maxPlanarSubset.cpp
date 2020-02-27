#include <fstream>
#include <iostream>
#include <cstdlib>
#include<vector>
using namespace std;
vector< vector<int> > m;
vector< vector<bool> > b;
int rm(vector<int>& D, int start, int end)
{
    //cout << " start: "<<start <<" end: "<< end << endl;
    if ( end <= start )//base case
    {
        //cout << "base case" << endl;
        b[start][end]=false;
        return 0;
        
    }
    if (m[start][end]!=0)//感覺可以修
    {
        return m[start][end];
    }
    else 
    {
        //cout << "end: " << end;
        //cout << "=======in=======" << endl;
            
            if (D[end] == start)//case3
            {
                //cout << "case 3"<< endl;
                m[start][end] = rm( D, start + 1, end - 1) + 1;
                b[start][end]=true;
                
                return m[start][end];
            }    
                
            else  if (D[end] > start && D[end]<end)//case
                {
                    //cout << "case2" << endl;
                    int p = rm( D, start, end - 1);
                    int q = rm( D, start , D[end] - 1) + 1 + rm( D, D[end] + 1, end - 1);
                    
                    if (p>q) //case 2
                    {
                        //cout << "case 2-1" << endl;
                        m[start][end] = p;
                        b[start][end]=false;
                        return m[start][end];
                    }
                    else
                    {
                        //cout << "case 2-2" << endl;
                        m[start][end] = q;
                        b[start][end]=true;
                        b[D[end]][end]=true;
                        return m[start][end];
                    }
                }
            
        //cout << "case 1"<<endl;
        m[start][end]=rm( D, start, end - 1);
        if (b[start][end]==true)
        {cout << "something wrong";}
        b[start][end]=false;
        return m[start][end];
    }
    cout << "mission failed";
    exit(-1);
}
void output(fstream& fout , vector<int>& D,int begin, int ended)
    {
        if(ended>begin)
        {
            if (b[begin][ended]==true)
            {
                if (D[ended]==begin)//case3
                {
                    fout<<begin<<" "<<ended<<endl;
                    output(fout,D,begin+1,ended-1);
                }
                else
                {
                    output(fout,D,begin,D[ended]-1);
                    fout<<D[ended]<<" "<<ended<<endl;
                    output(fout,D,D[ended]+1,ended-1);
                }
            }
            else
            {
                output(fout,D,begin,ended-1);
            }
        }
    }

int main(int argc, char *argv[]) {
    if (argc!=3) {
        cout <<"wrong number of arguments: "<< argc  << endl;
        return 0;
    }
    //cout<<"correct"<<endl;

    char  number[8];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin.getline(number,6);
    
    int start,end;
    const int num = atoi(number);
    
    vector<int> data(num);
    
    for(int i=0;i< int(num/2) ;i++ ) {
        fin>>start>>end;
        //cout<<"start: "<<start<<" end: "<<end<<endl;
        data[start]=end;
        data[end]=start;


    }
    
    
    
    vector<int> row;
    vector<bool> row2;
    row.assign(num,0);//配置一個 row 的大小
    row2.assign(num , 0);
    m.assign(num,row);//配置2維
    b.assign(num,row2);
    
    
    fout<<rm(data,0,num-1)<<endl;
    output(fout,data,0,num-1);
    fin.close();
    fout.close();
    
    
    return 0;



}
