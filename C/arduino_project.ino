#include <Servo.h>
#include <DHT.h>

#define DHTPIN 7  
#define DHTTYPE DHT11 

int gndPin = A0;
int vccPin = A1;
int xPin = A2;
int yPin = A3;
int swPin = A4;
int servoPin = 10;
int buzzerPin = 9;
int triggerPin = 5;
int echoPin = 6;
int ledPin = 2;

bool ledState = false;  // LED 토글 상태 저장

int hzData[8] = {262, 294, 330, 349, 392, 440, 494, 523}; // 도레미파솔라시도

Servo myServo;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(gndPin, OUTPUT);
  pinMode(vccPin, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);
  dht.begin();

  digitalWrite(gndPin, LOW);
  digitalWrite(vccPin, HIGH);
}

float getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms 이상 응답 없으면 타임아웃
  float distance = duration * 0.034 / 2;

  if (distance > 400 || distance <= 0) return -1; // 유효한 범위(0~400cm) 확인
  return distance;
}

void loop() {
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);
  int swState = digitalRead(swPin);

  //  부저 - 조이스틱 위로 이동하면 도레미파솔라시도 소리
  if (yRaw > 512) {
    for (int i = 0; i < 8; i++) {
      tone(buzzerPin, hzData[i]);
      delay(200);
    }
    noTone(buzzerPin);
  }

  // 온습도 센서 - 조이스틱 X축 오른쪽
  if (xRaw > 513) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {
      Serial.print("온도: ");
      Serial.print(temp);
      Serial.print("°C\t습도: ");
      Serial.print(hum);
      Serial.println("%");
    } else {
      Serial.println("센서 오류! 다시 시도 중...");
      delay(200);
    }
  }

  // 초음파 센서 - 조이스틱 아래로 이동
  if (yRaw < 500) {
    float distance = getDistance();
    if (distance != -1) {
      Serial.print("거리: ");
      Serial.print(distance);
      Serial.println("cm");

      if (distance < 30.0) { // 30cm 이하 시 경고음
        tone(buzzerPin, 1000);
        delay(500);
        noTone(buzzerPin);
      }
    } else {
      Serial.println("초음파 센서 오류! 측정 실패");
    }
    delay(500);
  }

  // 서보모터 제어 - 조이스틱 X축 이동
  int servoAngle = map(xRaw, 0, 1023, 0, 180);
  myServo.write(servoAngle);

  // 버튼을 누르면 LED 토글 (한 번 누르면 켜지고 다시 누르면 꺼짐)
  static bool lastButtonState = HIGH;  // 버튼 이전 상태
  if (swState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;  // LED 상태 반전
    digitalWrite(ledPin, ledState);
    delay(200);  // 디바운싱
  }
  lastButtonState = swState;
}
