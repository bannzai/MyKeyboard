#include <stdio.h>
#include <string.h>
//*** set pin number begin***//
const int mostLeftKey_Enter_5  = 9;
const int mostLeftKey_N_5 = 8;
const int mostLeftKey_H_5 = 7;
const int mostLeftKey_Y_5 = 6;
const int mostLeftKey_Ctrl_5 = 13;
const int mostLeftKey_Esc_6 = 12;
const int mostLeftKey_FnNum_6 = 11;
const int mostLeftKey_Tab_6 = 10;

const int input_1 = 5;
const int input_2 = 4;
const int input_3 = 3;
const int input_4 = 2;
const int input_5 = 1;
const int input_6 = 0;
//*** set pin number End ***//

char* arrLeftEnter[] = {"Enter","Fun_Direction","Alt_R","Command_R","Caps"};
char* arrLeftN[]     = {"n","m",",",".","EasterEgg"};
char* arrLeftH[]     = {"h","j","k","l","Back"};
char* arrLeftY[]     = {"y","u","i","o","p"};
char* arrLeftCtrl[]  = {"Ctrl","Command_L","Alt_L","Fn_mark","Space"};
char* arrLeftFnNum[] = {"Fn_Num","z","x", "c","v","b"};
char* arrLeftEsc[]   = {"Esc","a","s","d","f","g"};
char* arrLeftTab[]   = {"Tab","q","w","e","r","t"};

char* arrLeftEnter_Num[] = {"Enter","Fun_Direction","Alt_R","Command_R","Caps"};
char* arrLeftN_Num[]     = {"0","1","2","3","Slush"};
char* arrLeftH_Num[]     = {"Aster","4","5","6","Plus"};
char* arrLeftY_Num[]     = {"Equal","7","8","9","Minus"};
char* arrLeftCtrl_Num[]  = {"Ctrl","Command_L","Alt_L","Fn_mark","Space"};
char* arrLeftFnNum_Num[] = {"Fn_Num","F11","F12", "Non","Non","Non"};
char* arrLeftEsc_Num[]   = {"Esc","F6","F7","F8","F9","F10"};
char* arrLeftTab_Num[]   = {"Tab","F1","F2","F3","F4","F5"};

char* arrLeftEnter_Direction[] = {"Enter","Fun_Direction","Alt_R","Command_R","Caps"};
char* arrLeftN_Direction[]     = {"Non","Non","Non","Non","Non"};
char* arrLeftH_Direction[]     = {"Non","Non","Non","Non","Non"};
char* arrLeftY_Direction[]     = {"Non","Non","Non","Non","Non"};
char* arrLeftCtrl_Direction[]  = {"Ctrl","Command_L","Alt_L","Fn_mark","Space"};
char* arrLeftFnNum_Direction[] = {"Fn_Num","Non","Non", "Non","Non","Non"};
char* arrLeftEsc_Direction[]   = {"Esc","Non","Arrow_Left","Arrow_Down","Arrow_Right","Non"};
char* arrLeftTab_Direction[]   = {"Tab","Non","Non","Arrow_Up","Non","Non"};

