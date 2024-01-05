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
digital_out rightWing = digital_out(Brain.ThreeWirePort.A);
digital_out leftWing = digital_out(Brain.ThreeWirePort.B);
motor leftFrontMotor = motor(PORT19, ratio6_1, false);
motor leftBackMotor = motor(PORT18, ratio6_1, false);
motor rightFrontMotor = motor(PORT11, ratio6_1, true);
motor rightBackMotor = motor(PORT14, ratio6_1, true);
motor leftTopMotor = motor(PORT12, ratio6_1, true);
motor rightTopMotor = motor(PORT15, ratio6_1, false);
motor intakeMotor = motor(PORT20, ratio6_1, false);
motor cataMotor = motor(PORT16, ratio36_1, false);
inertial InertialA = inertial(PORT8);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void SplitDrive(){
    leftFrontMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftBackMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
    leftTopMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    rightFrontMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    rightBackMotor.spin(reverse,Controller1.Axis3.position()-Controller1.Axis1.position(),pct);
    rightTopMotor.spin(reverse,Controller1.Axis3.position()+Controller1.Axis1.position(),pct);
}

void setDriveSpeed (int driveSpeed) {
  leftFrontMotor.setVelocity(driveSpeed,percent);
  leftBackMotor.setVelocity(driveSpeed,percent);
  rightFrontMotor.setVelocity(driveSpeed,percent);
  rightBackMotor.setVelocity(driveSpeed,percent);
  leftTopMotor.setVelocity(driveSpeed,percent);
  rightTopMotor.setVelocity(driveSpeed,percent);
}

