void splashScreen() {
  const char* text = "AUTOHOLIK v2";
  int textLength = strlen(text);
  int y = 200; // y position of the text (centered vertically on 800x480)

  myGLCD.setTextColor(TFT_RED, TFT_BLACK);  // Red text on black background
  myGLCD.setTextSize(8);  // Larger text for bigger screen

  for (int i = 0; i < textLength; i++) {
    myGLCD.setCursor(150 + (i * 40), y);  // Better positioning for 800x480
    myGLCD.print(text[i]);
    delay(200); // Delay to create the animation effect
  }

  // Add version info and author
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(TFT_CYAN, TFT_BLACK);  // Cyan color
  myGLCD.setCursor(280, y + 80);
  myGLCD.print("800x480 Edition");
  
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(TFT_YELLOW, TFT_BLACK);  // Yellow color
  myGLCD.setCursor(320, y + 120);
  myGLCD.print("nazgut@gmail.com");

  delay(2000); // Keep the splash screen for 2 seconds
  myGLCD.fillScreen(TFT_BLACK); // Clear the screen with black
  splashScreenFinished = true;
}