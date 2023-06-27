#include <DFRobot_RGBLCD1602.h>

#define BUTTON 3
#define UV_SENSOR A1

DFRobot_RGBLCD1602 lcd(16, 2);

int I_B;
float I_uv_index;
String sensor_St;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.print("Portable");

  lcd.setCursor(0, 1);
  lcd.print("UV Radiometer");

  pinMode(UV_SENSOR, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  

  if (digitalRead(BUTTON) == LOW) {
    // Serial.print("GUVA : ");
    // Serial.print(GUVA);
    // Serial.print(" / GUVA_UV : ");
    // Serial.println(GUVA_UV);

    Serial.print("Button : ");
    Serial.println(digitalRead(BUTTON));
    Serial.print("I_B : ");
    Serial.println(I_B);

    switch (I_B) {
      case (1):
        {
          lcd.init();
          lcd.print("Want to Measure?");
          lcd.setCursor(0, 1);
          lcd.print("Press Button!");
        }
        break;
      case (2):
        {
          lcd.init();
          lcd.print("UV SENSING...");
          lcd.setCursor(0, 1);
          lcd.print("Please Wait...");

          delay(500);

          lcd.clear();
          lcd.print("UV Sensing:");
          while (1) {
            float GUVA = analogRead(A1);
  float GUVA_UV = GUVA / 47.43;  //255/5*0.93
            lcd.setCursor(12, 0);
            lcd.print("      ");
            lcd.setCursor(12, 0);
            lcd.print(GUVA_UV);
            lcd.setCursor(0, 1);
            if (GUVA_UV >= 0 && GUVA_UV < 6) {
              lcd.setRGB(0, 255, 0);
              lcd.print("Safe");
              lcd.setCursor(4, 1);
              lcd.print("  ");
              I_uv_index = GUVA_UV;
              sensor_St = "Safe";
            } else if (GUVA_UV >= 6 && GUVA_UV < 11) {
              lcd.setRGB(255, 255, 0);
              lcd.print("Alert");
              lcd.setCursor(5, 1);
              lcd.print(" ");
              I_uv_index = GUVA_UV;
              sensor_St = "Alert";

            } else if (GUVA_UV >= 11) {
              lcd.setRGB(255, 0, 0);
              lcd.print("Danger");
              I_uv_index = GUVA_UV;
              sensor_St = "Danger";
            }
            if (digitalRead(BUTTON) == LOW) break;
            ////////////////////////
          }
        }
        break;
      case (3):
        {
          lcd.clear();
          lcd.print("UV Index:");
          lcd.setCursor(10, 0);
          lcd.print(I_uv_index);

          lcd.setCursor(0, 1);
          lcd.print(sensor_St);
        }
        break;
      case (4):
        {
          lcd.init();
          lcd.print("LCD OFF");
          delay(300);
          lcd.print(".");
          delay(300);
          lcd.print(".");
          delay(300);
          lcd.print(".");
          delay(300);
          lcd.print(".");
          delay(500);
          lcd.setBacklight(false);
        }
        break;
    }
    if (I_B < 4) I_B += 1;
    else I_B = 0;
  }
}