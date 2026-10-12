// draw upper text
void drawTopText(char* text) {
  myGLCD.fillScreen(TFT_BLACK);  // Clear screen with black
  myGLCD.setTextSize(3);  // Larger text for bigger screen
  myGLCD.fillRect(0, 0, 800, 35, TFT_RED);  // Red background bar for 800px width
  myGLCD.setTextColor(TFT_WHITE, TFT_RED);  // White text on red background
  
  // Center the text on 800px width
  int textWidth = strlen(text) * 18;  // Approximate width calculation
  int x = (800 - textWidth) / 2;
  myGLCD.setCursor(x, 8);
  myGLCD.print(text);
}

// draw bottom text
void drawBottomText(char* text) {
  myGLCD.setTextSize(2);  // Medium text size
  myGLCD.fillRect(0, 440, 800, 480, TFT_RED);  // Red background bar at bottom
  myGLCD.setTextColor(TFT_WHITE, TFT_RED);  // White text on red background
  
  // Center the text on 800px width
  int textWidth = strlen(text) * 12;  // Approximate width calculation
  int x = (800 - textWidth) / 2;
  if (x < 5) x = 5;  // Minimum margin
  myGLCD.setCursor(x, 450);
  myGLCD.print(text);
}
