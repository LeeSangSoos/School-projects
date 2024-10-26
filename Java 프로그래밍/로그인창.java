package lab9;
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.event.*;

class MyFrame extends JFrame{
	String id="test";
	String password="12345678";
	
	MyFrame(){
		setTitle("Login");
		setPreferredSize(new Dimension(256,114));
		setVisible(true);
		setResizable(false);
		
		Container c = getContentPane();
		JLabel ids=new JLabel("Id");
		JLabel pass=new JLabel("Password");
		JTextField field_id = new JTextField();
		JPasswordField field_pw = new JPasswordField();
		JButton login = new JButton("login");
		JPanel panel = new JPanel();
		panel.setLayout(null);
		
		ids.setBounds(2,5,80,20);
		field_id.setBounds(82,5,160,20);
		pass.setBounds(2,30,80,20);
		field_pw.setBounds(82,30,160,20);
		login.setBounds(1,55,240,20);
		
		panel.add(ids);
		panel.add(field_id);
		panel.add(pass);
		panel.add(field_pw);
		panel.add(login);
		
		c.add(panel);
		
		pack();
		login.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(field_id.getText().equals(id)) {
					System.out.println("Id correct");
				}
				else if(!field_id.getText().equals(id)) {
					System.out.println("Id wrong");
				}
				if(field_pw.getText().equals(password)) {
					System.out.println("Password correct");
				}
				else if(!field_pw.getText().equals(password)) {
					System.out.println("Password wrong");
				}
			}
		});
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}

public class lab9 {
	public static void main(String[] args) {
		MyFrame mf= new MyFrame();
	}
}