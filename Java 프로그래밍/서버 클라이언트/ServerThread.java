package lab_14;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.Charset;
import java.io.File;
import java.io.*;

public class ServerThread extends Thread{
	public void ServerThread () {
		
	}
	public void run() {
		ServerSocket ss = null;
		try {
			ss = new ServerSocket(5000);
			System.out.println("server is ready");
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		Socket soc=null;
		InputStream in = null;
		OutputStream out=null;
		try {
			soc=ss.accept();
			in=soc.getInputStream();
			out=soc.getOutputStream();
			DataInputStream dis=new DataInputStream(in);
			DataOutputStream dos=new DataOutputStream(out);
			String filepath=dis.readUTF();
			System.out.println("File Name : "+filepath);
			Reader fr= new java.io.FileReader(filepath);
			try {
				BufferedReader read=new BufferedReader(fr);
				while(true){
				 	String data = read.readLine();
				 	if(data==null) {
				 		break;
				 	}
				 	dos.writeUTF(data);
				}
				read.close();
			}
			catch(IOException e) {
				System.out.println("File ["+filepath+"] doesn't exist!");
			}
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		Thread t = new ServerThread();
		t.start();
		boolean flag = true;
		while (flag) {
			try {
				Thread.sleep(2000);
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
