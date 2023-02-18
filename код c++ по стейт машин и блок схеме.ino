//Константы-состояния:
#define SETTING_STATE 0
#define WAITING_STATE 1
#define WARNING_STATE 2
#define RUNNING_STATE 3
#define SENSOR_WAITING 4
#define SENSOR_READY 5

//Константы команды:
#define RUN_CMD 0x0
#define ACCEPT_CMD 0x1
#define REJECT_CMD 0x2
#define LOOP_CMD 0x3
#define END_CMD 0x4
#define ERROR_CMD 0xFE
#define NO_CMD 0xFF

int state = _STATE;

void setup(){
}


int getCommand(){
 int cmd = NO_CMD;
 if (Serial.available()){
  cmd = Serial.read();
  if (cmd > ERROR_CMD)
   cmd = NO_CMD; 
 }
 return cmd;
}

void settingST_handler(int sensor_cmd){
  if (sensor_cmd == SENSOR_WAITING){
  state = SETTING_STATE;
 }
 else{
   if if (checkObject()){
   state = WAITING_STATE;
   }
  }
 }

void waitingSt_handler(int cmd){
 if (cmd == RUN_CMD){
  state = WARNING_STATE;
 }
 else{
  if (checkObject()){
   state = WAITING_STATE;
  }
 }
}

//elif можно юзать??
void warningSt_handler(int cmd){
 if (cmd == ACCEPT_CMD){
  state = RUNNING_STATE;
 }
 elif (cmd == REJECT_CMD){
   state = WAITING_STATE;
 }
 else{
  if (checkObject()){
   state = WAITING_STATE;
  }
}

void runningSt_handler(int cmd){
 if (cmd == LOOP_CMD){
  state = RUNNING_STATE;
 }
 else{
  if (checkObject()){
   state = WAITING_STATE;
  }
 }
}

void loop(){
 int cmd = getCommand();
 switch(state){
  case SETTING_STATE:{
   settingSt_handler(sensor_cmd);
   break;
  }
  case WAITING_STATE:{
   waitingSt_handler(cmd);
   break;
  }
  case WARNING_STATE:{
   errorSt_handler(cmd);
   break;
  }
  case RUNNING_STATE:{
   runningSt_handler(cmd);
   break;
  }
 }
}