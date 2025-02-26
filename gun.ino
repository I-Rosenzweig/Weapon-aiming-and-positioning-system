#include <Wire.h>
#include <MPU6050.h>


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);


#define TRIG_PIN 4
#define ECHO_PIN 2
#define BUTTON_PIN 3
#define LED_YELLOW 8
#define LED_GREEN 9
#define LED_RED 10

MPU6050 mpu;
bool waitingForAlignment = false;
float savedDistance = 0;
float savedTilt = 0; // Variable to store the tilt angle at the time of measurement
const float bulletSpeed = 7.67; // m/s
float gunHeight=1.70;
const float g = 9.81; // Gravity

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    Wire.begin();
    mpu.initialize();
    
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
    Serial.println("MPU6050 connected.");

    if (!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
        Serial.println("SSD1306 allocation failed");
        //delay(1000);  // Small delay
        while (1);
    }
    display.clearDisplay();
    display.display();

}

void getDistance(float* distance) {
    long duration;
    int attempts = 10;
    float total = 0;

    for (int i = 0; i < attempts; i++) {
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(20);
        duration = pulseIn(ECHO_PIN, HIGH, 30000);

        if (duration == 0) {
            Serial.println("Echo Timeout! No valid reading.");
            *distance = -1;
            return;
        }

        total += ((duration * 0.0343) / 2);
        delay(10);
    }

    *distance = total / attempts;
    *distance /=100;
    Serial.print("Measured Distance: ");
    Serial.print(*distance);
    Serial.println(" meters");
}

void getTiltAngle(float* tilt) {
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);

    *tilt = atan2(ax, ay) * 180.0 / PI;
    Serial.print("Tilt Angle: ");
    Serial.print(*tilt);
    Serial.println(" degrees");
}

float calculateTrajectory(float distance, float angle) {
    float theta = angle * PI / 180.0;
    float height = distance * tan(theta) - (g * pow(distance, 2)) / (2 * pow(bulletSpeed, 2) * pow(cos(theta), 2));
    Serial.print("Predicted Bullet Height: ");
    Serial.print(height);
    Serial.println(" meters");
    return height;
}



void indicateAlignment(float error) {
    if (error > 0.5) {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_YELLOW, LOW);
    } else if (error < -0.5) {
        digitalWrite(LED_YELLOW, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, LOW);
    } else {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, LOW);
    }
}

void updateDisplay(float distance, float tilt, float bulletHeight, float error) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Dist: "); display.print(distance); display.println(" m");
    display.print("Tilt: "); display.print(tilt); display.println(" deg");
    display.print("Bullet H: "); display.print(bulletHeight); display.println(" m");
    display.print("Error: "); display.print(error); display.println(" m");
    display.display();
}
void loop() {
    static bool buttonPressed = false;
    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(100);
        if (!buttonPressed) {
            buttonPressed = true;
            if (!waitingForAlignment) {
                getDistance(&savedDistance);
                getTiltAngle(&savedTilt);    // Save the tilt angle at the time of measurement
                waitingForAlignment = true;
                Serial.println("Target distance saved. Adjust your aim...");
            } else {
                waitingForAlignment = false;
                Serial.println("Canceled. Ready for new measurement.");
                display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("No Target ");
                display.display();
            }
        }
    } else {
        buttonPressed = false;
    }
    if (waitingForAlignment) {
        float currentDistance, tilt;
        //getDistance(&currentDistance);
        getTiltAngle(&tilt);

        //float bulletHeight = calculateTrajectory(currentDistance, tilt);
        float bulletHeight = calculateTrajectory(savedDistance, tilt);
        float targetHeight = calculateTrajectory(savedDistance, savedTilt);
        float error = targetHeight - bulletHeight;

        indicateAlignment(error);
        updateDisplay(savedDistance, tilt, bulletHeight, error);
    }
}
