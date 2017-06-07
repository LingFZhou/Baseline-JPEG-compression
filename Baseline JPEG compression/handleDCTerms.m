%this function is used to code DC terms to bitstreams as 'hsm' format
function [DCHuffmandict,TransDC]=handleDCTerms(DCTerms)
V=DCTerms(:);
%calculate k
V1=floor(log2(abs(V)))+1;%k
maxv=max(V1);
minv=min(V1);
%for simplicity, set 7 categories
prob=zeros(1,7);
for i = 1:6
    prob(i+1)=length(find(V1==i))/10240;%find probabilities
end
prob(1)=length(find(V1==-inf))/10240;%min of k is -inf
k=[-inf,1,2,3,4,5,6];
DCHuffmandict=huffmandict(k,prob);%generate huffman table
DCHuffman=cell(10240,1);
for i = 1:10240
    DCHuffman{i,1}=huffmanenco(V1(i),DCHuffmandict);%generate huffman code
end
H=cell(10240,1);
for i = 1:10240
    H{i}=DCHuffman{i}';
end
DCTermsH=H;%the h term

%calculate m,the (k-1)-bit binary representation of t
V2=abs(V)-power(2,(floor(log2(abs(V)))));%calculate t
V3=cell(10240,1);
for i = 1:10240
    if V1(i)==-inf
        V3{i}=0;
    else
        V3{i}=dec2bin(V2(i),V1(i));%transform to binary format
    end
end
V4=cell(10240,1);
for i = 1:10240
    j=length(V3{i});
    if V3{i}==0
        V4{i}=0;
    else
        for k = 1:j
        V4{i}(k)=str2num(V3{i}(k));%stroe the bits in cells
        end
    end
end
DCTermsM=V4;

%calculate the sign bit s
DCTermsS=cell(10240,1);
for i = 1:10240
    if V(i) > 0
        DCTermsS{i}=1;
    else
        if V(i) < 0
            DCTermsS{i}=0;
        end
    end
end

%combinate h,s,m to the coded stream 'hsm'
TransDC=[DCTermsH DCTermsS DCTermsM];
TransDC=TransDC';
TransDC=TransDC(:);
