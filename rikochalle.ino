#define threshold 12

#define right_1 11
#define right_2 12
#define right_speed 10

#define left_1 7
#define left_2 8
#define left_speed 9

#define right_sensor_pin A0
#define left_sensor_pin A3

#define robot_speed 180

void setup(){
 // 右側のモーター
 pinMode(right_1,OUTPUT);
 pinMode(right_2,OUTPUT);
 pinMode(right_speed,OUTPUT);
 pinMode(right_sensor_pin,INPUT);

 // 左側のモーター
 pinMode(left_1,OUTPUT);
 pinMode(left_2,OUTPUT);
 pinMode(left_speed,OUTPUT);
 pinMode(left_sensor_pin,INPUT);

 Serial.begin(115200);

 analogWrite(right_speed, robot_speed);
 analogWrite(left_speed, robot_speed);

}

void loop(){

   // 右
   int sensor_r ;
   int distance_r;
   sensor_r = analogRead(right_sensor_pin);
   distance_r = (6762/(sensor_r-9))-4;

   // 左
   int sensor_l ;
   int distance_l;
   sensor_l = analogRead(left_sensor_pin);
   distance_l = (6762/(sensor_l-9))-4;

   Serial.print(distance_r);
   Serial.print(” , “);
   Serial.println(distance_l);

//        motor_right(sin(2*PI*mills/10000))  //-1.0~1.0


   if (distance_r <= threshold && distance_l <= threshold){

     //台の上にある
       advance();
       Serial.println(“advance”);

   } else if (distance_r > threshold && distance_l <= threshold){

     // 右が落ちそう
       turnLeft();
       Serial.println(“turnLeft”);

   } else if (distance_r > threshold && distance_l > threshold){

     // 正面から落ちそう
       back();
        Serial.println(“back”);
       delay(random(500, 1000));

//        0~1が生成
       if (random(0,2) == 1) {
         turnLeft();
         Serial.println(“back_left”);
       } else {
         turnRight();
         Serial.println(“back_right”);
       }
       delay(random(1000, 2000));




   } else if (distance_r <= threshold && distance_l > threshold){

     // 左から落ちそう
       turnRight();
       Serial.println(“turnRight”);
   }

}

void advance() {
 rightMotor(true);
 leftMotor(true);
}

void turnRight() {
 rightMotor(false);
 leftMotor(true);
}

void turnLeft() {
 rightMotor(true);
 leftMotor(false);
}

void back() {
 rightMotor(false);
 leftMotor(false);
}

void rightMotor(bool is_advance) {
 if(is_advance) {
   // 右が前に動く
   digitalWrite(right_1,HIGH);
   digitalWrite(right_2,LOW);

 }else {
   // 右が後ろに動く
   digitalWrite(right_1,LOW);
   digitalWrite(right_2,HIGH);
 }
}

void leftMotor(bool is_advance) {
 if(is_advance) {
   // 左が前に動く
   digitalWrite(left_1,HIGH);
   digitalWrite(left_2,LOW);

 }else {
   // 左が後ろに動く
   digitalWrite(left_1,LOW);
   digitalWrite(left_2,HIGH);
 }

}
