function out=zigzag(in)
i=1;                                                   
j=1;                                                                                        
f1=0;                                        
f2=0;                                           
m=size(in,1);                                  
for k=1:m*m/2
	out(k)=in(i,j);
	out(m*m+1-k)=in(m+1-i,m+1-j);
	if i==1 
		f2=0;
		if f1==0
			j=j+1;
			f1=1;
		else
			i=i+1;
			j=j-1;
		end
		else
   			if j==1
                f1=0;
            	if f2==0
           			i=i+1;
           			f2=1;
       			else
           			i=i-1;
          			j=j+1;
                end
   			else
       			if f1==1
           			i=i+1;
           			j=j-1;
       			else
           			i=i-1;
           			j=j+1;
       			end
   			end
		end
end
