#define SensorPin A0

//Store the average value of the sensor feedback
unsigned long int avgValue;
int buf[10],temp;

//Initialize the calibration value.
//Change this value depending on the actual calibration of the sensor.
float cal_value = 0;
 
void setup()
{
  pinMode(13,OUTPUT);  
  Serial.begin(9600);  

  //Test the serial monitor
  Serial.println("Ready");   
}
void loop()
{
  Serial.print("start");

  //Read 10 sample analog values from the sensor.
  //This is done to smoothen the output value.
  for(int i=0;i<10;i++)       
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }

  //Sort the analog values from small to large.
  //This will be used in calculating the running average of the samples in the later stage. 
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }

  avgValue=0;

  //Take the average value of the 6 center samples.
  //This is done in order to remove outliers in the sample to minimize the error.
  for(int i=2;i<8;i++)                      
    avgValue+=buf[i];
  
  //convert the analog into millivolt
  float phValue=(float)avgValue * 5.0/1024/6;
  
  //convert the millivolt into pH value
  phValue=3.5*phValue + cal_value;                 

  //Print the average pH sample value 
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");

  digitalWrite(13, HIGH);       
  delay(800);
  digitalWrite(13, LOW); 
 
}
