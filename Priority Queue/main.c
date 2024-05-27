#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Konu: Coklu Oncelikli Kuyruk Gerceklenmesi
Problem: NxM’lik bir matrisin her satýrýnda max-heap-tree özelligi tasiyan öncelikli kuyruk 
oluþturulur, kullanýcýdan her bir kuyrugun kapasitesi alinir Her adýmda öncelikli 
kuyruklarýn ilk elemanlarýndan en yüksek önceliðe sahip olan ilgili kuyruktan çýkartýlýr. Bu adýmlar 
kuyruklarda eleman kalmayýncaya kadar devam eder. Tasarlanýlan algoritmada sýra ile boþa çýkan 
kuyruklarý ekrana yazdýrmalýdýr.
*/

/*
@brief Verilen sayýnýn daha önce matriste kullanýlýp kullanýlmadýðýný kontrol eden fonksiyon

@param matrix pointer
@param matrix satir sayisi
@param matrix sutun sayisi
@param matrixte olup olmadigi kontrol edilecek sayi

@return sayi kullanilmissa 0,kullanilmamissa 1 
*/
int isUnique(int **matrix, int N, int M, int num) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (matrix[i][j] == num) {
                return 0; // Sayý daha önce kullanýlmýþ
            }
        }
    }
    return 1; // Sayý daha önce kullanýlmamýþ
}


/*
@brief Bir matrisin ilk sütunundaki en büyük elemaný bulan fonksiyon 

@param matrix pointer
@param matrix satir sayisi

@return en buyuk elemanin bulundugu index
*/
int findMaxInFirstColumn(int **matrix, int N) {
   int max = -1; 
   int index;
   int i;
   printf("Kuyruklardan degerleri okunan elemanlar:");
    // Ýlk sütundaki her bir elemaný kontrol et
    for (i = 0; i < N; i++) {
    	if(matrix[i][0]!=-1) //sutun bos degilse islemleri yap
    {   printf("%d  ",matrix[i][0]);
         if (matrix[i][0] > max) {
            max = matrix[i][0]; // Eger bulunan eleman, su ana kadar en buyuk elemandan buyukse güncelle
            index=i; // en buyuk elemanin indexini tut
        }
    }
  }
    
    return index; // En buyuk elemanin bulundugu indexi dondurur
}


