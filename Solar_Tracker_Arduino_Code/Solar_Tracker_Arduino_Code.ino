/*
  * Project: Power Optimization of Photovoltaic Systems Using a Single-Axis Solar Tracker and AM-P&O Based MPPT
  * Module: Single-Axis Solar Tracker Control Code
  * Author: Lanang Timur Anjo
  */

#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <math.h>

// --- PIN MAPPING & OBJECT INSTANTIATION ---
const int pinServoKanan = 9;   // PWM signal for right-side servo motor control
const int pinServoKiri = 10;   // PWM signal for left-side servo motor control

RTC_DS3231 rtc;
Servo servoKanan;
Servo servoKiri;

// --- GEOGRAPHICAL & MECHANICAL PARAMETERS ---
const float phi = -7.77;       // Latitude coordinate of the test location (Yogyakarta)
const int limit_rotasi = 60;   // Maximum mechanical rotation angle limit of the device

int posKananSekarang = 90;     // Actual angle register value for central position (perpendicular reference)
int posKiriSekarang = 90;
const int jedaGerak = 50;      // Servo movement transition delay constant (ms/degree)

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  if (!rtc.begin()) {
    while (1); // Halt the program if the I2C communication circuit fails to detect
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Execute soft-start function for initial mechanical chassis alignment
  softStartTo90();
}

void loop() {
  DateTime now = rtc.now();

  // Convert real-time data into a continuous decimal format
  float jamDesimal = now.hour() + (now.minute() / 60.0) + (now.second() / 3600.0);
  int n = hitungHariKe(now.day(), now.month(), now.year());

  // Theoretical calculation of the optimal tilt angle for solar irradiance absorption (Rho)
  float rho = hitungSudutTracker(jamDesimal, n);

  // Determination of symmetrical target position orientation parameters (Mirroring Logic)
  int targetKanan = 90 + rho;
  int targetKiri = 90 - rho;

  // Drive the physical position of the actuator incrementally and smoothly towards the solar reference
  gerakkanKeTarget(targetKanan, targetKiri);

  // Telemetry monitoring output
  Serial.print("Jam: "); Serial.print(jamDesimal);
  Serial.print(" | Target Rho: "); Serial.print(rho);
  Serial.print(" | R: "); Serial.print(posKananSekarang);
  Serial.print(" | L: "); Serial.println(posKiriSekarang);

  delay(5000);
}

// --- INITIAL SMOOTH TRANSITION ROUTINE (SOFT-START) ---
void softStartTo90() {
  servoKanan.attach(pinServoKanan);
  servoKiri.attach(pinServoKiri);

  // Soft-start the mechanical chassis to 90 degrees for safety
  servoKanan.write(90);
  servoKiri.write(90);

  delay(1000);
}

// --- INCREMENTAL SMOOTH TRANSITION CONTROL FUNCTION ---
void gerakkanKeTarget(int targetKanan, int targetKiri) {
  while (posKananSekarang != targetKanan || posKiriSekarang != targetKiri) {
    
    if (posKananSekarang < targetKanan) posKananSekarang++;
    else if (posKananSekarang > targetKanan) posKananSekarang--;

    if (posKiriSekarang < targetKiri) posKiriSekarang++;
    else if (posKiriSekarang > targetKiri) posKiriSekarang--;

    servoKanan.write(posKananSekarang);
    servoKiri.write(posKiriSekarang);

    delay(jedaGerak);
  }
}

// --- SOLAR GEOMETRY KINEMATICS MATHEMATICAL FORMULATION ---
float hitungSudutTracker(float jam, int n) {
  if (jam <= 6.0 || jam >= 18.0) return 0; // Operational time restriction (Sun below horizon)

  // Calculation of declination angle (Delta) and hour angle (Omega) parameters
  float delta = 23.45 * sin(radians(360.0 * (284.0 + n) / 365.0));
  float omega = 15.0 * (jam - 12.0);

  // Calculation of solar elevation function projection
  float sin_alpha = sin(radians(phi)) * sin(radians(delta)) + 
                    cos(radians(phi)) * cos(radians(delta)) * cos(radians(omega));

  if (sin_alpha > 0) {
    float tan_rho = (cos(radians(delta)) * sin(radians(omega))) / sin_alpha;
    float rho = degrees(atan(tan_rho));
    return constrain(rho, -limit_rotasi, limit_rotasi); // Restrict mechanical motion range
  } else {
    return 0;
  }
}

// --- JULIAN DAY CALCULATION AND LEAP YEAR EVALUATION ---
int hitungHariKe(int d, int m, int y) {
  int days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int n = days[m - 1] + d;
  if (m > 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) n++; // Day addition compensation for leap years
  return n;
}