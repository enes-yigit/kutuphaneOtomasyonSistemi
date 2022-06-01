#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_KISI_SAYISI 50
#define MAX_KITAP_SAYISI 50

typedef enum{
	musteri=0, calisan=1
}kisiYetkiSeviyeleri;


typedef struct{
	char *kisiAdi;
	char *kisiSoyadi;
	int kutuphaneID;
	int sifre;
	kisiYetkiSeviyeleri kisiYetkisi;
}kisiBilgileri;

typedef struct{
	char *kitapAdi;
	char *kitapYazarAdi;
	char *kitapYazarSoyadi;
	char *kitapYayineviAdi;
	int kitapSayfasi;
	int kitapMevcutlukDurumu;
}kitapBilgileri;


//************Fonksiyonlar**************//

int kisiSorgula(kisiBilgileri *uyeListesi, int ID){
	int i;
	for(i=0;i<MAX_KISI_SAYISI;i++){
		if(uyeListesi[i].kutuphaneID==ID){
			return ID;
		}
	}	
	return -1;
}

int kayitOl(kisiBilgileri *uyeListesi){
	
	int i,kayitYapilacakIndex,ID;
	char kisiAdi[20],kisiSoyadi[20],ch;
	
	srand(time(NULL));
	for(i=0;i<MAX_KISI_SAYISI;i++){					//Liste taranir..
		if(uyeListesi[i].kutuphaneID==0){			//Kayit yapilacak bos index bulunur.
			kayitYapilacakIndex=i;
			break;
		}
	}
	ID=rand()%10000+1;								//ID atanir.
	if(kisiSorgula(uyeListesi,ID)!=-1){				//Atanan ID kullanilmis mi bakilir.
		printf("Bu ID daha once kullanilmistir..");
		exit(1);
	}
	printf("ID numaraniz %d olarak belirlenmistir",ID);
	uyeListesi[kayitYapilacakIndex].kutuphaneID=ID;//Onaylanan ID kayit yapan kullaniciya atanir.
	
	
	printf("lutfen sirasiyla ad-soyad bilgilerinizi giriniz..");
	scanf("%s%s",&kisiAdi,&kisiSoyadi);
	uyeListesi[kayitYapilacakIndex].kisiAdi=(char*)malloc(sizeof(char)*(strlen(kisiAdi)+1));
	uyeListesi[kayitYapilacakIndex].kisiSoyadi=(char*)malloc(sizeof(char)*(strlen(kisiSoyadi)+1));
	strcpy(uyeListesi[kayitYapilacakIndex].kisiAdi,kisiAdi);
	strcpy(uyeListesi[kayitYapilacakIndex].kisiSoyadi,kisiSoyadi);
	
	
	printf("Musteri iseniz 'M' tuslayiniz.\n Calisan iseniz 'C' tuslayiniz.");
	fflush(stdin);
	ch=getchar();
	if(ch=='M'||ch=='m'){
		uyeListesi[kayitYapilacakIndex].kisiYetkisi=musteri;
	}
	else{
		uyeListesi[kayitYapilacakIndex].kisiYetkisi=calisan;
	}
	
	printf("Lutfen sifrenizi giriniz.");
	scanf("%d",uyeListesi[kayitYapilacakIndex].sifre);
	
	return uyeListesi[kayitYapilacakIndex].kisiYetkisi;
}
  
int girisYap(kisiBilgileri *uyeListesi){
	int i, ID,sifre;
	printf("Lutfen kutuphane ID bilginizi giriniz:");
	scanf("%d",&ID);
	printf("Lutfen kutuphane sifre bilginizi giriniz:");
	scanf("%d",&sifre);	
	
	
	for(i=0;i<MAX_KISI_SAYISI;i++){
		if(uyeListesi[i].kutuphaneID=ID){
			if(uyeListesi[i].sifre=sifre){
				printf("Giris basarili..");
				return uyeListesi[i].kisiYetkisi;
			}
			return -1;//Sifre Yanlis Girildi..
		}
	}
	return -2;
}

