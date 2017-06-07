import java.util.regex.*;

readdata data1;
readdata data2;
readdata data3;
int k=7;
float dataMin1,dataMax1;
float dataMin2,dataMax2;
float dataMin3,dataMax3;
String[] rownames1,rownames2,rownames3;
String[] colnames1=new String[100];
String[] colnames2=new String[100];
String[] colnames3=new String[100];
float plotX1,plotY1;
float plotX2,plotY2;
float[][] linePoint1 = new float[100][9];
float[][] linePoint2 = new float[100][9];
float[][] linePoint3 = new float[100][9];
String[] year={"2004","2005","2006","2007","2008","2009","2010","2011","2012"};
void setup(){
  size(1280,720);
  smooth();
  data1=new readdata("air.csv");
  data2=new readdata("greenland.csv");
  data3=new readdata("wasted water.csv");
  rownames1=data1.getRowNames();
  colnames1=data1.getColumnNames();
  rownames2=data2.getRowNames();
  colnames2=data2.getColumnNames();
  rownames3=data3.getRowNames();
  colnames3=data3.getColumnNames();
  dataMin1=(int)data1.getRowMin(k);
  dataMax1=(int)data1.getRowMax(k);
  dataMin2=(int)data2.getRowMin(k);
  dataMax2=(int)data2.getRowMax(k);
  dataMin3=(int)data3.getRowMin(k);
  dataMax3=(int)data3.getRowMax(k);
  plotX1 = 100;
  plotX2 = width - plotX1;
  plotY1 = 50;
  plotY2 = height - plotY1;
  
}
void draw(){
  background(224);
  fill(255);
  rectMode(CORNERS);
  noStroke();
  rect(plotX1,plotY1,plotX2,plotY2);
  datapoints();
  drawpoints();
  drawaxis();
  drawnames();
 
}
void datapoints(){
  for(int col1=8;col1>=0;col1--){
      strokeWeight(2);
      stroke(0);
      float value1 = data1.getFloat(k,col1);
      linePoint1[k][col1] =value1; 
      float y1 = map(value1, dataMin1, dataMax1, plotY1+200,plotY2-200);
      linePoint1[k][col1] =plotY2-y1; 
    }
  for(int col2=8;col2>=0;col2--){
      strokeWeight(2);
      stroke(0);
      float value2 = data2.getFloat(k,col2);
      linePoint2[k][col2] =value2; 
      float y2 = map(value2, dataMin2, dataMax2, plotY1+200,plotY2-200);
      linePoint2[k][col2] =plotY2-y2; 
    }
  for(int col3=8;col3>=0;col3--){
      strokeWeight(2);
      stroke(0);
      float value3 = data3.getFloat(k,col3);
      linePoint3[k][col3] =value3; 
      float y3 = map(value3, dataMin3, dataMax3, plotY1+200,plotY2-200);
      linePoint3[k][col3] =plotY2-y3; 
    }
}
void drawpoints(){
  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;
  int j=180;
  for(int i=7;i>=0;i--){
    x1=linePoint1[k][i];
    y1=linePoint1[k][i+1];
    x2=linePoint2[k][i];
    y2=linePoint2[k][i+1];
    x3=linePoint3[k][i];
    y3=linePoint3[k][i+1];
    stroke(77,120,224);
    strokeWeight(5);
    line(j,y1,j+115,x1);
    stroke(240,19,19);
    strokeWeight(5);
    line(j,y2,j+115,x2);
    stroke(11,224,11);
    strokeWeight(5);
    line(j,y3,j+115,x3);
    j=j+115;
   }
     
}
void drawaxis(){
   String time = new String();
   int j=180;
   for(int i=0;i<9;i++){
      time=year[i];
      fill(0);
      textSize(20);
      textAlign(CENTER,BOTTOM);
      text(time,j,plotY2-10);
      stroke(0);
      strokeWeight(2);
      line(j,plotY1+100,j,plotY2-100);
      j=j+115;
  }
  stroke(0);
  strokeWeight(2);
  line(plotX1+20,plotY2-100,plotX2-20,plotY2-100);
}
void drawnames(){
    fill(0);
    textSize(30);
    textAlign(CENTER,TOP);
    text(rownames1[k],640,plotY1+10); 
    stroke(77,120,224);
    strokeWeight(5);
    line(110,plotY1+20,150,plotY1+20);
    textSize(20);
    textAlign(LEFT,CENTER);
    text("air",155,plotY1+20); 
    stroke(240,19,19);
    strokeWeight(5);
    line(110,plotY1+40,150,plotY1+40);
    textSize(20);
    textAlign(LEFT,CENTER);
    text("greenland",155,plotY1+40); 
    stroke(11,224,11);
    strokeWeight(5);
    line(110,plotY1+60,150,plotY1+60);
    textSize(20);
    textAlign(LEFT,CENTER);
    text("wasted water",155,plotY1+60); 
}
