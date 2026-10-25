#include <settings.h>
#define CHORUS_DELAY_LENGTH (256*AUDIO_BLOCK_SAMPLES)
short delayline[CHORUS_DELAY_LENGTH];
// int arpegioMs = 200;
int bpm = 100;
TimerMs tmr(1, 1, 0);
TimerMs arpegioDelay(20000/bpm, 1, 0);
// int editMode=0;
using namespace std;
  //  int wfZoom=2;

int menuActive=0;
int currentAlgo=0;
int currentEnvelopePoint=0;
int currentMenuPoint=0;

void selectFrequency(int voice, int opFrequency,int octaveUp){
  switch (voice)
  {
  case 0:
    operator1.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[0]);
    operator2.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[1]);
    operator3.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[2]);
    operator4.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[3]);
    break;
 case 1:
    operator1_1.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[0]);
    operator2_1.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[1]);
    operator3_1.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[2]);
    operator4_1.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[3]);
    break;
     case 2:
    operator1_2.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[0]);
    operator2_2.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[1]);
    operator3_2.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[2]);
    operator4_2.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[3]);
    break;
         case 3:
    operator1_3.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[0]);
    operator2_3.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[1]);
    operator3_3.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[2]);
    operator4_3.frequency(((freq[opFrequency]*octaveUp)*octaves[octave])*opRatioList[3]);
    break;
  }

    };

void voiceFrequency(char x, int voice){
  switch (x)
  {
     case 'C':
selectFrequency(voice,0,1);
    break;

    case 'c':
selectFrequency(voice,1,1);
    break;

      case 'D':
selectFrequency(voice,2,1);
    break;

      case 'd':
selectFrequency(voice,3,1);
    break;

      case 'E':
selectFrequency(voice,4,1);
    break;

      case 'F':
selectFrequency(voice,5,1);
    break;

      case 'f':
selectFrequency(voice,6,1);
    break;

     case 'G':
selectFrequency(voice,7,1);
    break;

      case 'g':
selectFrequency(voice,8,1);
    break;

     case 'A':
selectFrequency(voice,9,1);
    break;

      case 'a':
selectFrequency(voice,10,1);
    break;

         case 'B':
selectFrequency(voice,11,1);
    break;

      case '\x80':
selectFrequency(voice,0,2);
    break;

      case '\x87':
selectFrequency(voice,1,2);
    break;

          case '_':
 operator1.frequency(0.0);
 operator2.frequency(0.0);
 operator3.frequency(0.0);
 operator4.frequency(0.0);

    break;
  
  }
}
void activateVoice(int voice){
    switch (voice)
    {
    case 0:
      operator1_envelope.noteOn();
      operator2_envelope.noteOn();
      operator3_envelope.noteOn();
      operator4_envelope.noteOn();
      break;
     case 1:
      operator1_envelope_1.noteOn();
      operator2_envelope_1.noteOn();
      operator3_envelope_1.noteOn();
      operator4_envelope_1.noteOn();
      break;
          case 2:
      operator1_envelope_2.noteOn();
      operator2_envelope_2.noteOn();
      operator3_envelope_2.noteOn();
      operator4_envelope_2.noteOn();
      break;
          case 3:
      operator1_envelope_3.noteOn();
      operator2_envelope_3.noteOn();
      operator3_envelope_3.noteOn();
      operator4_envelope_3.noteOn();
      break;
    }

};

void deactivateVoice(int voice){
  switch (voice)
    {
    case 0:
      operator1_envelope.noteOff();
      operator2_envelope.noteOff();
      operator3_envelope.noteOff();
      operator4_envelope.noteOff();
      break;
     case 1:
      operator1_envelope_1.noteOff();
      operator2_envelope_1.noteOff();
      operator3_envelope_1.noteOff();
      operator4_envelope_1.noteOff();
      break;
          case 2:
      operator1_envelope_2.noteOff();
      operator2_envelope_2.noteOff();
      operator3_envelope_2.noteOff();
      operator4_envelope_2.noteOff();
      break;
          case 3:
      operator1_envelope_3.noteOff();
      operator2_envelope_3.noteOff();
      operator3_envelope_3.noteOff();
      operator4_envelope_3.noteOff();
      break;
    }

};

