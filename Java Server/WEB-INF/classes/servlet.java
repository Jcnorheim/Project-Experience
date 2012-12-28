
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.net.URL;
import java.util.ArrayList;

public class servlet extends HttpServlet{
	private String commandLine=null;
	private BufferedReader br;
	private BankSys bs=new BankSys();
	private boolean validlog=false, exit=false;
	private User currUser;
	public void doGet( HttpServletRequest req, HttpServletResponse res ) throws IOException, ServletException {
	parse( req, res );
}

public void doPost( HttpServletRequest req,HttpServletResponse res ) throws IOException, ServletException {
	parse( req, res );
}

private void parse( HttpServletRequest req,
HttpServletResponse res ) throws IOException,ServletException {
	res.setContentType( "text/html" );
	PrintWriter out = res.getWriter();
	out.println( "<html><head><meta name='cache-control' content='no-cache' /><meta name='expires' content='0' /><meta name='pragma' content='no-cache' /></head><body>" );
	if(req.getParameter("submit").equals("Login")){
		String username=req.getParameter( "username" );
		if(username.equals("Yu")){
			
				currUser=logSuccess(username);
				out.println(topmenu());
				}
			else{
				out.println("<p>Wrong username,please try again...</p>");
				req.getRequestDispatcher("../../examples/servlets/bank.html").include(req, res);  
			}
		
	}
	else if(req.getParameter("submit").equals("Create")){
		currUser=logSuccess("Yu");
		int type=Integer.parseInt(req.getParameter("create"));
		currUser.createAcc(Type.getType(type-1).toString(), 0);
		out.println("<p>New account created!</p>");
		out.println(topmenu());
	}
	else if(req.getParameter("submit").startsWith("delete")){
		int option=Integer.parseInt(req.getParameter("submit").split(" ")[1]);
		currUser=logSuccess("Yu");
		if(currUser.removeAcc(currUser.accounts.get(option), option)){
		out.println("<p>delete success</p>");
		out.println(topmenu());
		}
		else{
		out.println("<p>You can't remove this account!</p>");
		out.println(topmenu());
		}
	}
	else if(req.getParameter("submit").equals("Transfer")){
		int from=Integer.parseInt(req.getParameter("from"));
		int to=Integer.parseInt(req.getParameter("to"));
		double amount=Double.parseDouble(req.getParameter("amount"));
		if(currUser.accounts.get(from).trans(currUser.accounts.get(to), amount))
		out.println("Transfer success");
		else
		out.println("No enough funds in acount( ID:"+currUser.accounts.get(from).getIndex()+")");
		out.println(topmenu());
	}
	out.println( "</body></html>" );
	}

	public String topmenu(){
		String top="<p>Current account:</p>";
		top+="<form action='servlet'>";
		top+="<table>";
		top+="<tr><td>Select Index</td><td>Account Number</td><td>Account Type</td><td>Balance</td></tr>";
		int i=0;
		for(Account a:currUser.accounts){
			top+="<tr><td align='center'>"+i+"</td><td align='center'>"+a.getIndex()+"</td><td align='center'>"+a.getType()+"</td><td>"+a.getBalance()+"</td><td><input type='submit' name='submit' value='delete "+i+"'/></td></tr>";
			i++;
		}
		top+="</table>";
		top+="Create Account: <select name='create'><option value='1'>checking</option><option value='2'>saving</option><option value='3'>credit</option></select><input type='submit' name='submit' value='Create'/>";
		top+="<hr/>";
		top+="Transfer money: $ <input type='text' name='amount' /> from <input type='text' name='from' /> to <input type='text' name='to' /><br/><input type='submit' name='submit' value='Transfer'/></form>";
		return top;
	}
	public User logSuccess(String username) throws IOException{
		User user=null;
		if(username.equals("Yu"))
		user=new User("Yu", bs.initializeAcc("Yu"));
		if(user!=null){
		return user;
		}
		else return null;
	}
}
