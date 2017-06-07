PImage back;
Table locationTable;
readdata airdata;
readdata greendata;
readdata waterdata;
readdata deathdata;
//varaible used to apply air data
int airrowcount;
int aircolumncount;
float airmax=0;
float airmin=100000;

//varaible used to apply greenland data
int greenrowcount;
int greencolumncount;
float greenmax=0;
float greenmin=40;

//varaible used to wasted water
int waterrowcount;
int watercolumncount;
float watermax=0;
float watermin=100000;
//varaible used to death
int deathrowcount;
int deathcolumncount;
float deathmax=0;
float deathmin=20;
String disrowname;
int rowcount;//used to locate 
//x used to dragged the bar
float barx=21;
float dic=0;
int texts=0;
//to determin which to call decide year
int ycolumn=8;
//to determin which to display
int choose=0;
//to display the selected data
int selected=-1;
float selectedx=0;
float selectedy=0;
//to autorun
int speed=4;
float times=0;
int dragged=0;
//to start play
float play=-1;

//==========================================================below this is variables to graph====================================================
int drawgraph=0;
int drawed=-1;
float plotX1,plotY1;
float plotX2,plotY2;
float disc,disc2;
float dicx,dicy;
float[][] linePoint1 = new float[100][9];
float[][] linePoint2 = new float[100][9];
float[][] linePoint3 = new float[100][9];
float[][] linePoint4 = new float[100][9];
String[] year={"2004","2005","2006","2007","2008","2009","2010","2011","2012"};
float dataMin1,dataMax1;
float dataMin2,dataMax2;
float dataMin3,dataMax3;
float dataMin4,dataMax4;
String[] rownames1,rownames2,rownames3,rownames4;
String[] colnames1=new String[100];
String[] colnames2=new String[100];
String[] colnames3=new String[100];
String[] colnames4=new String[100];
//used to draw in magic
float drawingspeed=1;
//======================================================================below this is to draw year graph==============================================
float yeardataMin1,yeardataMax1;
float yeardataMin2,yeardataMax2;
float yeardataMin3,yeardataMax3;
float yeardataMin4,yeardataMax4;
float[][] yearlinePoint1 = new float[31][100];
float[][] yearlinePoint2 = new float[31][100];
float[][] yearlinePoint3 = new float[31][100];
float[][] yearlinePoint4 = new float[31][100];
float yeargraphx;
float yeargraphy;
float drawyeargraph;
float drawingyearspeed=1;
float dicyearx,dicyeary;
float onthis=0;
//=================================================================================================================================================
void setup(){
back=loadImage("map.png");
size(1366,768);
locationTable=new Table("location.tsv");
rowcount=locationTable.getRowCount();
//apply to air
airdata=new readdata("air.csv");
airrowcount=airdata.getRowCount();
aircolumncount=airdata.getColumnCount();
//apply to greenland
greendata=new readdata("greenland.csv");
greenrowcount=greendata.getRowCount();
greencolumncount=greendata.getColumnCount();
//apply to wasted water
waterdata=new readdata("wasted water.csv");
waterrowcount=waterdata.getRowCount();
watercolumncount=waterdata.getColumnCount();
//apply to deathrate
deathdata=new readdata("deathrate.csv");
deathrowcount=deathdata.getRowCount();
deathcolumncount=deathdata.getColumnCount();
//read their names
  rownames1=airdata.getRowNames();
  colnames1=airdata.getColumnNames();
  rownames2=greendata.getRowNames();
  colnames2=greendata.getColumnNames();
  rownames3=waterdata.getRowNames();
  colnames3=waterdata.getColumnNames();
  rownames4=deathdata.getRowNames();
  colnames4=deathdata.getColumnNames();
  plotX1 = 30;
  plotX2 = plotX1+790;
  plotY1 = 50;
  plotY2 = plotY1+610;
  disc=850;
  disc2=630;
  yeargraphx=60;
  yeargraphy=80;
  //
for(int j=0;j<aircolumncount;j++)//find the min and max to map
{
  //apply to air
  float max1=airdata.getColumnMax(j);
  float min1=airdata.getColumnMin(j);
  if(max1>airmax) airmax=max1;
  if(min1<airmin) airmin=min1;
  //apply to green land
  float max2=greendata.getColumnMax(j);
  float min2=greendata.getColumnMin(j);
  if(max2>greenmax)greenmax=max2;
  if(min2<greenmin)greenmin=min2;
  //apply to wasted water
  float max3=waterdata.getColumnMax(j);
  float min3=waterdata.getColumnMin(j);
  if(max3>watermax)watermax=max3;
  if(min3<watermin)watermin=min3;
  //apply to death
  float max4=deathdata.getColumnMax(j);
  float min4=deathdata.getColumnMin(j);
  if(max4>deathmax)deathmax=max4;
  if(min4<deathmin)deathmin=min4;
}
}


