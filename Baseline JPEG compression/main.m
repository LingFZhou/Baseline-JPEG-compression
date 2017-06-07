%the main function, get two huffman table for DC and AC terms, get coded
%output bitstreams of DC and AC terms, compute the compression ratio for a
%constant scalar
function comratio=main(G,scalar)
%for DC terms
D=GetDCTerms(G,scalar);
[DCHuffmandict,TransDC]=handleDCTerms(D);
%for AC terms
A=GetACTerms(G,scalar);
ACHuffmandict=cell(80,128);
TransAC=cell(80,128);
for i = 1:80
    for j = 1:128
        [ACHuffmandict{i,j},TransAC{i,j}]=handleACTerms(A{i,j});
    end
end
%calculate the comprssion ratio
count = 0;
%size of codec DC terms bitstream
for i = 1:length(TransDC)
    count = count + length(TransDC{i});
end
%size of codec DC terms bitstream
for i = 1:80
    for j = 1:128
        for k = 1:length(TransAC{i,j})
            count = count + length(TransAC{i,j}(k));
        end
    end
end
%compression ratio
comratio=8*640*1024/count;