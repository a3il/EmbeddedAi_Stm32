#include "NanoEdgeAI.h"
#include "knowledge.h"
#include <Nokia_LCD.h>

void Button_press(void);
typedef enum
{
  LOG,
  INFERENCE,
} States_t;

#define CONFIRMATIONS_NB         (uint32_t)(3)  /* Number of consecutive confirmations */

Nokia_LCD lcd(D13 /* CLK */, D11 /* DIN */, D2 /* DC */, D4 /* CE */, D3/* RST */, D7 /* BL */);
float mic_buffer[DATA_INPUT_USER * AXIS_NUMBER] = { 0 };
float mic_x = 0.F;

float output_class_buffer[CLASS_NUMBER]; // Buffer of class probabilities
const char *id2class[CLASS_NUMBER + 1] = { // Buffer for mapping class id to class name
  "unknown",
  "Ambulance",
  "Baby Cry",
  "No Input",
};



void Inference(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  lcd.begin();
  // Turn on the backlight
  lcd.setBacklight(true);
  // Set the contrast
  lcd.setContrast(60);  // Good values are usualy between 40 and 60
  // Clear the screen by filling it with black pixels
  lcd.clear(false);
  
  enum neai_state error_code = neai_classification_init(knowledge);
  if (error_code!=NEAI_OK)
  {
    Serial.print("Knowledge initialization ERROR:");
    Serial.println(error_code);
  }
  else
  {
    Serial.println("Knowledge initialization DONE:");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Inference();  
}

void read_mic()
  {
   unsigned int data;
   data=analogRead(A0);
   mic_x= data;
}

void fill_mic_buffer() {
  
      for (int i = 0; i < DATA_INPUT_USER; i++) 
      {
        read_mic();
        mic_buffer[AXIS_NUMBER * i] = mic_x;
        delay(3);
      }
}
void Inference(void)
{
  uint16_t i,id_class_t0,id_class_tn;

  fill_mic_buffer();
  neai_classification(mic_buffer,output_class_buffer,&id_class_t0);
  for (i=0;i<CONFIRMATIONS_NB-1;i++)
  {
    fill_mic_buffer();
    neai_classification(mic_buffer,output_class_buffer,&id_class_tn);
    if (id_class_t0 != id_class_tn) { break; }
  }
  if (id_class_t0 == id_class_tn)
  {
    lcd.setCursor(2, 5);
    lcd.clear(false);
    delay(50);
    lcd.print("Detected Class:");
    lcd.print(id2class[id_class_t0]);
    Serial.print("Detected Class:");
    Serial.println(id2class[id_class_t0]);
  }
  else
  {
    Serial.println("?");
    lcd.setCursor(0, 5);
    lcd.clear(false);
    delay(50);
    lcd.print("?");
  }
}