void uyeleriAktar(kisiBilgileri *uyeListesi){
	char ad[20],soyad[20];
	FILE *uyeKayitlari;
	int i;
	
	
	uyeKayitlari=fopen("uyeListesi.txt","r");
	if(uyeKayitlari==NULL){
		fprintf(stderr,"Dosya acilirken hata meydana geldi!");
		exit(1);
	}
	
	while(!feof(uyeKayitlari)){
		for(i=0;i<MAX_KISI_SAYISI;i++){
			if(uyeListesi[i].kutuphaneID=0){
				fscanf(uyeKayitlari,"%s\t%s\t%d\t%d\t%d\t",ad,soyad,uyeListesi[i].kisiYetkisi,uyeListesi[i].kutuphaneID,uyeListesi[i].sifre);		
				uyeListesi[i].kisiAdi=(char*)malloc(sizeof(char)*(strlen(ad)+1));
				uyeListesi[i].kisiSoyadi=(char*)malloc(sizeof(char)*(strlen(soyad)+1));
				strcpy(uyeListesi[i].kisiAdi,ad);
				strcpy(uyeListesi[i].kisiSoyadi,soyad);
				break;
			}	
		}
	}
	fclose(uyeKayitlari); 
}

void kitaplariAktar(kitapBilgileri *kitaplik){
	char kitapAdi[30],yazarAdi[30],yazarSoyadi[30],yayinEvi[30];
	int i;
	
	
	FILE *kitapKayitlari;									//kitap bilgileri ile alakali dosya islemleri bolumu
	kitapKayitlari=fopen("kitapListesi.txt","r");
	if(kitapKayitlari==NULL){
		fprintf(stderr,"Dosya acilirken hata meydana geldi!!");
		exit(1);
	}
	
	while(!feof(kitapKayitlari)){
		for(i=0;i<MAX_KITAP_SAYISI;i++){
			if(kitaplik[i].kitapSayfasi==0){
				fscanf(kitapKayitlari,"%s\t%s\t%s\t%s\t%d\t%d\t",kitapAdi,yazarAdi,yazarSoyadi,yayinEvi,&kitaplik[i].kitapSayfasi,&kitaplik[i].kitapMevcutlukDurumu);
				kitaplik[i].kitapAdi=(char*)malloc(sizeof(char)*(strlen(kitapAdi)+1));
				kitaplik[i].kitapYazarAdi=(char*)malloc(sizeof(char)*(strlen(yazarAdi)+1));
				kitaplik[i].kitapYazarSoyadi=(char*)malloc(sizeof(char)*(strlen(yazarSoyadi)+1));
				kitaplik[i].kitapYayineviAdi=(char*)malloc(sizeof(char)*(strlen(yayinEvi)+1));
				strcpy(kitaplik[i].kitapAdi,kitapAdi);
				strcpy(kitaplik[i].kitapYazarSoyadi,yazarSoyadi);
				strcpy(kitaplik[i].kitapYayineviAdi,yayinEvi);
				strcpy(kitaplik[i].kitapYazarAdi,yazarAdi);
				break;
			}
		}
	}	
	fclose(kitapKayitlari);
}

void kitaplariYedekle(kitapBilgileri *kitaplik){
	//programdan cikarken uyeleri ve kitaplari kaybetmemek icin

	FILE *kitapKayitlari;
	int i=0;
			
	kitapKayitlari=fopen("kitapListesi.txt","w");
	if(kitapKayitlari==NULL){
		fprintf(stderr,"Dosya acilirken hata meydana geldi!!");
		exit(1);
	}
	
	while(i<MAX_KITAP_SAYISI && kitaplik[i].kitapSayfasi!=0){
		fprintf(kitapKayitlari,"%s\t%s\t%s\t%s\t%d\t%d\n",kitaplik[i].kitapAdi,kitaplik[i].kitapYazarAdi,kitaplik[i].kitapYazarSoyadi,kitaplik[i].kitapYayineviAdi,kitaplik[i].kitapSayfasi,kitaplik[i].kitapMevcutlukDurumu);
		i++;
	}
	fclose(kitapKayitlari);
}

