#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

#define green_button 16
#define red_button 17

#define green_relay 21
#define red_relay 22

#define green_light 33
#define red_light 32

Audio audio;

long shutOffTime = 0; 
int lightTime = 1500; 



void setup() {
  pinMode(SD_CS, OUTPUT);      digitalWrite(SD_CS, HIGH);
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  Serial.begin(115200);
  Serial.println("Hello");
  SD.begin(SD_CS);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21); // default 0...21

  audio.connecttoFS(SD, "/green.wav");     // SD

  pinMode(green_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_relay, OUTPUT);
  pinMode(red_relay, OUTPUT);
  pinMode(green_light, OUTPUT);
  pinMode(red_light, OUTPUT);

}

void loop()
{
if (millis()>shutOffTime){
      digitalWrite(green_relay, LOW);
    digitalWrite(red_relay, LOW);
    digitalWrite(green_light, LOW);
    digitalWrite(red_light, LOW);
}


  if (digitalRead(green_button) == LOW) { // Assuming pull-up, press = LOW
    shutOffTime = millis()+lightTime; 
    Serial.println("Playing green.wav");
    audio.connecttoFS(SD, "/green.wav");
    digitalWrite(green_relay, HIGH);
    digitalWrite(red_relay, LOW);
    digitalWrite(green_light, HIGH);
    digitalWrite(red_light, LOW);
    delay(100); // Debounce delay
    while (digitalRead(green_button) == LOW); // Wait for button release
   // delay(5000); 

  }

  if (digitalRead(red_button) == LOW) { // Assuming pull-up, press = LOW
    shutOffTime = millis()+lightTime; 
    Serial.println("Playing red.wav");
    audio.connecttoFS(SD, "/red.wav");
    digitalWrite(green_relay, LOW);
    digitalWrite(red_relay, HIGH);
    digitalWrite(green_light, LOW);
    digitalWrite(red_light, HIGH);
    delay(100); // Debounce delay
    while (digitalRead(red_button) == LOW); // Wait for button release
   // delay(5000); 

  }
  audio.loop();
}

// optional
void audio_info(const char *info) {
  Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info) { //id3 metadata
  Serial.print("id3data     "); Serial.println(info);
}
void audio_eof_mp3(const char *info) { //end of file
  Serial.print("eof_mp3     "); Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     "); Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle "); Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     "); Serial.println(info);
}
void audio_commercial(const char *info) { //duration in sec
  Serial.print("commercial  "); Serial.println(info);
}
void audio_icyurl(const char *info) { //homepage
  Serial.print("icyurl      "); Serial.println(info);
}
void audio_lasthost(const char *info) { //stream URL played
  Serial.print("lasthost    "); Serial.println(info);
}
void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  "); Serial.println(info);
}
