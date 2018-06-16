#include<stdio.h>
int a[11][11],visited[11][11],n,stop=0; // a matrisi dosyadan okunup üzerine yazılan int tipinde matrisdir.
//stop depth first search için durmak koşulunu sağlayacak flagdir.visited matrisi başta initialize edilmiş üzerinde gezildikçe yazılan matrisdir.
char printArray[11][11]; //çıktıyı yazabilmek için kullanılacak matrisdir.

void controlStopCase(int x,int y){
    //eğer n boyutlu dizi ise n-2 boyutu durma koşulumuz olacaktır.
    if(x>=(n-2)&& y>= (n-2)){
        printArray[x][y]='X'; // durma koşulu olursa ekrana yazdıracagımız diziye X işareti atanır.
        stop=1;
    }
}

void depthFirstSearch(int x,int y)
{
    visited[x][y]=1;  //başlangıçda (1,1) noktesı visited dizisinde işaretlenir
    
    if(!stop){
        
        if( a[x+1][y]!=0 && visited[x+1][y]==0) // birinci olarak  güneyi komşusunu kontrol et.
        {
            printf("%d -> %d\n ",x,y);
            visited[x+1][y]=1;  // güney komşusu var ise visited dizisinde o komşuya gidildigini işaretleriz.
            printArray[x+1][y]='S'; // Depth first search de gezilen yerleri S olarak işaretleriz daha sonra istenen formata print metodunda getirilecektir.
            controlStopCase(x+1,y);//recursive fonksiyon oldugundan stop durumuna gelinip gelinmedigini visited dizisinde işaretleme yaptıktan sonra bakılır
            depthFirstSearch(x+1,y);//recursive olarak güney komşusu çağrılır.
        }
        else if(a[x][y+1]!=0 && visited[x][y+1]==0 ) // ikinci olarak doğu komşusunu kontrol et.
        {
            printf("%d -> %d\n ",x,y);
            visited[x][y+1]=1;// doğu komşusu var ise visited dizisinde o komşuya gidildigini işaretleriz.
            printArray[x][y+1]='S'; // Depth first search de gezilen yerleri S olarak işaretleriz daha sonra istenen formata print metodunda getirilecektir.
            controlStopCase(x,y+1);//recursive fonksiyon oldugundan stop durumuna gelinip gelinmedigini visited dizisinde işaretleme yaptıktan sonra bakılır
            depthFirstSearch(x,y+1);//recursive olarak doğu komşusu çağrılır.
        }
        else if( a[x-1][y]!=0 && visited[x-1][y]==0) //üçüncü olarak  kuzey komşusunu kontrol et.
        {
            printf("%d -> %d\n ",x,y);
            visited[x-1][y]=1; // kuzey komşusu var ise visited dizisinde o komşuya gidildigini işaretleriz.
            printArray[x-1][y]='S';// Depth first search de gezilen yerleri S olarak işaretleriz daha sonra istenen formata print metodunda getirilecektir.
            controlStopCase(x-1,y);//recursive fonksiyon oldugundan stop durumuna gelinip gelinmedigini visited dizisinde işaretleme yaptıktan sonra bakılır
            depthFirstSearch(x-1,y);//recursive olarak kuzey komşusu çağrılır.
        }
        
        else if( a[x][y-1]!=0 && visited[x][y-1]==0 ) // dördüncü olarak  batıdaki komşusunu kontrol et.
        {
            printf("%d -> %d\n ",x,y);
            visited[x][y-1]=1;// batıda komşusu var ise visited dizisinde o komşuya gidildigini işaretleriz.
            printArray[x][y-1]='S';// Depth first search de gezilen yerleri S olarak işaretleriz daha sonra istenen formata print metodunda getirilecektir.
            controlStopCase(x,y-1);//recursive fonksiyon oldugundan stop durumuna gelinip gelinmedigini visited dizisinde işaretleme yaptıktan sonra bakılır
            depthFirstSearch(x,y-1);//recursive olarak batı komşusu çağrılır.
        }
    }
    
    
}

