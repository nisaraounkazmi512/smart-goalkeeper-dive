#include <stdio.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>
#include <webots/motor.h>
#include <webots/robot.h>
#define SPEED 6
#define TIME_STEP 64

int main() {
  WbDeviceTag camera, left_motor, right_motor;
  int i=0;
  wb_robot_init();

  /* Camera device, recognition  and enabling*/
  camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);
  wb_camera_recognition_enable(camera, TIME_STEP);

  /* Motor Hnadlers and target position set to infinity. */
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");


  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);


  /* Main loop */
  while (wb_robot_step(TIME_STEP) != -1) {
    /* Current number recognized Object */
    
    int number_of_objects = wb_camera_recognition_get_number_of_objects(camera);
    printf("\nRecognized %d objects.\n", number_of_objects);
    /* Display objects information */
    const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(camera);
    if (number_of_objects == 0 )
      {
        wb_motor_set_velocity(left_motor, -SPEED);
        wb_motor_set_velocity(right_motor, SPEED);
      }
    else
    {
      if (objects[i].position_on_image[0]  < 125 )
      {
        wb_motor_set_velocity(left_motor, -SPEED);
        wb_motor_set_velocity(right_motor, -SPEED);
      }
      else if (objects[i].position_on_image[0] > 125)
      {
        wb_motor_set_velocity(left_motor, SPEED);
        wb_motor_set_velocity(right_motor, SPEED);
      }
      else
      {
        wb_motor_set_velocity(left_motor, 0.0);
        wb_motor_set_velocity(right_motor, 0.0);
      }
     }
    }

  wb_robot_cleanup();

  return 0;
}