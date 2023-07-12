void mqtt_config(){
  iot_kernel.mqtt.setCallback(mqtt_message_callback);
}

void mqtt_message_callback(char* topic, byte* payload, unsigned int payload_length) {

  Serial.print("[MQTT] message received on ");
  Serial.print(topic);
  Serial.print(", payload: ");
  for (int i = 0; i < payload_length; i++) Serial.print((char)payload[i]);
  Serial.println("");

  // Create a JSON object to hold the message
  // Note: size is limited by MQTT library
  StaticJsonDocument<MQTT_MAX_PACKET_SIZE> inbound_JSON_message;

  // Copy the message into the JSON object
  deserializeJson(inbound_JSON_message, payload);

    if(inbound_JSON_message.containsKey("state")){

    Serial.println("[MQTT] Payload is JSON with state");

    // Check what the command is and act accordingly
    // Use strdup so as to use strlwr later on
    char* command = strdup(inbound_JSON_message["state"]);

    if( strcmp(strlwr(command), "locked") == 0 ) {
      if(lock_state != "locked") {
        display_locked();
        display_start_time = millis();
        buzzer_play_notify();
        lock_state = "locked";
      }
      else {
        // Nothing if already locked
      }
    }
    else if( strcmp(strlwr(command), "unlocked") == 0 ) {
      if(lock_state != "unlocked") {
        display_unlocked();
        display_start_time = millis();
        buzzer_play_notify();
        lock_state = "unlocked";
      }
      else {
        // Nothing if already unlocked
      }
    }


    

    free(command);


  }

}

void mqtt_publish_valid_finger(){
  String topic = iot_kernel.mqtt_base_topic + "/events";
  Serial.print("[MQTT] Publishing to ");
  Serial.println(topic);
  


  StaticJsonDocument<MQTT_MAX_PACKET_SIZE> outbound_JSON_message;
  
  outbound_JSON_message["finger"] = "valid";
  
  char mqtt_payload[MQTT_MAX_PACKET_SIZE];
  serializeJson(outbound_JSON_message, mqtt_payload, sizeof(mqtt_payload));


  iot_kernel.mqtt.publish(topic.c_str(), mqtt_payload, MQTT_RETAIN);
  
}
