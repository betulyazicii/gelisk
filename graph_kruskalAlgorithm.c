#include<stdio.h>

#define MAX 900
#define MAXNUMCLUSTER 4 //en fazla kaç kümeye ayrılacagı limiti
#define LINESIZE 30
typedef struct edge //bağlantılı kenarları (u,v)->w u ve v kenar w ağırlık olacak şekilde struct olusturulur.
{
    int u,v,w;
}edge;

typedef struct edgelist   //kenarların bağıntılarını tutan liste
{
    edge data[MAX];
    int numberOfLine;
}edgelist;

edgelist elist; //sıralı olarak kenar bağlantılarını tutan liste.

int G[MAX][MAX]; //G matrisi dosyadan okunan bağlantıların matrisidir.
int numberOfLine; // kaç satır okunuyorsa bu bilgidir.Düğüm sayısıdır.
edgelist spanlist; //costu yazdırmak için kullandıgım dizi.
int grupMatris[MAXNUMCLUSTER][LINESIZE]; //bu matrisde hangi grupta hangi elemanların oldugu saklanmıstır.Distance için kullanabilmek için yazılmıstır.
static int getLineNumber() {
    //Bu fonksiyon dosyada kaç satır oldugunu bulur.
    FILE *file = fopen("/Users/betulyazici/Desktop/data3.txt", "r");
    int count=0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // yeni satıra geçtigini anlayınca count artırırız.
            count = count + 1;
    fclose(file);
    
    return count;
    
}

void readFile(int numberOfLine) {
    //dosyadan okuma yapılan metoddur ',' ile ayırır /n olunca yeni bir satıra geçtigini anlarız.
    FILE *file = fopen("/Users/betulyazici/Desktop/data3.txt", "r");
    for(int row = 0; row < numberOfLine; row++)
    {
        for(int column = 0; column < numberOfLine; column++)
        {
            fscanf(file, "%d, \n", &G[row][column]);
        }
    }
    fclose(file);
    
}
int find(int label[],int vertexno)
{ //bu metod girilen düğümü label dizisinde bulur.
    return(label[vertexno]);
}

void unionOfLabeledArray(int label[],int c1,int c2)
{ //bu metod etiket dizisinde farklı etiketli olan düğümleri aynı olacak şekilde değiştirir.
    
    for(int i=0;i<numberOfLine;i++)
        if(label[i]==c2)
            label[i]=c1;
    
}
int findClusterNum(int label[])
{
    //bu metod label dizisinin kaç farklı elemanı oldugunu tutar .O anda kaç alt kümeye ayrılmıs oldugu bilgisini tutuyor.
    int count=0;
    for (int i=0; i<numberOfLine; i++)
    {
        int j=0;
        int done=0;
        while(j<=i && !done){
            if (label[i] == label[j])
                done=1;
            if (j==i)
                count++;
            j++;
        }
        
    }
    return count;
    
    
}


static void initializeGrupMatris() {
    for(int a=0;a<MAXNUMCLUSTER;a++){
        for(int b=0;b<LINESIZE;b++){
            grupMatris[a][b]= 0;
        }
    }
}

static void findDistance() {
    int kume1,kume2;
    printf("\nUzaklıgını bulmak istediginiz 1.küme numarasını giriniz.\n");
    scanf("%d",&kume1);
    printf("Uzaklıgını bulmak istediginiz 1.küme numarasını giriniz.\n");
    scanf("%d",&kume2);
    
    int minDistance=10000; // initialize of minDistance variable
    for(int i=0;i<numberOfLine;i++){
        if(grupMatris[kume1-1][i]!=0){
            for(int j=0;j<numberOfLine;j++){
                if(grupMatris[kume2-1][j]!=0){
                    if(G[i][j] != 0 && G[i][j]<minDistance ){
                        minDistance =G[i][j]; }
                }
            }
        }
        
    }
    printf("Verilen %d. küme ile %d. küme arasındaki en kısa mesafe: %d dir\n",kume1,kume2,minDistance);
}

static void printCluster(int *grup, int k, int *label) {
   
    initializeGrupMatris();
    
    //Her kümedeki  düğümleri yazdıran fonksiyondur.
    for(int i=0;i<k;i++){
        printf("%d.grubun elemanları: ",i+1);
        for(int j=0;j<numberOfLine;j++){
            if(grup[i]==label[j]){
                printf("%d ",j);
                grupMatris[i][j]=1;
            }
        }
        printf("\n");
        
    }
    
  
}

