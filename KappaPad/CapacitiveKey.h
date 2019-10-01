class CapacitiveKey {
  public:
    CapacitiveSensor* sensor;
    bool keyReleased = true;
    char key;
    unsigned int releaseDelay = 20;
    unsigned int releaseTimer;
    unsigned int threshold;  
    int led;
    unsigned int sample;
    unsigned char ledBrightness;
    CapacitiveKey(uint8_t sendPin, uint8_t receivePin, int statusLED, unsigned int capacitiveThreshold, char keyboardKey, unsigned char ledBrightness)  {
      sensor = new CapacitiveSensor(sendPin, receivePin);
      threshold = capacitiveThreshold;
      key = keyboardKey;
      led = statusLED;
      pinMode(led, OUTPUT);
    }
    ~CapacitiveKey() {
      delete sensor;
    }
    void keyUpdate(bool keyboardActive) {
      sample = sensor->capacitiveSensorRaw(1);
      if (sample > threshold) {
        if (keyReleased) {
          analogWrite(led, 255);
          if (keyboardActive) Keyboard.press(key);
          keyReleased = false;
        }
        releaseTimer = releaseDelay;
      }
      else {
        if (!keyReleased) {
          if (releaseTimer == 0) {
            analogWrite(led, 0);
            Keyboard.release(key);
            keyReleased = true;
          }
          else {
            releaseTimer--;
          }
        }
      }
    }
};

