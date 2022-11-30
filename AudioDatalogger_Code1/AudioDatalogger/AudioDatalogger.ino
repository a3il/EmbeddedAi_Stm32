/*Read analog samples from A0 channel and store
 * the converted digital samples in a buffer of 512 samples.
 * Display the buffer(sensor samples) on Serial
 * Monitor. 
 */
#define DATA_INPUT_USER 512 //buffer size
#define AXIS_NUMBER 1

float mic_buffer[DATA_INPUT_USER * AXIS_NUMBER] = { 0 };
float mic_x = 0.F;
void read_mic(void);//function prototype to read microphone
void fill_mic_buffer(void);//function to fill buffer with audio samples
void Log(void);//function prototype to log the audio samples

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 Log();
}

void read_mic()
{
  unsigned int data;
  data=analogRead(A0);
  mic_x=data;
  }

void fill_mic_buffer() {
  
      for (int i = 0; i < DATA_INPUT_USER; i++) 
      {
        read_mic();
        mic_buffer[AXIS_NUMBER * i] = mic_x;
        delay(3);
      }
}

void Log()
{
  fill_mic_buffer();
  for (int i = 0; i < DATA_INPUT_USER; i++) {
  Serial.print(mic_buffer[AXIS_NUMBER * i]);
  Serial.print(" ");
  }
  Serial.println();
}
