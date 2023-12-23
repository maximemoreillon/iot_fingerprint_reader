void checkWifiConnection(){
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

  
  if(WiFi.status() != WL_CONNECTED){
    display_wifi_connecting();
  }


}
