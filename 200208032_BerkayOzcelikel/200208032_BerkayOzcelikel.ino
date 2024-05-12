#include <WiFi.h>
#include <WebServer.h>  //kütüphaneleri include ettim.
#include <DHT.h>

const char* ssid = "Berkay iPhone’u";  //Bağlanacağım wifi ağının adı ve şifresini yazdım.
const char* password = "A1B2C3D4";

WebServer server(80); //Web serverı oluşturuyor.   
DHT dht(27, DHT11);  //DHT11 sensörünü ve pini tanımladım.

String pin32State = "off"; //pin32'yi başlangıçta kapalı konumda başlattım.
String pin33State = "off"; //pin33'ü başlangıçta kapalı konumda başlattım.
String pin26State = "off"; //pin26'yı başlangıçta kapalı konumda başlattım.

const int output32 = 32; //32. pini output olarak tanımladım.
const int output33 = 33; //33. pini output olarak tanımladım.
const int output26 = 26; //26. pini output olarak tanımladım.

void setup() {
  Serial.begin(115200); // Seri haberleşmeyi başlatır.
  dht.begin(); //DHT sensörünün başlatılması için bir çağrıdır.
  
  pinMode(output32, OUTPUT); //Belirtilen pinlerin çıkış olarak yapılandırılmasını sağlar.
  pinMode(output33, OUTPUT);
  pinMode(output26, OUTPUT);
  digitalWrite(output32, LOW); //Çıkış pinlerinin başlangıç durumunu ayarlar. Bu kodda, pinlerin başlangıç ​​durumu "LOW" olarak ayarlanmıştır, yani çıkışları devre dışı bırakır.
  digitalWrite(output33, LOW);
  digitalWrite(output26, LOW);

  WiFi.mode(WIFI_STA); //istemci (client) modunu belirtir. Ardından, belirli bir SSID ve şifreyle ağa bağlanılır. Bağlantı sağlanana kadar bağlantı durumu sürekli kontrol edilir.
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Bağlanılıyor... ");
  Serial.println(ssid);
  Serial.print("IP adres: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); //Web sunucusu için yönlendirmeler tanımlanır.
  server.on("/32/on", HTTP_GET, []() {
    digitalWrite(output32, HIGH);
    pin32State = "on";
    server.send(200, "text/plain", "GPIO 32 is now on");
  });
  server.on("/32/off", HTTP_GET, []() {
    digitalWrite(output32, LOW);
    pin32State = "off";
    server.send(200, "text/plain", "GPIO 32 is now off");
  });
  server.on("/33/on", HTTP_GET, []() {
    digitalWrite(output33, HIGH);
    pin33State = "on";
    server.send(200, "text/plain", "GPIO 33 is now on");
  });
  server.on("/33/off", HTTP_GET, []() {
    digitalWrite(output33, LOW);
    pin33State = "off";
    server.send(200, "text/plain", "GPIO 33 is now off");
  });
  server.on("/26/on", HTTP_GET, []() {
    digitalWrite(output26, HIGH);
    pin26State = "on";
    server.send(200, "text/plain", "GPIO 26 is now on");
  });
  server.on("/26/off", HTTP_GET, []() {
    digitalWrite(output26, LOW);
    pin26State = "off";
    server.send(200, "text/plain", "GPIO 26 is now off");
  });

  server.begin();
  Serial.println("HTTP server başlatıldı");
}

void loop() {
  server.handleClient(); // Bu satır, web sunucusuna gelen istekleri işler. Eğer bir istek varsa, bu isteği işler ve gerekli yanıtı oluşturur. Eğer bir istek yoksa, bu işlev bekleme durumunda kalır.
  updateSensorReadings(); // Bu satır, sensörden okunan verilerin güncellenmesini sağlar. 
  delay(2000); // Bu satır, her döngüde 2 saniyelik bir gecikme ekler.
}

void handleRoot() {
  char msg[1500];
  snprintf(msg, 1500,
           "<html>\
  <head>\
    <meta http-equiv='refresh' content='4'/>\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>\
    <title>ESP32 Led Switchleme</title>\
    <style>\
    html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\
    h2 { font-size: 3.0rem; }\
    p { font-size: 3.0rem; }\
    .units { font-size: 1.2rem; }\
    .dht-labels{ font-size: 1.5rem; vertical-align:middle; padding-bottom: 15px;}\
    </style>\
  </head>\
  <body>\
      <h2>ESP32 Led Switchleme</h2>\
      <p>\
        <i class='fas fa-thermometer-half' style='color:#ca3517;'></i>\
        <span class='dht-labels'>Sicaklik</span>\
        <span>%.2f</span>\
        <sup class='units'>&deg;C</sup>\
      </p>\
      <p>\
        <i class='fas fa-tint' style='color:#00add6;'></i>\
        <span class='dht-labels'>Nemlilik Orani</span>\
        <span>%.2f</span>\
        <sup class='units'>&percnt;</sup>\
      </p>\
      <p>GPIO 32 - State %s</p>\
      <p><a href=\"/32/on\"><button>Acik</button></a> <a href=\"/32/off\"><button>Kapali</button></a></p>\
      <p>GPIO 33 - State %s</p>\
      <p><a href=\"/33/on\"><button>Acik</button></a> <a href=\"/33/off\"><button>Kapali</button></a></p>\
      <p>GPIO 26 - State %s</p>\
      <p><a href=\"/26/on\"><button>Acik</button></a> <a href=\"/26/off\"><button>Kapali</button></a></p>\
  </body>\
</html>",
           readDHTTemperature(), readDHTHumidity(), pin32State.c_str(), pin33State.c_str(), pin26State.c_str()
          );
  server.send(200, "text/html", msg);
}

float readDHTTemperature() { //Fonksiyon, sensörden sıcaklık değerini okur ve bu değeri döndürür.
  float t = dht.readTemperature(); // Bu satır, DHT sensöründen sıcaklık okumasını yapar ve sonucu t adlı bir değişkene atar.
  if (isnan(t)) {   //Bu satır, okunan sıcaklık değerinin geçerli olup olmadığını kontrol eder. 
    Serial.println("DHT sensöründen okunamadı!"); 
    return -1;
  }
  else {
    Serial.print("Sıcaklık: "); // Eğer t değişkeni geçerli bir sayıysa, yani sensörden geçerli bir sıcaklık okunmuşsa, bu blok çalışır. Bu durumda, okunan sıcaklık değeri seri monitöre yazılır ve bu değer döndürülür.
    Serial.println(t);
    return t;
  }
}

float readDHTHumidity() { // Bu fonksiyon, sensörden ölçülen nem değerini döndürür.
  float h = dht.readHumidity(); //Bu satır, DHT sensöründen nem ölçümü yapar ve sonucu h adlı bir değişkene atar.
  if (isnan(h)) { //Bu satır, okunan nem değerinin geçerli olup olmadığını kontrol eder.
    Serial.println("DHT sensöründen okunamadı!");
    return -1;
  }
  else {
    Serial.print("Nemlilik: "); // Eğer h değişkeni geçerli bir sayıysa, yani sensörden geçerli bir nem okunmuşsa, bu blok çalışır. Bu durumda, okunan nem değeri seri monitöre yazılır ve bu değer döndürülür.
    Serial.println(h);
    return h;
  }
}

void updateSensorReadings() { // Bu, sensör okumalarını güncellemek için kullanılan bir fonksiyon tanımıdır.
  // Herhangi bir ek işlem yapmanız gerekiyorsa sensör okumalarını buradan okuyun
  // Bu işlev, loop() işlevinin her yinelemesinde çağrılır.
  // Yalnızca sensör değerlerini işlemeden okumanız gerekiyorsa, handRoot() işlevinde doğrudan readDHTTemperature() ve readDHTHumidity() öğesini çağırabilirsiniz..
}