char* arrLeftEnter_Mark[] = {"Enter","Fun_Direction","Alt_R","Command_R","Caps"};
char* arrLeftN_Mark[]     = {"Non","Non","Non","Non","Non"};
char* arrLeftH_Mark[]     = {"<",">","・","Non","Non"};
char* arrLeftY_Mark[]     = {"~","¥","(",")","-"};
char* arrLeftCtrl_Mark[]  = {"Ctrl","Command_L","Alt_L","Fn_mark","Space"};
char* arrLeftFnNum_Mark[] = {"Fn_Num","[","]", "{","}","^"};
char* arrLeftEsc_Mark[]   = {"Esc","#","$","%","&","@"};
char* arrLeftTab_Mark[]   = {"Tab","!","?","_","""","'"};

//char** m_arrEnterArrays[] = {arrLeftEnter, arrLeftEnter_Num,  arrLeftEnter_Direction,  arrLeftEnter_Mark};
//char** m_arrCharNArrays[] = {arrLeftN,     arrLeftN_Num,      arrLeftN_Direction,      arrLeftN_Mark};
//char** m_arrCharHArrays[] = {arrLeftH,     arrLeftH_Num,      arrLeftH_Direction,      arrLeftH_Mark};
//char** m_arrCharYArrays[] = {arrLeftY,     arrLeftY_Num,      arrLeftY_Direction,      arrLeftY_Mark};
//char** m_arrCtrlArrays[]  = {arrLeftCtrl,  arrLeftCtrl_Num,   arrLeftCtrl_Direction,   arrLeftCtrl_Mark};
//char** m_arrFnNumArrays[] = {arrLeftFnNum, arrLeftFnNum_Num,  arrLeftEnter_Direction,  arrLeftFnNum_Mark};
//char** m_arrEscArrays[]   = {arrLeftEsc,   arrLeftEsc_Num,    arrLeftFnNum_Direction,  arrLeftEsc_Mark};
//char** m_arrTabArrays[]   = {arrLeftTab,   arrLeftTab_Num,    arrLeftTab_Direction,    arrLeftTab_Mark};

#define LOCK_FN_NUM 1
#define LOCK_FN_DIRECTION 2
#define LOCK_FN_MARK 3
#define LOCK_FN_SHIFT 4

const int delay_keyboard_char_press = 200;

int m_iLock = 0;
int m_currentOutput = -1;

boolean m_isPressedNum = false;
boolean m_isPressedDirection = false;
boolean m_isPressedMark = false;
boolean m_isPressedShift = false;

int m_iPressSameTimeFuncKeyType = 0;

unsigned long lastPressTime = 0;

struct keyEvent{
  char* pArr;
  int lockType;
  boolean isClearAfterKeyEvent;
};

void setup()
{
  pinMode(mostLeftKey_Enter_5,OUTPUT);
  pinMode(mostLeftKey_N_5 ,OUTPUT);
  pinMode(mostLeftKey_H_5,OUTPUT);
  pinMode(mostLeftKey_Y_5,OUTPUT);
  pinMode(mostLeftKey_Ctrl_5,OUTPUT);
  pinMode(mostLeftKey_FnNum_6,OUTPUT);
  pinMode(mostLeftKey_Esc_6,OUTPUT);
  pinMode(mostLeftKey_Tab_6,OUTPUT);
  pinMode(input_1,INPUT);
  pinMode(input_2,INPUT);
  pinMode(input_3,INPUT);
  pinMode(input_4,INPUT);
  pinMode(input_5,INPUT);
  pinMode(input_6,INPUT);
  Serial.begin(9600);
  Keyboard.begin();
}



void loop()
{
  for (int i=mostLeftKey_Y_5;i<=mostLeftKey_Ctrl_5;i++)
  {
    digitalWrite(i,HIGH);

    m_currentOutput = i;
    releaseCommandKey();
    releaseAltKey();
    releaseCtrlKey();
    setBooleanFnNum(isPressinm_FnNum());
    setBooleanFnDirection(isPressinm_FnDirection());
    setBooleanFnMark(isPressinm_FnMark());
    setBooleanShift(isPressinm_Shift());

    if (isPress())
    {
      selectPressButtonType(i);
    }
    digitalWrite(i,LOW);
  }
  return;

}

void setBooleanCommon(boolean isPressing, boolean* pressed,int lockType)
{

if (lastPressTime + 1000 > millis())
{
	if (m_iPressSameTimeFuncKeyType ==lockType )
	{
	*pressed = false;
return;
	}
}


  static int iDebug = 0;
  if (m_iLock != iDebug)
  {
    Serial.write("setBooleanCommon : ");
    Serial.print(m_iLock);
    Serial.println();    
    iDebug = m_iLock;
  }

  if (isPressing)
  {
    *pressed = true; 
    m_iLock = 0;
  }
  else
  {
    if (*pressed)
    {
      m_iLock = lockType;
    } 
    *pressed = false;
  }
  return; 
}

boolean isPressingCommon(int output,int input)
{
  boolean isPressing = false;
  
  digitalWrite(m_currentOutput,LOW);
  digitalWrite(output ,HIGH);
  
  isPressing = digitalRead(input);
  
  digitalWrite(output,LOW);
  digitalWrite(m_currentOutput,HIGH);

//  if (isPressing)
//  {
//    Serial.write("isPressingCommon");
//        Serial.print(output);
//        Serial.print(input);
//    Serial.println();
//  }

  return isPressing;
}
boolean isPress()
{
  boolean isPress = false;
  isPress = digitalRead(input_1) || isPress;
  isPress = digitalRead(input_2) || isPress;
  isPress = digitalRead(input_3) || isPress;
  isPress = digitalRead(input_4) || isPress;
  isPress = digitalRead(input_5) || isPress;
  isPress = digitalRead(input_6) || isPress;
  return isPress;
}

int pressingFuncKeyType(int defaultNum)
{
  int retNum = defaultNum;
  retNum = isPressinm_FnNum() ? LOCK_FN_NUM : retNum; 
  retNum = isPressinm_FnDirection() ? LOCK_FN_DIRECTION : retNum; 
  retNum = isPressinm_FnMark() ? LOCK_FN_MARK : retNum; 
  retNum = isPressinm_Shift() ? LOCK_FN_SHIFT : retNum;
  return retNum; 
}

void selectPressButtonType(int outputNum)
{
  int iLock = pressingFuncKeyType(m_iLock);
  
  boolean isPressing = iLock != m_iLock;
  
  switch (outputNum)
  {
  case mostLeftKey_Y_5:
    press_mostLeftKey_Y_5(iLock);
    break;
  case mostLeftKey_H_5:
    press_mostLeftKey_H_5(iLock);
    break;
  case mostLeftKey_N_5:
    press_mostLeftKey_N_5(iLock);
    break;
  case mostLeftKey_Enter_5:
    press_mostLeftKey_Enter_5(iLock);
    break;
  case mostLeftKey_Tab_6:
    press_mostLeftKey_Tab_6(iLock);
    break;
  case mostLeftKey_Esc_6:
    press_mostLeftKey_Esc_6(iLock);
    break;
  case mostLeftKey_FnNum_6:
    press_mostLeftKey_FunNum_6(iLock);
    break;
  case mostLeftKey_Ctrl_5:
    press_mostLeftKey_Ctrl_5(iLock);
    break;
  default:
    break;
  }
  lastPressTime = millis();
  return;
}

void keyboardPrint(char* printChar,int iLock)
{
  int iPressingFuncKeyType = pressingFuncKeyType(0);
  
  if (iLock == LOCK_FN_SHIFT)
  {
    Keyboard.press(KEY_LEFT_SHIFT) ;
  }
//  Serial.print(printChar);
//  Serial.println();


  Keyboard.print(printChar);

  if (iLock == LOCK_FN_SHIFT)
  {
    Keyboard.release(KEY_LEFT_SHIFT); 
  }

if (iPressingFuncKeyType > 0)
{
  Serial.print(iPressingFuncKeyType);
  m_iPressSameTimeFuncKeyType = iPressingFuncKeyType;
}

  delay(delay_keyboard_char_press);
  return;
}

void executeCommand(char* commandName,int iLock)
{
//  Serial.print(commandName);
//  Serial.println();
  if (!strcmp(commandName,"Non")) return;
  if (!strcmp(commandName,"""")) 
  {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("'");
    Keyboard.release(KEY_LEFT_SHIFT);
    delay(delay_keyboard_char_press);
    return;
  }

  int iPressingFuncKeyType = pressingFuncKeyType(0);

  if (!strcmp(commandName,"Enter"))
  {
    Keyboard.press(KEY_RETURN);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_RETURN);
  }
  else if (!strcmp(commandName,"Caps"))
  {
	m_iLock = 0;
	m_isPressedShift = true;
	iPressingFuncKeyType = 0;
  }
  else if (!strcmp(commandName,"Fun_Direction"))
  {
  	m_iLock = 0;
	m_isPressedDirection = true;
	iPressingFuncKeyType = 0;
  }
  else if (!strcmp(commandName,"Ctrl"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
  else if (!strcmp(commandName,"Command_L"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
  else if (!strcmp(commandName,"Command_R"))
  {
    Keyboard.press(KEY_RIGHT_GUI);
  }
  else if (!strcmp(commandName,"Alt_L"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
  else if (!strcmp(commandName,"Alt_R"))
  {
    Keyboard.press(KEY_RIGHT_ALT);
  }
  else if (!strcmp(commandName,"Fn_mark"))
  {
	m_iLock = 0;
	m_isPressedMark = true;
	iPressingFuncKeyType = 0;
  }
  else if (!strcmp(commandName,"Space"))
  {
    Keyboard.print(" ");
    delay(delay_keyboard_char_press);
  }
  else if (!strcmp(commandName,"Fn_Num"))
  {
	m_iLock = 0;
	m_isPressedNum = true;
	iPressingFuncKeyType = 0;
  }
  else if (!strcmp(commandName,"Tab"))
  {
    Keyboard.press(KEY_TAB);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_TAB);
  }
  else if (!strcmp(commandName,"Back"))
  {
    Keyboard.press(KEY_BACKSPACE);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_BACKSPACE);
  }
  else if (!strcmp(commandName,"Arrow_Left"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_LEFT_ARROW);
  }
  else if (!strcmp(commandName,"Arrow_Up"))
  {
    Keyboard.press(KEY_UP_ARROW);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_UP_ARROW);
  }
  else if (!strcmp(commandName,"Arrow_Right"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  else if (!strcmp(commandName,"Arrow_Down"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(delay_keyboard_char_press);
    Keyboard.release(KEY_DOWN_ARROW);
  }
  else if (!strcmp(commandName,"Esc"))
  {
    Keyboard.press(KEY_ESC);
    Keyboard.release(KEY_ESC);
  }
  else if (!strcmp(commandName,"EasterEgg"))
  {
    Serial.write("EasterEgg");
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
  }
  
if (iPressingFuncKeyType > 0)
{
  Serial.print(iPressingFuncKeyType);
  m_iPressSameTimeFuncKeyType = iPressingFuncKeyType;
}
  return;
}

int retInputHighNum()
{
  int iRead = -1;
  iRead = digitalRead(input_1) ? 0 : iRead;
  iRead = digitalRead(input_2) ? 1 : iRead;
  iRead = digitalRead(input_3) ? 2 : iRead;
  iRead = digitalRead(input_4) ? 3 : iRead;
  iRead = digitalRead(input_5) ? 4 : iRead;
  iRead = digitalRead(input_6) ? 5 : iRead;
  return iRead;
}


void pressButtonEvent (char** pArr, int iLock)
{
  int iRead = retInputHighNum();

  char* pressButtonType = *(pArr + iRead);
  int len = strlen(pressButtonType);

  if (len == 1)
  {
    keyboardPrint(pressButtonType,iLock); 
  }
  else
  {
    executeCommand(pressButtonType,iLock);
  }
  return;
}



void setBooleanFnNum(boolean isPressing)
{
  setBooleanCommon(isPressing,&m_isPressedNum,LOCK_FN_NUM);
  return; 
}

void setBooleanFnDirection(boolean isPressing)
{
  setBooleanCommon(isPressing,&m_isPressedDirection,LOCK_FN_DIRECTION);
  return; 
}


void setBooleanFnMark(boolean isPressing)
{
  setBooleanCommon(isPressing,&m_isPressedMark,LOCK_FN_MARK);
  return; 
}


void setBooleanShift(boolean isPressing)
{
  setBooleanCommon(isPressing,&m_isPressedShift,LOCK_FN_SHIFT);
  return; 
}


void releaseCommandKey()
{
  boolean isRelease = true;
  isRelease = !(isPressinm_CommandKey_Left() || isPressinm_CommandKey_Right());
  if (isRelease)
  {
    Keyboard.release(KEY_RIGHT_GUI);
    Keyboard.release(KEY_LEFT_GUI);
  }
  return;
}

void releaseAltKey()
{
  boolean isRelease = true;
  isRelease = !(isPressinm_AltKey_Left() || isPressinm_AltKey_Right()) ;
  if (isRelease)
  {
    Keyboard.release(KEY_RIGHT_ALT);
    Keyboard.release(KEY_LEFT_ALT);
  }    
  return;
}

void releaseCtrlKey()
{
  boolean isRelease = true;
  isRelease = !isPressinm_CtrlKey_Left();
  
  if (isRelease)
  {
    Keyboard.release(KEY_RIGHT_CTRL);
    Keyboard.release(KEY_LEFT_CTRL);
  }
  return;
}


boolean isPressinm_CommandKey_Left()
{
  return isPressingCommon(mostLeftKey_Ctrl_5,input_2);
}

boolean isPressinm_AltKey_Left()
{
  return isPressingCommon(mostLeftKey_Ctrl_5,input_3);
}

boolean isPressinm_CtrlKey_Left()
{
  return isPressingCommon(mostLeftKey_Ctrl_5,input_1);
}

boolean isPressinm_CommandKey_Right()
{
  return isPressingCommon(mostLeftKey_Enter_5,input_4);
}

boolean isPressinm_AltKey_Right()
{
  return isPressingCommon(mostLeftKey_Enter_5,input_3);
}

boolean isPressinm_Shift()
{
  return isPressingCommon(mostLeftKey_Enter_5,input_5);
}

boolean isPressinm_FnNum()
{
  return isPressingCommon(mostLeftKey_FnNum_6,input_1);
}

boolean isPressinm_FnDirection()
{
  return isPressingCommon(mostLeftKey_Enter_5,input_2);
}

boolean isPressinm_FnMark()
{
  return isPressingCommon(mostLeftKey_Ctrl_5,input_4);
}

void press_mostLeftKey_Y_5(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftY_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftY_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftY_Mark;
    break;
  default :
    pArr = arrLeftY;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void press_mostLeftKey_H_5(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftH_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftH_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftH_Mark;
    break;
  default :
    pArr = arrLeftH;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void press_mostLeftKey_N_5(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftN_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftN_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftN_Mark;
    break;
  default :
    pArr = arrLeftN;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void press_mostLeftKey_Enter_5(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftEnter_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftEnter_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftEnter_Mark;
    break;
  default :
    pArr = arrLeftEnter;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}


void press_mostLeftKey_Tab_6(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftTab_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftTab_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftTab_Mark;
    break;
  default :
    pArr = arrLeftTab;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void press_mostLeftKey_FunNum_6(int iLock)
{

  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftFnNum_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftFnNum_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftFnNum_Mark;
    break;
  default :
    pArr = arrLeftFnNum;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;

}

void press_mostLeftKey_Ctrl_5(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftCtrl_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftCtrl_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftCtrl_Mark;
    break;
  default :
    pArr = arrLeftCtrl;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void press_mostLeftKey_Esc_6(int iLock)
{
  char** pArr; 
  switch (iLock)
  {
  case LOCK_FN_NUM :
    pArr = arrLeftEsc_Num;
    break;
  case LOCK_FN_DIRECTION :
    pArr = arrLeftEsc_Direction;
    break;
  case LOCK_FN_MARK : 
    pArr = arrLeftEsc_Mark;
    break;
  default :
    pArr = arrLeftEsc;
    break;
  }

  pressButtonEvent(pArr,iLock);
  return;
}

void clearAllFlag()
{
	m_iLock = 0;
	m_isPressedNum = false;
	m_isPressedDirection = false;
	m_isPressedMark = false;
	m_isPressedShift = false;
}



void debug()
{
  digitalWrite(mostLeftKey_Enter_5,HIGH);
  digitalWrite(mostLeftKey_N_5,HIGH);
  digitalWrite(mostLeftKey_H_5,HIGH);
  digitalWrite(mostLeftKey_Y_5,HIGH);
  digitalWrite(mostLeftKey_Ctrl_5,HIGH);
  digitalWrite(mostLeftKey_FnNum_6,HIGH);
  digitalWrite(mostLeftKey_Esc_6,HIGH);
  digitalWrite(mostLeftKey_Tab_6,HIGH);
  debum_buttonPlace();
  delay(100);
  return;  
}



void debum_buttonPlace()
{
  if (digitalRead(input_1) == HIGH)
  {
    Keyboard.print("1");
  }
  if(digitalRead(input_2) == HIGH)
  {
    Keyboard.print("2");
  }
  if (digitalRead(input_3) == HIGH)
  {
    Keyboard.print("3");
  }
  if(digitalRead(input_4) == HIGH)
  {
    Keyboard.print("4");
  }
  if (digitalRead(input_5) == HIGH)
  {
    Keyboard.print("5");
  }
  if(digitalRead(input_6) == HIGH)
  {
    Keyboard.print("6");
  }
  return;
}

