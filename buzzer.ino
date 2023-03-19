void buzzer_init() {
  
  pinMode(BUZZER_PIN,OUTPUT);

  // Setting up PWM
  ledcSetup(BUZZER_CHANNEL, 2000, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  ledcWrite(BUZZER_CHANNEL, 0);
}

void buzzer_play_success(){

  tone_custom(1300,100);
  tone_custom(1500,300);

}


void buzzer_play_error(){

  tone_custom(600,100);
  tone_custom(300,300);
  
}


void tone_custom(int freq, int duration){
  ledcWriteTone(BUZZER_CHANNEL, freq);
  ledcWrite(BUZZER_CHANNEL, 125);
  delay(duration);
  ledcWrite(BUZZER_CHANNEL, 0);
}
