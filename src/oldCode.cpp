// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*    Module:       main.cpp                                                  */
// /*    Author:       jameshou                                                  */
// /*    Created:      11/8/2023, 9:43:46 AM                                     */
// /*    Description:  V5 project                                                */
// /*                                                                            */
// /*----------------------------------------------------------------------------*/

// #include "vex.h"
// #include <string>

// using namespace vex;

// // A global instance of brain used for printing to the V5 Brain screen
// brain  Brain;

// int AutonSelected = 0;
// int AutonMin = 0;
// int AutonMax = 3;

// void drawAutonSelector() {
//   Brain.Screen.clearScreen();
//   Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
//   Brain.Screen.printAt(1, 200, "Auton Selected =  %s   ", AutonSelected);
//   Brain.Screen.setFillColor(red);
//   Brain.Screen.drawRectangle(20, 50, 100, 100);
//   // Brain.Screen.drawCircle(300, 75, 25);
//   Brain.Screen.printAt(25, 75, "Next");
//   Brain.Screen.setFillColor(green);
//   Brain.Screen.drawRectangle(170, 50, 100, 100);
//   Brain.Screen.printAt(175, 75, "GO");
//   Brain.Screen.setFillColor(black);
// }

// // void drawAutonSelector2() {
// //   Brain.Screen.clearScreen();
// //   Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
// //   Brain.Screen.printAt(1, 200, "Auton Selected =  %s   ", AutonSelected);

// //   Brain.Screen.setFillColor("transparent");
// //   Brain.Screen.setPenColor("red");

// //   Brain.Screen.drawRectangle(20, 50, 100, 100);
// //   Brain.Screen.setPenColor("white");
// //   Brain.Screen.printAt(25, 75, "Prev");

// //   Brain.Screen.setPenColor("red");

// //   Brain.Screen.drawRectangle(170, 50, 100, 100);
// //   Brain.Screen.setPenColor("white");
// //   Brain.Screen.printAt(175, 75, "Next");
// //   Brain.Screen.setFillColor("green");
// //   Brain.Screen.setPenColor("green");

// //   Brain.Screen.drawRectangle(320, 50, 100, 100);
// //   Brain.Screen.setPenColor("white");
// //   Brain.Screen.printAt(325, 75, "GO!");

  
// //   Brain.Screen.setFillColor("black");
// //   // Brain.Screen.drawRectangle(170, 50, 100, 100);
// //   // Brain.Screen.printAt(175, 75, "GO");
// //   // Brain.Screen.setFillColor(black);
// // }

// void selectAuton() {
//   bool selectingAuton = true;

//   int x = Brain.Screen.xPosition(); 
//   int y = Brain.Screen.yPosition();

//   if (x >= 20 && x <= 120 && y >= 50 && y <= 150) {
//     AutonSelected++;
//     if (AutonSelected > AutonMax) {
//       AutonSelected = AutonMin; 
//     }  
//   }
//   // FOR AUTON SELECTOR 2 BELOW
//   if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
//     AutonSelected--;
//     if (AutonSelected < AutonMin) {
//       AutonSelected = AutonMax; 
//     }
//   }  

//   //**********************

//   Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", AutonSelected);
//   switch (AutonSelected)  {
//     case 0:
//       Brain.Screen.printAt(1, 250, "Auton Description: Score JUST preload into goal");
//       break;
//     case 1:
//       Brain.Screen.printAt(1, 250, "Auton Description: Offensive Auton: Score ________");
//       break;
//     case 2:
//       Brain.Screen.printAt(1, 250, "Auton Description: Defensive Auton: Score ________");
//       break;
//     case 3:
//       Brain.Screen.printAt(1, 250, "Auton Description: Skills auton");
//       break;
//     default:
//       Brain.Screen.printAt(1, 250, "Auton Description: Score JUST preload into goal");
//       break;
        
//     }

//   if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
//     selectingAuton = false; 
//     Brain.Screen.printAt(1, 200, "Auton  =  %d   Go           ", AutonSelected);
//   }
//   if (!selectingAuton) {
//     Brain.Screen.setFillColor(green);
//     Brain.Screen.drawCircle(300, 75, 25);
//   } else {
//     Brain.Screen.setFillColor(red);
//     Brain.Screen.drawCircle(300, 75, 25);
//   }
//   wait(10, msec);
//   Brain.Screen.setFillColor(black);
// }

// void drawAutonSelect() {
//   Brain.Screen.clearScreen();

//   drawButton(20,50,100,100,"Prev.");
//   drawButton(170,50,100,100,"Next");
//   drawButton(300,50,100,100,"GO!");

//   Brain.Screen.printAt(1, 200, "Auton Selected =  %s   ", AutonSelected);
  

// }

// // simple button to draw on screen
// void drawButton(int bottomLeftX, int bottomLeftY, int width=100, int height=100, std::string buttonText) {
//   Brain.Screen.setFillColor("#ffffff");
//   Brain.Screen.drawRectangle(bottomLeftX, bottomLeftY, width, height);
//   Brain.Screen.setPenColor("#000000");
//   Brain.Screen.printAt(bottomLeftX+5,bottomLeftY+25,buttonText.c_str());
// }