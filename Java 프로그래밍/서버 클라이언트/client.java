package lab_14;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class client {
	public static void main(String[] args) throws UnknownHostException, IOException {
		String serverIP = "localhost";
		Socket soc;
		String filepath;
		Scanner s = new Scanner(System.in);
			soc = new Socket(serverIP, 5000);
			InputStream in = soc.getInputStream();
			DataInputStream dis = new DataInputStream (in);
			OutputStream out = soc.getOutputStream();
			DataOutputStream dos = new DataOutputStream(out);
			filepath=s.nextLine();
			dos.writeUTF(filepath);
			System.out.println("Requested file name : "+filepath);
			byte[] bytes=new byte[100];
			while(true) {
				String msg=dis.readUTF();
				if(msg==null) break;
				System.out.println(msg);
			}
			soc.close();
			s.close();
	}
}
