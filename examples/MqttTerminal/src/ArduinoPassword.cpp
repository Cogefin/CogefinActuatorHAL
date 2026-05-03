#include "./ArduinoPassword.h"

#ifdef USE_MQTT_AUTH

Passwd::Passwd() : userNum(0)
{
}

bool Passwd::begin(uint8_t chipSelect) {
  if (!SD.begin(chipSelect)) {
    return false;
  }
  return true;
}

void Passwd::parsePasswdEntry(char userName[], uint8_t passwdHash[], char line[]) {
  int length=strlen(line);
  for (int i=0; i< MAX_USER_NAME_LEN; i++) {
    userName[i]=0;
  }
  for (int i=0; i< HASH_SIZE ; i++) {
    passwdHash[i]=0;
  }
#ifdef DEBUG
  Serial.println("");
  Serial.print("length = ");Serial.print(length);Serial.print(" , line = ");Serial.println(line);
  Serial.println("");
#endif /* DEBUG */

  int counter=0;
  while(true) {
    if (line[counter]==':') {
      counter++;
      break;
    }
    userName[counter]=line[counter];
    counter++;
  }
#ifdef DEBUG
  Serial.print("counter = ");Serial.println(counter);
  Serial.println("");
#endif /* DEBUG */
  convertPasswdHashStr(passwdHash,line+counter);
#ifdef DEBUG
  Serial.print("user name = ");Serial.print(userName);Serial.print(" , passwd = ");
  for (int i=0; i< HASH_SIZE; i++) {
    char buffer[3]; sprintf (buffer, "%02x", passwdHash[i]);
    Serial.print(buffer);
  }
  Serial.println("");
#endif /* DEBUG */
}

bool Passwd::init(char *path) {
  File passwdFile = SD.open(path);
  if (!(passwdFile)) return false;
  char buff[HASH_SIZE + MAX_USER_NAME_LEN];
  memset(buff,0,HASH_SIZE + MAX_USER_NAME_LEN);
  userNum=0;
  int counter=0;
  bool skip=false;
  while (passwdFile.available()) {
    if (userNum==USER_NUM_MAX) break;
    char c = passwdFile.read();
    if ((c!=CR) && (c!=LF)) {
      if ((counter==0) && (c=='#')) skip=true;
      if (!skip) {
        buff[counter]=c;
        counter++;
      }
    } else {
      skip=false;
      if (counter!=0) {
        parsePasswdEntry(passList[userNum].userName, passList[userNum].passwdHash, buff);
        userNum++;
        counter=0;
      }
    }
  }
  passwdFile.close();
}

void Passwd::convertPasswdHashStr(uint8_t hash[],char *str) {
  memset(hash, 0, HASH_SIZE);
  int counter=0;
  for (int i=0;i<HASH_SIZE;i++){
    char buffer[3];
    memset(buffer,0,3);
    memcpy(buffer, str+counter, 2);
    hash[i]=(uint8_t) strtol(buffer, NULL, 16);
    counter+=2;
  }
}

void Passwd::convertPasswdStr(uint8_t pass[], char str[]) {
  size_t num=strlen(str);
  for (int i=0; i< num ; i++){
    pass[i]=(uint8_t) str[i];
  }
}

bool Passwd::CheckPasswd(char userName[], char password[]){
  SHA3_512 hash;
  uint8_t mdValue[HASH_SIZE];
  hash.reset();
  hash.update(password, strlen(password));
  hash.finalize(mdValue, sizeof(mdValue));
#ifdef DEBUG
  Serial.print("userName = ");Serial.println(userName);
  Serial.print("password = ");
  for (int i=0; i< HASH_SIZE; i++) {
    char buffer[3]; sprintf (buffer, "%02x", mdValue[i]);
    Serial.print(buffer);
  }
  Serial.println("");
#endif /* DEBUG */
  for (int i=0; i< userNum; i++){
#ifdef DEBUG
    Serial.print("entry Name = ");Serial.println(passList[i].userName);
    //Serial.print("hash value = ");Serial.println(passList[i].passwdHash);
    Serial.print("hash value = ");
    for (int j=0; j< HASH_SIZE; j++) {
      char buffer[3]; sprintf (buffer, "%02x", passList[i].passwdHash[j]);
      Serial.print(buffer);
    }
    Serial.println("");
#endif /* DEBUG */
    if (0!=strcmp(userName, passList[i].userName)) continue;
    bool flag=true;
    for (int j=0; j< HASH_SIZE; j++) {
      if (mdValue[j]!=passList[i].passwdHash[j]) {
        flag=false;
      }
    }
    if (flag) return true;
  }
  return false;
}
#endif /* USE_MQTT_AUTH */
