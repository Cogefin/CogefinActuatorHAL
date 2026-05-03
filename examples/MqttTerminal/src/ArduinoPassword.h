
//#define DEBUG

#ifndef __PASSWD_CLASS__
#define __PASSWD_CLASS__

#include "../config.h"

#ifdef USE_MQTT_AUTH

#include <Crypto.h>
#include <SHA3.h>
#include <SPI.h>
#include <SD.h>

#define CR 0x0d
#define LF 0x0a

#define HASH_SIZE 64
#define USER_NUM_MAX 16
#define MAX_USER_NAME_LEN 32

typedef struct {
  char userName[MAX_USER_NAME_LEN];
  uint8_t passwdHash[HASH_SIZE];
} PasswdEntry;

class Passwd {
  public:
    Passwd();
    bool init(char *path);
    bool CheckPasswd(char userName[], char password[]);
    bool begin(uint8_t chipSelect);
  private:
    uint8_t userNum;
    PasswdEntry passList[USER_NUM_MAX];
    void convertPasswdHashStr(uint8_t hash[],char *str);
    void convertPasswdStr(uint8_t pass[], char str[]);
    void parsePasswdEntry(char userName[], uint8_t passwdHash[], char line[]);
};

#endif /* USE_MQTT_AUTH */

#endif /* __PASSWD_CLASS__ */