void uyeleriYedekle(kisiBilgileri *uyeListesi){
	FILE *uyeKayitlari;
	int i=0;
	
	
	uyeKayitlari=fopen("uyeListesi.txt","w");
	if(uyeKayitlari==NULL){
		fprintf(stderr,"Dosya acilirken hata meydana geldi!");
		exit(1);
	}
	while(i<MAX_KISI_SAYISI && uyeListesi[i].kutuphaneID !=0){
		fprintf(uyeKayitlari,"%s\t%s\t%d\t%d\t%d\n",uyeListesi[i].kisiAdi,uyeListesi[i].kisiSoyadi,uyeListesi[i].kisiYetkisi,uyeListesi[i].kutuphaneID,uyeListesi[i].sifre);
		i++;
	}
	fclose(uyeKayitlari);
}

void kitaplariGoruntule(kitapBilgileri *kitaplik){
	int i;
	for(i=0;i<MAX_KITAP_SAYISI;i++){
		if(kitaplik[i].kitapSayfasi!=0){
			printf("Kitap Adi:%s\n",kitaplik[i].kitapAdi);
			printf("Kitap Yazari:%s%s\n",kitaplik[i].kitapYazarAdi,kitaplik[i].kitapYazarSoyadi);
			printf("Kitap Yayinevi:%s\n",kitaplik[i].kitapYayineviAdi);
			printf("Kitap Sayfa Sayisi:%d\n",kitaplik[i].kitapSayfasi);
			if(kitaplik[i].kitapMevcutlukDurumu==0){
				printf("Bu kitap raftadir.");
			}
			else{
				printf("Bu kitap su an mevcut degildir.");
			}
		}
	}
	
}

void kitapAra(kitapBilgileri *kitaplik){
	int i=0;
	char kitapAdi[30];
	printf("lutfen aramak istediginiz kitabin adini giriniz");
	scanf("%s",&kitapAdi);
	
	while(i<MAX_KITAP_SAYISI&&kitaplik[i].kitapSayfasi!=0){
		if(strcmp(kitaplik[i].kitapAdi,kitapAdi)==0){
			printf("Kitap Adi:%s\n",kitaplik[i].kitapAdi);
			printf("Kitap Yazari:%s%s\n",kitaplik[i].kitapYazarAdi,kitaplik[i].kitapYazarSoyadi);
			printf("Kitap Yayinevi:%s\n",kitaplik[i].kitapYayineviAdi);
			printf("Kitap Sayfa Sayisi:%d\n",kitaplik[i].kitapSayfasi);
			if(kitaplik[i].kitapMevcutlukDurumu==0){
				printf("Bu kitap raftadir.");
			}
			else{
				printf("Bu kitap su an mevcut degildir.");
			}
			return;
		}
		i++;
	}
	printf("Aradiginiz Kitap Bulunamadi");
}

void kitapEkle(kitapBilgileri *kitaplik){
	int sayfaSayisi,i;
	char kitapAdi[30],yayinEvi[30],yazarAdi[30],yazarSoyadi[30];
	printf("Lutfen kitap adini giriniz:");
	scanf("%s",&kitapAdi);
	printf("Lutfen kitap yayinevi bilgisini giriniz:");
	scanf("%s",&yayinEvi);
	printf("Lutfen kitabin yazar adini ve soyadini sirasiyla giriniz:");
	scanf("%s %s",&yazarAdi,&yazarSoyadi);
	printf("Lutfen kitabin sayfa sayisini giriniz:");
	scanf("%d",&sayfaSayisi);
	
	for(i=0;i<MAX_KITAP_SAYISI;i++){
		if(kitaplik[i].kitapSayfasi==0){
			kitaplik[i].kitapAdi=(char*)malloc(sizeof(char)*(strlen(kitapAdi)+1));
			kitaplik[i].kitapYayineviAdi=(char*)malloc(sizeof(char)*(strlen(yayinEvi)+1));
			kitaplik[i].kitapYazarAdi=(char*)malloc(sizeof(char)*(strlen(yazarAdi)+1));
			kitaplik[i].kitapYazarSoyadi=(char*)malloc(sizeof(char)*(strlen(yazarSoyadi)+1));
			strcpy(kitaplik[i].kitapAdi,kitapAdi);
			strcpy(kitaplik[i].kitapYazarAdi,yazarAdi);
			strcpy(kitaplik[i].kitapYazarSoyadi,yazarSoyadi);
			strcpy(kitaplik[i].kitapYayineviAdi,yayinEvi);
			kitaplik[i].kitapSayfasi=sayfaSayisi;
			break;	
		}
	}	
}

