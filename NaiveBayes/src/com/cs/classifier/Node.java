package com.cs.classifier;

public class Node {
private String mean;
private String dev;
private String length;
private String kMer;
	
public Node(String mn,String dv,String ln,String kr){
	mean=mn;
	dev=dv;
	length=ln;
	kMer=kr;		
}

public String getAllValues(){
	
	return mean+" "+dev+" "+" "+length+" "+kMer;
}

public String getMean() {
	// TODO Auto-generated method stub
	return mean;
}
public String getDev() {
	// TODO Auto-generated method stub
	return dev;
}
public String getLength() {
	// TODO Auto-generated method stub
	return length;
}

}
