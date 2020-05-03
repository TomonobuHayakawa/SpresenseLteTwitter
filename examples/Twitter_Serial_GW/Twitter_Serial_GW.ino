#include <SpresenseLteTwitter.h>

// Sample : Serial port => Twitter gateway
//   Run this program on Spresense and connect via some Serial port terminal software.
//   Type a message and hit enter key, and it will be posted to Twitter.
//   Arduino IDE Serial Monitor is not usable because it doesn't seem able to send Enter key code.

// APN data
#define LTE_APN       "apn"      // replace your APN
#define LTE_USER_NAME "user"     // replace with your username
#define LTE_PASSWORD  "password" // replace with your password

SpresenseLteTwitter twitter("YourToken");

char msg[140+1] = "";
int len = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("> ");

  twitter.begin(LTE_APN, LTE_USER_NAME, LTE_PASSWORD);
}

void loop()
{
  if (Serial.available() > 0) {
    char recv = msg[len++] = Serial.read();
    if (recv == '\b' || recv == 127) { // Backspace
      if (len > 1) {
        len -= 2;
        Serial.print("\b \b");
      }
    }
    else if (recv == '\r' || recv == '\n') { // How to send CR/LF from IDE serial monitor ???
      Serial.print("\r\n");
      len--;
      msg[len] = 0;
      if (len > 0)
        post();
      len = 0;
      Serial.print("\r\n> ");
    }
    else if (len > 140)
      len = 140;
    else
      Serial.print(recv);
  }
}

void post()
{
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    }
    else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  }
  else {
    Serial.println("connection failed.");
  }
  delay(1000);
}

