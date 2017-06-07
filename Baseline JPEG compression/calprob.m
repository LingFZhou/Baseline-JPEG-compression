%this function is used to calculate the probabilities distribution of input signals
function [sym,prob]=calprob(cell)
p=zeros(length(cell),1);
tempsym=cell;
%calculate the occurance of each term
for i = 1:length(cell)
    for j = 1:length(cell) 
        if isequal(cell{i},cell{j})
            p(i)=p(i)+1;
        end
    end
end
%exclude the repeat of same terms
for i = 1:length(cell)
    for j = i:length(cell) 
        if isequal(cell{i},cell{j})
            if i~=j
                tempsym{j}=[];
            end
        end
    end
end
%calculate the probabilities of each term
tempprob=zeros(length(cell),1);
for i = 1:length(tempprob)
    tempprob(i)=p(i)/length(p);
end
%find the indexes of the non-repetitive terms
index=zeros(length(tempsym),1);
for i = 1:length(tempsym)
    if ~isempty(tempsym{i})
        index(i)=i;
    end
end
index=find(index);
%find the probabilites of these non-repetitive terms
prob=zeros(length(index),1);
sym=cell(length(index),1);
for i = 1:length(prob)
    prob(i)=tempprob(index(i));
    sym{i}=tempsym{index(i)};
end

sym=sym';

