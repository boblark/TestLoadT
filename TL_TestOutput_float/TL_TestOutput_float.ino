/* TestOutput_float.ino  Bob Larkin 3 July 2020
 * 
 */
#include <Audio.h>
#include <TL_OpenAudio_ArduinoLibrary.h>


// *****************  PLACE TO CHANGE  *****************
// If begin() is in constructor, i.e., BEGIN_IN_CONSTRUCTOR==1  load fails
// If begin() is in setup(), i.e., BEGIN_IN_CONSTRUCTOR==0  all is OK
// Change by next define 1 or 0
#define BEGIN_IN_CONSTRUCTOR 0
// *****************************************************


AudioSynthWaveformSine_F32  sine1;
TL_AudioOutputI2S_OA_F32    i2sOut(BEGIN_IN_CONSTRUCTOR);
AudioConnection_F32         patchCord1(sine1, 0, i2sOut, 0);
AudioControlSGTL5000        sgtl5000_1;

void setup(void) {
  Serial.begin(9600);   delay(1000);  // Any speed is OK
  Serial.print("Test load of F32 out with ");
  if (BEGIN_IN_CONSTRUCTOR)
     Serial.println("call to begin() in TL_AudioOutputI2S_OA_F32 constructor.");
  else
     Serial.println("call to begin() in setup().");
  AudioMemory(10);
  AudioMemory_F32(10);

  // Next line, moved from constructor, allows Loader to operate without crash
  if(!BEGIN_IN_CONSTRUCTOR) i2sOut.begin();
  
  sgtl5000_1.enable();
  
  sine1.frequency(300.0);  sine1.amplitude(0.005f);
  sine1.begin();
} 

void loop() {
}