/*
@brief Verilen diziyi maksimum heap agacýna donusturen fonksiyon

@param agaci tutan dizi pointer
@param dizinin eleman sayisi
@param agac kokunun indexi

*/
void heapify(int *arr, int n, int i) {
    int largest = i; // Kokun indexi
    int left = 2 * i + 1; // Sol alt dugumun indexi
    int right = 2 * i + 2; // Sað alt dugumun indexi

    // Sol alt dugumun degeri, kokten buyukse ve sol alt dugum dizinin sinirlari icindeyse
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Sag alt dugumun degeri, kokten buyukse ve sag alt dugum dizinin sinirlari icindeyse
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Eðer en buyuk deðer kok deðilse, yer degistir ve alt agaclarý heapify et
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

/*
@brief Verilen diziyi maksimum heap agacýna donusturen fonksiyon

@param agaci tutan dizi pointer
@param dizinin eleman sayisi

*/
void buildMaxHeap(int *arr, int n) {
	int i;
    // En sonuncu düðümden baþlayarak heapify iþlemi uygula
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

/*
@brief Verilen matrisi yazdiran fonksiyon

@param matris pointer
@param matrisin satir sayisi
@param matrisin sutun sayisi

*/
void printMat(int **matrix,int N,int M){
	int i,j;
	// Matrisi ekrana yazdýr
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
}

/*
@brief Verilen dizinin bos olup olmadigini kontrol eden fonksiyon

@param dizi pointer
@param dizi uzunlugu

@return dizi bos degilse 0, bossa 1 dondurur

*/
int isEmpyt(int *arr,int M){
	int i;
	for(i=0;i<M;i++){
		if(arr[i]!=-1){
			return 0;//bos degil
		}
	}
	return 1;//bos
}

/*
@brief Verilen matrisin sutunlarinda bulunan en buyuk elemani bulup bu elemani silen daha sonra bu elemanin 
bulundugu dizinin bos olup olmadigini kontrol ettirir, dizi bos degilse dizi max heap tree ozelligi kazandirilir,
dizi bossa kacinci kuyruk oldugu bir dizide tutulur daha sonra da matris yazdirilan fonksiyon

@param matris pointer
@param matrisin satir sayisi
@param matrisin sutun sayisi

*/
void removeMax(int **matrix,int N,int M){
	int index; //en buyuk elemanin oldugu satiri tutan degisken
	int count=0; //kac kuyrugun bos oldugunu tutan degisken
	int i;
	int arr[N];//bos olan kuyruklarin sirasini tutan dizi
	
	do{
	index=findMaxInFirstColumn(matrix,N);
    printf("\nSecilen eleman %d\n",matrix[index][0]);	
    matrix[index][0]=-1;//en buyuk elemani -1 yaparak kuyruktan kaldirir 
    if(isEmpyt(matrix[index],M)!=1){
    	buildMaxHeap(matrix[index], M);//kuyruk bos degilse max heap tree ozelligi kazandirir
	}
    else{
    	arr[count]=index;//kuyruk bossa kuyrugun numarasini tutar
    	count++;//bos olan kuyruk sayisini arttirir
}
    printMat(matrix,N,M);
	}while(count!=N);
	
	//matristeki kuyruklarin hepsi bosalinca kuyruklarin hangi sirayla tukendigini yazdirir
    for(i=0;i<N;i++){
    	printf("%d\n",arr[i]);
	}
}

int main() {
    int **matrix; 
    int N, M; //matrix satir ve sutun
    int i,j,k;
    int *kuyrukBoyut; //kullanicidan alinan kuyruk boyutlari dizisi
    int num; //random uretilen sayi
    // Kullanýcýdan satýr ve sütun sayýsýný al
    printf("Matrisin satir sayisi(N) girin: ");
    scanf("%d", &N);
    printf("Matrisin sutun sayisini(M) girin: ");
    scanf("%d", &M);
    
    // Bellekte matris için yer ayýr
    matrix = (int **)malloc(N * sizeof(int *));
    if (matrix == NULL) {
        printf("Bellek yetersiz!\n");
        exit(0);
    }
    for (i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Bellek yetersiz!\n");
            exit(0);
        }
    }
     // Bellekte kuyruk boyut dizisi için yer ayýr
    kuyrukBoyut = (int*)malloc(N * sizeof(int));
 
    if (kuyrukBoyut == NULL) {
        printf("Bellek yetersiz!\n");
        exit(0);
    }
    else {
        for (i = 0; i < N; ++i) {
        	printf("Oncelikli kuyruk boyutlarini girin.Kuyruk boyutu %d'den (sutun sayisindan)buyuk olmamali\n",M);
            scanf("%d",&kuyrukBoyut[i]);
        }
 }
    srand(time(NULL));
    
    //matrisi rastgele elemanlarla doldurmak icin
    for(i=0;i<N;i++)
    {
      for(j=0;j<kuyrukBoyut[i];j++)
        {	
        	do {
            num = 1 + rand() % (N * M); // 1 ile N*M arasýnda rastgele sayý üret
           } while (!isUnique(matrix, N, M, num));
         matrix[i][j] = num;//sayi daha once kullanilmamisa matrise ata
       		
		}
		for(k=j;k<M;k++)//kuyruk uzunlugu matris sutunundan kucukse kalan yerleri -1 ile doldur
		{
			matrix[i][k]=-1;
		}
	}
	printf("Rastgele uretilen %d kuyruk iceren matris\n",N);
	printMat(matrix,N,M);
	
    for (i = 0; i < N; i++) {
        buildMaxHeap(matrix[i], M);
    }
    
   printf("Max heap ozelligi tasiyan %d kuyruk iceren matris\n",N);
   printMat(matrix,N,M);
   
   removeMax(matrix,N,M);
    
    // Bellekten matris için ayrýlan yerleri serbest býrak
    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(kuyrukBoyut);
    return 0;
}


