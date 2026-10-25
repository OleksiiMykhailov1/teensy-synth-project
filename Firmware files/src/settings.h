#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Keypad.h>
#include "SPI.h"
#include "ILI9341_t3n.h"
#include <ili9341_t3n_font_Arial.h>
#include "EncButton2.h"
#include <TimerMs.h>
#include <algo_bitmap.h>
#include <algorithms.h>


#define TFT_RST 8
#define TFT_DC  20   
#define TFT_CS 21
#define TFT_MOSI 7
#define TFT_MISO 12
#define TFT_SCK 14

ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);

EncButton2<EB_ENCBTN> enc1(INPUT, 29, 30, 31);

const byte ROWS = 5; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'c','C','g','G'},
  {'d','D','a','A'},
  {'f','E','\x87','B'},
  {'0','F','5','\x80'}
};
byte rowPins[ROWS] = {24,25,26,27,28}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {0, 1, 2, 3}; //connect to the column pinouts of the kpd
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

  int largestWfRead=0;
int x=-80;
int oldX=-80;
int oldY=210;

bool arpegioPlayState=0;
int arpegioPosition = 0;
bool arpegioRecordState=0;
char arpegioSequence[32]{'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'};
int arpegioLength=16;
int n=0;
  int filled=0;
  
int ladderFrequency = 440; 
float ladderResonance = 0.7;
float filterWet=0;
float filterDry=100;
float filterLfo=0.0;

float reverbRoomSize = 0.5; //1.0 max
float reverbDamping = 0.0; //1.0 max
float reverbWet=0;
float reverbDry=100;

int delayTaps = 2;
float delayTime =150.0;
float delayFeedback = 0.2;
float delayWet=0;
float delayDry=100;

int selectedMenu=-1;
int currentScreen = 0;
int op1Attack=300;
int op1Decay=300;
float op1Sustain = 0.5;
int op1Release=300;

int op2Attack=300;
int op2Decay=300;
float op2Sustain = 0.5;
int op2Release=300;

int op3Attack=0;
int op3Decay=300;
float op3Sustain = 1.0;
int op3Release=0;

int op4Attack=0;
int op4Decay=300;
float op4Sustain = 1.0;
int op4Release=0;

float op1Ratio = 1.0;
float op2Ratio = 1.0;
float op3Ratio = 1.0;
float op4Ratio = 1.0;

float op1Amplitude = 0.5;
float op2Amplitude = 0.5;
float op3Amplitude = 0.5;
float op4Amplitude = 0.5;

int op1Waveform = 0;
int op2Waveform = 0;
int op3Waveform = 0;
int op4Waveform = 0;

// bool op1IsFixed=0;
// bool op2IsFixed=0;
// bool op3IsFixed=0;
// bool op4IsFixed=0;

// float op1FixedFrequency=10.0;
// float op2FixedFrequency=50.0;
// float op3FixedFrequency=50.0;
// float op4FixedFrequency=50.0;

// bool opIsFixedList[4]={op1IsFixed,op2IsFixed,op3IsFixed,op4IsFixed};
int freeVoice=0;
char listOfPressed[4]={'x','x','x','x'};
// int keysPressed=0;

int opAttackList[4]={op1Attack,op2Attack,op3Attack,op4Attack};
int opDecayList[4]={op1Decay,op2Decay,op3Decay,op4Decay};
float opSustainList[4]={op1Sustain,op2Sustain,op3Sustain,op4Sustain};
int opReleaseList[4]={op1Release,op2Release,op3Release,op4Release};
float opRatioList[4]={op1Ratio,op2Ratio,op3Ratio,op4Ratio};
float opAmplitudeList[4]={op1Amplitude,op2Amplitude,op3Amplitude,op4Amplitude};
int opWaveformsList[4]={op1Waveform,op2Waveform,op3Waveform,op4Waveform};
int waveformsList[3]={WAVEFORM_SINE,WAVEFORM_TRIANGLE,WAVEFORM_SQUARE};

int opStartX[4]={60,195,60,195};
int opStartY[4]={30,30,120,120};

double freq[]={16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};
double octaves[]={1, 2, 4, 8, 16, 32, 64, 128, 256};
int8_t octave = 3;

