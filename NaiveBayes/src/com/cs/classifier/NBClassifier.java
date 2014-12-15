package com.cs.classifier;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

public class NBClassifier {
DataManager dm;	
HashMap<String,ArrayList<Node>> trHM;
int totalCount;
public NBClassifier(String trPath){

dm = new DataManager(trPath,null);
	
	
}

public String classify(String mean, String dev, String length) {
	trHM =dm.getTrainingData();
	totalCount= dm.getTotalEntries();
	int meanCount,devCount,lengthCount;
	float maxProb=0;
	String predClass="";
	float pr1,pr2,pr3;
	for(Entry<String,ArrayList<Node>> er : trHM.entrySet()){
		meanCount=0;
		devCount=0;
		lengthCount=0;
		for(Node n: er.getValue()){
			if(n.getMean().equals(mean))
			meanCount++;
			if(n.getDev().equals(dev))
				devCount++;
			if(n.getLength().equals(length))
				lengthCount++;
		}
		pr1=((float)meanCount/er.getValue().size())*((float)devCount/er.getValue().size())*((float)lengthCount/er.getValue().size())*((float)er.getValue().size()/totalCount);
		if(pr1>maxProb){
			maxProb=pr1;
			predClass=er.getKey();
		}
		
		
		
	}
	return predClass;
}	
	

}
