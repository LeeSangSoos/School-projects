package FindingMine;

interface GameBase {
	int N = 15;
	int num_mine = 40;
	int[][]	  status_board = new int[N][N];
	
	MineBoard mine_map = new MineBoard (N, num_mine);
	HintBoard hint_map = new HintBoard (N, mine_map);
	
	// Just setup Status_board data.
	static void Init_Status () {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				status_board[i][j] = 0;
			}
		}
	}
	
	/*
	 * 
	 * Print (num_mine - num_mark), num_mark
	 * 
	 * Print hint if status board is 1
	 * Print @ if status board is 2
	 * Else, print " " (Empty Space)
	 * 
	 */
	void PrintBoard ();
	
	/*
	 * If action is 1:
	 * 		Set status board as 1 if there's no mine on that position.
	 * 		return true;
	 * 		
	 * 		If there's a mine, return false;
	 * 
	 * If action is 2:
	 * 		Set status board as 2 and increase num_mark
	 * 		if action is 2(Mark that it is mine) and return true;
	 * 
	 */
	boolean UpdateStatus (int i, int j, int action);
	
	// Check all mine is marked.
	boolean GameEnd ();
	
	/* Print following format and end game.
	 * 
	 * Game Over : Number of Mine
	 * 
	 * Print MineBoard only.
	 */
	void GameOver ();
}

public class Game implements GameBase{
	int found=0;
	int left=num_mine;
	int real_left=num_mine;
	@Override
	public void PrintBoard() {
		System.out.println(left+", "+found);
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				if(status_board[i][j]==1&&mine_map.board[i][j]!="M")
					System.out.print("|"+hint_map.board[i][j]);
				else if(status_board[i][j]==2)
					System.out.print("|"+"@");
				else
					System.out.print("|"+" ");
			}
			System.out.println("|");
		}
		/* 
		 * 
		 * Should be print board with given format
		 * You have to implement here.
		 * 
		 */
		
	}

	@Override
	public boolean UpdateStatus(int i, int j, int action) {
		/* Implement Here */
		if(action==1) {
			if(mine_map.getPoint(i, j)!="M") {
				status_board[i][j]=1;
				return true;
			}
			return false;
		}
		if(action==2) {
			if(status_board[i][j]==2) {
				status_board[i][j]=0;
				left++;
				found--;
				if(mine_map.getPoint(i, j)=="M") {
					real_left++;
				}
				return true;
			}
			else {
				status_board[i][j]=2;
				left--;
				found++;
				if(mine_map.getPoint(i, j)=="M") {
					real_left--;
				}
				return true;
			}
		}
		return false;
		/* You can remove or change below return */
	}

	@Override
	public void GameOver() {
		/* Implement Here */	
		System.out.println("Game over : "+real_left);
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				System.out.print("|"+mine_map.board[i][j]);
			}
			System.out.println("|");
		}	
	}

	@Override
	public boolean GameEnd() {
		/* Implement Here */	
		int check=0;
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				if(status_board[i][j]==1||mine_map.board[i][j]=="M") {
					check++;
				}
			}
		}
		if(check==N*N) {
			System.out.println(left+", "+found);
			for(int i=0;i<N;i++) {
				for(int j=0;j<N;j++) {
					System.out.print("|"+hint_map.board[i][j]);
				}
				System.out.println("|");
			}
			return true;
		}
		check=0;
		/* You can remove or change below return */
		return false;
	}

}
