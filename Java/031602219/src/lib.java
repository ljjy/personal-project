package src;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class lib {
	
	public static String text="";
	public static int linenum;
	
	public static int countChar(String path,int count) throws IOException{
		try {
			FileInputStream file = new FileInputStream(path);	//构造文件流
			InputStreamReader reader = new InputStreamReader(file);		//文件流读取
			BufferedReader buffReader = new BufferedReader(reader);
			String strline = "";
			String blank_regex = "^\\s*$";
			linenum = 0;
			text="";
			Pattern b_pat = Pattern.compile(blank_regex);
	        while((strline = buffReader.readLine())!=null){
	        	linenum+=1;		//每当读取任意一行默认该行存在换行符            
	            text += strline + " ";	
	            count+=strline.length()+linenum;
	            Matcher b_mat = b_pat.matcher(strline);
	            if(b_mat.matches())
	            	linenum--;
	        }
	        buffReader.close();		        
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}finally{
			text = text.toLowerCase();	//大写字母同意转化为小写字母
		}
		return count;
	}
	
	public static String getText(){
		return text;
	}
	
	public static int countLine(){
		return linenum;
	}

}