void drawEnvelope(int startX, int startY,int opAttack,int opDecay, float opSustain, int opRelease, uint16_t color){
tft.drawLine(startX,startY,startX+(opAttack*40)/1200,startY-30,color); //attack line
tft.drawLine(startX+(opAttack*40)/1200,startY-30,(startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY-(opSustain*30),color); //decay line
tft.drawLine((startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY-(opSustain*30),(opRelease/75)+(startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY,color); //release line
}
void drawEnvelopeEditPoint(int startX, int startY,int opAttack,int opDecay, float opSustain, int opRelease, uint16_t color,int currentPoint){
  switch (currentPoint)
  {
  case 0:
  tft.fillCircle(startX+(opAttack*40)/1200,startY-30,2,ILI9341_RED);  
    break;
  case 1:
  tft.fillCircle((startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY-(opSustain*30),2,ILI9341_GREEN);  
    break;
     case 2:
  tft.fillCircle((startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY-(opSustain*30),2,ILI9341_BLUE);  
    break;
      case 3:
  tft.fillCircle((opRelease/75)+(startX+(opAttack*40)/1200)+(opDecay*40)/1200,startY,2,ILI9341_YELLOW);  
    break;
  }
};

void drawOctave(int color){
  tft.fillRect(35,130,10,20,ILI9341_BLACK);
   tft.setTextColor(color);
  tft.drawString("OCT: ",5,130);
  tft.drawNumber(octave,35,130);
};
void drawAlgorithm(int currentAlgorithm, uint16_t color){
  tft.fillRect(0,0,50,114,ILI9341_BLACK); 
  tft.setTextColor(color);
  tft.drawString("ALG#",5,5);
  tft.drawNumber(currentAlgorithm+1,35,5);

  // tft.drawBitmap(10,30,algoallArray[currentAlgorithm],34,83,color);
  tft.drawBitmap(10,30,fm_allArray[currentAlgorithm],34,83,color);
  callCurrentAlgorithm(currentAlgorithm+1);
  tft.updateScreen();
};

void drawArpGrid(int length){
  int excess=320-((320/arpegioLength)*arpegioLength);
int n=excess-length;
int x=1;
 if(320%arpegioLength){
 if (n>0)
 {
 tft.drawRect(filled,30,(320/arpegioLength)+x,20,ILI9341_YELLOW);
 }
else{
  x=0;
 tft.drawRect(filled,30,(320/arpegioLength)+x,20,ILI9341_YELLOW);
 }
 
 }
  tft.drawRect((320/arpegioLength)*length,30,(320/arpegioLength),20,ILI9341_YELLOW);
//tft.drawRect((320/arpegioLength)*arpegioLength,30,320-((320/arpegioLength)*arpegioLength),20,ILI9341_GREEN);
Serial.println(excess);
};

void arpegioMenu(){
  if(menuActive&&selectedMenu==0){
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10,10);
  tft.fillRect(10,10,200,10,ILI9341_BLACK);
  for(int i=0;i<arpegioLength;i++){
 tft.print(arpegioSequence[i]); 
 tft.drawRect((320/arpegioLength)*i,30,320/arpegioLength,20,ILI9341_YELLOW);
}
 tft.setTextColor(ILI9341_YELLOW);
  tft.drawString("STP:", 212, 10);
 tft.drawNumber(arpegioLength,240, 10);
 tft.drawString("BPM:", 263, 10);
 tft.drawNumber(bpm,290, 10);
 
    }

else if(menuActive&&selectedMenu==1){
tft.setTextColor(ILI9341_YELLOW);
  tft.fillRect(10,10,200,10,ILI9341_BLACK);
    tft.setCursor(10,10);
    tft.fillRect(0,30,320,20,ILI9341_BLACK); 
  for(int i=0;i<arpegioLength;i++){
 tft.print(arpegioSequence[i]);
drawArpGrid(i);

}

tft.setTextColor(ILI9341_WHITE);
tft.fillRect(240,10,20,10,ILI9341_BLACK); 
  tft.drawString("STP:", 212, 10);
 tft.drawNumber(arpegioLength,240, 10); 

 tft.setTextColor(ILI9341_YELLOW);
 tft.drawString("BPM:", 263, 10);
 tft.drawNumber(bpm,290, 10);
 
    }

    else if(menuActive&&selectedMenu==2){
tft.setTextColor(ILI9341_YELLOW);
  //tft.fillRect(10,10,200,10,ILI9341_BLACK);
    tft.setCursor(10,10); 
     tft.fillRect(0,30,320,20,ILI9341_BLACK); 
  for(int i=0;i<arpegioLength;i++){
 tft.print(arpegioSequence[i]);
drawArpGrid(i);
}

//tft.fillRect(240,10,20,10,ILI9341_BLACK); 
  tft.drawString("STP:", 212, 10);
 tft.drawNumber(arpegioLength,240, 10);


tft.setTextColor(ILI9341_WHITE);
 tft.fillRect(290,10,30,10,ILI9341_BLACK); 
 tft.drawString("BPM:", 263, 10);
 tft.drawNumber(bpm,290, 10);
//  tft.drawBitmap();
    }
  else{tft.setTextColor(ILI9341_YELLOW);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10,10); 
    tft.fillRect(0,30,320,20,ILI9341_BLACK); 

  for(int i=0;i<arpegioLength;i++){
 tft.print(arpegioSequence[i]);
drawArpGrid(i);
 }
   tft.drawString("STP:", 212, 10);
 tft.drawNumber(arpegioLength,240, 10);

 tft.drawString("BPM:", 263, 10);
 tft.drawNumber(bpm,290, 10);

 
  //1
  // tft.drawRect(0,30,320,20,ILI9341_YELLOW);
    //2
  //  tft.drawRect(0,30,159,20,ILI9341_YELLOW);
  //    tft.drawRect(160,30,160,20,ILI9341_YELLOW);
     //3
// tft.drawRect(0,30,320/5,20,ILI9341_YELLOW);
// tft.drawRect(320/5,30,320/5,20,ILI9341_YELLOW);
// tft.drawRect(320/5*2,30,320/5,20,ILI9341_YELLOW);
// tft.drawRect(320/5*3,30,320/5,20,ILI9341_YELLOW);
// tft.drawRect(320/5*4,30,320/5,20,ILI9341_YELLOW);
 }
}
void arpegioPlay(){
  arpegioPlayState=!arpegioPlayState;
  arpegioPosition=0;
}

void arpegioRecord(){
arpegioMenu();

}


void menuSelection(int selectedMenu){
  uint16_t unselected=ILI9341_YELLOW;
  uint16_t selected=ILI9341_WHITE;
  uint16_t x=unselected;
if(currentScreen==0){
  if (selectedMenu==-2){x=selected;}
 drawOctave(x);
 if (selectedMenu==-2){x=unselected;}
if (selectedMenu==-1){x=selected;}
 drawAlgorithm(currentAlgo,x);
if (selectedMenu==-1){x=unselected;}

  if(selectedMenu==0){x=selected;}

drawEnvelope(opStartX[0],opStartY[0]+49,opAttackList[0],opDecayList[0],opSustainList[0],opReleaseList[0],x);
tft.drawRect(opStartX[0],opStartY[0],120,50,ILI9341_YELLOW);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("OP-1",60,5);
 tft.fillRect(60,16,29,8,ILI9341_BLACK);
tft.drawBitmap(60,16,wf_allArray[opWaveformsList[0]],29,8,ILI9341_YELLOW);
tft.setTextColor(x);
tft.drawString("LEVEL",110,5);
tft.drawString("RATIO",110,17);
tft.drawFloat(opRatioList[0],2,opStartX[0]+93,opStartY[0]-13);
tft.drawFloat(opAmplitudeList[0],2,opStartX[0]+93 ,opStartY[0]-25);

if(selectedMenu==0){x=unselected;}

  if(selectedMenu==1){x=selected;}

drawEnvelope(opStartX[1],opStartY[1]+49,opAttackList[1],opDecayList[1],opSustainList[1],opReleaseList[1],x);
tft.drawRect(195,30,120,50,ILI9341_YELLOW);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("OP-2",195,5);
tft.fillRect(195,16,29,8,ILI9341_BLACK);
tft.drawBitmap(195,16,wf_allArray[opWaveformsList[1]],29,8,ILI9341_YELLOW);
tft.setTextColor(x);
tft.drawString("LEVEL",245,5);
tft.drawString("RATIO",245,17);
tft.drawFloat(opRatioList[1],2,opStartX[1]+93,opStartY[1]-13);
tft.drawFloat(opAmplitudeList[1],2,opStartX[1]+93 ,opStartY[1]-25);

if(selectedMenu==1){x=unselected;}

  if(selectedMenu==2){x=selected;}

drawEnvelope(opStartX[2],opStartY[2]+49,opAttackList[2],opDecayList[2],opSustainList[2],opReleaseList[2],x);
tft.drawRect(60,120,120,50,ILI9341_YELLOW);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("OP-3",60,95);
tft.fillRect(60,106,29,8,ILI9341_BLACK);
tft.drawBitmap(60,106,wf_allArray[opWaveformsList[2]],29,8,ILI9341_YELLOW);
tft.setTextColor(x);
tft.drawString("LEVEL",110,95);
tft.drawString("RATIO",110,107);
tft.drawFloat(opRatioList[2],2,opStartX[2]+93,opStartY[2]-13);
tft.drawFloat(opAmplitudeList[2],2,opStartX[2]+93 ,opStartY[2]-25);

  if(selectedMenu==2){x=unselected;}

  if(selectedMenu==3){x=selected;}
drawEnvelope(opStartX[3],opStartY[3]+49,opAttackList[3],opDecayList[3],opSustainList[3],opReleaseList[3],x);
tft.drawRect(195,120,120,50,ILI9341_YELLOW);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("OP-4",195,95);
tft.fillRect(195,106,29,8,ILI9341_BLACK);
tft.drawBitmap(195,106,wf_allArray[opWaveformsList[3]],29,8,ILI9341_YELLOW);
tft.setTextColor(x);
tft.drawString("LEVEL",245,95);
tft.drawString("RATIO",245,107);
 tft.drawFloat(opRatioList[3],2,opStartX[3]+93,opStartY[3]-13);
  tft.drawFloat(opAmplitudeList[3],2,opStartX[3]+93 ,opStartY[3]-25);

  if(selectedMenu==3){x=unselected;}
}

if(currentScreen==1){

switch (selectedMenu)
{
case 0:
//tft.fillRect(210,20,40,30,ILI9341_BLACK);
tft.fillRect(80,20,55,30,ILI9341_BLACK);

tft.setTextColor(ILI9341_WHITE);
tft.drawString("REVERB:",10,10);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("ROOM SIZE:",10,20);

tft.drawFloat(reverbRoomSize,2,80,20);


tft.drawString("DAMPING:",10,30);
tft.drawFloat(reverbDamping,1,80,30);

tft.drawString("WET/DRY:",10,40);
tft.drawNumber(reverbWet,80,40);
tft.drawString("/",100,40);
tft.drawNumber(reverbDry,112,40);

tft.drawString("DELAY:",150,10);

tft.drawString("TAPS:",150,20);
tft.drawNumber(delayTaps,215,20);
tft.drawString("TIME:",150,30);
tft.drawNumber(delayTime,215,30);
tft.drawString("FEEDBACK:",150,40);
tft.drawFloat(delayFeedback,2,215,40);
tft.drawString("WET/DRY:",150,50);
tft.drawNumber(delayWet,215,50);
tft.drawString("/",235,50);
tft.drawNumber(delayDry,247,50);

tft.drawString("FILTER:",10,60);

tft.drawString("FREQUENCY:",10,70);
tft.drawNumber(ladderFrequency,80,70);
tft.drawString("RESONANCE:",10,80);
tft.drawFloat(ladderResonance,2,80,80);
tft.drawString("WET/DRY:",10,90);
tft.drawNumber(filterWet,80,90);
tft.drawString("/",100,90);
tft.drawNumber(filterDry,112,90);
tft.drawString("LFO:",10,100);
tft.drawFloat(filterLfo,2,80,100);
  break;
  
case 1:
tft.fillRect(210,20,80,50,ILI9341_BLACK);
//tft.fillRect(80,20,55,30,ILI9341_BLUE);

tft.setTextColor(ILI9341_WHITE);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("REVERB:",10,10);


tft.drawString("ROOM SIZE:",10,20);
tft.drawFloat(reverbRoomSize,2,80,20);

tft.drawString("DAMPING:",10,30);
tft.drawFloat(reverbDamping,1,80,30);

tft.drawString("WET/DRY:",10,40);
tft.drawNumber(reverbWet,80,40);
tft.drawString("/",100,40);
tft.drawNumber(reverbDry,112,40);

tft.setTextColor(ILI9341_WHITE);
tft.drawString("DELAY:",150,10);
tft.setTextColor(ILI9341_YELLOW);
tft.drawString("TAPS:",150,20);
tft.drawNumber(delayTaps,215,20);
tft.drawString("TIME:",150,30);

tft.drawNumber(delayTime,215,30);
tft.drawString("FEEDBACK:",150,40);
tft.drawFloat(delayFeedback,2,215,40);
tft.drawString("WET/DRY:",150,50);
tft.drawNumber(delayWet,215,50);
tft.drawString("/",235,50);
tft.drawNumber(delayDry,247,50);

tft.drawString("FILTER:",10,60);

tft.drawString("FREQUENCY:",10,70);
tft.drawNumber(ladderFrequency,80,70);
tft.drawString("RESONANCE:",10,80);
tft.drawFloat(ladderResonance,2,80,80);
tft.drawString("WET/DRY:",10,90);
tft.drawNumber(filterWet,80,90);
tft.drawString("/",100,90);
tft.drawNumber(filterDry,112,90);
tft.drawString("LFO:",10,100);
tft.drawFloat(filterLfo,2,80,100);
  break;

  case 2:
// tft.fillRect(210,20,40,30,ILI9341_BLUE);
// tft.fillRect(80,20,55,30,ILI9341_BLUE);
tft.fillRect(80,70,65,50,ILI9341_BLACK);

tft.setTextColor(ILI9341_YELLOW);
tft.drawString("REVERB:",10,10);


tft.drawString("ROOM SIZE:",10,20);
tft.drawFloat(reverbRoomSize,2,80,20);

tft.drawString("DAMPING:",10,30);
tft.drawFloat(reverbDamping,1,80,30);

tft.drawString("WET/DRY:",10,40);
tft.drawNumber(reverbWet,80,40);
tft.drawString("/",100,40);
tft.drawNumber(reverbDry,112,40);

tft.drawString("DELAY:",150,10);
tft.drawString("TAPS:",150,20);
tft.drawNumber(delayTaps,215,20);
tft.drawString("TIME:",150,30);

tft.drawNumber(delayTime,215,30);
tft.drawString("FEEDBACK:",150,40);
tft.drawFloat(delayFeedback,2,215,40);
tft.drawString("WET/DRY:",150,50);
tft.drawNumber(delayWet,215,50);
tft.drawString("/",235,50);
tft.drawNumber(delayDry,247,50);

tft.setTextColor(ILI9341_WHITE);
tft.drawString("FILTER:",10,60);
tft.setTextColor(ILI9341_YELLOW);

tft.drawString("FREQUENCY:",10,70);
tft.drawNumber(ladderFrequency,80,70);
tft.drawString("RESONANCE:",10,80);
tft.drawFloat(ladderResonance,2,80,80);
tft.drawString("WET/DRY:",10,90);
tft.drawNumber(filterWet,80,90);
tft.drawString("/",100,90);
tft.drawNumber(filterDry,112,90);
tft.drawString("LFO:",10,100);
tft.drawFloat(filterLfo,2,80,100);
  break;
}
}

if(currentScreen==2){

switch (selectedMenu)
{
case 0:
arpegioMenu();
  break;
  
case 1:
arpegioMenu();
  break;

  case 2:
arpegioMenu();
  break;
}
}

tft.updateScreen();
};
void drawSelectArrow(int currentMenu){
  

   if (currentScreen==1){
      
   
    if(menuActive){ 
        if(selectedMenu==0){
         tft.fillRect(140,20,10,40,ILI9341_BLACK);
        switch (currentMenuPoint)
        {

        case 0:
         tft.fillRect(0,20,10,40,ILI9341_BLACK);
         tft.drawString(">",0,20);
        break;

        case 1:
          tft.fillRect(0,20,10,40,ILI9341_BLACK);
          tft.drawString(">",0,30);
        break;
         case 2:
         tft.fillRect(0,20,10,40,ILI9341_BLACK);
          tft.drawString(">",0,40);
        break;
                 case 3:
         tft.fillRect(0,20,10,40,ILI9341_BLACK);
          tft.drawString(">",0,50);
        break;


        }
      }
        if(selectedMenu==1){
          tft.fillRect(0,20,10,40,ILI9341_BLACK);
          tft.fillRect(0,70,10,40,ILI9341_BLACK);

        switch (currentMenuPoint)
        {

        case 0:
          tft.fillRect(140,20,10,40,ILI9341_BLACK);
          tft.drawString(">",140,20);
        break;

        case 1:
          tft.fillRect(140,20,10,40,ILI9341_BLACK);
           tft.drawString(">",140,30);
        break;

         case 2:
          tft.fillRect(140,20,10,40,ILI9341_BLACK);
           tft.drawString(">",140,40);
        break;

       case 3:
          tft.fillRect(140,20,10,40,ILI9341_BLACK);
           tft.drawString(">",140,50);
        break;
        }
      }

       if(selectedMenu==2){
         tft.fillRect(140,20,10,40,ILI9341_BLACK);
        switch (currentMenuPoint)
        {

        case 0:
         tft.fillRect(0,70,10,40,ILI9341_BLACK);
         tft.drawString(">",0,70);
        break;

        case 1:
          tft.fillRect(0,70,10,40,ILI9341_BLACK);
          tft.drawString(">",0,80);
        break;

        case 2:
          tft.fillRect(0,70,10,40,ILI9341_BLACK);
          tft.drawString(">",0,90);
        break;

          case 3:
          tft.fillRect(0,70,10,40,ILI9341_BLACK);
          tft.drawString(">",0,100);
        break;

        }
      }
      }
       if(!menuActive){
        tft.fillRect(140,20,10,40,ILI9341_BLACK);
        tft.fillRect(0,20,10,40,ILI9341_BLACK);
        tft.fillRect(0,70,10,40,ILI9341_BLACK);

        currentMenuPoint=0;
       }

 }

if(currentScreen==0){

}
}
void screenSelection ( int selectedScreen){
 switch (selectedScreen)
 {
 case 1:
menuSelection(0);
tft.fillScreen(ILI9341_BLACK);
tft.drawString("REVERB:",10,10);
tft.drawString("ROOM SIZE:",10,20);
tft.drawFloat(reverbRoomSize,2,80,20);
tft.drawString("DAMPING:",10,30);
tft.drawFloat(reverbDamping,1,80,30);


tft.drawString("DELAY:",150,10);
tft.drawString("TAPS:",150,20);
tft.drawNumber(delayTaps,215,20);
tft.fillRect(200,20,10,10,ILI9341_BLACK);
tft.drawString("TIME:",150,30);
tft.drawNumber(delayTime,215,30);

  break;
 
 case 0:
 tft.fillScreen(ILI9341_BLACK);
 menuSelection(0);
  drawAlgorithm(currentAlgo,ILI9341_YELLOW);
  break;
 
  case 2:
  
arpegioMenu();
  break;
 }
};
 
 void compareAR(int wf){
if(wf>largestWfRead){largestWfRead=wf;};
}

void wetDrySetup(){
 filter_mix.gain(0,filterDry/100);
filter_mix.gain(1,filterWet/100);

delay_mix.gain(0,delayDry/100);
delay_mix.gain(1,delayWet/100);

freeverb_mix.gain(0,reverbDry/100);
freeverb_mix.gain(1,reverbWet/100);
}

void setup() {
  dacs1.analogReference(INTERNAL);
  wetDrySetup();
ladder1.octaveControl(5.0);
ladder1.frequency(ladderFrequency);
ladder1.resonance(ladderResonance);
ladder_LFO.begin(0.7,0.0,WAVEFORM_SINE);
// ladder_resonance_control.frequency(100.0);
//  ladder_resonance_control.amplitude(0.5);
//  ladder_frequency_controll.frequency(50.0);
//  ladder_frequency_controll.amplitude(1.0);

voices_mixer.gain(0,1.0);
voices_mixer.gain(1,1.0);
voices_mixer.gain(2,1.0);
voices_mixer.gain(3,1.0);

Effect_mixer.gain(0,1.0);
Effect_mixer.gain(1,0.0);
Effect_mixer.gain(2,0.0);
Effect_mixer.gain(3,0.0);

//freeverbFilter.frequency(1200);
delayFeedbackMix.gain(0,0.5);
delayFeedbackMix.gain(1,delayFeedback);
delayFeedbackMix.gain(2,delayFeedback);
delayFeedbackMix.gain(3,delayFeedback);


delay1.disable(0);
delay1.disable(1);
delay1.disable(2);

// sgtl5000.enable();
// sgtl5000.volume(2.0);
// sgtl5000.unmuteHeadphone();
// sgtl5000.unmuteLineout();
// sgtl5000.dacVolume(10.0);
// sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
  tmr.setMicros(true);
  soundSetup();
  pinMode(A21, OUTPUT);

AudioMemory(400);

freeverb1.roomsize(0.0);
freeverb1.damping(0.0);
algorithm_10();  
SPI.begin();
SPI.setSCK(14);
tft.begin();
tft.setRotation(1);
tft.useFrameBuffer(true);
tft.updateChangedAreasOnly(true);
tft.setTextSize(1);
tft.fillScreen(ILI9341_BLACK);

Serial.begin(10000000);

drawOctave(ILI9341_YELLOW);
menuSelection(selectedMenu);
// voiceFrequency('C',0);
// activateVoice(0);
}

void loop() {

enc1.tick();
char key = kpd.getKey();
if(!menuActive&&enc1.right()){
  if(currentScreen==0&&selectedMenu<3){selectedMenu++;}
  if(currentScreen==1&&selectedMenu<2){selectedMenu++;}
if(currentScreen==2&&selectedMenu<2){selectedMenu++;}
menuSelection(selectedMenu);
}

if(!menuActive&&enc1.left()){
  if(currentScreen==0&&selectedMenu>-2){selectedMenu--;}
  if(currentScreen==1&&selectedMenu>0){selectedMenu--;} 
   if(currentScreen==2&&selectedMenu>0){selectedMenu--;} 
  menuSelection(selectedMenu);
}

if(menuActive&&selectedMenu==-1){

if(enc1.right()&&currentAlgo<10){
currentAlgo++;
drawAlgorithm(currentAlgo,ILI9341_WHITE);
}
if(enc1.left()&&currentAlgo>0){
currentAlgo--;
drawAlgorithm(currentAlgo,ILI9341_WHITE);
}

};

if(menuActive&&selectedMenu==-2){

if(enc1.right()&&octave<8){
octave++;
drawOctave(ILI9341_WHITE);
}
if(enc1.left()&&octave>0){
octave--;
drawOctave(ILI9341_WHITE);
}

};
if(menuActive){

  if(enc1.right()){
  if(currentScreen==0){
  switch (currentEnvelopePoint)
{
  case 0:
  opAttackList[selectedMenu]+=25;
  if(opAttackList[selectedMenu]>1000){opAttackList[selectedMenu]=1000;}
  break;

  case 1:
  opDecayList[selectedMenu]+=25;
  if(opDecayList[selectedMenu]>1000){opDecayList[selectedMenu]=1000;}
  break;

  case 2:
  opSustainList[selectedMenu]+=0.1;
  if(opSustainList[selectedMenu]>1.0){opSustainList[selectedMenu]=1.0;}
  break;

  case 3:
  opReleaseList[selectedMenu]+=100;
  if(opReleaseList[selectedMenu]>3800){opReleaseList[selectedMenu]=3800;}
  break;

  case 4:
  opRatioList[selectedMenu]+=0.05;
  if(opRatioList[selectedMenu]>16.0){opRatioList[selectedMenu]=16.0;}
  break;

  case 5:
  opAmplitudeList[selectedMenu]+=0.01;
  if(opAmplitudeList[selectedMenu]>1.0){opAmplitudeList[selectedMenu]=1.0;}
  break;
    case 6:
  opWaveformsList[selectedMenu]+=1;
  if(opWaveformsList[selectedMenu]>2){opWaveformsList[selectedMenu]=0;}
  break;

}

  tft.fillRect(opStartX[selectedMenu]-5,opStartY[selectedMenu],125,65,ILI9341_BLACK);
  drawEnvelope(opStartX[selectedMenu],opStartY[selectedMenu]+49, opAttackList[selectedMenu], opDecayList[selectedMenu], opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_WHITE);
  tft.fillRect(opStartX[selectedMenu]+92,opStartY[selectedMenu]-26,30,22,ILI9341_BLACK);
  tft.fillRect(opStartX[selectedMenu],opStartY[selectedMenu]-14,29,8,ILI9341_BLACK);
  tft.drawBitmap(opStartX[selectedMenu],opStartY[selectedMenu]-14,wf_allArray[opWaveformsList[selectedMenu]],29,8,ILI9341_YELLOW);
  drawEnvelopeEditPoint(opStartX[selectedMenu],opStartY[selectedMenu]+49, opAttackList[selectedMenu], opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_RED,currentEnvelopePoint);
  tft.drawFloat(opRatioList[selectedMenu],2,opStartX[selectedMenu]+93 ,opStartY[selectedMenu]-13);
  tft.drawFloat(opAmplitudeList[selectedMenu],2,opStartX[selectedMenu]+93 ,opStartY[selectedMenu]-25);
  tft.drawRect(opStartX[selectedMenu],opStartY[selectedMenu],120,50,ILI9341_YELLOW);
  soundSetup();
  }
  if(currentScreen==1){
    if(selectedMenu==0){
    switch (currentMenuPoint)
    {
    case 0:
    
      if(reverbRoomSize<1.0)reverbRoomSize+=0.01;
      freeverb1.roomsize(reverbRoomSize);
      break;
   
    case 1:
      if(reverbDamping<1.0)reverbDamping+=0.01;
      freeverb1.damping(reverbDamping);
      break;

       case 2:
      if(reverbWet<100){reverbWet+=1;
                        reverbDry-=1;}
                        wetDrySetup();
      break;
    }
    // if(reverbRoomSize>0){
    //   Effect_mixer.gain(0,reverbDry/100);
    //   Effect_mixer.gain(1,reverbDry/100);
    //   Effect_mixer.gain(2,reverbWet/100);
    // }
    }
    if(selectedMenu==1){
      switch (currentMenuPoint)
    {
    case 0:
      if(delayTaps<3){delayTaps+=1;}
      if(delayTaps==0){
      delay1.disable(0);
      delay1.disable(1);
      delay1.disable(2);};
      if(delayTaps==1){
      delay1.delay(0,delayTime);
      delay1.disable(1);
      delay1.disable(2);};
      if(delayTaps==2){
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.disable(2);};
      if(delayTaps==3){
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.delay(2,delayTime);};
    //      if(delayTaps>0&&reverbRoomSize==0){
    //   Effect_mixer.gain(0,reverbDry/100);
    //   Effect_mixer.gain(1,reverbDry/100);
    //   Effect_mixer.gain(2,reverbWet/100);
    // }
      break;
    
    case 1:
      if(delayTime<500.0){delayTime+=5.0;}
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.delay(2,delayTime);
      break;

          case 2:
      if(delayFeedback<0.5){delayFeedback+=0.01;}
     delayFeedbackMix.gain(1,delayFeedback);
     delayFeedbackMix.gain(2,delayFeedback);
     delayFeedbackMix.gain(3,delayFeedback);
      break;

         case 3:
      if(delayWet<100){delayWet+=1;
                        delayDry-=1;}
                        wetDrySetup();
      break;
    }
    
  
    }

        if(selectedMenu==2){
      switch (currentMenuPoint)
    {
    case 0:
      if(ladderFrequency<5000){ladderFrequency+=50;}
      ladder1.frequency(ladderFrequency);
      break;
    
    case 1:
if(ladderResonance<4.9){ladderResonance+=0.1;}
      ladder1.resonance(ladderResonance); 
      break;

case 2:
      if(filterWet<100){filterWet+=1;
                        filterDry-=1;}
                        wetDrySetup();
      break;

      case 3:
      if(filterLfo<50){filterLfo+=0.1;}
      ladder_LFO.frequency(filterLfo);
      break;
    }
  
    }
    menuSelection(selectedMenu);
    }
  if(currentScreen==2){
  if(selectedMenu==1){
  arpegioLength+=1;
  if(arpegioLength>32){arpegioLength=32;} 
  arpegioMenu();
}
if(selectedMenu==2){
  bpm+=1;
  arpegioDelay.setTime(20000/bpm);
  arpegioMenu();
}
  }
  }

  if(enc1.left()){
  if(currentScreen==0){
  switch (currentEnvelopePoint)
{
  case 0:
  opAttackList[selectedMenu]-=10;
  if(opAttackList[selectedMenu]<0){opAttackList[selectedMenu]=0;}
  break;

  case 1:
  opDecayList[selectedMenu]-=10;
  if(opDecayList[selectedMenu]<0){opDecayList[selectedMenu]=0;}
  break;

  case 2:
  opSustainList[selectedMenu]-=0.1;
  if(opSustainList[selectedMenu]<0.0){opSustainList[selectedMenu]=0.0;}
  break;

  case 3:
  opReleaseList[selectedMenu]-=50;
  if(opReleaseList[selectedMenu]<0){opReleaseList[selectedMenu]=0;}
  break;
  case 4:
  opRatioList[selectedMenu]-=0.05;
  if(opRatioList[selectedMenu]<0.0){opRatioList[selectedMenu]=0.0;}
  break;

  case 5:
  opAmplitudeList[selectedMenu]-=0.01;
  if(opAmplitudeList[selectedMenu]<0.0){opAmplitudeList[selectedMenu]=0.0;}
  break;
  case 6:
  opWaveformsList[selectedMenu]-=1;
  if(opWaveformsList[selectedMenu]<0){opWaveformsList[selectedMenu]=2;}
  break;
}
  tft.fillRect(opStartX[selectedMenu]-5,opStartY[selectedMenu],125,65,ILI9341_BLACK);
  drawEnvelope(opStartX[selectedMenu],opStartY[selectedMenu]+49, opAttackList[selectedMenu], opDecayList[selectedMenu], opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_WHITE);
  tft.fillRect(opStartX[selectedMenu]+92,opStartY[selectedMenu]-26,30,22,ILI9341_BLACK);
   tft.fillRect(opStartX[selectedMenu],opStartY[selectedMenu]-14,29,8,ILI9341_BLACK);
tft.drawBitmap(opStartX[selectedMenu],opStartY[selectedMenu]-14,wf_allArray[opWaveformsList[selectedMenu]],29,8,ILI9341_YELLOW);
  drawEnvelopeEditPoint(opStartX[selectedMenu],opStartY[selectedMenu]+49, opAttackList[selectedMenu], opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_RED,currentEnvelopePoint);
  tft.drawFloat(opRatioList[selectedMenu],2,opStartX[selectedMenu]+93,opStartY[selectedMenu]-13);
  tft.drawFloat(opAmplitudeList[selectedMenu],2,opStartX[selectedMenu]+93 ,opStartY[selectedMenu]-25);
  tft.drawRect(opStartX[selectedMenu],opStartY[selectedMenu],120,50,ILI9341_YELLOW);
  soundSetup();
  }
  if(currentScreen==1){
    if(selectedMenu==0){
    switch (currentMenuPoint)
    {
    case 0:
      if(reverbRoomSize>0.0)reverbRoomSize-=0.01;
       if(reverbRoomSize<0){reverbRoomSize=0;}
      freeverb1.roomsize(reverbRoomSize);
      break;
    
    case 1:
      if(reverbDamping>0.0)reverbDamping-=0.01;
      freeverb1.damping(reverbDamping);
      break;
       case 2:
      if(reverbWet>0){reverbWet-=1;
                        reverbDry+=1;}
                        wetDrySetup();
      break;
    }
    //     if(reverbRoomSize<0.01&&reverbDamping<0.01){
        

    //   Effect_mixer.gain(0,1.0);
    //   //Effect_mixer.gain(1,0.0);
    //   Effect_mixer.gain(2,0.0);
    // }
    }
    if(selectedMenu==1){
switch (currentMenuPoint)
    {
    case 0:
      if(delayTaps>0){delayTaps-=1;}
      if(delayTaps==0){
      delay1.disable(0);
      delay1.disable(1);
      delay1.disable(2);};
      if(delayTaps==1){
      delay1.delay(0,delayTime);
      delay1.disable(1);
      delay1.disable(2);};
      if(delayTaps==2){
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.disable(2);};
      if(delayTaps==3){
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.delay(2,delayTime);};
      break;
    
    case 1:
      if(delayTime>10.0){delayTime-=5.0;}
      delay1.delay(0,delayTime);
      delay1.delay(1,delayTime);
      delay1.delay(2,delayTime);
      break;

      
          case 2:
      if(delayFeedback>0){delayFeedback-=0.01;}
     delayFeedbackMix.gain(1,delayFeedback);
     delayFeedbackMix.gain(2,delayFeedback);
     delayFeedbackMix.gain(3,delayFeedback);
      break;

            case 3:
      if(delayWet>0){delayWet-=1;
                        delayDry+=1;}
                        wetDrySetup();
      break;
    }
    }
    if(selectedMenu==2){
      switch (currentMenuPoint)
    {
    case 0:
      if(ladderFrequency>0){ladderFrequency-=50;}
      ladder1.frequency(ladderFrequency);
      break;
    
    case 1:
if(ladderResonance>0.8){ladderResonance-=0.1;}
      ladder1.resonance(ladderResonance); 
      break;

         case 2:
      if(filterWet>0){filterWet-=1;
                        filterDry+=1;}
                        wetDrySetup();
      break;

         case 3:
      if(filterLfo>0){filterLfo-=0.1;}
      ladder_LFO.frequency(filterLfo);
      break;
      
    }
   
    }
     menuSelection(selectedMenu);
  }
  if(currentScreen==2){
    if(selectedMenu==1){
  arpegioLength-=1;
if(arpegioLength<1){arpegioLength=1;} 
arpegioMenu();
}
if(selectedMenu==2){
  bpm-=1;
  arpegioDelay.setTime(20000/bpm);
  arpegioMenu();
}
   }
}
}

if(tmr.tick()){   // Draw waveform

  int wf=analogRead(A21);
  // compareAR(wf);
  //   if(((186-largestWfRead)/wfZoom)+210<186){wfZoom++;}
  //   else if(((186-largestWfRead)/wfZoom)+210>209&&wfZoom>1){wfZoom--;}

  x=x+1;
  tft.drawRect(oldX+1,170,1,70,ILI9341_BLACK);
  int newY=((186-wf)/3)+210;
  if(newY<175){newY=175;}
  if(newY>238){newY=238;}
  tft.drawLine(oldX,oldY,x,newY,ILI9341_YELLOW);
  oldX=x;
  oldY=newY;

  if(x>320){

  // largestWfRead=0;
  x=-80; 
  oldX=x;
  tft.drawRect(0,175,2,65,ILI9341_BLACK);
  }

  tft.updateScreen();
}
  
if(arpegioDelay.tick()){
  if(arpegioPlayState){
    if(arpegioSequence[arpegioPosition]=='_'){
      deactivateVoice(0);
    }
    else{
    deactivateVoice(0);
    voiceFrequency(arpegioSequence[arpegioPosition],0);
    activateVoice(0);
    }
    
    arpegioPosition++;
    if(arpegioPosition>arpegioLength-1){arpegioPosition=0;}
    }

}



if (kpd.getKeys()){
  for (int i=0; i<LIST_MAX; i++){
  if(kpd.key[i].stateChanged){
  switch (kpd.key[i].kstate){
  
  case PRESSED:
 if(arpegioRecordState){
    if(kpd.key[i].kchar!='0'&&kpd.key[i].kchar!='3'&&kpd.key[i].kchar!='4'&&kpd.key[i].kchar!='5'){
 if(kpd.key[i].kchar!='2'&&kpd.key[i].kchar!='1'){
arpegioSequence[arpegioPosition]=kpd.key[i].kchar;
 }
 else{
  arpegioSequence[arpegioPosition]='_';
 }
    
      
    arpegioPosition++;
    if(arpegioPosition>arpegioLength){arpegioPosition=0;}
    arpegioRecord();
  }
    }
  
    if(kpd.key[i].kchar!='2'&&kpd.key[i].kchar!='1'&&kpd.key[i].kchar!='0'&&kpd.key[i].kchar!='3'&&kpd.key[i].kchar!='4'&&kpd.key[i].kchar!='5'){

  Serial.print("Pressed: ");
  Serial.println(kpd.key[i].kchar);
  if(listOfPressed[freeVoice]=='x'){
 
    listOfPressed[freeVoice]=kpd.key[i].kchar;
    voiceFrequency(kpd.key[i].kchar,freeVoice);
    activateVoice(freeVoice);
    }freeVoice++;
    if(freeVoice>3){freeVoice=0;}
  Serial.print("List: ");
  Serial.println(listOfPressed);
     
    }
 if(kpd.key[i].kchar=='5'){
  deactivateVoice(0);
  deactivateVoice(1);
  deactivateVoice(2);
  deactivateVoice(3);

arpegioPlay();
 }
    if(kpd.key[i].kchar=='1'){

      if(currentEnvelopePoint<6&&menuActive&&currentScreen==0){
      currentEnvelopePoint++;
      if(currentEnvelopePoint>6){currentEnvelopePoint=0;}
      
      if(selectedMenu!=-1&&selectedMenu!=-2){
       tft.fillRect(opStartX[selectedMenu]-5,opStartY[selectedMenu],125,65,ILI9341_BLACK);
        drawEnvelope(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_WHITE);
        tft.drawRect(opStartX[selectedMenu],opStartY[selectedMenu],120,50,ILI9341_YELLOW);
        if(currentEnvelopePoint<4){drawEnvelopeEditPoint(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_RED,currentEnvelopePoint);}
      }
      }
      if(currentMenuPoint<3&&currentScreen==1&&menuActive){
      currentMenuPoint++;
      drawSelectArrow(currentMenuPoint);
      }
      if(!menuActive&&currentScreen<2){
      //  tft.fillScreen(ILI9341_BLACK);
      currentScreen++;
      selectedMenu=0;
      screenSelection(currentScreen);

      }
      menuSelection(selectedMenu);

    }

    if(kpd.key[i].kchar=='2'){
      if(currentEnvelopePoint>-1&&menuActive&&currentScreen==0){
      currentEnvelopePoint--;
      if(currentEnvelopePoint<0){currentEnvelopePoint=6;}
      if(selectedMenu!=-1&&selectedMenu!=-2){
        tft.fillRect(opStartX[selectedMenu]-5,opStartY[selectedMenu],125,65,ILI9341_BLACK);
        drawEnvelope(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_WHITE);
        tft.drawRect(opStartX[selectedMenu],opStartY[selectedMenu],120,50,ILI9341_YELLOW);
        drawEnvelopeEditPoint(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_RED,currentEnvelopePoint);
        }
        }  
      if(currentMenuPoint>0&&currentScreen==1&&menuActive){
      currentMenuPoint--;
      drawSelectArrow(currentMenuPoint);
      }
      if(!menuActive&&currentScreen>0){
      currentScreen--;
      selectedMenu=0;
      screenSelection(currentScreen);
      }
      menuSelection(selectedMenu);
    }
  break;

  case RELEASED:
      if(kpd.key[i].kchar!='2'&&kpd.key[i].kchar!='1'&&kpd.key[i].kchar!='0'&&kpd.key[i].kchar!='3'&&kpd.key[i].kchar!='4'&&kpd.key[i].kchar!='5'){

//  keysPressed--;

  Serial.print("Released: ");
  Serial.println(kpd.key[i].kchar);
  for(int keyReleased=0; keyReleased<4; keyReleased++){
    if(kpd.key[i].kchar==listOfPressed[keyReleased]){
       Serial.print("keyReleased: ");
  Serial.println(keyReleased);
      listOfPressed[keyReleased]='x';
    deactivateVoice(keyReleased);  
      freeVoice=keyReleased;}
  }
  Serial.print("List: ");
  Serial.println(listOfPressed);
      }
    if(kpd.key[i].kchar=='0'){
    menuActive=!menuActive;
    drawSelectArrow(currentMenuPoint);
     if(currentScreen==0){
       currentEnvelopePoint=0;
      if(selectedMenu==0||selectedMenu==1||selectedMenu==2||selectedMenu==3){
      tft.fillRect(opStartX[selectedMenu]-5,opStartY[selectedMenu],125,65,ILI9341_BLACK);
      drawEnvelope(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_WHITE);
      tft.drawRect(opStartX[selectedMenu],opStartY[selectedMenu],120,50,ILI9341_YELLOW); 
      if(menuActive){drawEnvelopeEditPoint(opStartX[selectedMenu],opStartY[selectedMenu]+49,opAttackList[selectedMenu],opDecayList[selectedMenu],opSustainList[selectedMenu],opReleaseList[selectedMenu],ILI9341_RED,currentEnvelopePoint);
      }
      }
      
      }
 if(currentScreen==2){
  if(selectedMenu==0){  arpegioRecordState=!arpegioRecordState;
  arpegioRecord();}



 }
    }

//     if(kpd.key[i].kchar!='2'&&kpd.key[i].kchar!='1'&&kpd.key[i].kchar!='0'&&kpd.key[i].kchar!='3'&&kpd.key[i].kchar!='4'&&kpd.key[i].kchar!='5'){
// deactivateVoice(0);
//       }
break;
}
}}}

}
 //}
