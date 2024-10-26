package PA2;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.OutputStream;
import java.io.File;

public class Board {
	static final String ANSI_RESET = "\033[0m";
	static final String ANSI_FG_BLACK = "\033[30m";
	static final String ANSI_FG_WHITE = "\033[37m";
	static final String ANSI_BG_WHITE = "\033[47m";
	static final String ANSI_BG_YELLOW = "\033[43m";
	Scanner scan = new Scanner(System.in);
	String[][] board=new String[10][9];
	String[][] keyb=new String[10][9];
	HashMap<String,gameObject> map= new HashMap<>();
	int x,y,q,w;
	int inleft=0;
	String xy;
	char c;
	int turn=0;
	String start, keys, sd;
	Board(boolean withFile) {
		int m,n;
		for(m=0;m<10;m++) {
			for(n=0;n<9;n++) {
				board[m][n]="0";
			}
		}
		king rk=new king(8,4,'K','r','g');
		rook rr1=new rook(9,0,'R','r','g');
		knight rn1=new knight(9,1,'N','r','g');
		elephant re1=new elephant(9,2,'E','r','g');
		guard rg1=new guard(9,3,'G','r','g');
		cannon rc1=new cannon(7,1,'C','r','g');
		pawn rp1=new pawn(6,0,'P','r','g');
		pawn rp2=new pawn(6,2,'P','r','g');
		pawn rp3=new pawn(6,4,'P','r','g');
		pawn rp4=new pawn(6,6,'P','r','g');
		pawn rp5=new pawn(6,8,'P','r','g');
		rook rr2=new rook(9,8,'P','r','g');
		knight rn2=new knight(9,7,'N','r','g');
		elephant re2=new elephant(9,6,'E','r','g');
		guard rg2=new guard(9,5,'G','r','g');
		cannon rc2=new cannon(7,7,'C','r','g');
		
		king gk=new king(1,4,'K','g','r');
		rook gr1=new rook(0,0,'R','g','r');
		knight gn1=new knight(0,1,'N','g','r');
		elephant ge1=new elephant(0,2,'E','g','r');
		guard gg1=new guard(0,3,'G','g','r');
		cannon gc1=new cannon(2,1,'C','g','r');
		pawn gp1=new pawn(3,0,'P','g','r');
		pawn gp2=new pawn(3,2,'P','g','r');
		pawn gp3=new pawn(3,4,'P','g','r');
		pawn gp4=new pawn(3,6,'P','g','r');
		pawn gp5=new pawn(3,8,'P','g','r');
		rook gr2=new rook(0,8,'R','g','r');
		knight gn2=new knight(0,7,'N','g','r');
		elephant ge2=new elephant(0,6,'E','g','r');
		guard gg2=new guard(0,5,'G','g','r');
		cannon gc2=new cannon(2,7,'C','g','r');
		
		map.put("rk", rk); map.put("rr1", rr1); map.put("rn1", rn1); map.put("re1", re1); map.put("rg1", rg1);
		map.put("rc1", rc1); map.put("rp1", rp1); map.put("rp2", rp2); map.put("rp4", rp4); map.put("rp3", rp3);
		map.put("rp5", rp5); map.put("rr2", rr2); map.put("rn2", rn2); map.put("re2", re2); map.put("rg2", rg2); map.put("rc2", rc2);
		map.put("gk", gk); map.put("gr1", gr1); map.put("gn1", gn1); map.put("ge1", ge1); map.put("gg1", gg1);
		map.put("gc1", gc1); map.put("gp1", gp1); map.put("gp2", gp2); map.put("gp4", gp4); map.put("gp3", gp3);
		map.put("gp5", gp5); map.put("gr2", gr2); map.put("gn2", gn2); map.put("ge2", ge2); map.put("gg2", gg2); map.put("gc2", gc2);
		
		for(Entry<String, gameObject> entry : map.entrySet()) {
			board[entry.getValue().getX()][entry.getValue().getY()]=(entry.getKey().substring(0,1)+entry.getKey().substring(1,2).toUpperCase());
			keyb[entry.getValue().getX()][entry.getValue().getY()]=(entry.getKey());
		}
	}

	public boolean isFinish(boolean withFile) throws IOException {
		
		if(map.get("rk").getX()==100) {
			if(withFile==true) {
				File output=new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Output.txt");
				if(!output.exists()) {
					output.createNewFile();
				}
				FileWriter ow=new FileWriter(output,true);
				BufferedWriter bw=new BufferedWriter(ow);
				bw.write("Green Wins");
				bw.close();
			}
			System.out.println("Green Wins");
			return true;
		}
		if(map.get("gk").getX()==100) {
			if(withFile==true) {
				File output=new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Output.txt");
				if(!output.exists()) {
					output.createNewFile();
				}
				FileWriter ow=new FileWriter(output,true);
				BufferedWriter bw=new BufferedWriter(ow);
				bw.write("Red Wins");
				bw.close();
			}
			System.out.println("Red Wins");
			return true;
		}
		return false;
	}
	
