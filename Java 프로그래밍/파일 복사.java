package week8;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.Scanner;
import java.io.File;

public class Copy {
	public static void main(String[] args) throws IOException{
		Scanner sc=new Scanner(System.in);
		int input=0, count=0;
		if(args.length==2) {
			File in= new File("C:\\Users\\proto\\Desktop\\javavava\\Week8\\"+args[0]);
			File out= new File("C:\\Users\\proto\\Desktop\\javavava\\Week8\\"+args[1]);
			if(in.exists()) {
				if(out.exists()) {
					System.err.println("Target file "+args[1]+"already exist");
				}
				else {
					InputStream fis= new FileInputStream(in);
					
					BufferedInputStream br = new BufferedInputStream(fis);
					
					byte[] data = new byte[10000000];
					
					FileOutputStream fos = new FileOutputStream(out);
					BufferedOutputStream bw = new BufferedOutputStream (fos);
					
					 while((input=fis.read(data))!=-1){
						   bw.write(data, 0, input);
						   count+=input;
					 }
					bw.flush();
					bw.close(); fos.close();
					br.close(); fis.close();
					System.out.println(in.length()+" bytes copied");
				}
				
			}
			else
				System.err.println("Source file "+args[0]+" does not exist");
			
		}
		else {
			System.err.println("Usage:java Copy sourceFile targetFile");
		}
		
		
		
	}
}
