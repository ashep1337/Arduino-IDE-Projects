// ESP32-S3 Full Super Mario Bros Theme Player
// Connect speaker between GPIO8 and GND (optionally with 10-100Ω resistor)

const int speakerPin = 2;

// Note frequencies
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define REST     0

// Full Super Mario Bros main theme melody
int melody[] = {
  // Intro
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5, REST,
  NOTE_G5, REST, REST, REST, NOTE_G4, REST, REST, REST,
  
  // Part 1
  NOTE_C5, REST, REST, NOTE_G4, REST, REST, NOTE_E4, REST,
  REST, NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST,
  NOTE_G4, NOTE_E5, REST, NOTE_G5, NOTE_A5, REST, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, REST, NOTE_C5, NOTE_D5, NOTE_B4, REST, REST,
  
  // Part 2
  NOTE_C5, REST, REST, NOTE_G4, REST, REST, NOTE_E4, REST,
  REST, NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST,
  NOTE_G4, NOTE_E5, REST, NOTE_G5, NOTE_A5, REST, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, REST, NOTE_C5, NOTE_D5, NOTE_B4, REST, REST,
  
  // Bridge
  REST, REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, REST, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C5, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, REST, NOTE_E5,
  REST, NOTE_C6, REST, NOTE_C6, NOTE_C6, REST, REST, REST,
  
  REST, REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, REST, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C5, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, REST, NOTE_DS5, REST, REST, NOTE_D5, REST, REST,
  NOTE_C5, REST, REST, REST, REST, REST, REST, REST,
  
  // Repeat Part 1
  NOTE_C5, REST, REST, NOTE_G4, REST, REST, NOTE_E4, REST,
  REST, NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST,
  NOTE_G4, NOTE_E5, REST, NOTE_G5, NOTE_A5, REST, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, REST, NOTE_C5, NOTE_D5, NOTE_B4, REST, REST,
  
  // Repeat Part 2
  NOTE_C5, REST, REST, NOTE_G4, REST, REST, NOTE_E4, REST,
  REST, NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST,
  NOTE_G4, NOTE_E5, REST, NOTE_G5, NOTE_A5, REST, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, REST, NOTE_C5, NOTE_D5, NOTE_B4, REST, REST,
  
  // Ending
  NOTE_E5, NOTE_C5, REST, NOTE_G4, REST, REST, NOTE_GS4, REST,
  NOTE_A4, NOTE_F5, REST, NOTE_F5, NOTE_A4, REST, REST, REST,
  NOTE_B4, NOTE_A5, REST, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, REST, NOTE_A4, NOTE_G4, REST, REST, REST
};

// Note durations
int durations[] = {
  // Intro
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Part 1
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  12, 12, 12, 12, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Part 2
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  12, 12, 12, 12, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Bridge
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Repeat Part 1
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  12, 12, 12, 12, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Repeat Part 2
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  12, 12, 12, 12, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  
  // Ending
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8
};

void setup() {
  ledcAttach(speakerPin, 1000, 8);  // Initialize PWM
}

void loop() {
  // Play the full Mario theme
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / durations[i];
    
    if (melody[i] == REST) {
      delay(noteDuration);
    } else {
      ledcWriteTone(speakerPin, melody[i]);
      delay(noteDuration);
      
      // Short pause between notes
      ledcWriteTone(speakerPin, 0);
      delay(noteDuration * 0.1);
    }
  }
  
  // Pause before repeating
  delay(2000);
}