void uyeleriGoruntule(kisiBilgileri *uyeListesi){
	int i=0;
	while(i<MAX_KISI_SAYISI && uyeListesi[i].kutuphaneID!=0){
		printf("Uye Adi-Soyadi:%s %s\n",uyeListesi[i].kisiAdi,uyeListesi[i].kisiSoyadi);
		printf("Uye ID Bilgisi:%d\n",uyeListesi[i].kutuphaneID);
		if(uyeListesi[i].kisiYetkisi==1){
			printf("Uye Durumu: Calisan\n");
		}
		else{
			printf("Uye Durumu: Ogrenci\n");
		}
		printf("--------------------------------------------------------------------------------------\n");
		i++;	
	}	
}





int main(void){
	char ch;
	int girisDurumu;
	kisiYetkiSeviyeleri uyeYetkisi;



	kitapBilgileri *kitaplik;
	kisiBilgileri *uyeListesi;
	
	kitaplik=(kitapBilgileri*)calloc(MAX_KITAP_SAYISI,sizeof(kitapBilgileri));
	uyeListesi=(kisiBilgileri*)calloc(MAX_KISI_SAYISI,sizeof(kisiBilgileri));
	
	uyeleriAktar(uyeListesi);
	 kitaplariAktar(kitaplik);
	
	// Kayit Ol-Giris Yap //
	printf("************************************************");
	printf("\t\tMerhaba, Kutuphane Sistemimize Hos Geldiniz :)");
	printf("************************************************");
	printf(" Sisteme Kayit olmak icin 'k' tusuna basiniz \n Sisteme uye iseniz giris yapmak icin 'g' tusuna basiniz ");
	fflush(stdin);
	
	ch=getchar();
	if(ch=='K'||ch=='k'){
		girisDurumu=kayitOl(uyeListesi);
	}
	else if(ch=='G'||ch=='g'){
		girisDurumu=girisYap(uyeListesi);
		if(girisDurumu== -1){
			printf("Sifrenizi Yanlis Girdiniz..");
			exit(1);
		}else if(girisDurumu== -2){
			printf("Boyle bir ID bulunamadi!!");
			exit(1);
		}
	}else{
		printf("Hatali Tuslama Yaptiniz..Lutfen Tekrar Deneyin.");
		exit(1);

	}
	
	// Uyenin Yetkisini Belirleme
	if(girisDurumu==1){
		uyeYetkisi=calisan;
	}else{
		uyeYetkisi=musteri;
	}
	
	
	//Musteri Menusu
	if(uyeYetkisi==musteri){
		do{
		printf("1-Tum Kitaplari Goruntulemek Icin 'G' tuslayiniz\n");
		printf("2-Kitaplari Aramak Icin 'A' tuslayiniz\n");
		printf("3-Cikis Yapmak Icin 'Q' tuslayiniz\n");
		
		ch=getchar();
		switch(ch){
			case 'G':
			case 'g':
				kitaplariGoruntule(kitaplik);
				break;
			case 'A':
			case 'a':
				kitapAra(kitaplik);
				break;			
			case 'Q':
			case 'q':
				kitaplariYedekle(kitaplik);
				uyeleriYedekle(uyeListesi);
				printf("Cikis Yapiliyor..");
				break;
			default:
				printf("Hatali Bir Tuslama Yaptiniz..");
				break;
			}
		}while(ch !='Q');
	} 
	
	//Calisan Menusu
	else{
		do{
		printf("1-Kitap Eklemek Icin 'E' tuslayiniz\n");
		printf("2-Tum Uyeleri Goruntulemek Icin 'U' tuslayiniz\n");
		printf("3-Cikis Yapmak Icin 'Q' tuslayiniz\n");
		ch=getchar();
		switch(ch){
			case 'E':
			case 'e':
				kitapEkle(kitaplik);
				break;
			case 'U':
			case 'u':
				uyeleriGoruntule(uyeListesi);
				break;			
			case 'Q':
			case 'q':
				kitaplariYedekle(kitaplik);
				uyeleriYedekle(uyeListesi);
				printf("Cikis Yapiliyor..");
				break;
			default:
				printf("Hatali Bir Tuslama Yaptiniz..");
				break;			
		}
		}while(ch!='Q');
	}
	return 0;
}


























