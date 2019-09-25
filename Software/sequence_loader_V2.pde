
import processing.serial.*;

// The serial port:
Serial myPort; 
String[] steps = null;
int currentStep = 0;
boolean waitingForArduino = false;
String[] sessionInfo = {"sequence_path", "total_steps", "current_step"};
String logSessionPath = "last_session_log.txt";

/*
    Serial.println("Please state which lens you are using 35, 55 or 90");
    //if 90 make delay longer in takePhoto as 90mm hunts for focus
    
    Serial.println("Place object on the turntable, input character to initiate scan");
*/

void setup() {
  
  size(500,200);
  // List all the available serial ports:
  printArray(Serial.list());
  
  int numOfPorts = Serial.list().length;
  int currentPortIndex = 0;
  boolean arduinoFound = false;
  while(!arduinoFound && currentPortIndex<numOfPorts)
    try{
    // Open the port you are using at the rate you want:
    // Select the corresponding COM Port to Arduino
    myPort = new Serial(this, Serial.list()[currentPortIndex], 9600);
    arduinoFound = true;
    } catch (Exception e) {
      currentPortIndex++;
    }
   
  // Send a capital A out the serial port:
  //myPort.write(65);
  String sessionlogAbsolutePath = sketchPath()+"/last_session_log.txt";
  sessionInfo = loadStrings(sessionlogAbsolutePath);
  println("Session log");
  printArray(sessionInfo);
  selectInput("Select a sequence to process:", "fileSelected");
}

int CAMERA_MOUNT_NO_READY = 0;
int CAMERA_MOUNT_ORIGIN = 1;
int CAMERA_MOUNT_LEVEL = 2;
int CAMERA_MOUNT_CALIBRATED = 3;
int cameraMountState = CAMERA_MOUNT_NO_READY;


// Main loop
void draw() {
  
  
  if(steps!=null){
    // Camera mount calibration
    if(cameraMountState==CAMERA_MOUNT_NO_READY && !waitingForArduino){
      
      background(100,0,0);
      
      println("Send C");
      myPort.write('C');
      waitingForArduino = true;
    } else if(cameraMountState==CAMERA_MOUNT_ORIGIN && !waitingForArduino){
      
      background(51);
      text(sessionInfo[0], 20,20);
      text("Mount the camera and click on the window", 20,50);
      
      if(mousePressed){
        println("Send V");
        myPort.write('V');
        waitingForArduino = true;        
      }
    } if(cameraMountState==CAMERA_MOUNT_LEVEL && !waitingForArduino){
      
      background(51);
      text(sessionInfo[0], 20,20);
      text("Please calibrate the camera and click on the window", 20,50);
      
      if(mousePressed){
        println("Send B");
        myPort.write('B');
        waitingForArduino = true;        
      }
    } 
    else if(cameraMountState==CAMERA_MOUNT_CALIBRATED && !waitingForArduino && steps.length > currentStep){
      background(51);
      text(sessionInfo[0], 20,20);
      text("Recording sequence, step number " + currentStep + " of " + steps.length, 20,50);      
      myPort.write(steps[currentStep]);
      waitingForArduino = true;
      println("Sent step ", currentStep);
      println("Waiting for Arduino");
    } else if(steps.length == currentStep){
      background(51);
      text(sessionInfo[0], 20,20);
      text("End of sequence", 20,50);      
      //println("End of sequence"); 
    }
  }
  


}


// Event for file selection
void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    
    steps = loadStrings(selection.getAbsolutePath());
    println("there are " + steps.length + " lines");
    for (int i = 0 ; i < steps.length; i++) {
      println(steps[i]);
    }
    sessionInfo[0] = selection.getAbsolutePath();
    sessionInfo[1] = Integer.toString(steps.length);
    sessionInfo[2] = "0";
    saveStrings(logSessionPath,sessionInfo);
  }
}

// Serial commands from Arduino
void serialEvent(Serial p) { 
  String msg = p.readString();
  //println("New message", msg);
  if(msg!=null && msg.contains("E")){
    println("step request from Arduino");
    sessionInfo[2] = Integer.toString(currentStep);
    saveStrings(logSessionPath,sessionInfo);
    currentStep++;
    waitingForArduino = false;
  } 
  // Calibrating mount
  else if(msg!=null && msg.contains("C")){
    println("Mount the camera and click on the window");
    cameraMountState = CAMERA_MOUNT_ORIGIN;
    waitingForArduino = false;
  } else if(msg!=null && msg.contains("V")){
    println("Please calibrate the camera and click on the window");
    cameraMountState = CAMERA_MOUNT_LEVEL;
    waitingForArduino = false;
  } else if(msg!=null && msg.contains("B")){
    println("Camera calibrated, ready to start sequence");
    cameraMountState = CAMERA_MOUNT_CALIBRATED;
    waitingForArduino = false;
  }
} 
