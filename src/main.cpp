/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jameshou                                                  */
/*    Created:      11/8/2023, 9:43:46 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <string>

using namespace vex;

// A global instance of competition
competition Competition;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
digital_out vertWing = digital_out(Brain.ThreeWirePort.A);
digital_out hangWing = digital_out(Brain.ThreeWirePort.B);
motor leftFrontMotor = motor(PORT19, ratio6_1, false);
motor leftBackMotor = motor(PORT18, ratio6_1, false); 
motor rightFrontMotor = motor(PORT1, ratio6_1, true);
motor rightBackMotor = motor(PORT20, ratio6_1, true); 
motor leftMiddleMotor = motor(PORT3, ratio6_1, false);  
motor rightMiddleMotor = motor(PORT10, ratio6_1, true);  
motor intakeMotor = motor(PORT16, ratio6_1, false); 
motor punchMotor = motor(PORT11, ratio36_1, true);  
inertial InertialA = inertial(PORT2);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void SplitDrive(){
    leftFrontMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftBackMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftMiddleMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    rightFrontMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    rightBackMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    rightMiddleMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
}

void setDriveSpeed (int driveSpeed) {
  leftFrontMotor.setVelocity(driveSpeed,percent);
  leftBackMotor.setVelocity(driveSpeed,percent);
  rightFrontMotor.setVelocity(driveSpeed,percent);
  rightBackMotor.setVelocity(driveSpeed,percent);
  leftMiddleMotor.setVelocity(driveSpeed,percent);
  rightMiddleMotor.setVelocity(driveSpeed,percent);
}

void driveStop(){
  leftFrontMotor.stop();
  leftBackMotor.stop();
  leftMiddleMotor.stop();
  rightFrontMotor.stop();
  rightBackMotor.stop();
  rightMiddleMotor.stop();
}
void intake() {
  if (Controller1.ButtonR1.pressing()){
    intakeMotor.spin(forward,100,pct);
  }
  else if (Controller1.ButtonR2.pressing()){
    intakeMotor.spin(reverse,100,pct);
  }
  else {
    intakeMotor.stop();
  }
}

void punch(){
  if (Controller1.ButtonL2.pressing()){
    punchMotor.spin(reverse,100,pct);
  }
  else if (Controller1.ButtonL1.pressing()){
    punchMotor.spin(reverse,100,pct);
  }
  else {
    punchMotor.stop(hold);
  }
}

bool holdWingsBool = false;

void holdWings () {
  while(true){
    wait(50,msec);
    if(!holdWingsBool) {
      if(Controller1.ButtonL2.pressing()) {
        vertWing.set(true);
        holdWingsBool = true;
      }
    }
    if(!Controller1.ButtonL2.pressing()){
      vertWing.set(false);
      holdWingsBool = false;
    }
  } 
}

bool toggle_released = true;

void toggleWings () {
  while(true){
    wait(50,msec);
    if(toggle_released) {
      if(Controller1.ButtonX.pressing()) {
        if (vertWing.value() == 0) {
          vertWing.set(true);
        }
        else {
          vertWing.set(false);
        }
        
        toggle_released = false;
      }
    }
    if(!Controller1.ButtonX.pressing()){
      toggle_released = true;
    }
  } 
}


bool hang_released = true;

void hangWingFunc() {
  if(hang_released) {
    if(Controller1.ButtonB.pressing()) {
      if (hangWing.value() == 0) {
        hangWing.set(true);
      }
      else {
        hangWing.set(false);
      }
      
      hang_released = false;
    }
  }
  if(!Controller1.ButtonB.pressing()){
    hang_released = true;
  }

}

bool A_released = true;

void positionPuncher() {
  if(A_released) {
    if(Controller1.ButtonX.pressing()) {
      punchMotor.spin(reverse);
      wait(0.25,seconds); // FIX TO WHATEVER IT SHOULD BE
      punchMotor.stop();
      
      A_released = false;
    }
  }
  if(!Controller1.ButtonX.pressing()){
    A_released = true;
  }

}

void driveForward(double distance, double speed=70) {   
   leftFrontMotor.setPosition(0,degrees);
   while(leftFrontMotor.position(degrees)<distance){
  
        leftFrontMotor.spin(fwd, speed, pct);
        rightFrontMotor.spin(fwd, speed, pct);
        leftBackMotor.spin(fwd, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
        leftMiddleMotor.spin(fwd, speed, pct);
        rightMiddleMotor.spin(fwd, speed, pct);
    }

    driveStop();
}

void driveReverse(double distance, double speed=70) {   
   leftFrontMotor.setPosition(0,degrees);
   while(leftFrontMotor.position(degrees) > -distance){
  
        leftFrontMotor.spin(reverse, speed, pct);
        rightFrontMotor.spin(reverse, speed, pct);
        leftBackMotor.spin(reverse, speed, pct);
        rightBackMotor.spin(reverse, speed, pct);
        leftMiddleMotor.spin(reverse, speed, pct);
        rightMiddleMotor.spin(reverse, speed, pct);
    }

    driveStop();
}

void turnLeftFUpdated(int target) {  
  double fast_speed = 50;
  double slow_speed = 25;
  int speed = 50;

  InertialA.resetRotation();
  wait(.25, sec); //Let em' get used to stuff

  while(InertialA.rotation(degrees) > -target * .3) { //negative target because turning left is negative while turning right is positive
      speed = fast_speed; 

      leftMiddleMotor.spin(fwd, speed, pct);
      rightMiddleMotor.spin(reverse, speed, pct);
      leftFrontMotor.spin(reverse, speed, pct);
      rightFrontMotor.spin(fwd, speed, pct);
      leftBackMotor.spin(reverse, speed, pct);
      rightBackMotor.spin(fwd, speed, pct);
   }

  while(InertialA.rotation(degrees) > -target) {
      speed = slow_speed; 

      leftMiddleMotor.spin(fwd, speed, pct);
      rightMiddleMotor.spin(reverse, speed, pct);
      leftFrontMotor.spin(reverse, speed, pct);
      rightFrontMotor.spin(fwd, speed, pct); 
      leftBackMotor.spin(reverse, speed, pct);
      rightBackMotor.spin(fwd, speed, pct);
   }
   

   

  driveStop();
    
}

void turnRightF(int targetright) {  
    double fast_speedright = 50;
    double slow_speedright = 25;
    int speed = 50;

    InertialA.resetRotation();
    wait(.25, sec); 
    
    while (InertialA.rotation(degrees) < targetright * .3) {
      speed = fast_speedright; 
      leftMiddleMotor.spin(reverse, speed, pct);
      rightMiddleMotor.spin(fwd, speed, pct);
      leftFrontMotor.spin(fwd, speed, pct);   
      rightFrontMotor.spin(reverse, speed, pct); 
      leftBackMotor.spin(fwd, speed, pct);
      rightBackMotor.spin(reverse, speed, pct);
   }

   while (InertialA.rotation(degrees) < targetright ) {
      speed = slow_speedright; 
      leftMiddleMotor.spin(reverse, speed, pct);
      rightMiddleMotor.spin(fwd, speed, pct);
      leftFrontMotor.spin(fwd, speed, pct);
      rightFrontMotor.spin(reverse, speed, pct);
      leftBackMotor.spin(fwd, speed, pct);
      rightBackMotor.spin(reverse, speed, pct);
   }
   
  driveStop();
   
}

void kPTurnTest(float target) {
  float accuracy=2.0; //how accurate to make the turn in degrees
  float error=target-InertialA.heading(degrees);
  float kp=5.0;
  float speed=kp*error;
  InertialA.resetHeading();  //reset Gyro to zero degrees
  while(fabs(error)>=accuracy) {
    speed=kp*error;
    leftMiddleMotor.spin(reverse, -speed, pct);
    rightMiddleMotor.spin(fwd, speed, pct);
    leftFrontMotor.spin(fwd, speed, pct);
    rightFrontMotor.spin(reverse, -speed, pct);
    leftBackMotor.spin(fwd, speed, pct);
    rightBackMotor.spin(fwd, -speed, pct); 
    error=target-InertialA.heading(degrees);  //calculate error
  }
  driveStop();
}
int AutonSelected = 0;
int AutonMin = 0;
int AutonMax = 2;

void drawAutonSelector2() {
  // clear brain screen and print text
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
  Brain.Screen.printAt(1, 200, "Auton Selected =  %s   ", AutonSelected);

  //set color presets for shapes and text below
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(red);
  
  // draw prev. button
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.setPenColor(white);
  Brain.Screen.printAt(25, 75, "Prev");

  // draw next button
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(170, 50, 100, 100);
  Brain.Screen.setPenColor(white);
  Brain.Screen.printAt(175, 75, "Next");

  // draw GO button
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(320, 50, 100, 100);
  Brain.Screen.setPenColor("white");
  Brain.Screen.printAt(325, 75, "GO!");

  // reset shape fill color to black
  Brain.Screen.setFillColor("black");
}


void selectAuton() {
  // get click position
  int x = Brain.Screen.xPosition(); 
  int y = Brain.Screen.yPosition();
  bool autonSelected = false;

  // if auton not yet selected
  if (autonSelected == false) {
    // go button clicked (auton selected)
    if (x >= 320 && x <= 420 && y >= 50 && y <= 150) {
      autonSelected = true;
      Brain.Screen.printAt(1, 200, "Auton Selected =  %d                             ", AutonSelected);
      Brain.Screen.clearScreen();

      Brain.Screen.printAt(1,40, "--------4610M--------                              ");
    

      Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonSelected);

      switch (AutonSelected)  {
        case 0:
          Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal                              ");
          break;
        case 1:
          Brain.Screen.printAt(1, 225, "Auton Description: Offensive Auton: Score ________                              ");
          break;
        case 2:
          Brain.Screen.printAt(1, 225, "Auton Description: Defensive Auton: Score ________                              ");
          break;
        default:
          Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal                              ");
          break;
      }
    }

    // prev button clicked
    else if (x >= 20 && x <= 120 && y >= 50 && y <= 150) {
      AutonSelected--;
      if (AutonSelected < AutonMin) {
        AutonSelected = AutonMax; 
      }
    }
    // next button clicked
    else if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
      AutonSelected++;
      if (AutonSelected > AutonMax) {
        AutonSelected = AutonMin; 
      }  
    }
  }  
  
  
  //print description of auton selected
  Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonSelected);
  switch (AutonSelected)  {
    case 0:
      Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal               ");
      break;
    case 1:
      Brain.Screen.printAt(1, 225, "Auton Description: Offensive Auton: Score ________                      ");
      break;
    case 2:
      Brain.Screen.printAt(1, 225, "Auton Description: Defensive Auton: Score ________                          ");
      break;
    default:
      Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal                           ");
      break;
  }
}

void controllerDisplay(){
  while(true){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Auton Selected =  %s   ", AutonSelected);
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("InertialA Rot: %f",InertialA.rotation(degrees));
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("InertialA Head: %f",InertialA.heading(degrees));
    Controller1.Screen.setCursor(4,1);
    Controller1.Screen.print("LeftFrontMotor: %f",leftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(50);
  }
}

void initialize() {
    vertWing.set(false);
    hangWing.set(false);
    intakeMotor.setStopping(brake);

    leftFrontMotor.setStopping(brake);
    leftBackMotor.setStopping(brake);
    leftMiddleMotor.setStopping(brake);
    rightFrontMotor.setStopping(brake);
    rightBackMotor.setStopping(brake);
    rightMiddleMotor.setStopping(brake);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA: Calibrating");

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("InertialA: Calibrating");

    InertialA.calibrate();
    // waits for the Inertial Sensor to calibrate
    while (InertialA.isCalibrating()) {
        wait(100, msec);
    }

    thread t2(controllerDisplay);
}


// // -----------
// // auton codes
// // -----------

void preloadAuton(){
  //push preload into goal
  driveForward(700,100);
  wait(0.6,seconds);
  intakeMotor.spin(forward,100,pct);
  wait(1,seconds);
  driveForward(200,100);
  wait(0.5, seconds);
  intakeMotor.stop();
  wait(0.2,seconds);
  driveReverse(200);

  // at the end of auton
  
}

void defensiveAuton(){
  // // drive into matchload bar
  // driveForward(150);
  // vertWing.set(true);
  // wait(0.2,seconds);
  // // get triball out of matchload zone
  // turnRight(180);
  // wait(0.2,seconds);
  // vertWing.set(false);
  // turnLeft(60);
  // // push preload into goal
  // driveForward(150);
  // intakeMotor.spin(forward);
  // driveForward(150);
  // wait(0.2,seconds);
  // // turn around and touch elevation bar
  // driveReverse(50);
  // turnRight(210);
  // wait(0.2,seconds);
  // driveForward(200);
  // turnRight(45);
  // driveForward(200);

  //NEW DEFENSE CODE
  driveForward(500);
  driveReverse(350);
  //Wing function or whatever to get triball out of corner
  turnLeftFUpdated(45);
  driveReverse(200);
  turnRightF(45);
  driveForward(1000);
  turnRightF(90);
  driveForward(300);

  // at the end of auton
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftMiddleMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightMiddleMotor.setStopping(coast);
}
void offensiveAuton() {
  // driveForward(500);
  // wait(0.2,seconds);
  // turnRight(90);
  // wait(0.2,seconds);
  // // score alliance triball
  // intakeMotor.spin(reverse,100,pct); 
  // driveForward(150);
  // wait(0.2,seconds);
  // intakeMotor.stop();
  // driveReverse(300);
  // turnLeft(45);
  // // pick up triball
  // intakeMotor.spin(forward,100,pct);
  // driveForward(150); 
  // wait(0.2, seconds);
  // intakeMotor.stop();
  // turnRight(45);
  // wait(0.2, seconds);
  // //push triball out
  // intakeMotor.spin(reverse,100,pct);
  // driveForward(200);
  // driveReverse(300);

/*
  driveForward(100);
  turnRightF(45);
  driveForward(200);
  turnrightF(150);
  driveForward(400);
  turnleftFUpdated(60);
  driveForward(200);
*/


  driveForward(400);
  turnRightF(90);
  intakeMotor.spin(forward);
  turnRightF(160);
  driveForward(1000);
  intakeMotor.spin(reverse);
  turnRightF(110);
  turnRightF(90);
  vertWing.set(true);
  driveForward(1000);
  intakeMotor.spin(forward);

  // at the end of auton
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftMiddleMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightMiddleMotor.setStopping(coast);
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  initialize();
  drawAutonSelector2();

  Brain.Screen.pressed(selectAuton);
  wait(100,msec);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  // drop intake down
  intakeMotor.spin(reverse);
  wait(0.5,seconds);
  intakeMotor.stop();

  // pick between auton programs
  switch (AutonSelected) {
    case 0:
      preloadAuton();
      break;
    case 1:
      offensiveAuton();
      break;
    case 2:
      defensiveAuton();
      break;

  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftMiddleMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightMiddleMotor.setStopping(coast);
  // User control code here, inside the loop

  // start threads
  thread a(toggleWings);
  thread b(holdWings);
  while (1) {
    
    
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    SplitDrive();
    intake();
    punch();
    hangWingFunc();
    positionPuncher();


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  
  // Prevent main from exiting with an infinite loop.
  
  while (true) {
    wait(100, msec);

  }
}