static int getLineNumber() {
    //Bu fonksiyon dosyada kaç satır oldugunu bulur.
    FILE *file = fopen("/Users/betulyazici/Desktop/input1.txt", "r");
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
    FILE *file = fopen("/Users/betulyazici/Desktop/input1.txt", "r");
    for(int row = 0; row < numberOfLine; row++)
    {
        for(int column = 0; column < numberOfLine; column++)
        {
            fscanf(file, "%d, \n", &a[row][column]);
        }
    }
    fclose(file);
    
}

static void initializeOfVisitedArray() {
    //visited dizisinin elemanlarını 0 olarak işartlenir o düğümler gezilince 1 olarak değiştirilir.
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            visited[i][j]=0;
    
}
static void initializeSValues(){
    // S valueları boşluk olarak değiştiririz.Çünkü ödev formatında yanlızca B ile işaretlenen yerlerin gezilen oldugunun işaretlenmesi istenmektedir.
    //matrise erişmek için 2 for döngüsü iç içe yazılır i satır j sütunlara erişmek için kullanılan indislerdir.
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if (printArray[i][j]=='S'){
                printArray[i][j]='\0';
            }
        }
        
    }
}

static void printMatris() {
    // printArray dizisinin elemanlarının  yazıdırıldıgı fonksiyondur
    
    initializeSValues(); // S valueları boşluk olarak değiştiririz.Çünkü ödev formatında yanlızca B ile işaretlenen yerlerin gezilen oldugunun işaretlenmesi istenmektedir.
    for(int j=0;j<n;j++)
    {
        
        for(int k=0;k<n;k++)
        {
            if (printArray[j][k]=='\0'){
                printf(" "); // boşluk karakterleri konsola yazıdırırken yanyana yazıyordu bu hatayı gidermek için printf fonksiyonu ile boşluk koydum.xs
            }
            printf("%c",printArray[j][k]);  // dizinin elemanları yazıdırlır
            
        }
        printf("\n");
    }
}

static void formatArrayInside() {
    
    //bu metod arrayin içini satırlar çift sayı ve sütunlar tek sayı ise |
    // satırlar çift sayı sütunlar çift sayı ise +
    // sütunlar tek sayı ise - işareti koyar.
    for(int i=1;i<(n-1);i++)
    {
        for(int j=1;j<(n-1);j++){
            
            if(a[i][j]==0){
                
                if(j%2==0 && i%2==1){
                    printArray[i][j]='|';
                }
                else if (j%2==0 && i%2==0){
                    printArray[i][j]='+';
                }
                else if(j%2==1){
                    printArray[i][j]='-';
                }
                
            }
            
            else if (a[i][j]==2 &&  printArray[i][j] == 'S'){
                printArray[i][j]='I';  // eğer dosyadan okudugumuz dizi elemanı 2 ise B anlamına geliyor. ve S ise yani gezilen olarak işaretlendiyse I olarak işaretlenir.
            }
            
        }
    }
}

void formatEdge(){
    //kenarları istenen formata getirmek için yazılmıs fonksiyondur
    //bu fonksiyon satırların çift sayılarda + tek sayılarda -
    //sütunların çift sayılarda + tek sayılarda | gözükmesi için kullanılır.
    for(int i=0;i<n;i++){
        if(i%2==1){
            //tek sayı oldugunu anlamak için mod alma kullanılır
            printArray[0][i]='-';
            printArray[10][i]='-';
            printArray[i][0]='|';
            printArray[i][10]='|';
            
        }
        else{
            //çift sayı oldugunu anlamak için mod alma kullanılır
            printArray[0][i]='+';
            printArray[10][i]='+';
            printArray[i][0]='+';
            printArray[i][10]='+';
        }
    }
    
    formatArrayInside();//matrisin içindeki gezilmeyen yerleri formatlamak için kullanılan fonksiyondur.
    printMatris();// formatlanmış matrisi yazdırmak için kullanılan fonskiyondur.
    
    
}

int main()
{
    int numberOfLine=0;
    printf("Enter number of n:");
    scanf("%d",&n);
    
    numberOfLine =getLineNumber(); //bu metod kaç satır oldugu bilgisini okur.
    readFile(numberOfLine); //bu metod dosyadan okudugu bilgileri a matrisine yazıdırır.
    
    initializeOfVisitedArray();
    printArray[1][1]='*';
    depthFirstSearch(1,1); //başlangıç noktası 1,1 ile başlıyor.
    formatEdge();
    
    
}

