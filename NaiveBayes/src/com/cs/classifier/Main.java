package com.cs.classifier;

import java.util.ArrayList;
import java.util.HashMap;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		NBClassifier nbc = new NBClassifier("/Users/chaitanya/Documents/workspace/CompBio/file2.txt");
		
		String result=nbc.classify("90.1913198885" ,"1.06905155728", "0.1124");
		System.out.println(result);
		//HashMap<String,ArrayList<Node>> hm = dm.getTrainingData();
		//ArrayList<Node> arr = hm.get("G");
		//for(Node n : arr){
		//	System.out.println(n.getAllValues());
	//	}
		
	}

}
