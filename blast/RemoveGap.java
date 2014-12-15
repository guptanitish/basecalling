import java.io.*;
import java.util.*;

public class RemoveGap {
	public static void main(String[] args) throws IOException {
		String path = args[0];
		String fileName = path.substring(path.lastIndexOf('/')+1, path.lastIndexOf('.'));
		String folder = path.substring(0, path.lastIndexOf('/'));
		BufferedReader br = new BufferedReader(new FileReader(path));
		PrintWriter out = new PrintWriter(folder+"/"+fileName+".alignedfasta");
		StringTokenizer st = new StringTokenizer(br.readLine());
		int start = -1, end = -1;
		String query = null;
		String subject = null;
		
		if (st.hasMoreTokens()) 
			start = Integer.parseInt(st.nextToken());
		if (st.hasMoreTokens())
			end = Integer.parseInt(st.nextToken());
		if (st.hasMoreTokens())
			query = st.nextToken();
		if (st.hasMoreTokens())
			subject = st.nextToken();

		out.println(start);
		out.println(end);

		int length1 = query.length();
		int length2 = subject.length();

		if (length1 == length2) {
			StringBuffer temp1 = new StringBuffer();
			StringBuffer temp2 = new StringBuffer();
			for (int i = 0; i < length1; ++i) {
				char ch1 = query.charAt(i);
				char ch2 = subject.charAt(i);	
				if (ch1 != '-') {
					temp1.append(ch1);
					temp2.append(ch2);
				}
			}

			if ((end-start+1) != temp1.length())
				System.out.println("Query string doesn't agree with start and end, start =  " + start + ", end = " + end + ", length = " + temp1.length());
			out.println(temp1.toString());
			out.println(temp2.toString()); 
		}

		out.flush();
		out.close();

		System.exit(0);
	}
}
			
					
