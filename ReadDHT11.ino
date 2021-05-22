#include "DHT.h"
#define DHTPIN 5      // Chân DATA nối với chân D3
#define DHTTYPE DHT11  

// Khởi tạo cảm biến
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Khởi tạo cổng serial baud 115200
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  // Bắt đầu đọc dữ liệu
  dht.begin();
}

void loop() {
  // Đợi chuyển đổi dữ liệu khoảng 2s
  delay(2000);
  float h = dht.readHumidity();        // Đọc giá trị nhiệt độ ẩm (%)
  float t = dht.readTemperature();     // Đọc giá trị nhiệt độ C (mặc định)
  float f = dht.readTemperature(true); // Đọc giá trị nhiệt độ F(isFahrenheit = true)

  // Kiểm tra quá trình đọc thành công hay không
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // IN thông tin ra màn hình
  Serial.print("Do am: ");
  Serial.print(h);
  Serial.print(" %\t\t");
  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print(" *C");
  Serial.print("\t");
  Serial.print(f);
  Serial.println(" *F");
}