void draw(){
background(0,0,0);
image(back,0,0);
smooth();
noStroke();
textAlign(LEFT);
fill(0,0,0);
//note the meaning of them
textSize(10);
text("Air Pollute",890,665);
text("WasteWater",890,680);
text("GreenLand",890,695);
text("DeathRate",890,710);
text("Please choose which to display",21,520);
text("All",40,540);
text("Air Pollute",40,560);
text("WasteWater",40,580);
text("GreenLand",40,600);
text("DeathRate",40,620);
text("Show whole data each year",430,715);
//the result display word
textSize(15);
text("Area:",1020,560);
text("Year:",1020,590);
text("Air Pollute:",1020,620);
text("WasteWater:",1020,650);
text("GreenLand:",1020,680);
text("DeathRate:",1020,710);
//the control
text("Play:",20,670);
text("Pause:",120,670);
text("Stop:",220,670);
fill(247,68,97);
ellipse(880,662,10,10);
fill(253,218,4);
ellipse(880,677,10,10);
//fill(107,194,53);
fill(26,111,35);
ellipse(880,692,10,10);
fill(0,0,0);
ellipse(880,707,10,10);
//draw the ball

fill(87,96,105);
rect(20,680,361,30,7);
//draw the control
//play
triangle(60,655,60,675,80,665);
//pause
ellipse(180,665,20,20);
//stop
rect(270,655,20,20);
//play year data
triangle(460,675,460,705,490,690);/////////////////////////////////////////////////////////////////
//draw the choice
rect(21,530,10,10);
rect(21,550,10,10);
rect(21,570,10,10);
rect(21,590,10,10);
rect(21,610,10,10);
//draw the choice

fill(247,68,97);
if(choose==0)
{
rect(21,530,10,10);
}
if(choose==1)
{
rect(21,550,10,10);
}
if(choose==2)
{
rect(21,570,10,10);
}
if(choose==3)
{
rect(21,590,10,10);
}
if(choose==4)
{
rect(21,610,10,10);
}
if(play==0)
{
rect(270,655,20,20);
}
if(play==1)
{
triangle(60,655,60,675,80,665);
}
if(play==2)
{
ellipse(180,665,20,20);
}
if(drawyeargraph==1)
{
triangle(460,675,460,705,490,690);
}

//draw the little bar

fill(185,227,217);
rect(barx,681,40,28,7);

if(dragged==0&&play==1)
{
times++;
barx=barx+(times/1600.0)*speed;
if(barx>341)
{
times=0;
barx=341;
}
}
if(dragged==0&&play==0)
{
times=0;
barx=21;
}
if(barx>=21&&barx<61)
{
ycolumn=8;
texts=2004;
}
if(barx>=61&&barx<101)
{
texts=2005;
ycolumn=7;
}
if(barx>=101&&barx<141)
{
texts=2006;
ycolumn=6;
}
if(barx>=141&&barx<181)
{
texts=2007;
ycolumn=5;
}
if(barx>=181&&barx<221)
{
texts=2008;
ycolumn=4;
}
if(barx>=221&&barx<261)
{
texts=2009;
ycolumn=3;
}
if(barx>=261&&barx<301)
{
texts=2010;
ycolumn=2;
}
if(barx>=301&&barx<341)
{
texts=2011;
ycolumn=1;
}
if(barx>=341&&barx<381)
{
texts=2012;
ycolumn=0;
}

fill(0);
textSize(15);
text(texts,385,700);
noStroke();
if(mouseX>barx&&mouseX<(barx+45)&&mouseY>681&&mouseY<709&&mousePressed==true)
{
dic=mouseX-barx;
}
if(mouseX>=plotX1&&mouseX<=(plotX1+disc)&&mouseY>=plotY1&&mouseY<=(plotY1+630)&&mousePressed==true&&drawgraph==1)
{
dicx=mouseX-plotX1;
dicy=mouseY-plotY1;
}
if(mouseY>=yeargraphy&&mouseY<=yeargraphy+360&&mouseX>=yeargraphx&&mouseX<=yeargraphx+640&&mousePressed==true&&drawyeargraph==1)
{
dicyearx=mouseX-yeargraphx;
dicyeary=mouseY-yeargraphy;
}
for(int row=0;row<rowcount;row++)
{
  //location
float x=locationTable.getFloat(row,1);
float y=locationTable.getFloat(row,2);
if(mouseX>x-20&&mouseX<x+20&&mouseY>y-20&&mouseY<y+20)
{
selected=row;
selectedx=x;
selectedy=y;
disrowname=airdata.getRowName(row);
}
//map to air
if(choose==0||choose==4)
{
float data4=deathdata.data[row][ycolumn];
float mapped4=5;
if(choose==0)
{
mapped4=map(data4,deathmin,deathmax,5,40);
}
if(choose==4)
{
mapped4=map(data4,deathmin,deathmax,5,70);
}
fill(0,0,0,200);
ellipse(x+5,y+15,mapped4,mapped4);
if(selected!=-1)
{
float displaydata=deathdata.data[selected][ycolumn];
textSize(10);
text(displaydata,selectedx-10,selectedy-55);
fill(0);
text(displaydata,1120,710);
}
}
if(selected!=-1)
{

fill(0);
textSize(10);
text(disrowname,1120,560);

}
if(choose==0||choose==1)
{
float data1=airdata.data[row][ycolumn];
float mapped1=5;
if(choose==0)
{
 mapped1=map(data1,airmin,airmax,5,60);
}
if(choose==1)
{
 mapped1=map(data1,airmin,airmax,5,100);
}
//mapped1=255-mapped1;

fill(247,68,97,200);
ellipse(x,y,mapped1,mapped1);
if(selected!=-1)
{
float displaydata=airdata.data[selected][ycolumn];
textSize(10);
text(displaydata,selectedx-10,selectedy-40);
fill(0);
text(displaydata,1120,620);
}
}

//map to greenland
if(choose==0||choose==3)
{
float data2=greendata.data[row][ycolumn];
float mapped2=5;
if(choose==0)
{
mapped2=map(data2,greenmin,greenmax,5,70);
}
if(choose==3)
{
mapped2=map(data2,greenmin,greenmax,5,100);
}
//mapped2=255-mapped2;

fill(26,111,35,190);
ellipse(x+15,y+15,mapped2,mapped2);
if(selected!=-1)
{
float displaydata=greendata.data[selected][ycolumn];
textSize(10);
text(displaydata,selectedx-10,selectedy-10);
fill(0);
text(displaydata,1120,680);
}

}
if(selected!=-1)
{
text(texts,1120,590);
}
//map to wasted water
if(choose==0||choose==2)
{
float data3=waterdata.data[row][ycolumn];
float mapped3=5;
if(choose==0)
{
mapped3=map(data3,watermin,watermax,5,60);
}
if(choose==2)
{
mapped3=map(data3,watermin,watermax,5,100);
}
//mapped3=255-mapped3;

fill(253,218,4,180);
ellipse(x-15,y+15,mapped3,mapped3);
if(selected!=-1)
{
float displaydata=waterdata.data[selected][ycolumn];
textSize(10);
text(displaydata,selectedx-10,selectedy-25);
fill(0);
text(displaydata,1120,650);
}

}

selected=-1;

//==================================below is to draw graph=========================================================
}
if(drawgraph==1&&drawed!=-1)
{
  dataMin1=airdata.getRowMin(drawed);
  dataMax1=airdata.getRowMax(drawed);
  dataMin2=greendata.getRowMin(drawed);
  dataMax2=greendata.getRowMax(drawed);
  dataMin3=waterdata.getRowMin(drawed);
  dataMax3=waterdata.getRowMax(drawed);
  dataMin4=deathdata.getRowMin(drawed);
  dataMax4=deathdata.getRowMax(drawed);
  fill(131,175,155,210);
  noStroke();
  drawingspeed++;
  float drawto=drawingspeed*0.05;
  if(drawto<1)
  {
  rect(plotX1,plotY1,850*drawto,630*drawto);
  }
  if(drawto>=1)
  {
  rect(plotX1,plotY1,850,630);
  fill(255,0,0,150);
  rect(disc+plotX1-40,plotY1,40,25);
  strokeWeight(2);
  stroke(255);
  line(disc+plotX1-30,plotY1+5,disc+plotX1-10,plotY1+20);
  line(disc+plotX1-30,plotY1+20,disc+plotX1-10,plotY1+5);
if(mouseX>(disc+plotX1-40)&&mouseX<(disc+plotX1)&&mouseY>plotY1&&mouseY<(plotY1+25)&&drawgraph==1&&mousePressed==true){
noStroke();
fill(106,28,28);
rect(disc+plotX1-40,plotY1,40,25);
strokeWeight(2);
stroke(255);
line(disc+plotX1-30,plotY1+5,disc+plotX1-10,plotY1+20);
line(disc+plotX1-30,plotY1+20,disc+plotX1-10,plotY1+5);
}
  datapoints(drawed);
  drawpoints(drawed);
  drawaxis();
  drawnames(drawed);
}
}
//=============================================================================below this is to draw year graph===============================================
if(drawyeargraph==1)
{
  yeardataMin1=airdata.getColumnMin(ycolumn);
  yeardataMax1=airdata.getColumnMax(ycolumn);
  yeardataMin2=greendata.getColumnMin(ycolumn);
  yeardataMax2=greendata.getColumnMax(ycolumn);
  yeardataMin3=waterdata.getColumnMin(ycolumn);
  yeardataMax3=waterdata.getColumnMax(ycolumn);  
  yeardataMin4=deathdata.getColumnMin(ycolumn);
  yeardataMax4=deathdata.getColumnMax(ycolumn);
  fill(131,175,155,210);
  rectMode(CORNER);
  noStroke();
  drawingyearspeed++;
  float drawyearto=drawingyearspeed*0.05;
  if(drawyearto<1)
  {
  rect(yeargraphx,yeargraphy,640*drawyearto,360*drawyearto);
  }
  if(drawyearto>=1)
  {
  rect(yeargraphx,yeargraphy,640,360);
  fill(255,0,0,150);
  rect(yeargraphx+640-40,yeargraphy,40,25);
  strokeWeight(2);
  stroke(255);
  line(yeargraphx+640-30,yeargraphy+5,yeargraphx+640-10,yeargraphy+20);
  line(yeargraphx+640-30,yeargraphy+20,yeargraphx+640-10,yeargraphy+5);
  if(mouseX>(yeargraphx+640-40)&&mouseX<(yeargraphx+640)&&mouseY>yeargraphy&&mouseY<(yeargraphy+25)&&drawyeargraph==1&&mousePressed==true){
   noStroke();
  fill(106,28,28);
  rect(yeargraphx+640-40,yeargraphy,40,25);
  strokeWeight(2);
  stroke(255);
  line(yeargraphx+640-30,yeargraphy+5,yeargraphx+640-10,yeargraphy+20);
  line(yeargraphx+640-30,yeargraphy+20,yeargraphx+640-10,yeargraphy+5);
}
  datayearpoints(ycolumn);
  drawyearpoints(ycolumn);
  drawyearline();
  drawyearnames(ycolumn);
  }


}
}

