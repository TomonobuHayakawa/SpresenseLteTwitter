#include <SpresenseLteTwitter.h>

// APN data
#define LTE_APN       "apn"      // replace your APN
#define LTE_USER_NAME "user"     // replace with your username
#define LTE_PASSWORD  "password" // replace with your password

SpresenseLteTwitter twitter("YourToken");
char msg[] = "Hello, World! I'm Spresense!";

void setup()
{
  Serial.begin(115200);
  Serial.println("connecting ...");

  twitter.begin(LTE_APN, LTE_USER_NAME, LTE_PASSWORD);

  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println(twitter.response());
    }
    else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  }
  else {
    Serial.println("connection failed.");
  }
}

void loop()
{
}

