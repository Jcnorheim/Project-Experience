
import java.lang.*;
import java.util.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.URL;

public class log extends HttpServlet{
	private String filename="/class/tomcat/tongx114/WEB-INF/log.txt";
	public ArrayList<Account> getAccs(String user) throws IOException{
		BankSys bs = new BankSys();
		FileInputStream fstream = new FileInputStream(filename);
		DataInputStream in = new DataInputStream(fstream);
		ArrayList<Account> accounts = new ArrayList<Account>();

		while (in.available() !=0) {
			String[] tokens = in.readLine().split(" ");
			int index = Integer.parseInt(tokens[0]);
			double balance = Double.parseDouble(tokens[1]);
			String type = tokens[2];
			Account a = bs.setAcc(index, user, type, false);
			a.makeDeposite(balance, false);
			accounts.add(a);
		}
		in.close();
		return accounts;
	}

	

	public void modify(int index, double balance, boolean isUp) throws IOException{
		
		FileInputStream fstream = new FileInputStream(filename);
		DataInputStream in = new DataInputStream(fstream);
		
		
		String line = null;
		String i = "" + index;
		String type = null;
		StringBuilder sb=new StringBuilder();


		while(in.available() != 0) {
			line = in.readLine();
			if (!line.startsWith(i)) {
				sb.append(line+"\n");
			}
			else {
				String[] tokens = line.split(" ");
				type = tokens[2];
				if(isUp) {
					sb.append(i+" "+balance+" "+type+"\n");
				}
			}
		}
		in.close();
		FileOutputStream pw = new FileOutputStream(filename, false);
		PrintStream ps= new PrintStream(pw);
		ps.println(sb.toString().substring(0, sb.length()-1));
		ps.close();
		

	}

	public void addAcc(String user, String type) throws IOException{
		File inFile = new File(filename);
		BufferedReader br = new BufferedReader(new FileReader(filename));
		int i = 0;
		String line = null;

		while((line = br.readLine()) != null) {
			i++;
		}

		br.close();
		FileWriter pw = new FileWriter(filename, true);
		BufferedWriter out = new BufferedWriter(pw);
		String s = i + " 0 " + type + "\n" ;
		out.write(s);
		out.close();
	}
}
		
		