void mouseDragged()
{
if(mouseX>barx&&mouseX<(barx+40)&&mouseY>681&&mouseY<709)
{
barx=mouseX-dic;
dragged=1;
if(barx<21)
barx=21;
if(barx>341)
barx=341;
}
if(mouseX>=plotX1&&mouseX<=(plotX1+disc)&&mouseY>=plotY1&&mouseY<=(plotY1+630)&&mousePressed==true&&drawgraph==1)
{
plotX1=mouseX-dicx;
plotY1=mouseY-dicy;
if(plotX1>=516)
plotX1=516;
if(plotX1<=0)
plotX1=0;
if(plotY1>=138)
plotY1=138;
if(plotY1<=0)
plotY1=0;
}
if(mouseY>=yeargraphy&&mouseY<=yeargraphy+360&&mouseX>=yeargraphx&&mouseX<=yeargraphx+640&&mousePressed==true&&drawyeargraph==1)
{
yeargraphx=mouseX-dicyearx;
yeargraphy=mouseY-dicyeary;
if(yeargraphx>=726)
yeargraphx=726;
if(yeargraphx<=0)
yeargraphx=0;
if(yeargraphy>=408)
yeargraphy=408;
if(yeargraphy<=0)
yeargraphy=0;
}

}
void mousePressed()
{

}