void print(int label[],int k){
    //grup dizisi k adet kümeye ayrılan label dizisinin elemanlarının ne oldugunu tutan dizidir.
    int grup[MAXNUMCLUSTER]={1000,1000,1000,1000}; //initialize of grup array bu kümeye ayrılan elemanların değerlerini tutar.
    int a=1; // grup dizisi için tutulan indis.
    grup[0]=label[0];
    for(int i=1;i<numberOfLine;i++)
    { //i indisi label dizisinde gezinmemizi sağlayan indis.
        int isInclude=0;
        for(int j=0;j<k;j++){
            //j indisi grup dizindeki elemanlara erişmek için kullanılır
            if(grup[j]==label[i]){
                isInclude=1; //isInclude 1 olursa o eleman zaten grupda vardır.
            }
        }
        
        if(isInclude==0){
            grup[a]=label[i];
            a++;
        }
    }
    
    
    printCluster(grup, k, label);//Her kümedeki  düğümleri yazdıran fonksiyondur.
    
    
}

void sort()
{
    //okunan elemanları küçükten büyüğe sıralayan fonksiyondur.
    //Bubble sort algoritması kullanılmıstır.
    int i,j;
    edge temp;
    
    for(i=1;i<elist.numberOfLine;i++)
        for(j=0;j<elist.numberOfLine-1;j++)
            if(elist.data[j].w>elist.data[j+1].w)
            {
                temp=elist.data[j];
                elist.data[j]=elist.data[j+1];
                elist.data[j+1]=temp;
            }
}
void printWithCostInformation(int k)
{
    //cost bilgisini de yazdıran fonksiyon
    
    int cost=0;
    for(int i=0;i<spanlist.numberOfLine;i++)
    {
        printf("\n%d\t%d\t Cost of edge: %d",spanlist.data[i].u,spanlist.data[i].v,spanlist.data[i].w);
        cost=cost+spanlist.data[i].w;
    }
    
    printf("\nTotal Cost of the spanning tree= %d ",cost);
}



void kruskal(int numberOfLine,int k)
{
    int label[MAX],i,j,cno1,cno2; //label etiket bilgisini tutan düğüm sayısında oluştulumuş dizidir.
    elist.numberOfLine=0;
    
    for(i=1;i<numberOfLine;i++)
        for(j=0;j<i;j++)
        {
            if(G[i][j]!=0 && i!=j)
            {
                //txt den okunan G ye yazılan matrisin elist structure'na yazılmasını sağlar.
                elist.data[elist.numberOfLine].u=i;
                elist.data[elist.numberOfLine].v=j;
                elist.data[elist.numberOfLine].w=G[i][j];
                elist.numberOfLine++;
            }
        }
    
    sort(); //okunan elemanları küçükten büyüğe sıralayan fonksiyondur.
    
    for(i=0;i<numberOfLine;i++)
        label[i]=i; //initialize of label array label dizisine ilk eleman olarak indislerini atar.
    spanlist.numberOfLine=0;
    
    i=0;
    int count=0; // label dizisindeki etiket sayısını bulmak için kullanılır.
    int stop=0;  // count sayacı istenen küme sayısına geldigi zaman döngünün durması için tutulmustur.
    
    while (i<elist.numberOfLine && !stop)
    {
        cno1=find(label,elist.data[i].u); //bu metod girilen düğümü label dizisinde bulur.u için.
        cno2=find(label,elist.data[i].v);//bu metod girilen düğümü label dizisinde bulur.v için.
        
        if(cno1!=cno2)
        {
            spanlist.data[spanlist.numberOfLine]=elist.data[i];
            spanlist.numberOfLine=spanlist.numberOfLine+1;
            unionOfLabeledArray(label,cno1,cno2);//bu metod etiket dizisinde farklı etiketli olan düğümleri aynı olacak şekilde değiştirir.
            count= findClusterNum(label);
            if( count<=k){
                stop=1;
            }
            
        }
        i++;
    }
    
    print(label,k); //Her kümedeki  düğümleri yazdıran fonksiyondur.
    
}


int main()
{
    int k; // number of cluster
    numberOfLine =getLineNumber(); //bu metod kaç satır oldugu bilgisini okur.
    readFile(numberOfLine); //bu metod dosyadan okudugu bilgileri G matrisine yazıdırır.
    printf("\n Please enter number of cluster:");
    scanf("%d",&k);
    kruskal(numberOfLine,k); //kruskal algoritmasına göre verilen matrisi istenen sayıda alt kümeye ayırmak için yazılan fonksiyondur.
    findDistance(); //bu metod dışardan girilen kümelerin birbirine olan uzaklıgını bulur.
}



