Arkanoid - Kocaeli Üniversitesi Projesi
Bu proje, Arkanoid oyununun modern C++ ve SFML kütüphanesi kullanılarak geliştirilmiş versiyonudur.

Geliştirici: Taha Çelik - Kocaeli Üniversitesi, Yazılım Mühendisliği

Oyun Hakkında
Oyun, klasik bir tuğla kırma mekaniğine dayalı, bölüm geçişli ve ilerlemeli bir yapıya sahiptir. Oyuncunun temel amacı, topu çubukla kontrol ederek ekrandaki tüm tuğlaları kırmaktır.

Temel Özellikler
Çoklu Bölüm Desteği: levelX.txt dosyaları ile dinamik seviye yükleme.

Ses Efektleri: Tuğla kırılma, menü etkileşimleri ve oyun sonu bildirimleri için ses desteği.

Arayüz Yönetimi: Menü, oyun içi, geçiş ekranı (Transition) ve Game Over durumlarını içeren profesyonel Game State (Durum Makinesi) yönetimi.

Hile Modu: + (Artı) tuşu ile hızlı bölüm geçişi.

Checkpoint Sistemi: Oyuncu yandığında kaldığı bölümden devam edebilme özelliği.

Kontroller
Hareket: A / D tuşları veya Sol / Sağ ok tuşları.

Menü Gezinme: Yukarı / Aşağı ok tuşları.

Seçim: Enter tuşu.

Hızlı İlerleme: + tuşu.

Devam Etme: Space (Boşluk) tuşu.

Teknik Gereksinimler
Dil: C++11 veya üzeri

Kütüphane: SFML 2.5 (Graphics, Window, Audio, System)

Derleme Aracı: CMake (Min. 3.10) ve Make (MinGW/GCC)

Kurulum ve Çalıştırma (CMake)
Proje, çapraz platform derleme aracı olan CMake ile yapılandırılmıştır. Projeyi kendi ortamınızda derlemek için aşağıdaki adımları izleyin:

Proje dosyalarını içeren klasörün ana dizininde bir terminal (CMD, PowerShell veya Git Bash) açın.

CMake ile derleme dosyalarını oluşturmak için şu komutu çalıştırın:

Bash
cmake .
   *(Not: Windows üzerinde MinGW kullanıyorsanız `cmake -G "MinGW Makefiles" .` komutunu kullanabilirsiniz.)*
3. Projeyi derlemek için:
   ```bash
make
(Windows'ta MinGW için: mingw32-make)
4. Derleme tamamlandıktan sonra oluşan Arkanoid.exe (veya Linux/Mac için Arkanoid) dosyasını çalıştırarak oyuna giriş yapabilirsiniz.

⚠️ Önemli Not: Oyunun görsellerinin, bölüm tasarımlarının ve seslerinin eksiksiz yüklenmesi için assets/ klasörünün çalıştırılabilir dosya (.exe) ile aynı ana dizinde bulunduğundan emin olun. Projede mutlak (absolute) dosya yolları kullanılmamış olup, tüm kaynaklar assets/ klasörü üzerinden dinamik olarak çekilmektedir.