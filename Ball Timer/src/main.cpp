/**
 * Project for measuring the time is takes for an object to cover a distance.
 * Two sensors used to read object passing points. Based on what was in 
 * my toolbox a light sensor was used to detect the object passing start and a proximity sensor
 * was used to detect the object (a steel ball) passing the finish.
 * 
 * The ESP32 was setup with USB power from the laptop, the usb power pin was used to power the
 * proximity sensor (6-12v) and also the light sensor (5v).
 * 
 * The inputs back to the ESP32 were driven through a level balancer.
 * 
 * The track the ball ran on was two left over chair rail pieces that were concave so ensured
 * the ball stayed on track.
 * 
 * Sample measurements over time were
 * 10" 
 *  317mS
 *  320mS
 *  324mS
 * 20" 
 *  657mS
 *  662mS
 *  656mS
 * 30" 
 *  973mS
 *  983mS
 *  982mS
 * 40" 
 *  1322mS
 *  1330mS
 *  1327mS
 * 50" 
 *  1655mS
 *  1690mS
 *  1672mS
 * 
 * 
 * John Astill
 */
#include <Arduino.h>

#define DEBUG 0
#define START_PIN 33
#define FINISH_PIN 27

long timer = 0;
int runningFlag = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(START_PIN,INPUT_PULLDOWN);
  pinMode(FINISH_PIN,INPUT_PULLDOWN);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  int start = 0x01 ^ digitalRead(START_PIN);
  int finish = 0x01 ^  digitalRead(FINISH_PIN);

#if DEBUG
  Serial.print("Start: ");
  Serial.println(start);
  Serial.print("Finish: ");
  Serial.println(finish);

  delay(500);
#endif

  if (start && runningFlag == false) {
    runningFlag = true;
    timer = millis();

    Serial.println("Started");
  }

  if (finish && runningFlag == true) {
    Serial.print("Finished : ");
    Serial.print(millis() - timer);
    Serial.print("mS");

    runningFlag = false;
  }
}