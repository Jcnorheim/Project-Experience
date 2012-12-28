
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import java.net.URL;
import java.util.Iterator; 
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.io.File;
 import java.io.FileWriter;
 import java.io.IOException;
 import java.io.FilePermission;
 import java.util.PropertyPermission;
 
/*
 * Takes in form data from the html file and handles which feeds will be printed
 */
public class ShowParameters extends HttpServlet {
private static ShowParameters instance = null;
static String table[][];
static PrintWriter out; 
  public void doGet(HttpServletRequest request,
                    HttpServletResponse response)
      throws ServletException, IOException {
	table = new String[10][10];
    response.setContentType("text/html");
    out= response.getWriter();
    String title = "Here are the RSS feeds";
    out.println(ServletUtilities.headWithTitle(title) +
                "<H1 ALIGN=CENTER>" + title + "</H1>\n");
    Enumeration paramNames = request.getParameterNames();
	   int c=0,d=0,e=0,f=0;
	while(paramNames.hasMoreElements()) {
	
      String paramName = (String)paramNames.nextElement();

      // storing the data and removes the symbols specified
      String[] paramValues = request.getParameterValues(paramName);
	while(d<paramValues.length){
		table[c][d]=paramValues[d];
		table[c][d]=table[c][d].replaceAll("[\"\']", "");
		table[c][d]=table[c][d].replace(".", "");
		table[c][d]=table[c][d].replace(",", "");
		table[c][d]=table[c][d].replace(";", "");
		table[c][d]=table[c][d].replace(":", "");
		table[c][d]=table[c][d].replace(")", "");
		table[c][d]=table[c][d].replace("(", "");
		table[c][d]=table[c][d].trim();
		if(c==0){
			f++;
		}
		d++;
	}
	d=0;
	c++;
	// got all proper pieces of data or otherwise the system will not work
	if(c==3){
		e=1;
	}
 
      }
    

	int a =0;
	String temp;
	// data is exists and the system handles the chosen feeds
	if(c>1 && e==1){
		while(a<f){
			temp = table[0][a];
			if(temp.equals("ABC")==true){
				out.println("<br/><H1>ABC</H1><br/>");
				parse("http://feeds.abcnews.com/abcnews/internationalheadlines");
			}
			else if(temp.equals("CNN")==true){
				out.println("<br/><H1>CNN</H1><br/>");
				parse("http://rss.cnn.com/rss/cnn_world.rss");
			}
			else if(temp.equals("NBC")==true){
				out.println("<br/><H1>NBC</H1><br/>");
				parse("http://rss.msnbc.msn.com/id/3032091/device/rss/rss.xml");
			}
			else if(temp.equals("BBC")==true){
				out.println("<br/><H1>BBC</H1><br/>");
				parse("http://newsrss.bbc.co.uk/rss/newsonline_uk_edition/world/rss.xml");
			}
			a++;
		}
}

	out.println("</BODY></HTML>");
  }
/*
* Gets the rss/xml data and handles the chosen search
*/
 public void parse(String arg)throws IOException{
 table[1][0]=table[1][0].trim();
 String[] searchList = table[1][0].split(" "); // gets the words to search for
 int d=0;
 while(d<searchList.length){
	searchList[d]=searchList[d].trim();
d++;
}
d=0;
int e=0;
// user requested nothing for search so shows everything
if(searchList[0].equals("")==true){
e=-1;
}
String filePath = arg;
 URL deptHome = new URL(arg);
  	DataInputStream in = new DataInputStream(
  				 deptHome.openStream());
	
  Document  xmlDOM  =  null;  

  try {
      DocumentBuilderFactory docBuilderFactory =   DocumentBuilderFactory.newInstance();

      DocumentBuilder   docBuilder  =  docBuilderFactory.newDocumentBuilder();

      File  fileObj  =  new File ( filePath );

      xmlDOM  = docBuilder.parse ( in );    
   }  catch ( Exception ex )  {
         ex.printStackTrace();
   }

  NodeList itemNodeList  =  xmlDOM.getElementsByTagName( "item" );
int a =0,b =0, c =0, f=0; 
boolean yes = false;
  for (int i = 0; i<  itemNodeList.getLength();  i++ )  {
    Node item = itemNodeList.item( i );
    NodeList itemContentList = item.getChildNodes();

	
     for (int j = 0; j< itemContentList.getLength();  j++ )  {
       Node content =  itemContentList.item( j );
	// user wants data that contains one of his words
	if(table[2][0].equals("any")==true){
         if (content.getNodeName().equals( "title" ) )  {
              Node  child = content.getFirstChild();
			a=0;
			b=0;
			String[] title = child.getNodeValue().split(" ");
			 while(d<title.length){
				// storing the data and removes the symbols specified
				title[d]=title[d].replaceAll("[\"\']", "");
				title[d]=title[d].replace(".", "");
				title[d]=title[d].replace(",", "");
				title[d]=title[d].replace(";", "");
				title[d]=title[d].replace(":", "");
				title[d]=title[d].replace("(", "");
				title[d]=title[d].replace(")", "");
				title[d]=title[d].trim();
				d++;
				}
				d=0;		
			while(a<title.length){
				b=0;
				while(b<searchList.length){
					if(title[a].equals("")==false){
						if(title[a].equals(searchList[b])==true){
							yes= true;
							c++;
							break;
						}
					}

					b++;				
				}		
				a++;
			}
	// found something
	     if(yes==true|| e==-1){
             	out.println("-----------------------------------------------------------------------<br/>" ); 
             	out.println("<H3> "  + child.getNodeValue()+"</H3>");
		} 
          }
	// found something
	if(yes==true || e==-1){
		if (content.getNodeName().equals( "link" ) )  {
		      Node  child = content.getFirstChild();
		     out.println("<a href= \""+child.getNodeValue()+"\"/>Go to full article</a><br/>"); 

			f++;
			if(f==2){
			c=0;
			yes=false;
			f=0;
			}
		  }
		   if (content.getNodeName().equals( "description" ) )  {
		      Node  child = content.getFirstChild();
		      out.println("<H5>"+child.getNodeValue()+"</H5>"); 
			f++;
			if(f==2){
			c=0;
			yes=false;
			f=0;
			}
			
		  }

	}
	}
	// user wants all words to be present
	if(table[2][0].equals("all")==true){
		int array[]=new int[searchList.length];
		int q =0;
		while(q<searchList.length){
			array[q]=0;
			q++;
		}
         if (content.getNodeName().equals( "title" ) )  {
              Node  child = content.getFirstChild();
			a=0;
			b=0;
			c=0;
			String[] title = child.getNodeValue().split(" ");
			 while(d<title.length){
				title[d]=title[d].trim();
				d++;
				}
				d=0;							
			while(a<title.length){
				b=0;
				while(b<searchList.length){
					if(title[a].equals("")==false){
						if(title[a].equals(searchList[b])==true){
							// not a repeat							
							if(array[b]==0){
								c++;
								
								array[b]=1;
							}
						}
					}
					
					b++;				
				}		
				a++;
			}
	// found something
	     if(c>=searchList.length || e==-1){
             	out.println("<br/>-----------------------------------------------------------------------<br/>" ); 
             	out.println("<H3> "  + child.getNodeValue()+"</H3>");
		} 
          }
	// found something
	if(c>=searchList.length ||  e==-1){
		  if (content.getNodeName().equals( "link" ) )  {
		      Node  child = content.getFirstChild();
		     out.println("<a href= \""+child.getNodeValue()+"\"/>Go to full article</a><br/>"); 
			f++;
			if(f==2){
			c=0;
			f=0;
			}
		  }
		   if (content.getNodeName().equals( "description" ) )  {
		      Node  child = content.getFirstChild();
		      out.println("<H5>"+child.getNodeValue()+"</H5>"); 
			f++;
			if(f==2){
			c=0;
			f=0;
			}
		  }

	}
	}
     }  

  }   

}

  public void doPost(HttpServletRequest request,
                     HttpServletResponse response)
      throws ServletException, IOException {
    doGet(request, response);
  }
}

