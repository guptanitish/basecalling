package com.cs.classifier;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;

public class DataManager {

String trainingPath;	
String testPath;
int totalCount=0;
public DataManager(String trainingDataPath,String testDataPath){
	trainingPath=trainingDataPath;
	testPath=testDataPath;
}	
public HashMap<String,ArrayList<Node>> getTrainingData(){
	HashMap<String,ArrayList<Node>> resultMap = new HashMap<String,ArrayList<Node>>();
	
	File trainingFile = new File(trainingPath);	
	BufferedReader reader = null;
	try {
	
	
		reader = new BufferedReader(new FileReader(trainingFile));
		String text = null;
		int count=0;
		while ((text = reader.readLine()) != null) {
			String[] lineStr= text.split(" ");
			if(lineStr[3]!=null){
				if(resultMap.containsKey(lineStr[3].substring(2,3))){
					resultMap.get(lineStr[3].substring(2,3)).add(new Node(lineStr[0],lineStr[1],lineStr[2],lineStr[3]));
				}
				else{
				resultMap.put(lineStr[3].substring(2,3), new ArrayList<Node>());
				resultMap.get(lineStr[3].substring(2,3)).add(new Node(lineStr[0],lineStr[1],lineStr[2],lineStr[3]));
				}
				
			count++;	
				
			}
			totalCount=count;	
			
		}
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} 
	finally {
		try {
			if (reader != null) {
				reader.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

return resultMap;	
}
public int getTotalEntries() {
	
	return totalCount;
}


}