void mouseClicked()
{
if(mouseX>=20&&mouseX<=90&&mouseY>=526&&mouseY<=545)
choose=0;
if(mouseX>=20&&mouseX<=90&&mouseY>=546&&mouseY<=565)
choose=1;
if(mouseX>=20&&mouseX<=90&&mouseY>=566&&mouseY<=585)
choose=2;
if(mouseX>=20&&mouseX<=90&&mouseY>=586&&mouseY<=605)
choose=3;
if(mouseX>=20&&mouseX<=90&&mouseY>=606&&mouseY<=625)
choose=4;
if(mouseX>=60&&mouseX<=80&&mouseY>=655&&mouseY<=675)
play=1;
if(mouseX>=170&&mouseX<=190&&mouseY>=645&&mouseY<=665)
{
play=2;
times=0;
}
if(mouseX>=270&&mouseX<=290&&mouseY>=655&&mouseY<=675)
play=0;
if(mouseX>=450&&mouseX<=500&&mouseY>=660&&mouseY<=700) //460,675,460,705,490,690
{
drawyeargraph=1;
}
for(int row=0;row<rowcount;row++)
{
  //location
float x=locationTable.getFloat(row,1);
float y=locationTable.getFloat(row,2);
if(mouseX>x-20&&mouseX<x+20&&mouseY>y-20&&mouseY<y+20)
{
drawgraph=1;
drawed=row;
}
}
if(mouseX>(disc+plotX1-40)&&mouseX<(disc+plotX1)&&mouseY>plotY1&&mouseY<(plotY1+25)&&drawgraph==1)
{
drawgraph=0;
drawed=-1;
drawingspeed=0;
}
if(mouseX>(yeargraphx+640-40)&&mouseX<(yeargraphx+640)&&mouseY>yeargraphy&&mouseY<(yeargraphy+25)&&drawyeargraph==1)
{
  drawyeargraph=0;
  drawingyearspeed=0;
}
}

