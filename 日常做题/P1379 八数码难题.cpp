#include <cstdio>
#include <cstring>
struct node{ int map[5][5],wi,wj,t; } f[100001];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int xd[5][5]={0,0,0,0,0,
              0,1,2,3,0,
              0,8,0,4,0,
              0,7,6,5,0,
              0,0,0,0,0};
bool cq[9][9][9][9][9][9][9][9][9];
int nz[5][5];
bool zp(int tou)
{
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
        {
            if(f[tou].map[i][j]!=xd[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
bool pdc()
{
    if(cq[nz[1][1]][nz[1][2]][nz[1][3]][nz[2][1]][nz[2][2]][nz[2][3]][nz[3][1]][nz[3][2]][nz[3][3]]==true)
    {
        return false;
    }
    return true;
}
void paint()
{
    cq[nz[1][1]][nz[1][2]][nz[1][3]][nz[2][1]][nz[2][2]][nz[2][3]][nz[3][1]][nz[3][2]][nz[3][3]]=true;
}
void bfs()
{
    int tou=1,wei=2;
    while(tou<wei)
    {
        if(zp(tou)==true)
        {
            printf("%d",f[tou].t);
            return ;
        }
        for(int i=0;i<=3;i++)
        {
            int nx=f[tou].wi+dx[i];
            int ny=f[tou].wj+dy[i];
            if(nx>=1 && nx<=3 && ny>=1 && ny<=3)
            {
                memset(nz,0,sizeof(nz));
                for(int j=1;j<=3;j++)
                {
                    for(int k=1;k<=3;k++)
                    {
                        nz[j][k]=f[tou].map[j][k];
                    }
                }
                nz[f[tou].wi][f[tou].wj]=f[tou].map[nx][ny];
                nz[nx][ny]=0;
                if(pdc()==true)
                {
                    for(int j=1;j<=3;j++)
                    {
                        for(int k=1;k<=3;k++)
                        {
                            f[wei].map[j][k]=nz[j][k];
                        }
                    }
                    f[wei].t=f[tou].t+1;
                    f[wei].wi=nx;
                    f[wei].wj=ny;
                    paint();
                    if(zp(wei)==true)
                    {
                        printf("%d",f[tou].t+1);
                        return ;
                    }
                    wei++;
                }
            }
        }
        tou++;
    }
}
int main()
{
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
        {
            char ch;
            scanf("%c",&ch);
            f[1].map[i][j]=ch-'0';
            if(f[1].map[i][j]==0)
            {
                f[1].t=0;
                f[1].wi=i;
                f[1].wj=j;
            }
        }
    }
    bfs();
    return 0;
}
