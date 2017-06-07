%This function is used to compute SNR for different scalar quantization
%between the original picture and reconstructed picture
function GSNR = CalSNR(G,scalar)
%get reconstructed image
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
for i = 1:80
    for j =1:128
        blockDctG{i,j}=round(blockDctG{i,j}./Q);
    end
end
RblockDctG=cell(80,128);
for i = 1:80
    for j =1:128
        RblockDctG{i,j}=round(blockDctG{i,j}.*Q);
    end
end
RG=cell2mat(RblockDctG);
RG=blkproc(RG,[8,8],'idct2')+128;

%compute snr
Diff=G-RG;
EG=0;%to compute ||G||
ED=0;%to compute||G-RG||
for i = 1:640
    for j = 1:1024
        EG=EG+G(i,j)*G(i,j);
        ED=ED+Diff(i,j)*Diff(i,j);
    end
end
EG=sqrt(EG);
ED=sqrt(ED);
GSNR=20*log10(EG/ED);
        