void mouseReleased()
{
if(dragged==1)
{
dragged=0;
times=0;
onthis=0;
if(play==0)
play=-1;
}
}
//====================================================================================below this is used to draw graphs==================================================
void datapoints(int k){
  for(int col=8;col>=0;col--){
      strokeWeight(2);
      stroke(0);
      float value1 = airdata.getFloat(k,col);
      float y1 = map(value1, dataMin1, dataMax1, 0,disc2-320);
      linePoint1[k][col] =plotY1+disc2-150-y1; 
    }
  for(int col=8;col>=0;col--){
      strokeWeight(2);
      stroke(0);
      float value2 = greendata.getFloat(k,col);
      float y2 = map(value2, dataMin2, dataMax2, 0,disc2-520);
      linePoint2[k][col] =plotY1+disc2-150-y2; 
    }
  for(int col=8;col>=0;col--){
      strokeWeight(2);
      stroke(0);
      float value3 = waterdata.getFloat(k,col);
      float y3 = map(value3, dataMin3, dataMax3, 0,disc2-320);
      linePoint3[k][col] =plotY1+disc2-150-y3; 
    }
  for(int col=8;col>=0;col--){
     strokeWeight(2);        
     stroke(0);
     float value4=deathdata.getFloat(k,col);
     float y4=map(value4,dataMin4,dataMax4,50,disc2-400);
     linePoint4[k][col]=plotY1+disc2-100-y4;
  }
}
void drawpoints(int k){
  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;
  float x4;
  float y4;
  float j=plotX1+40;
  for(int i=7;i>=0;i--){
    x1=linePoint1[k][i];
    y1=linePoint1[k][i+1];
    x2=linePoint2[k][i];
    y2=linePoint2[k][i+1];
    x3=linePoint3[k][i];
    y3=linePoint3[k][i+1];
    x4=linePoint4[k][i];
    y4=linePoint4[k][i+1];
    stroke(247,68,97);
    strokeWeight(5);
    line(j,y1,j+80,x1);
    
    stroke(26,111,35);
    strokeWeight(5);
    line(j,y2,j+80,x2);
    
    stroke(253,218,4);
    strokeWeight(5);
    line(j,y3,j+80,x3);
    
    strokeWeight(5);
    stroke(0,0,0);
    line(j,y4,j+80,x4);
    j=j+80;
   }
     
}
void drawaxis(){
   String time = new String();
   float j=plotX1+40;
   for(int i=0;i<9;i++){
      time=year[i];
      fill(0);
      textSize(20);
     textAlign(CENTER,BOTTOM);
      text(time,j,plotY1+disc2-80);
      stroke(0);
      strokeWeight(2);
      line(j,plotY1+100,j,plotY1+disc2-120);
      j=j+80;
  }
  stroke(0);
  strokeWeight(2);
  line(plotX1+30,plotY1+disc2-120,plotX1+disc-140,plotY1+disc2-120);
}
void drawnames(int k){
    fill(0);
    textSize(30);
    textAlign(CENTER,TOP);
    text(rownames1[k],plotX1+400,plotY1+10); 
    
    stroke(247,68,97);
    strokeWeight(5);
    line(plotX1+disc-135,plotY1+disc2-100,plotX1+disc-90,plotY1+disc2-100);
    textSize(15);
    textAlign(LEFT,CENTER);
    text("Air pollute",plotX1+disc-85,plotY1+disc2-105); 
    
    stroke(26,111,35);
    strokeWeight(5);
    line(plotX1+disc-135,plotY1+disc2-40,plotX1+disc-90,plotY1+disc2-40);
    textAlign(LEFT,CENTER);
    text("GreenLand",plotX1+disc-85,plotY1+disc2-45); 
    
    stroke(253,218,4);
    strokeWeight(5);
    line(plotX1+disc-135,plotY1+disc2-70,plotX1+disc-90,plotY1+disc2-70);
    textAlign(LEFT,CENTER);
    text("WasteWater",plotX1+disc-85,plotY1+disc2-75); 
    
    stroke(0,0,0);
    strokeWeight(5);
    line(plotX1+disc-135,plotY1+disc2-10,plotX1+disc-90,plotY1+disc2-10);
    textAlign(LEFT,CENTER);
    text("DeathRate",plotX1+disc-85,plotY1+disc2-15);
}

