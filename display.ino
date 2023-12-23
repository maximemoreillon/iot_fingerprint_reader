void display_setup() {
  // Initializes the SSD1306 display
  
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setBrightness(100);
//  display.flipScreenVertically();
  //display.invertDisplay();
  
  delay(10);
  display_image(logo);
}

void invert_display_periodically(){

  static long display_inversion_time = 0;
  static boolean display_inverted = false;
  
  // Inverts the display every once in a while to prevent screen burn in
  if(millis() - display_inversion_time > DISPLAY_INVERSION_PERIOD){
    display_inversion_time = millis();
    if(display_inverted){
      display_inverted = false;
      display.normalDisplay();
    }
    else {
      display_inverted = true;
      display.invertDisplay();
    }
  }
}

void display_nothing(){
  // Empty screen
  display.clear();
  display.display();
}


void display_wifi_connecting(){
  // Display the connecting animation
  
  long now = millis();
  static long last_change;
  const long change_period = 200;
  static int frame = 0;
  
  if(now-last_change > change_period){
    last_change = now;
    frame++;
    if(frame > 3){
      frame = 0;
    }
  }

  display.clear();
  if(frame == 0) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_1_2_3_off);
  else if(frame == 1) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_2_3_off);
  else if(frame == 2) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_3_off);
  else if(frame == 3) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_full);
  display.display();
  
}


void display_wifi_connected(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, wifi_ok);
  display.display();
}

void display_locked(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, image_locked);
  display.display();
}

void display_unlocked(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, image_unlocked);
  display.display();
}

void display_check(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, image_check);
  display.display();
}

void display_cross(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, image_cross);
  display.display();
}

void display_image(const uint8_t* image_name){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, image_name);
  display.display();
}

void display_message(String message){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 8, message);
  display.display();
}

void handleTimeLimitedContent(){
  // Displaying time limited content
  static boolean displaying_time_limited_content = false;
  long now = millis();
  if(now - display_start_time < DISPLAY_DURATION){
    if(!displaying_time_limited_content) displaying_time_limited_content = true;
  }
  else {
    if(displaying_time_limited_content) {
      displaying_time_limited_content = false;
      // Display logo by default
      display_image(logo);
    }
  }
}


void handle_display(){

  invert_display_periodically();

  //  If wifi not connected, show connecting animation
  static int lastWifiStatus;
  if(lastWifiStatus != WiFi.status()){
    Serial.println("[Wifi] Wifi status changed");
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("[Wifi] Wifi is now connected");
      display_image(logo);
    }
    else if(WiFi.status() != WL_CONNECTED){
      Serial.println("[Wifi] Wifi is now disconnected");
    }

    lastWifiStatus = WiFi.status();
  }

  if(WiFi.status() == WL_CONNECTED){
    handleTimeLimitedContent();
  }
  
  else {
    display_wifi_connecting();
  }
  

}