void driveStop(){
  leftFrontMotor.stop();
  leftBackMotor.stop();
  leftTopMotor.stop();
  rightFrontMotor.stop();
  rightBackMotor.stop();
  rightTopMotor.stop();
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

void cata(){
  if (Controller1.ButtonL2.pressing()){
    cataMotor.spin(reverse,100,pct);
  }
  else if (Controller1.ButtonL1.pressing()){
    cataMotor.spin(reverse,100,pct);
  }
  else {
    cataMotor.stop(hold);
  }
}

int wingVar = 0;

void wings () {
  if (Controller1.ButtonX.pressing()) {
    wingVar += 1;
    wait(10,msec);
  }
  if (wingVar%2 == 1) {
    leftWing.set(true);
    rightWing.set(true);
  }
  else {
    leftWing.set(false);
    rightWing.set(false);
  }
}

void driveForward(double distance, double speed=70) {   
   leftFrontMotor.setPosition(0,degrees);
   while(leftFrontMotor.position(degrees)<distance){
  
        leftFrontMotor.spin(fwd, speed, pct);
        rightFrontMotor.spin(fwd, speed, pct);
        leftBackMotor.spin(fwd, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
        leftTopMotor.spin(fwd, speed, pct);
        rightTopMotor.spin(fwd, speed, pct);
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
        leftTopMotor.spin(reverse, speed, pct);
        rightTopMotor.spin(reverse, speed, pct);
    }

    driveStop();
}

void turnLeft(int target) {   
    InertialA.resetRotation();
    wait(.2, sec); 
    
    while(InertialA.rotation(degrees) > -target) {
        int speed = 5;  

        leftFrontMotor.spin(reverse, speed, pct);
        rightFrontMotor.spin(fwd, speed, pct);
        leftBackMotor.spin(reverse, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
        leftTopMotor.spin(reverse, speed, pct);
        rightTopMotor.spin(fwd, speed, pct);
        wait(10,msec);
    }

    driveStop();
}

void turnRight(int target, int driveSpeed=50) {   
    InertialA.resetRotation();
    wait(.2, sec); 
    
    while(InertialA.rotation(degrees) < target) {
        int speed = driveSpeed;  

        leftFrontMotor.spin(fwd, speed, pct);
        rightFrontMotor.spin(reverse, speed, pct);
        leftBackMotor.spin(fwd, speed, pct);
        rightBackMotor.spin(reverse, speed, pct);
        leftTopMotor.spin(fwd, speed, pct);
        rightTopMotor.spin(reverse, speed, pct);
        wait(10,msec);
    }

    driveStop();
}
void turnLeftFUpdated(int target) {   
    
    InertialA.resetRotation();
    wait(.25, sec); //Let em' get used to stuff 
    
    double change_point = 45; 
    double fast_speed = 50;
    double slow_speed = 5;

    while(InertialA.rotation(degrees) > target/3) {
        int speed = fast_speed;  

        /*leftTopMotor.spin(fwd, speed, pct);
        rightTopMotor.spin(reverse, speed, pct);
        leftFrontMotor.spin(reverse, speed, pct);
        rightFrontMotor.spin(fwd, speed, pct); */
        leftBackMotor.spin(reverse, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
    }

    while(InertialA.rotation(degrees) < target/3) {
        int speed = slow_speed;  

      /*  leftTopMotor.spin(fwd, speed, pct);
        rightTopMotor.spin(reverse, speed, pct);
        leftFrontMotor.spin(reverse, speed, pct);
        rightFrontMotor.spin(fwd, speed, pct); */
        leftBackMotor.spin(reverse, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
    }


    /*leftTopMotor.stop();
    rightTopMotor.stop();
    leftFrontMotor.stop();
    rightFrontMotor.stop(); */
    leftBackMotor.stop();
    rightBackMotor.stop();  
}

void turnRightF(int target) {   
    
    InertialA.resetRotation();
    wait(.25, sec); //Let 'em settle...
    
    double change_point = 45; 
    double fast_speed = 50;
    double slow_speed = 5;
    int speed = 50;
    while (InertialA.rotation(degrees) < target/2) { 
        speed = fast_speed;  


        /*leftTopMotor.spin(reverse, speed, pct);
        rightTopMotor.spin(fwd, speed, pct);
        leftFrontMotor.spin(fwd, speed, pct);    
        rightFrontMotor.spin(reverse, speed, pct); */
        leftBackMotor.spin(fwd, speed, pct);
        rightBackMotor.spin(fwd, speed, pct);
    }

    while (InertialA.rotation(degrees) > target/2 ) { 
        speed = slow_speed;  

      /*  leftTopMotor.spin(reverse, speed, pct);
        rightTopMotor.spin(fwd, speed, pct);
        leftFrontMotor.spin(fwd, speed, pct);
        rightFrontMotor.spin(reverse, speed, pct); */ 
        leftBackMotor.spin(fwd, speed, pct);
        rightBackMotor.spin(fwd, speed, pct); 
    }
    /*leftTopMotor.stop();
    rightTopMotor.stop();
    leftFrontMotor.stop();
    rightFrontMotor.stop(); */
    leftBackMotor.stop();
    rightBackMotor.stop();
}
void controllerDisplay(){
  while(true){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA Rot: %f",InertialA.rotation(degrees));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("InertialA Head: %f",InertialA.heading(degrees));
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("LeftFrontMotor: %f",leftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(50);
  }
}
void inertialBrainUpdate() {
  while(true) {
    Brain.Screen.printAt(1,120, "Inertial Heading: %f",InertialA.heading(degrees));
    this_thread::sleep_for(50);
  }
}
void initialize() {
    leftWing.set(false);
    rightWing.set(false);
    intakeMotor.setStopping(brake);

    leftFrontMotor.setStopping(brake);
    leftBackMotor.setStopping(brake);
    leftTopMotor.setStopping(brake);
    rightFrontMotor.setStopping(brake);
    rightBackMotor.setStopping(brake);
    rightTopMotor.setStopping(brake);

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
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftTopMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightTopMotor.setStopping(coast);
}

void defensiveAuton(){
  // // drive into matchload bar
  // driveForward(150);
  // leftWing.set(true);
  // wait(0.2,seconds);
  // // get triball out of matchload zone
  // turnRight(180);
  // wait(0.2,seconds);
  // leftWing.set(false);
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

  // at the end of auton
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftTopMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightTopMotor.setStopping(coast);
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

  // at the end of auton
  leftFrontMotor.setStopping(coast);
  leftBackMotor.setStopping(coast);
  leftTopMotor.setStopping(coast);
  rightFrontMotor.setStopping(coast);
  rightBackMotor.setStopping(coast);
  rightTopMotor.setStopping(coast);
}

void skillsAuton() {

  // 50% drive speed
  setDriveSpeed(50);
  
  // max shooting speed
  cataMotor.setVelocity(100,percent);

  // drop intake
  intakeMotor.spinFor(100,degrees);

  // go forward, turn to position bar
//  driveForward(200,50); UNCOMMENT IN REAL CODE (((((((((((((99(((((((((())))))))))))))))))))))

  wait(0.5, seconds);

  // turn right for one second
  turnRightF(90);

  wait(1,seconds);
/*
  leftBackMotor.stop();
  leftFrontMotor.stop(); UNCOMMENT IN REAL CODE (((((((((((((((((((((((())))))))))))))))))))))))

  // go next to bar
  driveForward(100, 50);

  wait(1,seconds);
*/
  // turn left while touching bar (to straighten up)

  turnLeftFUpdated(90);

  wait(1.5,seconds);
/*
  leftBackMotor.stop();
  leftFrontMotor.stop();
  
  wait(1, seconds); UNCOMMENT IN REAL CODE ((((((((((((((((((()))))))))))))))))))

  // shoot for 40 seconds

  cataMotor.spin(reverse);

  wait(40,seconds);

  cataMotor.stop();
*/
}

int AutonSelected = 0;
int AutonMin = 0;
int AutonMax = 3;

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

  // go button clicked
  if (autonSelected == false) {
    if (x >= 320 && x <= 420 && y >= 50 && y <= 150) {
      autonSelected = true;
      Brain.Screen.printAt(1, 200, "Auton Chosen =  %d                             ", AutonSelected);
      Brain.Screen.clearScreen();

      Brain.Screen.printAt(1,40, "--------4610M--------                              ");

      thread t1(inertialBrainUpdate);

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
        case 3:
          Brain.Screen.printAt(1, 225, "Auton Description: Skills auton                              ");
          break;
        default:
          Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal                              ");
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
    case 3:
      Brain.Screen.printAt(1, 225, "Auton Description: Skills auton                                                 ");
      break;
    default:
      Brain.Screen.printAt(1, 225, "Auton Description: Score JUST preload into goal                           ");
  }
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
  wait (3, sec);
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
    case 3:
      skillsAuton();
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
  // User control code here, inside the loop
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
    cata();
    wings();

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
  //Skills, testing the turns that I (calv) updated
  skillsAuton();
  // Prevent main from exiting with an infinite loop.
  
  while (true) {
    wait(100, msec);

  }
}