//=============================================================================================below this is to draw year graphs=========================================================
void datayearpoints(int j){
  for(int row1=0;row1<31;row1++){
      float value1 = airdata.getFloat(row1,j);
      float y1 = map(value1, yeardataMin1, yeardataMax1,25,125);
      yearlinePoint1[row1][j] =y1;
      float value2 = greendata.getFloat(row1,j);
      float y2 = map(value2, yeardataMin2, yeardataMax2,25,125);
      yearlinePoint2[row1][j] =y2;  
      float value3 = waterdata.getFloat(row1,j);
      float y3 = map(value3, yeardataMin3, yeardataMax3,25,125);
      yearlinePoint3[row1][j] =y3; 
      float value4 = deathdata.getFloat(row1,j);
      float y4 = map(value4, yeardataMin4, yeardataMax4,25,125);
      yearlinePoint4[row1][j] =y4; 
    }
}
void drawyearpoints(int j){
  int x=10;
  for(int i=0;i<31;i++){
    noStroke();
    rectMode(CORNER);
    fill(0,0,0,150);
    rect(yeargraphx+x,yeargraphy+192.5,16.5,yearlinePoint4[i][j]);
    
    fill(247,68,97);
    rect(yeargraphx+x,yeargraphy+192.5-yearlinePoint1[i][j],5.5,yearlinePoint1[i][j]);
    
    fill(26,111,35);
    rect(yeargraphx+x+5.5,yeargraphy+192.5-yearlinePoint2[i][j],5.5,yearlinePoint2[i][j]);
    
    fill(253,218,4);
    rect(yeargraphx+x+11,yeargraphy+192.5-yearlinePoint3[i][j],5.5,yearlinePoint3[i][j]);
    
    x=x+20;
    
   }
     
} 

