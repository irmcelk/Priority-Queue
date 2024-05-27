#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Konu: Coklu Oncelikli Kuyruk Gerceklenmesi
Problem: NxM�lik bir matrisin her sat�r�nda max-heap-tree �zelligi tasiyan �ncelikli kuyruk 
olu�turulur, kullan�c�dan her bir kuyrugun kapasitesi alinir Her ad�mda �ncelikli 
kuyruklar�n ilk elemanlar�ndan en y�ksek �nceli�e sahip olan ilgili kuyruktan ��kart�l�r. Bu ad�mlar 
kuyruklarda eleman kalmay�ncaya kadar devam eder. Tasarlan�lan algoritmada s�ra ile bo�a ��kan 
kuyruklar� ekrana yazd�rmal�d�r.
*/

/*
@brief Verilen say�n�n daha �nce matriste kullan�l�p kullan�lmad���n� kontrol eden fonksiyon

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
                return 0; // Say� daha �nce kullan�lm��
            }
        }
    }
    return 1; // Say� daha �nce kullan�lmam��
}


/*
@brief Bir matrisin ilk s�tunundaki en b�y�k eleman� bulan fonksiyon 

@param matrix pointer
@param matrix satir sayisi

@return en buyuk elemanin bulundugu index
*/
int findMaxInFirstColumn(int **matrix, int N) {
   int max = -1; 
   int index;
   int i;
   printf("Kuyruklardan degerleri okunan elemanlar:");
    // �lk s�tundaki her bir eleman� kontrol et
    for (i = 0; i < N; i++) {
    	if(matrix[i][0]!=-1) //sutun bos degilse islemleri yap
    {   printf("%d  ",matrix[i][0]);
         if (matrix[i][0] > max) {
            max = matrix[i][0]; // Eger bulunan eleman, su ana kadar en buyuk elemandan buyukse g�ncelle
            index=i; // en buyuk elemanin indexini tut
        }
    }
  }
    
    return index; // En buyuk elemanin bulundugu indexi dondurur
}


/*
@brief Verilen diziyi maksimum heap agac�na donusturen fonksiyon

@param agaci tutan dizi pointer
@param dizinin eleman sayisi
@param agac kokunun indexi

*/
void heapify(int *arr, int n, int i) {
    int largest = i; // Kokun indexi
    int left = 2 * i + 1; // Sol alt dugumun indexi
    int right = 2 * i + 2; // Sa� alt dugumun indexi

    // Sol alt dugumun degeri, kokten buyukse ve sol alt dugum dizinin sinirlari icindeyse
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Sag alt dugumun degeri, kokten buyukse ve sag alt dugum dizinin sinirlari icindeyse
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // E�er en buyuk de�er kok de�ilse, yer degistir ve alt agaclar� heapify et
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

/*
@brief Verilen diziyi maksimum heap agac�na donusturen fonksiyon

@param agaci tutan dizi pointer
@param dizinin eleman sayisi

*/
void buildMaxHeap(int *arr, int n) {
	int i;
    // En sonuncu d���mden ba�layarak heapify i�lemi uygula
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
	// Matrisi ekrana yazd�r
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
    // Kullan�c�dan sat�r ve s�tun say�s�n� al
    printf("Matrisin satir sayisi(N) girin: ");
    scanf("%d", &N);
    printf("Matrisin sutun sayisini(M) girin: ");
    scanf("%d", &M);
    
    // Bellekte matris i�in yer ay�r
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
     // Bellekte kuyruk boyut dizisi i�in yer ay�r
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
            num = 1 + rand() % (N * M); // 1 ile N*M aras�nda rastgele say� �ret
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
    
    // Bellekten matris i�in ayr�lan yerleri serbest b�rak
    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(kuyrukBoyut);
    return 0;
}


