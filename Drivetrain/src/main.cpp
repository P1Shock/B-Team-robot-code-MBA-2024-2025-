/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hoonigan                                                  */
/*    Created:      8/16/2024, 3:32:03 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

motor motor6 = motor(PORT14, false);
motor motor1 = motor(PORT16, true);
motor motor2 = motor(PORT17,false);
motor motor3 = motor(PORT18,true);
motor motor4 = motor(PORT19,false);
motor motor5 = motor(PORT20, true);
brain brian = brain();
digital_out solenoid1 = digital_out(brian.ThreeWirePort.A);
controller cont = controller();
motor_group lm = motor_group(motor1, motor3);
motor_group rm = motor_group(motor2, motor4);
motor_group intake = motor_group(motor5);
motor_group intakefront = motor_group(motor6);
motor_group intaketwo = motor_group(motor5, motor6);
drivetrain drive = drivetrain(lm,rm);

bool intakeBtn = true;

bool intakefrontBtn = true;

bool intakeBtntwo = false;

bool clampBtn = true;

bool solenoid1Value = false;

void pre_auton(void) {

 

}



void autonomous(void) {
  

  //drive.drive(10,inches);
  //drive.turn(90,right);

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}



void solenoid1Function(){

    if(solenoid1Value == false){

        solenoid1.set(true);
        solenoid1Value = true;

    }else{

        solenoid1.set(false);
        solenoid1Value = false;

    }

}




void btnBPressed(){
  if (clampBtn == true) { 
    clampBtn = false;
  } else {
    clampBtn = true;
  }
}

void btnAPressed(){
    
  if(intakeBtn == true){

    intakeBtn = false;

  }else{

    intakeBtn = true;

  }

  if(intakefrontBtn == true){

    intakefrontBtn = false;

  }else{

    intakefrontBtn = true;

  }
}

void btnYpressed(){

  if(intakeBtntwo == true){
    
    intakeBtntwo = false;

  }else{

    intakeBtntwo = true;
  }
}
void usercontrol(void) {

  cont.ButtonB.pressed(solenoid1Function);
  cont.ButtonA.pressed(btnAPressed);
  cont.ButtonY.pressed(btnYpressed);

  solenoid1.set(false);
  
  lm.spin(forward);
  rm.spin(forward);
  intake.spin(reverse);
  intakefront.spin(reverse);
  
  double ax3,ax1,right,left;
  
  

  
  while (true) {
    
    ax3 = cont.Axis3.position(pct)*1;
    ax1 = cont.Axis1.position(pct)*0.35;

    right = ax3-ax1;
    left = ax3+ax1;
    
    lm.setVelocity(left,pct);
    rm.setVelocity(right,pct);

    if(intakeBtn == true){

      intake.setVelocity(30, percent);

    }else if(intakeBtntwo) {
      intaketwo.setVelocity(-33,percent);
    } else {

      intaketwo.setVelocity(0, percent);
    }
  
  }
  
    if(intakefrontBtn == true){

      intakefront.setVelocity(100, percent);
      
    }else if(intakeBtntwo) {
      intaketwo.setVelocity(-33,percent);
    } else {

      intaketwo.setVelocity(0, percent);
    }
}
  wait(20,msec);


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