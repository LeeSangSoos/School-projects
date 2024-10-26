import java.util.Scanner;

public class LA_1 {
	public static void main(String[] args) {
		Scanner scn = new Scanner(System.in);
		int number= scn.nextInt();
		int[] arr_int=new int[100];
		int a = number;
		int length=0;
		while(a>0) {
			arr_int[length]=a%2;
			a=a/2;
			length++;
		}
		int i=length-1;
		System.out.print("b ");
		while(i>=0) {
			System.out.print(arr_int[i]);
			i--;
		}
		System.out.print("\n");
		a = number;
		length=0;
		while(a>0) {
			arr_int[length]=a%8;
			a=a/8;
			length++;
		}
		i=length-1;
		System.out.print("o ");
		while(i>=0) {
			System.out.print(arr_int[i]);
			i--;
		}
		System.out.print("\n");
		a = number;
		length=0;
		while(a>0) {
			arr_int[length]=a%16;
			a=a/16;
			length++;
		}
		i=length-1;
		System.out.print("h ");
		while(i>=0) {
			if(arr_int[i]==10) {
				System.out.print("a");
			}
			else if(arr_int[i]==11) {
				System.out.print("b");
			}
			else if(arr_int[i]==12) {
				System.out.print("c");
			}
			else if(arr_int[i]==13) {
				System.out.print("d");
			}
			else if(arr_int[i]==14) {
				System.out.print("e");
			}
			else if(arr_int[i]==15) {
				System.out.print("f");
			}
			else {
				System.out.print(arr_int[i]);
			}
			i--;
		}
		scn.close();
	}
}
