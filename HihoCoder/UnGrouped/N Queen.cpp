#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<string>> solveNQueens(int n){
    	Total_Q = n;
    	vector<int> board(Total_Q+1);
    	CHESS_BOARD = board;
    	guess_n_row(n);
    	return ret;
    }
private:
	vector<vector<string>> ret;
	vector<int> CHESS_BOARD;
	int Total_Q;
	void guess_n_row(int rest_row){
		if(rest_row<=0)
			return;
		int this_row = Total_Q - rest_row +1;
		for(int col=1;col<Total_Q+1;col++){
			CHESS_BOARD[this_row]=col;
			if(judge(this_row)==false)
				continue;
			if(this_row==Total_Q)
				board_to_string();
			guess_n_row(rest_row-1);
		}
	}
	bool judge(int jg_ROW){
		int jg_COL = CHESS_BOARD[jg_ROW];
		for(int row=1;row<jg_ROW;row++){
			if(jg_ROW==row)
				return false;
			int col = CHESS_BOARD[row];
			if(col==jg_COL)
				return false;
			if(abs(jg_ROW-row)==abs(jg_COL-col))
				return false;
		}
		return true;
	}
	void board_to_string(){
		vector<string> one_solution;
		for(int row=1;row<Total_Q+1;row++){
			string basic(Total_Q,'.');
			int col = CHESS_BOARD[row];
			basic[col-1]='Q';
			one_solution.push_back(basic);
		}
		ret.push_back(one_solution);
	}
};

int main()
{
	Solution t;
	t.solveNQueens(4);
	return 0;
}
