// fix_fft library from:
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1286718155
//
//Grab analog data from X and Y accelerometer axis and perform FFT using 128 samples
//
//
////////////////////////////////////////////////////////

#include "fix_fft.h"

char im[128];
char re[128];
char axis;
char x = A0;
char y = A1;

void setup()
{

  Serial.begin(57600);
  char mark;
}

void GetData(char axis, char mark){
  
  int i;
  int data;
 
  for(i=0;i<128;i++) {
    // The imaginary part is always zero
    im[i] = 0;
   data = analogRead(axis);
    re[i] =(data * 10);
  }
  // compute the FFT of the samples
  fix_fft(re,im,7,0);
  // and send it to the serial monitor
   print_fft((char *)"Acc data",mark);
   
}


// Generate the magnitude of each bin and print it on the serial monitor
void print_fft(char *title, char mark)
{
 
  int i,j,largest;
  char str[65];
  char linfo[6];

  str[64] = 0;  
  largest = 0;
  // Find the largest entry which will determine how many lines
  // are needed to print the whole histogram
  for (i=0; i< 64;i++){
    re[i] = sqrt(re[i] * re[i] + im[i] * im[i]);
    if(re[i] > largest)largest = 32;
  }
  // print a blank line just in case there's
  // garbage when the Serial monitor starts up
  Serial.println("");
  // and the title
  Serial.println(title);
  Serial.println("");
  // print the histogram starting with the highest amplitude
  // and working our way back down to zero.
  for(j=largest;j >= 0;j--) {
    for(i=0;i<64;i++) {
      // If the magnitude of this bin is at least as large as
      // the current magnitude we print an asterisk
      if(re[i] >= j)str[i] = mark;
      // otherwise print a space
      else str[i] = ' ';
    }
    sprintf(linfo,"%3d ",j);
    Serial.print(linfo);
    Serial.println(str);
  }
  // print the bin numbers along the bottom
  Serial.print("    ");
  for(i=0;i<64;i++) {
    Serial.print(i%10);
  }
  Serial.println("");
  Serial.print("    ");
  for(i=0;i<64;i++) {
    if(i < 10)Serial.print(" ");
    else Serial.print((i/10)%10);
  }
  Serial.println("");
}

void loop()
{
  int i;
  for (i=0;i=1;){
    
  GetData(x,'x');  // Axis, Mark used for graph
  GetData(y,'y');
  
  //delay(10000);
  }
}

