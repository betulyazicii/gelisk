
//
//  main.c
//  Problem2
//
//  Created by Betul Yazıcı on 28.03.2018.
//  Copyright © 2018 Betul Yazıcı. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 15
#define lineSize 10
int enteredValue=0; //ekrandan girilen bütün kimlik numarası bilgileri bu değişkene atanır.
struct node* searchedValue=NULL;  //aranan kimlik numarasına her metoddan erişebilmek için global tanımlanmıstır.

struct node
{
    int identityValue;
    char name[SIZE];
    struct node* left;
    struct node* right;
    int friends[SIZE];
    
};

void initialize(struct node *newnode){
    //node olusturuken elemanların initialize edilmesini adreslerin sıfırlanmasını sağlayan metoddur.
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->identityValue=0;
    for(int i=0;i<SIZE;i++){
        newnode->friends[i]=0;
    }
    
}



void Insert(struct node* root,struct node *newNode){
    
    //yeni bir node eklenecegind BST kuralına uygun olması için yapılan kontrollerdir küçükse ağacın soluna,büyükse ağacın sağına yazılır.
    if(newNode->identityValue < root->identityValue ){
        
        if(root->left == NULL){
            root->left=newNode;
        }
        else
            Insert(root->left,newNode);
    }
    else{
        
        if(root->right == NULL){
            root->right= newNode;
        }
        else
        {
            Insert(root->right,newNode);
        }
    }
    
    
}

void Search(struct node* root, int x)
{
    //BST kurallarına göre girilen elemanı arar girilen eleman rootdan büyükse sağındadır.Küçükse solundadır özyinemeli olarak çağırır ve eleman var ise bulunur.
    if(root->identityValue < x ){
        if(root->right != NULL){
            Search(root->right,x);
        }
    }
    else if(root->identityValue > x ){
        if(root->left != NULL){
            Search(root->left,x);
        }
    }
    else{
        printf(" %d nolu kimlik bilgisinin ad-soyad bilgisi: %s dir \n",root->identityValue, root->name);
        searchedValue=root;
    }
    
}

int getSize(struct node* root){
    //ağacın eleman sayısını bulan fonksiyondur.
    
    if(root == NULL)
        return 0;
    else{
        return(getSize(root->left) + 1 + getSize(root->right));
    }
    
}


void printInOrder(struct node* root){
    //bu metod sadece ilk agc olustuktan sonra K->B ağacı göstermek için yazılmıstır.
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->identityValue);
        printInOrder(root->right);
    }
}

void printInOrderNameDetail(struct node* root){
    //Bu metod Inorder gösterim şekliyle Left root right kimlik ve isim bilgileri ile ağacı kimlik bilgilerine göre K->B dizilecek şekilde göstermek  için yazılmıstır.
    if (root != NULL)
    {
        printInOrderNameDetail(root->left);
        printf("kimlik numarası: %d - Ad-soyad: %s\n", root->identityValue,root->name);
        printInOrderNameDetail(root->right);
    }
}



void printNext(struct node *root,int x){
    Search(root,x); //önce kimlik numarası verilen kişinin ağactaki yeri bulunur
    printInOrderNameDetail(searchedValue); //sonra alt agacı yazdırılır.
}


void printGreater(struct node *root){
    //girilen kimlik değerinden daha büyük olan kimlik bilgilerini bulur.
    if (root != NULL){
        if( root->identityValue > enteredValue)
        {
            printGreater(root->right);
            printf("kimlik numarası: %d - Ad-soyad: %s\n", root->identityValue,root->name);
            printGreater(root->left);
            
        }
        else {
            printGreater(root->right);
        }
    }
}



struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    
    //agacın en solundaki en küçük değeri buluruz.
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

struct node* deleteNode(struct node* root,int deletedValue){
    //ağactan girilen kimlik değerini siler.
    if (root == NULL) return root;
    if (deletedValue < root->identityValue) //eğer root silinecek elemandan büyük ise root'un leftinden sililinecektir
        root->left = deleteNode(root->left, deletedValue);
    else if (deletedValue > root->identityValue)
        root->right = deleteNode(root->right, deletedValue);
    
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        
        struct node* temp = minValueNode(root->right);//ağacı yeniden düzenlemek içn min değer bulunur
        
        root->identityValue = temp->identityValue;
        
        root->right = deleteNode(root->right, temp->identityValue);
    }
    return root;
}



struct node* readFile(FILE *file) {
    //Bu metod txt dosyasından okunan bilgileri node struct yapısına uygun hale getirir.
    char identityValues[SIZE]; // dosyada 4-5-6 şeklinde yazılan node'un friends bilgileri char olarak okunmustur.Sonradan parse edilmiştir.
    struct node* newnode = (struct node*)malloc(sizeof(struct node)); //eklenen her node için bellekte dinamik olarak yer açılır
    initialize(newnode);
    fscanf(file,"%d,%99[^,],%s\r\n", &newnode->identityValue,newnode->name,identityValues); //fscanf fonksiyonu ile , ile satır parse edilmiştir.
    int k=1; // friends eleman sayısıdır
    char *p; // friends bilgilerinin - ile ayırarak ayrılan kısmı geçici olarak tutulan değişkendir.
    int stop=0; // karakter dizisinin null oldugu durumda döngüden cıkmak için olusturulmustur
    p = strtok(identityValues,"-");
    newnode->friends[0]=  atoi(p);//atoi fonksiyonu char'ı integer 'a çevirir.
    
