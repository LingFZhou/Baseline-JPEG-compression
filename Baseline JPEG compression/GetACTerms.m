%This function is used to get the AC terms from the original picture after
%dct transform and quantization use a constant scalar
function ACTerms = GetACTerms(G,scalar)
G1=G;
GMeanNor = G1-128;
DctG=blkproc(GMeanNor,[8,8],'dct2');
blockDctG=mat2cell(DctG,ones(640/8,1)*8,ones(1024/8,1)*8);
QuanMatrix = [16	11	10	16	24	40	51	61
12	12	14	19	26	58	60	55
14	13	16	24	40	57	69	56
14	17	22	29	51	87	80	62
18	22	37	56	68	109	103	77
24	35	55	64	81	104	113	92
49	64	78	87	103	121	120	101
72	92	95	98	112	100	103	99];
Q = scalar*QuanMatrix;
DG=blockDctG;
for i = 1:80
    for j =1:128
       DG{i,j}=round(blockDctG{i,j}./Q);
    end
end
ACTerms=DG;

