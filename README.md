# Philosophers

---

## 🌀 İlham Veren Söz

> **"I never thought philosophy would be so deadly."**

---

Bu proje, çoklu iş parçacığı ve senkronizasyon konularında temel bilgiler edinmeyi hedefler. Filozofların yemek, düşünme ve uyuma döngülerini simüle ederek thread ve mutex yapılarını uygulamalı olarak öğrenmenizi sağlar.

## İçindekiler
- Proje Özeti
- Kurallar ve Gereksinimler
- Projenin Mantığı
- Data Race ve Çözüm Yöntemleri
- Thread ve Mutex Kullanımı
- Giriş Parametreleri
- Log Formatı
- Derleme ve Kullanımı
- Hedefler

## Proje Özeti
Bu proje, filozofların "Düşünen Filozoflar Problemi"ni simüle eder. Filozofların yemek, düşünme ve uyuma döngülerinde veri yarışını önlemeniz ve senkronizasyonu sağlamanız beklenir. Her filozofun açlıktan ölmeden önce yemek yemesi sağlanmalıdır.

## Kurallar ve Gereksinimler
- Dil: Proje tamamen C dilinde yazılmıştır.
- Norm Uyumluluğu: Kod belirtilen norm standartlarına uygun olmalıdır.
- Bellek Yönetimi: Bellek sızıntısına kesinlikle izin verilmez.
- Global Değişkenler: Kullanımı yasaktır.
- İş Parçacıkları ve Mutex:
-- Her filozof bir iş parçacığı (thread) ile temsil edilir.
-- Çatalların paylaşımı mutex yapıları ile korunur.

## Projenin Mantığı
#### 1. Masa Düzeni:
- Masada n filozof ve n çatal bulunur.
- Her filozofun sağında ve solunda bir çatal yer alır.
#### 2. Filozofların Durumları:
- Yemek Yeme: Filozof iki çatalını da alarak yemek yer.
- Uyuma: Yemek bittikten sonra çatalları masaya bırakır ve uyumaya geçer.
- Düşünme: Uyandıktan sonra yeniden düşünmeye başlar.
#### 3. Simülasyon Kuralları:
- Filozoflar birbirleriyle konuşmaz.
- Simülasyon bir filozof öldüğünde sona erer.

## Data Race ve Çözüm Yöntemleri
Data Race (veri yarışı), aynı veri üzerinde birden fazla iş parçacığının aynı anda işlem yapmaya çalışması ve bu işlemlerin sıralamasının belirsiz olması durumudur. Bu durum, hatalı sonuçlara veya program çökmesine yol açabilir.
### Data Race Nedenleri:
- Paylaşılan belleğe aynı anda erişim.
- Bellek yazma ve okuma işlemleri arasında senkronizasyon eksikliği.
- Bir iş parçacığının yazdığı verinin diğer iş parçacığı tarafından okunması.

### Çözüm:
#### 1. Mutex Kullanımı:
- pthread_mutex_lock() ve pthread_mutex_unlock() fonksiyonları ile paylaşılan verilere erişim sırasını kontrol edin.
- Örneğin, bir filozofun çatalları alması ve bırakması işlemleri mutex ile korunmalıdır.
#### 2. Thread Güvenli Kodlama:
- Her iş parçacığı kendi özel değişkenlerini kullanmalıdır.
- Paylaşılan kaynaklar için yalnızca senkronize işlemler yapılmalıdır.
#### 3. Atomik İşlemler:
- Eğer mümkünse, atomik işlemler kullanarak veri yarışını önleyebilirsiniz.

## Thread ve Mutex Kullanımı
### Thread Kullanımı
Bir filozofun davranışlarını bir iş parçacığı (thread) ile simüle edeceksiniz. İş parçacıkları pthread_create fonksiyonu ile oluşturulur:
```c
pthread_t thread;
pthread_create(&thread, NULL, thread_function, (void *)argument);
```
- thread: İş parçacığı kimliğini saklar
- thread_function: İş parçacığının çalıştıracağı fonksiyon.
- argument: Fonksiyona geçirilecek argüman.
İş parçacığının sonlandırılması için pthread_join veya pthread_detach kullanılır.
### Mutex Kullanımı
Bir filozofun çatallara erişimini kontrol etmek için mutex kullanılır. Mutex şu şekilde başlatılır ve kullanılır:
##### 1. Başlatma:
```c
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);
```
##### 2. Kilitleme ve Kilit Açma:
```c
pthread_mutex_lock(&mutex);   // Kaynak erişimi başlatılır
// Paylaşılan kaynak üzerinde işlem
pthread_mutex_unlock(&mutex); // Kaynak erişimi bitirilir
```
##### 3. Yok Etme:
```c
pthread_mutex_destroy(&mutex);
```
## Giriş Parametreleri
```c
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## Log Formatı
```css
[timestamp_in_ms] [philosopher_number] [action]
```
```bash
200 1 has taken a fork
210 1 is eating
300 1 is sleeping
```
## Derleme ve Kullanım

### 1. Derleme:
```bash
make
```
### 2. Kullanım:
```bash
./philo <arguments>
```
### 3. Örnek:
```bash
./philo 5 800 200 200
```
## Hedefler
- İş Parçacıkları: İş parçacıklarını (pthread) kullanarak paralel işlem yapmayı öğrenmek.
- Veri Yarışı Yönetimi: mutex kullanarak veri yarışlarını önlemek.
- Senkronizasyon: Kritik bölge koruması ve kaynak paylaşımı üzerinde çalışmak.
