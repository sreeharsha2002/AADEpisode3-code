// this code is a approximation algorithm (Heuristic -2)
#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define int long long int
int min(int a, int b) {  //returns minimum values
    if(a<b)
        return a;
    else 
        return b;
}
int K[60][20000];
void printknapSack(int W, int wt[], int val[], int n,int maxv,int m,string actval[])  //this will be done by dp.
{
    int i, v;
    //printf("%lld\n",n*maxv+1);
    //int K[n + 1][n*maxv + 1];             //dp array
    for (i = 0; i <= n; i++)                   //looping upto noof objects
    {
        for (v = 0; v <= n*maxv; v++)            //looping upto n*maximum value of val[].
        {
            if ( v == 0)                        //these are base cases.
                K[i][v] = 0;
            else if(i==0 && v!=0)
            {
                K[i][v]= INF;
            }
            else if (val[i-1] <= v)        //if the condition satisfied then we have to take the minimum of adding the weight to the dp or taking directly previous one.
            { 
                   K[i][v] = min(wt[i-1] +K[i - 1][v - val[i-1]], K[i - 1][v]);
            }
            else                         //otherwise we have to take the minimum of current weight and previous dp.
                K[i][v] = min(wt[i-1],K[i - 1][v]);
           // cout << K[i][v] << " , "<<endl;   
        }      
                               //logic is like we will find the minimum weight for the value 'v'. because more weights can be added futher in iteration.
    }
    int maxw=0,vf;
    for(int x=0;x<=n*maxv;x++)           //Above we did not pud the condition of max capacity of knapsack, So from dp we will get for  particular value 'v'  the value is the minimum weight (added the elements weight).
    {
        if(K[n][x]<=W)            //we will find the maximum value of dp and less than the Knapsack capacity. As we did in iterative i.e in increasing order so we can check only one condition <= W.
        {
            maxw = K[n][x];
            vf = x;
        }
    }
    int res = maxw;
    printf("%lld\n", vf*m);
    int  w = vf;
    for (i = n; i > 0 && res > 0; i--)   //Here we are printing which objects are taken into knapsack. going back from the weight and value we got. to find objects.
    {
        if (res == K[i - 1][w])         
            continue;
        else
        {
            cout<<actval[i-1]<<' ';      //outputing the name.
            res = res - wt[i-1];
            w = w - val[i-1];
        }  
    }
    cout << endl;
}
signed main()
{
    int n,W,m;
    scanf("%lld %lld %lld",&n,&W,&m);  //taking inputs noof objects , max capacity , and the m should be divided for actual values because they are very big and after dividing we will n^2Vmax algo.
    int actval[n];
    int  val[n],wt[n];
    string name[n];
    int maxv=0;
    for(int i=0;i<n;i++){
        cin>>name[i];
        cin>>actval[i];
        cin>>wt[i];
        val[i]=actval[i]/m;          //this approximation , here we are dividing actual values with m to get solved in n^2vmax time.
        if(maxv<val[i])
        {
            maxv=val[i];
        }
    }
    printknapSack(W, wt, val, n,maxv,m,name);      //printing total value and what the objects are.
    return 0;
}