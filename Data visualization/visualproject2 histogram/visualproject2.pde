import java.util.regex.*;
readdata data1;
readdata data2;
readdata data3;
readdata data4;
float dataMin1,dataMax1;
float dataMin2,dataMax2;
float dataMin3,dataMax3;
float dataMin4,dataMax4;
int j=1;
String[] rownames1,rownames2,rownames3;
String[] colnames1=new String[100];
String[] colnames2=new String[100];
String[] colnames3=new String[100];
float[][] linePoint1 = new float[31][100];
float[][] linePoint2 = new float[31][100];
float[][] linePoint3 = new float[31][100];
float[][] linePoint4 = new float[31][100];
void setup(){
  size(1280,720);
  smooth();
  data1=new readdata("air.csv");
  data2=new readdata("greenland.csv");
  data3=new readdata("wasted water.csv");
  data4=new readdata("deathrate.csv");
  rownames1=data1.getRowNames();
  colnames1=data1.getColumnNames();
  dataMin1=(int)data1.getColumnMin(j);
  dataMax1=(int)data1.getColumnMax(j);
  dataMin2=(int)data2.getColumnMin(j);
  dataMax2=(int)data2.getColumnMax(j);
  dataMin3=(int)data3.getColumnMin(j);
  dataMax3=(int)data3.getColumnMax(j);  
  dataMin4=(int)data4.getColumnMin(j);
  dataMax4=(int)data4.getColumnMax(j);  
}
void draw(){
  background(224);
  fill(255);
  rectMode(CORNER);
  noStroke();
  rect(0,0,1280,720);
  datapoints();
  drawpoints();
  drawline();
  drawnames();
 
}
void datapoints(){
  for(int row1=0;row1<31;row1++){
      strokeWeight(2);
      stroke(0);
      float value1 = data1.getFloat(row1,j);
      linePoint1[row1][j] =value1; 
      float y1 = map(value1, dataMin1, dataMax1,50,250);
      linePoint1[row1][j] =y1;
      float value2 = data2.getFloat(row1,j);
      linePoint2[row1][j] =value2; 
      float y2 = map(value2, dataMin2, dataMax2,50,250);
      linePoint2[row1][j] =y2;  
      float value3 = data3.getFloat(row1,j);
      linePoint3[row1][j] =value3; 
      float y3 = map(value3, dataMin3, dataMax3,50,250);
      linePoint3[row1][j] =y3; 
      float value4 = data4.getFloat(row1,j);
      linePoint4[row1][j] =value4; 
      float y4 = map(value4, dataMin4, dataMax4,50,250);
      linePoint4[row1][j] =y4; 
    }
}
void drawpoints(){
  int x=20;
  for(int i=0;i<31;i++){
    rectMode(CORNER);
    fill(0,255,255);
    rect(x,385,33,linePoint4[i][j]);
    fill(65,188,84);
    rect(x,385-linePoint1[i][j],11,linePoint1[i][j]);
    fill(228,245,10);
    rect(x+10,385-linePoint2[i][j],11,linePoint2[i][j]);
    fill(220,20,20);
    rect(x+20,385-linePoint3[i][j],11,linePoint3[i][j]);
    x=x+40;
    
   }
     
} 

void drawline(){
  stroke(0,0,0);
  strokeWeight(5);
  line(10,385,1270,385);
}
void drawnames(){
  fill(0);
  textSize(40);
  textAlign(CENTER,TOP);
  text(colnames1[j],640,10); 
  int x=20;
  for(int i=0;i<31;i++){
    if(mouseX<x+40*(i+1)&&mouseX>x+40*i&&mouseY<685&&mouseY>80){
      fill(0,0,255);
      textSize(30);
      textAlign(LEFT,BOTTOM);
      text(rownames1[i],mouseX,mouseY);
      }
  }
  strokeWeight(1);
  rectMode(CORNER);
  fill(0,255,255);
  rect(20,20,60,20);
  fill(0);
  textSize(20);
  textAlign(LEFT,CENTER);
  text("deathrate",85,30); 
  
  fill(65,188,84);
  rect(20,50,60,20);
  fill(0);
  textSize(20);
  textAlign(LEFT,CENTER);
  text("air",85,60); 
  
  fill(228,245,10);
  rect(20,80,60,20);
  fill(0);
  textSize(20);
  textAlign(LEFT,CENTER);
  text("greenland",85,90);
  
  fill(220,20,20);
  rect(20,110,60,20);
  fill(0);
  textSize(20);
  textAlign(LEFT,CENTER);
  text("wasted water",85,120); 
  
}
