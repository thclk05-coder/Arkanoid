Arkanoid - Kocaeli Üniversitesi Projesi
Bu proje, Arkanoid oyununun modern C++ ve SFML kütüphanesi kullanılarak geliştirilmiş versiyonudur.

Geliştirici
Taha Çelik - Kocaeli Üniversitesi, Yazılım Mühendisliği

Oyun Hakkında
Oyun, klasik bir tuğla kırma mekaniğine dayalı, bölüm geçişli ve ilerlemeli bir yapıya sahiptir. Oyuncunun temel amacı, topu çubukla kontrol ederek ekrandaki tüm tuğlaları kırmaktır.

Temel Özellikler
Çoklu Bölüm Desteği: levelX.txt dosyaları ile dinamik seviye yükleme.

Ses Efektleri: Tuğla kırılma, menü etkileşimleri ve oyun sonu bildirimleri için ses desteği.

Arayüz Yönetimi: Menü, oyun içi, geçiş ekranı (Transition) ve Game Over durumlarını içeren profesyonel Game State yönetimi.

Hile Modu: + (Artı) tuşu ile hızlı bölüm geçişi.

Checkpoint Sistemi: Oyuncu yandığında kaldığı bölümden devam edebilme özelliği.

Kontroller
Hareket: A / D tuşları veya Sol / Sağ ok tuşları.

Menü Gezinme: Yukarı / Aşağı ok tuşları.

Seçim: Enter tuşu.

Hızlı İlerleme: + tuşu.

Devam Etme: Space (Boşluk) tuşu.

Teknik Gereksinimler
Dil: C++

Kütüphane: SFML (Graphics, Window, Audio, System)

IDE: Visual Studio (x64 yapılandırması önerilir)

Kurulum ve Çalıştırma
Proje dosyalarını içeren klasörü açın.

.dll dosyalarının (sfml-audio-2.dll dahil) çalışma dizininde olduğundan emin olun.

Visual Studio üzerinde "Release" modunda derleyin.

arkaplan.jpg, font.ttf ve wav dosyalarının tam dizin yollarının kod içerisinde belirtilen (C:\\Users\\thclk\\Desktop\\Arkanoid\\) dizinle eşleştiğini kontrol edin.