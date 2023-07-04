class CapacitiveKey 
{
  /*
  Class attributes
  Add more key variables if you are adding more modes
  */
  public:
    CapacitiveSensor* sensor;
    bool keyReleased = true;
    char key1;
    char key2;
    char key3;
    unsigned int releaseDelay=20;  
    unsigned int releaseTimer;  
    unsigned int treshold;  
    unsigned int sample;
  /*
  Constructor of the class
  Add more key parameters if you need more modes. 
  */
  CapacitiveKey(uint8_t sendPin, uint8_t receivePin, unsigned int capacitiveTreshold, char k1,char k2,char k3)
  {
    sensor = new CapacitiveSensor(sendPin, receivePin);
    treshold = capacitiveTreshold;
    key1 = k1;
    key2 = k2;
    key3 = k3;
  }

  ~CapacitiveKey() 
  {
    delete sensor;
  }

/* Add more modes accordingly*/
  void keyUpdate(int MODE) 
  { 
    sample = sensor->capacitiveSensorRaw(1);
    if (sample > treshold) 
    {
      if (keyReleased) 
      {      
        switch(MODE)
        { 
          case (0):
            if(key1!=0) Keyboard.press(key1);
            if(RGB_LED_MODE==1) setRgbLedColor(20,0,20);
            break;

          case (1):
            if(key2!=0) Keyboard.press(key2);
            if(RGB_LED_MODE==1) setRgbLedColor(0, 1, 0); 
            break;

          case (2):
            if(key3!=0) Keyboard.press(key3);
            if(RGB_LED_MODE==1) setRgbLedColor(0, 0, 20); 
            break;

          //if you have more modes, add them here.

          case (NUMBER_OF_MODES-1):
            if(RGB_LED_MODE==1) setRgbLedColor(20, 0, 0); 
            break;

          default:
            setRgbLedColor(255,255,255); //You should never get here.
            break;
        }
        keyReleased = false;
      }
      releaseTimer = releaseDelay;
    }
    else 
    {
      if (!keyReleased) 
      {
        if (releaseTimer == 0) 
        {
          switch(MODE)
          { 
            case (0):
              Keyboard.release(key1);
              break;
            
            case (1):
              Keyboard.release(key2);
              break;

            case (2):
              Keyboard.release(key3);
              break;

            //if you have more modes, add them here.

            case (NUMBER_OF_MODES-1): /* Not needed to do anything*/
            default:
              break;
  
          }
          if(RGB_LED_MODE==1) setRgbLedColor(0, 0, 0); 
          keyReleased = true;
        }
        else 
        {
          releaseTimer--;
        }
      }
    }
  }
};