	public void selectObject(boolean withFile) throws IOException {
		int i,j;
		File in= new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Input.txt");
		FileReader readin = new FileReader(in);
		BufferedReader bufread= new BufferedReader(readin);
		if(withFile==true) {
			int h;
			for(h=inleft;h>0;h--) {
				sd=bufread.readLine();
			}
			sd=bufread.readLine();
			if(!sd.equals("F")) {
				xy=sd.substring(0, 2);
			}
			if(sd.equals("F")) {
				System.exit(0);
			}
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
			inleft++;
			while(x<0||x>9||y<0||y>8||(turn%2==0&&!board[x][y].substring(0, 1).equals("g"))) {
				sd=bufread.readLine();
				if(!sd.equals("F")) {
				xy=sd.substring(0, 2);
				}
				if(sd.equals("F")) {
					System.exit(0);
				}
				c=xy.charAt(0);
				y=c-'a';
				x=Integer.valueOf(xy.substring(1,2));
				inleft++;
			}
			while(x<0||x>9||y<0||y>8||(turn%2==1&&!board[x][y].substring(0, 1).equals("r"))) {
				sd=bufread.readLine();
				if(!sd.equals("F")) {
				xy=sd.substring(0, 2);
				}
				if(sd.equals("F")) {
					System.exit(0);
				}
				c=xy.charAt(0);
				y=c-'a';
				x=Integer.valueOf(xy.substring(1,2));
				inleft++;
			}
		}
		if(withFile==false) {
		System.out.print("Select piece: ");
		xy = scan.nextLine();
		if(xy.equals("F")) {
			System.exit(0);
		}
		c=xy.charAt(0);
		y=c-'a';
		x=Integer.valueOf(xy.substring(1,2));
		while(x<0||x>9||y<0||y>8||(turn%2==0&&!board[x][y].substring(0, 1).equals("g"))) {
			System.out.print("Not valid, select again: ");
			xy = scan.nextLine();
			if(xy.equals("F")) {
				System.exit(0);
			}
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
		}
		while(x<0||x>9||y<0||y>8||(turn%2==1&&!board[x][y].substring(0, 1).equals("r"))) {
			System.out.print("Not valid, select again: ");
			xy = scan.nextLine();
			if(xy.equals("F")) {
				System.exit(0);
			}
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
		}
		}
		int check=0;
		while(check==0) {
		if(board[x][y].equals("rK")||board[x][y].equals("rG")) {
			if(x+1>6&&x+1<10&&board[x+1][y].equals("0")) {
				board[x+1][y]="*";
			}
			else if(x+1>6&&x+1<10&&board[x+1][y].substring(0,1).equals("g")) {
				board[x+1][y]=(board[x+1][y]+"*");
			}
			if(x+1>6&&x+1<10&&y+1>2&&y+1<6&&board[x+1][y+1].equals("0")) {
				board[x+1][y+1]="*";
			}
			else if(x+1>6&&x+1<10&&y+1>2&&y+1<6&&board[x+1][y+1].substring(0,1).equals("g")) {
				board[x+1][y+1]=(board[x+1][y+1]+"*");
			}
			if(x+1>6&&x+1<10&&y-1>2&&y-1<6&&board[x+1][y-1].equals("0")) {
				board[x+1][y-1]="*";
			}
			else if(x+1>6&&x+1<10&&y-1>2&&y-1<6&&board[x+1][y-1].substring(0,1).equals("g")) {
				board[x+1][y-1]=(board[x+1][y-1]+"*");
			}
			if(y+1>2&&y+1<6&&board[x][y+1].equals("0")) {
				board[x][y+1]="*";
			}
			else if(y+1>2&&y+1<6&&board[x][y+1].substring(0,1).equals("g")) {
				board[x][y+1]=(board[x][y+1]+"*");
			}
			if(y-1>2&&y-1<6&&board[x][y-1].equals("0")) {
				board[x][y-1]="*";
			}
			else if(y-1>2&&y-1<6&&board[x][y-1].substring(0,1).equals("g")) {
				board[x][y-1]=(board[x][y-1]+"*");
			}
			if(x-1>6&&x-1<10&&board[x-1][y].equals("0")) {
				board[x-1][y]="*";
			}
			else if(x-1>6&&x-1<10&&board[x-1][y].substring(0,1).equals("g")) {
				board[x-1][y]=(board[x-1][y]+"*");
			}
			if(x-1>6&&x-1<10&&y+1>2&&y+1<6&&board[x-1][y+1].equals("0")) {
				board[x-1][y+1]="*";
			}
			else if(x-1>6&&x-1<10&&y+1>2&&y+1<6&&board[x-1][y+1].substring(0,1).equals("g")) {
				board[x-1][y+1]=(board[x-1][y+1]+"*");
			}
			if(x-1>6&&x-1<10&&y-1>2&&y-1<6&&board[x-1][y-1].equals("0")) {
				board[x-1][y-1]="*";
			}
			else if(x-1>6&&x-1<10&&y-1>2&&y-1<6&&board[x-1][y-1].substring(0,1).equals("g")) {
				board[x-1][y-1]=(board[x-1][y-1]+"*");
			}
		}
		if(board[x][y].equals("rP")) {
			if(x-1>=0&&x-1<10&&board[x-1][y].equals("0")) {
				board[x-1][y]="*";
			}
			else if(x-1>=0&&x-1<10&&board[x-1][y].substring(0,1).equals("g")) {
				board[x-1][y]=(board[x-1][y]+"*");
			}
			if(y+1>=0&&y+1<9&&board[x][y+1].equals("0")) {
				board[x][y+1]="*";
			}
			else if(y+1>=0&&y+1<9&&board[x][y+1].substring(0,1).equals("g")) {
				board[x][y+1]=(board[x][y+1]+"*");
			}
			if(y-1>=0&&y-1<9&&board[x][y-1].equals("0")) {
				board[x][y-1]="*";
			}
			else if(y-1>=0&&y-1<9&&board[x][y-1].substring(0,1).equals("g")) {
				board[x][y-1]=(board[x][y-1]+"*");
			}
		}
		if(board[x][y].equals("rR")) {
			for(i=1;i<10;i++) {
				if(x+i>=0&&x+i<10&&board[x+i][y].equals("0")) {
					board[x+i][y]="*";
				}
				else if(x+i>=0&&x+i<10&&board[x+i][y].substring(0,1).equals("g")) {
					board[x+i][y]=(board[x+i][y]+"*");
					break;
				}
				else if(x+i>=0&&x+i<10&&board[x+i][y].substring(0,1).equals("r")) {
					break;
				}
			}
			for(i=1;i<10;i++) {
				if(x-i>=0&&x-i<10&&board[x-i][y].equals("0")) {
					board[x-i][y]="*";
				}
				else if(x-i>=0&&x-i<10&&board[x-i][y].substring(0,1).equals("g")) {
					board[x-i][y]=(board[x-i][y]+"*");
					break;
				}
				else if(x-i>=0&&x-i<10&&board[x-i][y].substring(0,1).equals("r")) {
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y+i>=0&&y+i<9&&board[x][y+i].equals("0")) {
					board[x][y+i]="*";
				}
				else if(y+i>=0&&y+i<9&&board[x][y+i].substring(0,1).equals("g")) {
					board[x][y+i]=(board[x][y+i]+"*");
					break;
				}
				else if(y+i>=0&&y+i<9&&board[x][y+i].substring(0,1).equals("r")) {
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y-i>=0&&y-i<9&&board[x][y-i].equals("0")) {
					board[x][y-i]="*";
				}
				else if(y-i>=0&&y-i<9&&board[x][y-i].substring(0,1).equals("g")) {
					board[x][y-i]=(board[x][y-i]+"*");
					break;
				}
				else if(y-i>=0&&y-i<9&&board[x][y-i].substring(0,1).equals("r")) {
					break;
				}
			}
		}
		if(board[x][y].equals("rN")) {
			if(x+1<10&&board[x+1][y].length()!=2) {
			if(x+2>0&&x+2<10&&y+1>0&&y+1<9&&board[x+2][y+1].equals("0")) {
				board[x+2][y+1]="*";
			}
			else if(x+2>=0&&x+2<10&&y+1>=0&&y+1<9&&board[x+2][y+1].substring(0,1).equals("g")) {
				board[x+2][y+1]=(board[x+2][y+1]+"*");
			}
			}
			if(x+1<10&&board[x+1][y].length()!=2) {
			if(x+2>=0&&x+2<10&&y-1>=0&&y-1<9&&board[x+2][y-1].equals("0")) {
				board[x+2][y-1]="*";
			}
			else if(x+2>=0&&x+2<10&&y-1>=0&&y-1<9&&board[x+2][y-1].substring(0,1).equals("g")) {
				board[x+2][y-1]=(board[x+2][y-1]+"*");
			}
			}
			if(x-1>-1&&board[x-1][y].length()!=2) {
			if(x-2>=0&&x-2<10&&y+1>=0&&y+1<9&&board[x-2][y+1].equals("0")) {
				board[x-2][y+1]="*";
			}
			else if(x-2>=0&&x-2<10&&y+1>=0&&y+1<9&&board[x-2][y+1].substring(0,1).equals("g")) {
				board[x-2][y+1]=(board[x-2][y+1]+"*");
			}
			if(x-2>=0&&x-2<10&&y-1>=0&&y-1<9&&board[x-2][y-1].equals("0")) {
				board[x-2][y-1]="*";
			}
			else if(x-2>=0&&x-2<10&&y-1>=0&&y-1<9&&board[x-2][y-1].substring(0,1).equals("g")) {
				board[x-2][y-1]=(board[x-2][y-1]+"*");
			}
			}
			if(y+1<9&&board[x][y+1].length()!=2) {
			if(x+1>=0&&x+1<10&&y+2>=0&&y+2<9&&board[x+1][y+2].equals("0")) {
				board[x+1][y+2]="*";
			}
			else if(x+1>=0&&x+1<10&&y+2>=0&&y+2<9&&board[x+1][y+2].substring(0,1).equals("g")) {
				board[x+1][y+2]=(board[x+1][y+2]+"*");
			}
			if(x-1>=0&&x-1<10&&y+2>=0&&y+2<9&&board[x-1][y+2].equals("0")) {
				board[x-1][y+2]="*";
			}
			else if(x-1>=0&&x-1<10&&y+2>=0&&y+2<9&&board[x-1][y+2].substring(0,1).equals("g")) {
				board[x-1][y+2]=(board[x-1][y+2]+"*");
			}
			}
			if(y-1>-1&&board[x][y-1].length()!=2) {
			if(x+1>=0&&x+1<10&&y-2>=0&&y-2<9&&board[x+1][y-2].equals("0")) {
				board[x+1][y-2]="*";
			}
			else if(x+1>=0&&x+1<10&&y-2>=0&&y-2<9&&board[x+1][y-2].substring(0,1).equals("g")) {
				board[x+1][y-2]=(board[x+1][y-2]+"*");
			}
			
			if(x-1>=0&&x-1<10&&y-2>=0&&y-2<9&&board[x-1][y-2].equals("0")) {
				board[x-1][y-2]="*";
			}
			else if(x-1>=0&&x-1<10&&y-2>=0&&y-2<9&&board[x-1][y-2].substring(0,1).equals("g")) {
				board[x-1][y-2]=(board[x-1][y-2]+"*");
			}
			}
		}
		if(board[x][y].equals("rE")) {
			if(x+1<10&&x+2<10&&y+1<9&&board[x+1][y].length()!=2&&board[x+2][y+1].length()!=2) {
			if(x+3>=0&&x+3<10&&y+2>=0&&y+2<9&&board[x+3][y+2].equals("0")) {
				board[x+3][y+2]="*";
			}
			else if(x+3>=0&&x+3<10&&y+2>=0&&y+2<9&&board[x+3][y+2].substring(0,1).equals("g")) {
				board[x+3][y+2]=(board[x+3][y+2]+"*");
			}
			}
			if(x+1<10&&x+2<10&&y-1>-1&&board[x+1][y].length()!=2&&board[x+2][y-1].length()!=2) {
			if(x+3>=0&&x+3<10&&y-2>=0&&y-2<9&&board[x+3][y-2].equals("0")) {
				board[x+3][y-2]="*";
			}
			else if(x+3>=0&&x+3<10&&y-2>=0&&y-2<9&&board[x+3][y-2].substring(0,1).equals("g")) {
				board[x+3][y-2]=(board[x+3][y-2]+"*");
			}
			}
			if(x-1>=0&&x-2>=0&&y+1<9&&board[x-1][y].length()!=2&&board[x-2][y+1].length()!=2) {
			if(x-3>=0&&x-3<10&&y+2>=0&&y+2<9&&board[x-3][y+2].equals("0")) {
				board[x-3][y+2]="*";
			}
			else if(x-3>=0&&x-3<10&&y+2>=0&&y+2<9&&board[x-3][y+2].substring(0,1).equals("g")) {
				board[x-3][y+2]=(board[x-3][y+2]+"*");
			}
			}
			if(x-1>=0&&x-2>=0&&y-1>-1&&board[x-1][y].length()!=2&&board[x-2][y-1].length()!=2) {
			if(x-3>=0&&x-3<10&&y-2>=0&&y-2<9&&board[x-3][y-2].equals("0")) {
				board[x-3][y-2]="*";
			}
			else if(x-3>=0&&x-3<10&&y-2>=0&&y-2<9&&board[x-3][y-2].substring(0,1).equals("g")) {
				board[x-3][y-2]=(board[x-3][y-2]+"*");
			}
			}
			if(x+1<10&&y+2<9&&y+1<9&&board[x][y+1].length()!=2&&board[x+1][y+2].length()!=2) {
			if(x+2>=0&&x+2<10&&y+3>=0&&y+3<9&&board[x+2][y+3].equals("0")) {
				board[x+2][y+3]="*";
			}
			else if(x+2>=0&&x+2<10&&y+3>=0&&y+3<9&&board[x+2][y+3].substring(0,1).equals("g")) {
				board[x+2][y+3]=(board[x+2][y+3]+"*");
			}
			}
			if(x+1<10&&y-1>=0&&y-2>=0&&board[x][y-1].length()!=2&&board[x+1][y-2].length()!=2) {
			if(x+2>=0&&x+2<10&&y-3>=0&&y-3<9&&board[x+2][y-3].equals("0")) {
				board[x+2][y-3]="*";
			}
			else if(x+2>=0&&x+2<10&&y-3>=0&&y-3<9&&board[x+2][y-3].substring(0,1).equals("g")) {
				board[x+2][y-3]=(board[x+2][y-3]+"*");
			}
			}
			if(x-1>=0&&y+2<9&&y+1<9&&board[x][y+1].length()!=2&&board[x-1][y+2].length()!=2) {
			if(x-2>=0&&x-2<10&&y+3>=0&&y+3<9&&board[x-2][y+3].equals("0")) {
				board[x-2][y+3]="*";
			}
			else if(x-2>=0&&x-2<10&&y+3>=0&&y+3<9&&board[x-2][y+3].substring(0,1).equals("g")) {
				board[x-2][y+3]=(board[x-2][y+3]+"*");
			}
			}
			if(x-1>=0&&y-2>=0&&y-1>=0&&board[x][y-1].length()!=2&&board[x-1][y-2].length()!=2) {
			if(x-2>=0&&x-2<10&&y-3>=0&&y-3<9&&board[x-2][y-3].equals("0")) {
				board[x-2][y-3]="*";
			}
			else if(x-2>=0&&x-2<10&&y-3>=0&&y-3<9&&board[x-2][y-3].substring(0,1).equals("g")) {
				board[x-2][y-3]=(board[x-2][y-3]+"*");
			}
			}
		}
		if(board[x][y].equals("rC")) {
			for(i=1;i<10;i++) {
				if(x+i>=0&&x+i<10&&(board[x+i][y].substring(0,1).equals("g")||board[x+i][y].substring(0,1).equals("r"))&&!board[x+i][y].substring(1,2).equals("C")) {
					for(j=1;j<10;j++) {
						if(x+i+j>=0&&x+i+j<10&&board[x+i+j][y].equals("0")) {
							board[x+i+j][y]="*";
						}
						else if(x+i+j>=0&&x+i+j<10&&board[x+i+j][y].substring(0,1).equals("g")&&!board[x+i+j][y].substring(1,2).equals("C")) {
							board[x+i+j][y]=(board[x+i+j][y]+"*");
							break;
						}
						else if(x+i+j>=0&&x+i+j<10&&(board[x+i+j][y].substring(0,1).equals("r")||board[x+i+j][y].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<10;i++) {
				if(x-i>=0&&x-i<10&&(board[x-i][y].substring(0,1).equals("g")||board[x-i][y].substring(0,1).equals("r"))&&!board[x-i][y].substring(1,2).equals("C")) {
					for(j=1;j<10;j++) {
						if(x-i-j>=0&&x-i-j<10&&board[x-i-j][y].equals("0")) {
							board[x-i-j][y]="*";
						}
						else if(x-i-j>=0&&x-i-j<10&&board[x-i-j][y].substring(0,1).equals("g")&&!board[x-i-j][y].substring(1,2).equals("C")) {
							board[x-i-j][y]=(board[x-i-j][y]+"*");
							break;
						}
						else if(x-i-j>=0&&x-i-j<10&&(board[x-i-j][y].substring(0,1).equals("r")||board[x-i-j][y].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y+i>=0&&y+i<9&&(board[x][y+i].substring(0,1).equals("g")||board[x][y+i].substring(0,1).equals("r"))&&!board[x][y+i].substring(1,2).equals("C")) {
					for(j=1;j<8;j++) {
						if(y+i+j>=0&&y+i+j<9&&board[x][y+i+j].equals("0")) {
							board[x][y+i+j]="*";
						}
						else if(y+i+j>=0&&y+i+j<9&&board[x][y+i+j].substring(0,1).equals("g")&&!board[x][y+i+j].substring(1,2).equals("C")) {
							board[x][y+i+j]=(board[x][y+i+j]+"*");
							break;
						}
						else if(y+i+j>=0&&y+i+j<9&&(board[x][y+i+j].substring(0,1).equals("r")||board[x][y+i+j].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y-i>=0&&y-i<9&&(board[x][y-i].substring(0,1).equals("g")||board[x][y-i].substring(0,1).equals("r"))&&!board[x][y-i].substring(1,2).equals("C")) {
					for(j=1;j<8;j++) {
						if(y-i-j>=0&&y-i-j<9&&board[x][y-i-j].equals("0")) {
							board[x][y-i-j]="*";
						}
						else if(y-i-j>=0&&y-i-j<9&&board[x][y-i-j].substring(0,1).equals("g")&&!board[x][y-i-j].substring(1,2).equals("C")) {
							board[x][y-i-j]=(board[x][y-i-j]+"*");
							break;
						}
						else if(y-i-j>=0&&y-i-j<9&&(board[x][y-i-j].substring(0,1).equals("r")||board[x][y-i-j].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
		}
		
		if(board[x][y].equals("gK")||board[x][y].equals("gG")) {
			if(x+1>=0&&x+1<3&&board[x+1][y].equals("0")) {
				board[x+1][y]="*";
			}
			else if(x+1>=0&&x+1<3&&board[x+1][y].substring(0,1).equals("r")) {
				board[x+1][y]=(board[x+1][y]+"*");
			}
			if(x+1>=0&&x+1<3&&y+1>2&&y+1<6&&board[x+1][y+1].equals("0")) {
				board[x+1][y+1]="*";
			}
			else if(x+1>=0&&x+1<3&&y+1>2&&y+1<6&&board[x+1][y+1].substring(0,1).equals("r")) {
				board[x+1][y+1]=(board[x+1][y+1]+"*");
			}
			if(x+1>=0&&x+1<3&&y-1>2&&y-1<6&&board[x+1][y-1].equals("0")) {
				board[x+1][y-1]="*";
			}
			else if(x+1>=0&&x+1<3&&y-1>2&&y-1<6&&board[x+1][y-1].substring(0,1).equals("r")) {
				board[x+1][y-1]=(board[x+1][y-1]+"*");
			}
			if(y+1>2&&y+1<6&&board[x][y+1].equals("0")) {
				board[x][y+1]="*";
			}
			else if(y+1>2&&y+1<6&&board[x][y+1].substring(0,1).equals("r")) {
				board[x][y+1]=(board[x][y+1]+"*");
			}
			if(y-1>2&&y-1<6&&board[x][y-1].equals("0")) {
				board[x][y-1]="*";
			}
			else if(y-1>2&&y-1<6&&board[x][y-1].substring(0,1).equals("r")) {
				board[x][y-1]=(board[x][y-1]+"*");
			}
			if(x-1>=0&&x-1<3&&board[x-1][y].equals("0")) {
				board[x-1][y]="*";
			}
			else if(x-1>=0&&x-1<3&&board[x-1][y].substring(0,1).equals("r")) {
				board[x-1][y]=(board[x-1][y]+"*");
			}
			if(x-1>=0&&x-1<3&&y+1>2&&y+1<6&&board[x-1][y+1].equals("0")) {
				board[x-1][y+1]="*";
			}
			else if(x-1>=0&&x-1<3&&y+1>2&&y+1<6&&board[x-1][y+1].substring(0,1).equals("r")) {
				board[x-1][y+1]=(board[x-1][y+1]+"*");
			}
			if(x-1>=0&&x-1<3&&y-1>2&&y-1<6&&board[x-1][y-1].equals("0")) {
				board[x-1][y-1]="*";
			}
			else if(x-1>=0&&x-1<3&&y-1>2&&y-1<6&&board[x-1][y-1].substring(0,1).equals("r")) {
				board[x-1][y-1]=(board[x-1][y-1]+"*");
			}
		}
		if(board[x][y].equals("gP")) {
			if(x+1>=0&&x+1<10&&board[x+1][y].equals("0")) {
				board[x+1][y]="*";
			}
			else if(x+1>=0&&x+1<10&&board[x+1][y].substring(0,1).equals("r")) {
				board[x+1][y]=(board[x+1][y]+"*");
			}
			if(y+1>=0&&y+1<9&&board[x][y+1].equals("0")) {
				board[x][y+1]="*";
			}
			else if(y+1>=0&&y+1<9&&board[x][y+1].substring(0,1).equals("r")) {
				board[x][y+1]=(board[x][y+1]+"*");
			}
			if(y-1>=0&&y-1<9&&board[x][y-1].equals("0")) {
				board[x][y-1]="*";
			}
			else if(y-1>=0&&y-1<9&&board[x][y-1].substring(0,1).equals("r")) {
				board[x][y-1]=(board[x][y-1]+"*");
			}
		}
		if(board[x][y].equals("gR")) {
			for(i=1;i<10;i++) {
				if(x+i>=0&&x+i<10&&board[x+i][y].equals("0")) {
					board[x+i][y]="*";
				}
				else if(x+i>=0&&x+i<10&&board[x+i][y].substring(0,1).equals("r")) {
					board[x+i][y]=(board[x+i][y]+"*");
					break;
				}
				else if(x+i>=0&&x+i<10&&board[x+i][y].substring(0,1).equals("g")) {
					break;
				}
			}
			for(i=1;i<10;i++) {
				if(x-i>=0&&x-i<10&&board[x-i][y].equals("0")) {
					board[x-i][y]="*";
				}
				else if(x-i>=0&&x-i<10&&board[x-i][y].substring(0,1).equals("r")) {
					board[x-i][y]=(board[x-i][y]+"*");
					break;
				}
				else if(x-i>=0&&x-i<10&&board[x-i][y].substring(0,1).equals("g")) {
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y+i>=0&&y+i<9&&board[x][y+i].equals("0")) {
					board[x][y+i]="*";
				}
				else if(y+i>=0&&y+i<9&&board[x][y+i].substring(0,1).equals("r")) {
					board[x][y+i]=(board[x][y+i]+"*");
					break;
				}
				else if(y+i>=0&&y+i<9&&board[x][y+i].substring(0,1).equals("g")) {
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y-i>=0&&y-i<9&&board[x][y-i].equals("0")) {
					board[x][y-i]="*";
				}
				else if(y-i>=0&&y-i<9&&board[x][y-i].substring(0,1).equals("r")) {
					board[x][y-i]=(board[x][y-i]+"*");
					break;
				}
				else if(y-i>=0&&y-i<9&&board[x][y-i].substring(0,1).equals("g")) {
					break;
				}
			}
		}
		if(board[x][y].equals("gN")) {
			if(x+1<10&&board[x+1][y].length()!=2) {
				if(x+2>0&&x+2<10&&y+1>0&&y+1<9&&board[x+2][y+1].equals("0")) {
					board[x+2][y+1]="*";
				}
				else if(x+2>=0&&x+2<10&&y+1>=0&&y+1<9&&board[x+2][y+1].substring(0,1).equals("r")) {
					board[x+2][y+1]=(board[x+2][y+1]+"*");
				}
				}
				if(x+1<10&&board[x+1][y].length()!=2) {
				if(x+2>=0&&x+2<10&&y-1>=0&&y-1<9&&board[x+2][y-1].equals("0")) {
					board[x+2][y-1]="*";
				}
				else if(x+2>=0&&x+2<10&&y-1>=0&&y-1<9&&board[x+2][y-1].substring(0,1).equals("r")) {
					board[x+2][y-1]=(board[x+2][y-1]+"*");
				}
				}
				if(x-1>-1&&board[x-1][y].length()!=2) {
				if(x-2>=0&&x-2<10&&y+1>=0&&y+1<9&&board[x-2][y+1].equals("0")) {
					board[x-2][y+1]="*";
				}
				else if(x-2>=0&&x-2<10&&y+1>=0&&y+1<9&&board[x-2][y+1].substring(0,1).equals("r")) {
					board[x-2][y+1]=(board[x-2][y+1]+"*");
				}
				if(x-2>=0&&x-2<10&&y-1>=0&&y-1<9&&board[x-2][y-1].equals("0")) {
					board[x-2][y-1]="*";
				}
				else if(x-2>=0&&x-2<10&&y-1>=0&&y-1<9&&board[x-2][y-1].substring(0,1).equals("r")) {
					board[x-2][y-1]=(board[x-2][y-1]+"*");
				}
				}
				if(y+1<9&&board[x][y+1].length()!=2) {
				if(x+1>=0&&x+1<10&&y+2>=0&&y+2<9&&board[x+1][y+2].equals("0")) {
					board[x+1][y+2]="*";
				}
				else if(x+1>=0&&x+1<10&&y+2>=0&&y+2<9&&board[x+1][y+2].substring(0,1).equals("r")) {
					board[x+1][y+2]=(board[x+1][y+2]+"*");
				}
				if(x-1>=0&&x-1<10&&y+2>=0&&y+2<9&&board[x-1][y+2].equals("0")) {
					board[x-1][y+2]="*";
				}
				else if(x-1>=0&&x-1<10&&y+2>=0&&y+2<9&&board[x-1][y+2].substring(0,1).equals("r")) {
					board[x-1][y+2]=(board[x-1][y+2]+"*");
				}
				}
				if(y-1>-1&&board[x][y-1].length()!=2) {
				if(x+1>=0&&x+1<10&&y-2>=0&&y-2<9&&board[x+1][y-2].equals("0")) {
					board[x+1][y-2]="*";
				}
				else if(x+1>=0&&x+1<10&&y-2>=0&&y-2<9&&board[x+1][y-2].substring(0,1).equals("r")) {
					board[x+1][y-2]=(board[x+1][y-2]+"*");
				}
				
				if(x-1>=0&&x-1<10&&y-2>=0&&y-2<9&&board[x-1][y-2].equals("0")) {
					board[x-1][y-2]="*";
				}
				else if(x-1>=0&&x-1<10&&y-2>=0&&y-2<9&&board[x-1][y-2].substring(0,1).equals("r")) {
					board[x-1][y-2]=(board[x-1][y-2]+"*");
				}
				}
		}
		if(board[x][y].equals("gE")) {
			if(x+1<10&&x+2<10&&y+1<9&&board[x+1][y].length()!=2&&board[x+2][y+1].length()!=2) {
				if(x+3>=0&&x+3<10&&y+2>=0&&y+2<9&&board[x+3][y+2].equals("0")) {
					board[x+3][y+2]="*";
				}
				else if(x+3>=0&&x+3<10&&y+2>=0&&y+2<9&&board[x+3][y+2].substring(0,1).equals("r")) {
					board[x+3][y+2]=(board[x+3][y+2]+"*");
				}
				}
				if(x+1<10&&x+2<10&&y-1>-1&&board[x+1][y].length()!=2&&board[x+2][y-1].length()!=2) {
				if(x+3>=0&&x+3<10&&y-2>=0&&y-2<9&&board[x+3][y-2].equals("0")) {
					board[x+3][y-2]="*";
				}
				else if(x+3>=0&&x+3<10&&y-2>=0&&y-2<9&&board[x+3][y-2].substring(0,1).equals("r")) {
					board[x+3][y-2]=(board[x+3][y-2]+"*");
				}
				}
				if(x-1>=0&&x-2>=0&&y+1<9&&board[x-1][y].length()!=2&&board[x-2][y+1].length()!=2) {
				if(x-3>=0&&x-3<10&&y+2>=0&&y+2<9&&board[x-3][y+2].equals("0")) {
					board[x-3][y+2]="*";
				}
				else if(x-3>=0&&x-3<10&&y+2>=0&&y+2<9&&board[x-3][y+2].substring(0,1).equals("r")) {
					board[x-3][y+2]=(board[x-3][y+2]+"*");
				}
				}
				if(x-1>=0&&x-2>=0&&y-1>-1&&board[x-1][y].length()!=2&&board[x-2][y-1].length()!=2) {
				if(x-3>=0&&x-3<10&&y-2>=0&&y-2<9&&board[x-3][y-2].equals("0")) {
					board[x-3][y-2]="*";
				}
				else if(x-3>=0&&x-3<10&&y-2>=0&&y-2<9&&board[x-3][y-2].substring(0,1).equals("r")) {
					board[x-3][y-2]=(board[x-3][y-2]+"*");
				}
				}
				if(x+1<10&&y+2<9&&y+1<9&&board[x][y+1].length()!=2&&board[x+1][y+2].length()!=2) {
				if(x+2>=0&&x+2<10&&y+3>=0&&y+3<9&&board[x+2][y+3].equals("0")) {
					board[x+2][y+3]="*";
				}
				else if(x+2>=0&&x+2<10&&y+3>=0&&y+3<9&&board[x+2][y+3].substring(0,1).equals("r")) {
					board[x+2][y+3]=(board[x+2][y+3]+"*");
				}
				}
				if(x+1<10&&y-1>=0&&y-2>=0&&board[x][y-1].length()!=2&&board[x+1][y-2].length()!=2) {
				if(x+2>=0&&x+2<10&&y-3>=0&&y-3<9&&board[x+2][y-3].equals("0")) {
					board[x+2][y-3]="*";
				}
				else if(x+2>=0&&x+2<10&&y-3>=0&&y-3<9&&board[x+2][y-3].substring(0,1).equals("r")) {
					board[x+2][y-3]=(board[x+2][y-3]+"*");
				}
				}
				if(x-1>=0&&y+2<9&&y+1<9&&board[x][y+1].length()!=2&&board[x-1][y+2].length()!=2) {
				if(x-2>=0&&x-2<10&&y+3>=0&&y+3<9&&board[x-2][y+3].equals("0")) {
					board[x-2][y+3]="*";
				}
				else if(x-2>=0&&x-2<10&&y+3>=0&&y+3<9&&board[x-2][y+3].substring(0,1).equals("r")) {
					board[x-2][y+3]=(board[x-2][y+3]+"*");
				}
				}
				if(x-1>=0&&y-2>=0&&y-1>=0&&board[x][y-1].length()!=2&&board[x-1][y-2].length()!=2) {
				if(x-2>=0&&x-2<10&&y-3>=0&&y-3<9&&board[x-2][y-3].equals("0")) {
					board[x-2][y-3]="*";
				}
				else if(x-2>=0&&x-2<10&&y-3>=0&&y-3<9&&board[x-2][y-3].substring(0,1).equals("r")) {
					board[x-2][y-3]=(board[x-2][y-3]+"*");
				}
				}
		}
		if(board[x][y].equals("gC")) {
			for(i=1;i<10;i++) {
				if(x+i>=0&&x+i<10&&(board[x+i][y].substring(0,1).equals("g")||board[x+i][y].substring(0,1).equals("r"))&&!board[x+i][y].substring(1,2).equals("C")) {
					for(j=1;j<9;j++) {
						if(x+i+j>=0&&x+i+j<10&&board[x+i+j][y].equals("0")) {
							board[x+i+j][y]="*";
						}
						else if(x+i+j>=0&&x+i+j<10&&board[x+i+j][y].substring(0,1).equals("r")&&!board[x+i+j][y].substring(1,2).equals("C")) {
							board[x+i+j][y]=(board[x+i+j][y]+"*");
							break;
						}
						else if(x+i+j>=0&&x+i+j<10&&(board[x+i+j][y].substring(0,1).equals("g")||board[x+i+j][y].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<10;i++) {
				if(x-i>=0&&x-i<10&&(board[x-i][y].substring(0,1).equals("g")||board[x-i][y].substring(0,1).equals("r"))&&!board[x-i][y].substring(1,1).equals("C")) {
					for(j=1;j<9;j++) {
						if(x-i-j>=0&&x-i-j<10&&board[x-i-j][y].equals("0")) {
							board[x-i-j][y]="*";
						}
						else if(x-i-j>=0&&x-i-j<10&&board[x-i-j][y].substring(0,1).equals("r")&&!board[x-i-j][y].substring(1,2).equals("C")) {
							board[x-i-j][y]=(board[x-i-j][y]+"*");
							break;
						}
						else if(x-i-j>=0&&x-i-j<10&&(board[x-i-j][y].substring(0,1).equals("g")||board[x-i-j][y].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y+i>=0&&y+i<9&&(board[x][y+i].substring(0,1).equals("g")||board[x][y+i].substring(0,1).equals("r"))&&!board[x][y+i].substring(1,2).equals("C")) {
					for(j=1;j<8;j++) {
						if(y+i+j>=0&&y+i+j<9&&board[x][y+i+j].equals("0")) {
							board[x][y+i+j]="*";
						}
						else if(y+i+j>=0&&y+i+j<9&&board[x][y+i+j].substring(0,1).equals("r")&&!board[x][y+i+j].substring(1,2).equals("C")) {
							board[x][y+i+j]=(board[x][y+i+j]+"*");
							break;
						}
						else if(y+i+j>=0&&y+i+j<9&&(board[x][y+i+j].substring(0,1).equals("g")||board[x][y+i+j].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
			for(i=1;i<9;i++) {
				if(y-i>=0&&y-i<9&&(board[x][y-i].substring(0,1).equals("g")||board[x][y-i].substring(0,1).equals("r"))&&!board[x][y-i].substring(1,2).equals("C")) {
					for(j=1;j<8;j++) {
						if(y-i-j>=0&&y-i-j<9&&board[x][y-i-j].equals("0")) {
							board[x][y-i-j]="*";
						}
						else if(y-i-j>=0&&y-i-j<9&&board[x][y-i-j].substring(0,1).equals("r")&&!board[x][y-i-j].substring(1,2).equals("C")) {
							board[x][y-i-j]=(board[x][y-i-j]+"*");
							break;
						}
						else if(y-i-j>=0&&y-i-j<9&&(board[x][y-i-j].substring(0,1).equals("g")||board[x][y-i-j].substring(1,2).equals("C"))) {
							break;
						}
					}
					break;
				}
			}
		}
		for(i=0;i<10;i++) {
			for(j=0;j<9;j++) {
				if(board[i][j].equals("*")||board[i][j].length()==3) {
					check++;
				}
			}
		}
		if(check!=0) {
			break;
		}
		if(check==0) {
			if(withFile==true) {
				sd=bufread.readLine();
				if(!sd.equals("F")) {
				xy=sd.substring(0, 2);
				}
				if(sd.equals("F")) {
					System.exit(0);
				}
				while(x<0||x>9||y<0||y>8||(turn%2==0&&!board[x][y].substring(0, 1).equals("g"))) {
					sd=bufread.readLine();
					if(!sd.equals("F")) {
					xy=sd.substring(0, 2);
					}
					if(sd.equals("F")) {
						System.exit(0);
					}
					c=xy.charAt(0);
					y=c-'a';
					x=Integer.valueOf(xy.substring(1,2));
					inleft++;
				}
				while(x<0||x>9||y<0||y>8||(turn%2==1&&!board[x][y].substring(0, 1).equals("r"))) {
					sd=bufread.readLine();
					if(!sd.equals("F")) {
					xy=sd.substring(0, 2);
					}
					if(sd.equals("F")) {
						System.exit(0);
					}
					c=xy.charAt(0);
					y=c-'a';
					x=Integer.valueOf(xy.substring(1,2));
					inleft++;
				}
			}
			if(withFile==false) {
				System.out.print("No place to go, select again: ");
				xy = scan.nextLine();
				if(xy.equals("F")) {
					System.exit(0);
				}
				while(x<0||x>9||y<0||y>8||(turn%2==0&&!board[x][y].substring(0, 1).equals("g"))) {
					System.out.print("Not valid, select again: ");
					xy = scan.nextLine();
					if(xy.equals("F")) {
						System.exit(0);
					}
					c=xy.charAt(0);
					y=c-'a';
					x=Integer.valueOf(xy.substring(1,2));
				}
				while(x<0||x>9||y<0||y>8||(turn%2==1&&!board[x][y].substring(0, 1).equals("r"))) {
					System.out.print("Not valid, select again: ");
					xy = scan.nextLine();
					if(xy.equals("F")) {
						System.exit(0);
					}
					c=xy.charAt(0);
					y=c-'a';
					x=Integer.valueOf(xy.substring(1,2));
				}
			}
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
			inleft++;
		}
			check=0;
		}
		bufread.close();
		if(withFile==true){
		System.out.println("Select piece: "+xy);
		}
		System.out.println("   a  b  c  d  e  f  g  h  i");
		for(i = 9; i >-1; i--) {
			System.out.print(i + " ");
			for (j = 0; j <9; j++) {
				if(board[i][j].length()==2) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ board[i][j]+" "
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ board[i][j]+" "
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].equals("*")) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ "  "+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ "  "+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].length()==3) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].equals("0")){
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ "   "
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ "   "
								+ ANSI_RESET + ANSI_RESET);
					}
				}
			}
			System.out.println();
		}
		if(withFile==true) {
			File output=new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Output.txt");
			if(!output.exists()) {
				output.createNewFile();
			}
			FileWriter ow=new FileWriter(output,true);
			BufferedWriter bw=new BufferedWriter(ow);
			bw.write("Select piece: "+xy+"\r\n");
			bw.write("   a  b  c  d  e  f  g  h  i\r\n");
			for(i = 9; i >-1; i--) {
				bw.write(i + " ");
				for (j = 0; j < 9; j++) {
					if(board[i][j].length()==2) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write(
									 board[i][j]+" ");
						} else {
							bw.write( board[i][j]+" "
									);
						}
					}
					if(board[i][j].equals("*")) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write("  "+board[i][j]
									);
						} else {
							bw.write( "  "+board[i][j]
									);
						}
					}
					if(board[i][j].length()==3) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write(board[i][j]
									);
						} else {
							bw.write(board[i][j]
									);
						}
					}
					if(board[i][j].equals("0")){
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write( "    "
									);
						} else {
							bw.write( "    "
									);
						}
					}
				}
				bw.newLine();
			}
			bw.close();
		}
		start=board[x][y];
		keys=keyb[x][y];
		q=x; w=y;
	}
	
	public void moveObject(boolean withFile) throws IOException {
		if(withFile==true) {
			File in= new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Input.txt");
			FileReader readin = new FileReader(in);
			BufferedReader bufread= new BufferedReader(readin);
			int h;
			xy=sd.substring(4, 6);
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
			if(x<0||x>9||y<0||y>8||(!(board[x][y].equals("*"))&&!(board[x][y].length()==3))) {
				for(h=inleft;h>1;h--) {
					sd=bufread.readLine();
				}
			}
			while(x<0||x>9||y<0||y>8||(!(board[x][y].equals("*"))&&!(board[x][y].length()==3))) {
				sd=bufread.readLine();
				if(!sd.equals("F")) {
				xy=sd.substring(4, 6);
				}
				if(sd.equals("F")) {
					System.exit(0);
				}
				c=xy.charAt(0);
				y=c-'a';
				x=Integer.valueOf(xy.substring(1,2));
				inleft++;
			}
			File output=new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Output.txt");
			if(!output.exists()) {
				output.createNewFile();
			}
			FileWriter ow=new FileWriter(output,true);
			BufferedWriter bw=new BufferedWriter(ow);
			bw.write("Move piece: "+xy+"\r\n");
			bw.close();
			System.out.println("Move piece: "+xy);
		}
		if(withFile==false) {
		System.out.print("Move piece: ");
		xy = scan.nextLine();
		if(xy.equals("F")) {
			System.exit(0);
		}
		c=xy.charAt(0);
		y=c-'a';
		x=Integer.valueOf(xy.substring(1,2));
		while(x<0||x>9||y<0||y>8||(!(board[x][y].equals("*"))&&!(board[x][y].length()==3))) {
			System.out.print("Not valid, select again: ");
			xy = scan.nextLine();
			if(xy.equals("F")) {
				System.exit(0);
			}
			c=xy.charAt(0);
			y=c-'a';
			x=Integer.valueOf(xy.substring(1,2));
		}
		}
		if(board[x][y].length()==3) {
			map.get(keyb[x][y]).setX(100);
			map.get(keyb[x][y]).setY(100);
		}
		int i,j;
		board[x][y]=start;
		board[q][w]="0";
		keyb[x][y]=keys;
		keyb[q][w]="0";
		map.get(keyb[x][y]).setX(x);
		map.get(keyb[x][y]).setX(y);
		for(i=0;i<10;i++) {
			for(j=0;j<9;j++) {
				if(board[i][j].equals("*")) {
					board[i][j]="0";
				}
				if(board[i][j].length()==3) {
					board[i][j]=board[i][j].substring(0,2);
				}
			}
		}
		turn++;
	}
	public void printBoard(boolean withFile) throws IOException {
		int i, j;
		if(withFile==true) {
			File output=new File("C:\\Users\\proto\\Desktop\\javavava\\PA2\\Output.txt");
			if(!output.exists()) {
				output.createNewFile();
			}
			FileWriter ow=new FileWriter(output,true);
			BufferedWriter bw=new BufferedWriter(ow);
			bw.write("    a  b  c  d  e  f  g  h  i\r\n");
			for(i = 9; i >-1; i--) {
				bw.write(i + " ");
				for (j = 0; j < 9; j++) {
					if(board[i][j].length()==2) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write(
									board[i][j]+" "
									);
						} else {
							bw.write(
									 board[i][j]+" "
									);
						}
					}
					if(board[i][j].equals("*")) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write( "  "+board[i][j]
									);
						} else {
							bw.write("  "+board[i][j]
									);
						}
					}
					if(board[i][j].length()==3) {
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write(board[i][j]
									);
						} else {
							bw.write(board[i][j]
									);
						}
					}
					if(board[i][j].equals("0")){
						if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
							bw.write( "    "
									);
						} else {
							bw.write("    "
									);
						}
					}
				}
				bw.newLine();
			}
			bw.close();
		}
		System.out.println("   a  b  c  d  e  f  g  h  i");
		for(i = 9; i >-1; i--) {
			System.out.print(i + " ");
			for (j = 0; j < 9; j++) {
				if(board[i][j].length()==2) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ board[i][j]+" "
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ board[i][j]+" "
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].equals("*")) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ "  "+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ "  "+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].length()==3) {
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+board[i][j]
								+ ANSI_RESET + ANSI_RESET);
					}
				}
				if(board[i][j].equals("0")){
					if(i%2==1&&j%2==0||i%2==0&&j%2==1) {
						System.out.print(ANSI_BG_WHITE + ANSI_FG_BLACK
								+ "   "
								+ ANSI_RESET + ANSI_RESET);
					} else {
						System.out.print(ANSI_BG_YELLOW+ ANSI_FG_WHITE
								+ "   "
								+ ANSI_RESET + ANSI_RESET);
					}
				}
			}
			System.out.println();
		}
	}
}

class king extends gameObject{

	public king(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class guard extends gameObject{

	public guard(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class pawn extends gameObject{

	public pawn(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class cannon extends gameObject{

	public cannon(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class rook extends gameObject{

	public rook(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class knight extends gameObject{

	public knight(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}
class elephant extends gameObject{

	public elephant(int x, int y, char type, char color, char target) {
		super(x, y, type, color, target);
	}
	
}