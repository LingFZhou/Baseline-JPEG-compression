install.packages("tm")
library(tm)
install.packages("textreuse")
library(textreuse)
install.packages("wordcloud")
library(wordcloud)
install.packages("ggplot2")
library("ggplot2");
install.packages("wordnet")
library("wordnet")
install.packages("zipfR")
library(zipfR)
data("acq")


#try the functions in lecture 7,display the dendrogram and the WordCloud
SATlow <- tm_map(acq[1], content_transformer(tolower));
removeNumPunct <- function(x) gsub("[^[:alpha:][:space:]]*", "", x);
SATcl <- tm_map(SATlow, content_transformer(removeNumPunct))
myStopwords <- c(stopwords('english'));
SATstop <- tm_map(SATcl, removeWords, myStopwords);
SATtdm2 <-TermDocumentMatrix(SATstop,control=list(wordLengths=c(1,Inf)));
freq.terms <- findFreqTerms(SATtdm2,lowfreq = 5);
findAssocs(SATtdm2,"states",0.25);
term.freq<-rowSums(as.matrix(SATtdm2));
term.freq<-subset(term.freq,term.freq>=2);
df<-data.frame(term=names(term.freq),freq=term.freq);
ggplot(df,aes(x=term,y=freq))+geom_bar(stat="identity")+xlab("Terms")+ylab("count")+coord_flip();
tdm2<-removeSparseTerms(SATtdm2,sparse=0.50);
distMatrix<-dist(scale(tdm2));
fit<-hclust(distMatrix,method="ward.D2");
plot(fit)
rh<-rect.hclust(fit,k=10);
tm<-t(distMatrix);
k<-6;
kr<-kmeans(tm,k);
round(kr$centers,digits=3);
m1<-as.matrix(tdm2);
word.freq<-sort(rowSums(m1),decreasing=T);
pal<-brewer.pal(9,"BuGn");
pal<-pal[-(1:4)];
wordcloud(words=names(word.freq),freq=word.freq,min.freq=2,random.order=F,colors=pal);

#Find the 10 longest documents (in number of words)
count=array(dim = 50)
for(i in 1:50){
    count[i]=length(tokenize_words(acq[[i]]$content));
}
countindex=array(dim = 10)
for(i in 1:10){
    countindex[i]=which(count==sort(count)[length(count)-i+1]);
 }
countindex;


#find longest words
#store as words
acq1word=tokenize_words(acq[[1]]$content);
#compute length of each words
acq1wordlen=array(dim = length(acq1word));
for(i in 1:length(acq1wordlen)){
  acq1wordlen[i]=nchar(acq1word[i]);
}
#find the index of longest words
acq1wordindex=which(acq1wordlen==sort(acq1wordlen)[length(acq1wordlen)]);
#find the longest words
acq1Longestword=array(dim=length(acq1wordindex));
for(i in 1:length(acq1wordindex)){
  acq1Longestword[i]=acq1word[acq1wordindex[i]];
}


#find longest sentence
#remove "\n" 
removen <-function(x) gsub("\n", " ", x);
acq1sentence <- tm_map(acq[1], content_transformer(removen));
#store as sentences
acq1sen=tokenize_sentences(acq1sentence[[1]]$content);
#compute length of each sentence
acq1senlen=array(dim = length(acq1sen))
for(i in 1:length(acq1senlen)){
  acq1senlen[i]=length(unlist(strsplit(acq1sen[i]," ")));
}
#find the index of longest sentences
acq1senindex=which(acq1senlen==sort(acq1senlen)[length(acq1senlen)]);
#find the longest sentences
acq1Longestsen=array(dim = length(acq1senindex));
for(i in 1:length(acq1senindex)){
  acq1Longestsen[i]=acq1sen[acq1senindex[i]];
}


#Print a table of the length of each sentence in each of the 10 documents
#index of 10 longest docs
countindex
#compute number of words of each sentence
#the number of sentences in these 10 docs is at most 31 
NumOfWords<-matrix(nrow=10,ncol=31);
for(i in 1:10){
  #remove "\n"
  removen <-function(x) gsub("\n", " ", x);
  sentence <- tm_map(acq[countindex[i]], content_transformer(removen));
  #store as sentences
  sen=tokenize_sentences(sentence[[1]]$content);
  #compute number of words for sentence j
  for(j in 1:length(sen)){
    NumOfWords[i,j]=length(unlist(strsplit(sen[j]," ")));
  }
}


#For each sentence of each document, remove the punctuation. Display the sentences
#remove punctuation
removeNumPunct <- function(x) gsub("[^[:alpha:][:space:]]*", "", x)
acq.rem <- tm_map(acq[1], content_transformer(removeNumPunct))
#remove "\n"
removen <-function(x) gsub("\n", " ", x);
acq.rem2 <- tm_map(acq.rem, content_transformer(removen));
acq.rem2=tokenize_sentences(acq.rem2[[1]]$content);


#For each word print its part of speech using the Wordnet package.
#init the dict, set the path
initDict("D:/R/R-3.3.1/R-3.3.1/library/wn3.1.dict/dict")
setDict("D:/R/R-3.3.1/R-3.3.1/library/wn3.1.dict/dict")
#store as words
acq.word=tokenize_words(acq[[1]]$content);
#set the filter and get the result
filter <- getTermFilter("StartsWithFilter",acq.word[1], TRUE);
getIndexTerms("ADJECTIVE", 1, filter)


#Analyze word frequency using functions from package zipfR.
SATlow <- tm_map(acq[1], content_transformer(tolower))
removeNumPunct <- function(x) gsub("[^[:alpha:][:space:]]*", "", x)
SATcl <- tm_map(SATlow, content_transformer(removeNumPunct))
myStopwords <- c(stopwords('english'))
SATstop <- tm_map(SATcl, removeWords, myStopwords)
SATtdm2 <-TermDocumentMatrix(SATstop,control=list(wordLengths=c(1,Inf)));
term.freq<-rowSums(as.matrix(SATtdm2));
term.freq<-subset(term.freq,term.freq>=2);
term.freq.df=as.data.frame(term.freq)
term.freq.dfrn=row.names(term.freq.df)
term.freq.wordno=1:length(term.freq.dfrn)
term.freq.spc=spc(term.freq,term.freq.wordno)
plot(term.freq.spc)

#search a word, return # of document, # of sentence, index of word
#remove "\n"
removen <-function(x) gsub("\n", " ", x);
acqr <- tm_map(acq, content_transformer(removen));
#create a 100*3 array to store the result of # of document, # of sentence, index of word
e=array(dim = c(100,3));
count=1;
for (i in 1:50){
  #store as sentences
  a=acqr[i]
  b=tokenize_sentences(a[[1]]$content);
  for(j in 1:length(b)){
    c=b[j];
    if(c!=""){
      #split to get words 
      d=unlist(strsplit(c," "));
      for(k in 1:length(d)){
        #find the target words
        if(d[k]=="warrants"){
          e[count,1]=i;
          e[count,2]=j;
          e[count,3]=k;
          count=count+1;
        }
        else{count=count}
      }
    }
  }
}