void soundSetup(){


operator1.begin(waveformsList[opWaveformsList[0]]);
operator2.begin(waveformsList[opWaveformsList[1]]);
operator3.begin(waveformsList[opWaveformsList[2]]);
operator4.begin(waveformsList[opWaveformsList[3]]);

operator1_1.begin(waveformsList[opWaveformsList[0]]);
operator2_1.begin(waveformsList[opWaveformsList[1]]);
operator3_1.begin(waveformsList[opWaveformsList[2]]);
operator4_1.begin(waveformsList[opWaveformsList[3]]);

operator1_2.begin(waveformsList[opWaveformsList[0]]);
operator2_2.begin(waveformsList[opWaveformsList[1]]);
operator3_2.begin(waveformsList[opWaveformsList[2]]);
operator4_2.begin(waveformsList[opWaveformsList[3]]);

operator1_3.begin(waveformsList[opWaveformsList[0]]);
operator2_3.begin(waveformsList[opWaveformsList[1]]);
operator3_3.begin(waveformsList[opWaveformsList[2]]);
operator4_3.begin(waveformsList[opWaveformsList[3]]);

operator1.amplitude(opAmplitudeList[0]);
operator2.amplitude(opAmplitudeList[1]);
operator3.amplitude(opAmplitudeList[2]);
operator4.amplitude(opAmplitudeList[3]);

operator1_1.amplitude(opAmplitudeList[0]);
operator2_1.amplitude(opAmplitudeList[1]);
operator3_1.amplitude(opAmplitudeList[2]);
operator4_1.amplitude(opAmplitudeList[3]);

operator1_2.amplitude(opAmplitudeList[0]);
operator2_2.amplitude(opAmplitudeList[1]);
operator3_2.amplitude(opAmplitudeList[2]);
operator4_2.amplitude(opAmplitudeList[3]);

operator1_3.amplitude(opAmplitudeList[0]);
operator2_3.amplitude(opAmplitudeList[1]);
operator3_3.amplitude(opAmplitudeList[2]);
operator4_3.amplitude(opAmplitudeList[3]);

operator1.phaseModulation(360);
operator2.phaseModulation(360);
operator3.phaseModulation(360);
operator4.phaseModulation(360);

operator1_1.phaseModulation(360);
operator2_1.phaseModulation(360);
operator3_1.phaseModulation(360);
operator4_1.phaseModulation(360);

operator1_2.phaseModulation(360);
operator2_2.phaseModulation(360);
operator3_2.phaseModulation(360);
operator4_2.phaseModulation(360);

operator1_3.phaseModulation(360);
operator2_3.phaseModulation(360);
operator3_3.phaseModulation(360);
operator4_3.phaseModulation(360);


// operator1.frequencyModulation(8);
// operator2.frequencyModulation(8);
// operator3.frequencyModulation(8);
// carrier.frequencyModulation(8);

operator1_envelope.attack(opAttackList[0]);
operator2_envelope.attack(opAttackList[1]);
operator3_envelope.attack(opAttackList[2]);
operator4_envelope.attack(opAttackList[3]);

operator1_envelope.decay(opDecayList[0]);
operator2_envelope.decay(opDecayList[1]);
operator3_envelope.decay(opDecayList[2]);
operator4_envelope.decay(opDecayList[3]);

operator1_envelope.sustain(opSustainList[0]);
operator2_envelope.sustain(opSustainList[1]);
operator3_envelope.sustain(opSustainList[2]);
operator4_envelope.sustain(opSustainList[3]);

operator1_envelope.release(opReleaseList[0]);
operator2_envelope.release(opReleaseList[1]);
operator3_envelope.release(opReleaseList[2]);
operator4_envelope.release(opReleaseList[3]);


operator1_envelope_1.attack(opAttackList[0]);
operator2_envelope_1.attack(opAttackList[1]);
operator3_envelope_1.attack(opAttackList[2]);
operator4_envelope_1.attack(opAttackList[3]);

operator1_envelope_1.decay(opDecayList[0]);
operator2_envelope_1.decay(opDecayList[1]);
operator3_envelope_1.decay(opDecayList[2]);
operator4_envelope_1.decay(opDecayList[3]);

operator1_envelope_1.sustain(opSustainList[0]);
operator2_envelope_1.sustain(opSustainList[1]);
operator3_envelope_1.sustain(opSustainList[2]);
operator4_envelope_1.sustain(opSustainList[3]);

operator1_envelope_1.release(opReleaseList[0]);
operator2_envelope_1.release(opReleaseList[1]);
operator3_envelope_1.release(opReleaseList[2]);
operator4_envelope_1.release(opReleaseList[3]);


operator1_envelope_2.attack(opAttackList[0]);
operator2_envelope_2.attack(opAttackList[1]);
operator3_envelope_2.attack(opAttackList[2]);
operator4_envelope_2.attack(opAttackList[3]);

operator1_envelope_2.decay(opDecayList[0]);
operator2_envelope_2.decay(opDecayList[1]);
operator3_envelope_2.decay(opDecayList[2]);
operator4_envelope_2.decay(opDecayList[3]);

operator1_envelope_2.sustain(opSustainList[0]);
operator2_envelope_2.sustain(opSustainList[1]);
operator3_envelope_2.sustain(opSustainList[2]);
operator4_envelope_2.sustain(opSustainList[3]);

operator1_envelope_2.release(opReleaseList[0]);
operator2_envelope_2.release(opReleaseList[1]);
operator3_envelope_2.release(opReleaseList[2]);
operator4_envelope_2.release(opReleaseList[3]);


operator1_envelope_3.attack(opAttackList[0]);
operator2_envelope_3.attack(opAttackList[1]);
operator3_envelope_3.attack(opAttackList[2]);
operator4_envelope_3.attack(opAttackList[3]);

operator1_envelope_3.decay(opDecayList[0]);
operator2_envelope_3.decay(opDecayList[1]);
operator3_envelope_3.decay(opDecayList[2]);
operator4_envelope_3.decay(opDecayList[3]);

operator1_envelope_3.sustain(opSustainList[0]);
operator2_envelope_3.sustain(opSustainList[1]);
operator3_envelope_3.sustain(opSustainList[2]);
operator4_envelope_3.sustain(opSustainList[3]);

operator1_envelope_3.release(opReleaseList[0]);
operator2_envelope_3.release(opReleaseList[1]);
operator3_envelope_3.release(opReleaseList[2]);
operator4_envelope_3.release(opReleaseList[3]);
}