void drawyearline(){
  stroke(0,0,0);
  strokeWeight(5);
  line(yeargraphx+5,yeargraphy+192.5,yeargraphx+635,yeargraphy+192.5);
}
void drawyearnames(int j){
  fill(0);
  textSize(20);
  textAlign(CENTER,TOP);
  text(colnames1[j],320+yeargraphx,yeargraphy+5); 
  int x=10;
  for(int i=0;i<31;i++){
    if(mouseX<yeargraphx+x+20*(i+1)&&mouseX>yeargraphx+x+20*i&&mouseY<342.5+yeargraphy&&mouseY>40+yeargraphy){
      fill(23,80,100);
      textSize(30);
      textAlign(LEFT,BOTTOM);
      text(rownames1[i],mouseX,mouseY);
      }
  }
  noStroke();
  strokeWeight(1);
  rectMode(CORNER);
  fill(0,0,0,150);
  rect(10+yeargraphx,10+yeargraphy,30,10);
  fill(0);
  textSize(10);
  textAlign(LEFT,CENTER);
  text("deathrate",42.5+yeargraphx,15+yeargraphy); 
  
  fill(247,68,97);
  rect(10+yeargraphx,25+yeargraphy,30,10);
  fill(0);
  textSize(10);
  textAlign(LEFT,CENTER);
  text("air",42.5+yeargraphx,30+yeargraphy); 
  
  fill(26,111,35);
  rect(10+yeargraphx,40+yeargraphy,30,10);
  fill(0);
  textSize(10);
  textAlign(LEFT,CENTER);
  text("greenland",42.5+yeargraphx,45+yeargraphy);
  
  fill(253,218,4);
  rect(10+yeargraphx,55+yeargraphy,30,10);
  fill(0);
  textSize(10);
  textAlign(LEFT,CENTER);
  text("wasted water",42.5+yeargraphx,60+yeargraphy); 
  
}