    while(k<SIZE && stop == 0){
        
        p = strtok(NULL, "-");
        
        if(p == NULL){
            stop=1;
        }
        else{
            newnode->friends[k]=  atoi(p);//yeni olusturulan node'a parse edilen ve  int'e çevrilen eleman eklenir.
            k++;
        }
        
        
        
    }
    return newnode; //node struct yapısına göre parse edilmiş node geri dönülür.
    
}

static int getLineNumber(FILE *file) {
    //Bu fonksiyon dosyada kaç satır oldugunu bulur.
    int count=0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // yeni satıra geçtigini anlayınca count artırırız.
            count = count + 1;
    
    return count;
}

int main(int argc, const char * argv[]) {
    
    
    FILE *file = fopen("/Users/betulyazici/Desktop/input2.txt", "r");
    struct node *root = NULL;
    // int lineSize = getLineNumber(file); //bu metod kaç satır oldugu bilgisini okur.
    root =  readFile(file);  //ilk okudugumuz satırı root'a atacagımız için i'nin 0 olması durumunu koşula bağladım.
    for(int i=1;i<lineSize;i++){
        struct node *newNode =  readFile(file); //dosyadan root dısındaki satırlar okunur.
        Insert(root, newNode);  //okunan değerler ağaca BST kuralına uygun şekilde eklenir.
    }
    
    fclose(file); //okunan dosya okuma bitince kapatılır.
    printInOrder(root); //oluşan agacı küçükten büyüge sıralı görmek için yazılmıstır.
    
    
    int option=0; // yapılması istenen seçenegi tutan değişkendir.
    int tempfriends[SIZE] = {0}; //kimlik nosu girilen kişilerin arkadslarını tutmak için olusturulmustur.
    
    printf("\n1.Delete User Option\n2.Search (Contains) Option\n3.Find Friends Option\n4.Find Size Option\n5.printNext Option\n6.printInOrder Option\n7.PrintGreaterOption\n8.Exit");
    printf("Enter your choice:\n");
    scanf("%d", &option);
    
    switch(option) {
            
        case 1:
            printf("\n Silinecek elemanın kimlik numarasını giriniz : ");
            scanf("%d", &enteredValue);
            deleteNode(root,enteredValue); //girilen node eğer ağaçta varsa silme işlemini yapar ve ağacı yeniden düzenler.
            printInOrder(root); //delete işleminden sonra ağacın elemanlarını yazdırma amacı ile kullanılmıstır.
            break;
        case 2:
            printf("\n Bulunması gereken elemanın kimlik numarasını giriniz : ");
            scanf("%d", &enteredValue);
            Search(root,enteredValue); //kimlik nosu verilen kişi ağacta var ise ad-soyad bilgisini yazdırır.
            break;
        case 3:
            printf("\n Friends bulunacak kimlik numarasını giriniz.");
            scanf("%d", &enteredValue);
            Search(root,enteredValue);
            printf("\n %d Kimlik numarası verilen kişinin arkadslarının ad-soyad bilgileri:\n",enteredValue);
            int i=0,j=0;
            while (i<SIZE && searchedValue->friends[i] != 0 ){
                //Kimlik numarası girilen kişinin arkadslarını temfriends dizisinde tutulur.
                tempfriends[i]=searchedValue->friends[i] ;
                i++;
            }
            while(j<SIZE && tempfriends[j] != 0){
                //herbir arkadası için search metodu çağrılır ve isim bilgileri yazdırılır.
                Search(root,tempfriends[j]);
                j++;
            }
            break;
        case 4:
            printf("Ağacın size bilgisi= %d",getSize(root)); //agacın size bilgisini bulur.
            break;
            
        case 5:
            printf("\n Alt ağacı bulunacak node'un kimlik numarasını giriniz : ");
            scanf("%d", &enteredValue);
            printNext(root,enteredValue); //alt ağacı bulup isim kimlik bilgilerinin yazdırır.
            break;
        case 6:
            printInOrderNameDetail(root); //Left root right şeklinde yazdırmak için kullanılan fonksiyondur.
            break;
        case 7:
            printf("\nGreate print option için  kimlik nosunu gir: ");
            scanf("%d", &enteredValue);
            Search(root,enteredValue);
            printGreater(root); //girilen elemandan daha büyük olan kimlik bilgilerini bulup ad-soyad bilgilerini ekrana yazdırır.
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    
    
    return 0;
    
}
