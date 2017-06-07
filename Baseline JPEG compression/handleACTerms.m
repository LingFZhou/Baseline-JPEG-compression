%this function is used to code AC terms to bitstreams as 'hsm' format
%input AC is a 8*8 block
function [ACHuffmandict,TransAC]=handleACTerms(AC)
ZZACBlock=zigzag(AC);%apply zigzag scan to the block
ZZACBlock=ZZACBlock(2:64);%exclude DC term
Z=ZZACBlock;
if isempty(find(Z(2:end)))%if all AC terms are zero, set huffman table as null, output EOB(1010)
    ACHuffmandict=[];
    TransAC=[1;0;1;0];
else
    %calculate the length d of the zero run between nonzero AC terms
    IndexZ=cell(1,1);
    IndexZ{1}=find(Z);%find the indexes of non-zero terms
    Dis=cell(1,1);
    Dis{1}(1)=0;%the length of the first term is 0
    for i = 2:length(IndexZ{1})
        Dis{1}(i)=IndexZ{1}(i)-IndexZ{1}(i-1)-1;%calculate d
    end
    ACDis=Dis{1};
    ACIndex=IndexZ{1};
    ACTerms=ZZACBlock;
    %calculate k
    V=zeros(length(ACIndex),1);
    for i = 1:length(ACIndex)
        V(i)=ACTerms(ACIndex(i));
    end
    V1=floor(log2(abs(V)))+1;%k
    %calculate (d,k) pairs
    V2=ACDis';%d
    V3=cell(length(V1),1);
    for i = 1:length(V1)
        V3{i}(1)=V2(i);
        V3{i}(2)=V1(i);
    end
    %use pair (d,k) to generate huffman table
    V4=V3;%V4 is the signals to be coded
    [Sym,prob]=calprob(V4);%Sym is the symbols, prob is the probabilities
    if length(Sym)==1 %if only one (d,k) pair
        ACHuffmandict=[Sym prob];
        ACHuffman=cell(length(V4),1);
        for i = 1:length(ACHuffman)
            ACHuffman{i}=1;
        end
        ACTermsH=ACHuffman;
    else
        ACHuffmandict=huffmandict(Sym,prob);%generate huffman table
        %generate huffman code
        ACHuffman=cell(length(V4),1);
        for i = 1:length(ACHuffman)
            ACHuffman{i}=huffmanenco(V4(i),ACHuffmandict);
        end
        ACTermsH=ACHuffman;
    end
    
    %calculate the sign bit s
    ACTermsS=cell(length(V),1);
    for i = 1:length(V);
        if V(i)>0
            ACTermsS{i}=1;
        else
            if V(i)<0
                ACTermsS{i}=0;
            end
        end
    end
    
    %calculate m,the (k-1)-bit binary representation of t
    T2=abs(V)-power(2,(floor(log2(abs(V))))); %calculate t
    T3=cell(length(T2),1);
    for i = 1:length(T3)
        T3{i}=dec2bin(T2(i),V1(i));%transform to binary format
    end
    T4=cell(length(T2),1);
    for i = 1:length(T2)
        j=length(T3{i});
        for k = 1:j
            T4{i}(k)=str2num(T3{i}(k));%stroe the bits in cells
        end
    end
    ACTermsM=T4;
    
    %combinate h,s,m to the coded stream 'hsm'
    TransAC=[ACTermsH ACTermsS ACTermsM];
    TransAC=TransAC';
    TransAC=TransAC(:);
    TransAC{length(TransAC)+1}=[1;0;1;0];%add EOB bits
end
