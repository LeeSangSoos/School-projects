import java.util.Scanner;

public class StringMethod {
	// Returns the string created by adding 's2' after position 'index' of 's1'.
	static String stringToNum(String[] s) {
		int i=0;
		String[] s2=new String[3];
		while(i<3) {
			if(s[i].equals("Zero")) {
				s2[i]="0";
			}
			if(s[i].equals("One")) {
				s2[i]="1";
			}
			if(s[i].equals("Two")) {
				s2[i]="2";
			}
			if(s[i].equals("Three")) {
				s2[i]="3";
			}
			if(s[i].equals("Four")) {
				s2[i]="4";
			}
			if(s[i].equals("Five")) {
				s2[i]="5";
			}
			if(s[i].equals("Six")) {
				s2[i]="6";
			}
			if(s[i].equals("Seven")) {
				s2[i]="7";
			}
			if(s[i].equals("Eight")) {
				s2[i]="8";
			}
			if(s[i].equals("Nine")) {
				s2[i]="9";
			}
			i++;
		}
		i=0;
		String s3="";
		while(i<3) {
			s3+=s2[i];
			i++;
		}
		return s3;
	}
	// Returns three number in alphabetical ascending order
	static String orderString(String[] s) {
		int i=0;
		String wait;
		while(i<2) {
			if(s[i].charAt(0)>s[i+1].charAt(0)) {
				wait=s[i+1];
				s[i+1]=s[i];
				s[i]=wait;
			}
			else if(s[i].charAt(0)==s[i+1].charAt(0)&&s[i].charAt(1)>s[i+1].charAt(1)) {
				wait=s[i+1];
				s[i+1]=s[i];
				s[i]=wait;
			}
			i++;
		}
		i=0;
		while(i<2) {
			if(s[i].charAt(0)>s[i+1].charAt(0)) {
				wait=s[i+1];
				s[i+1]=s[i];
				s[i]=wait;
			}
			else if(s[i].charAt(0)==s[i+1].charAt(0)&&s[i].charAt(1)>s[i+1].charAt(1)) {
				wait=s[i+1];
				s[i+1]=s[i];
				s[i]=wait;
			}
			i++;
		}
		i=0;
		String s3="";
		while(i<3) {
			s3+=s[i];
			s3+=" ";
			i++;
		}
		return s3;
		
	}
	// Returns reversed string of 's'
	static String reverse(String s) {
		String wait;
		int i=0;
		String[] s1=new String[3];
		while(i<3) {
			s1[i]=s.split("\\s")[i];
			i++;
		}
		i=0;
		String[] s2=new String[3];
		while(i<3) {
			if(s1[i].equals("Zero")) {
				s2[i]="0";
			}
			if(s1[i].equals("One")) {
				s2[i]="1";
			}
			if(s1[i].equals("Two")) {
				s2[i]="2";
			}
			if(s1[i].equals("Three")) {
				s2[i]="3";
			}
			if(s1[i].equals("Four")) {
				s2[i]="4";
			}
			if(s1[i].equals("Five")) {
				s2[i]="5";
			}
			if(s1[i].equals("Six")) {
				s2[i]="6";
			}
			if(s1[i].equals("Seven")) {
				s2[i]="7";
			}
			if(s1[i].equals("Eight")) {
				s2[i]="8";
			}
			if(s1[i].equals("Nine")) {
				s2[i]="9";
			}
			i++;
		}
		wait=s2[2];
		s2[2]=s2[0];
		s2[0]=wait;
		String s3="";
		i=0;
		while(i<3) {
			s3+=s2[i];
			i++;
		}
		return s3;
	}
	public static void main(String[] args) {
		// Prompt the user to enter the number(string)
		Scanner scn = new Scanner(System.in);
		System.out.print("Enter the Number : ");
		System.out.print(" ");
		String strLine=scn.nextLine();
		String[] s1=new String[3];
		int i=0;
		while(i<3) {
			s1[i]=strLine.split("\\s")[i];
			i++;
		}
		// Call your function
		String variable1=stringToNum(s1);
		String variable2=orderString(s1);
		String variable3=reverse(strLine);
		// Display result
		System.out.println(variable1);
		System.out.println("");
		System.out.println(variable2);
		System.out.println("");
		System.out.print("Reverse number is : ");
		System.out.println(variable3);
		scn.close();
	}
}