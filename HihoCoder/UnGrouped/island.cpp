#include<stdlib.h>

void visitCross(char **grid, int numRows, int numColumns, int i, int j){
	grid[i][j]='0';
    if(i<numRows-1&&grid[i+1][j]=='1')
        visitCross(grid,numRows,numColumns,i+1,j);
    if(i>0&&grid[i-1][j]=='1')
        visitCross(grid,numRows,numColumns,i-1,j);
    if(j<numColumns-1&&grid[i][j+1]=='1')
        visitCross(grid,numRows,numColumns,i,j+1);
    if(j>0&&grid[i][j-1]=='1')
        visitCross(grid,numRows,numColumns,i,j-1);
}
int numIslands(char **grid, int numRows, int numColumns) {
    int island = 0;
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numColumns;j++){
            if(grid[i][j]=='0')
                continue;
            visitCross(grid,numRows,numColumns,i,j);
            island ++;
        }
    }
    return island;
}


int main()
{
	char *island[1];
	char s[] = "1111110";
	island[0]=s;
	//island[1]="1";
	int ret = numIslands((char**)island,1,7);
	return 0;
}