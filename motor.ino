void motor(int cocktailValue) {
  myGLCD.fillScreen(TFT_BLACK);  // Clear screen
  drawTopText("Preparing Your Cocktail...");
  drawBottomText("Please wait while your drink is being prepared");

  unsigned long startTimes[RELAY_PIN_COUNT];
  bool pouring[RELAY_PIN_COUNT];
  int activeBottles = 0;

  // Count active bottles and show preparation screen
  for (int i = 0; i < RELAY_PIN_COUNT; i++) {
    if (drinksComposition[cocktailValue][i] != 0) {
      activeBottles++;
    }
  }

  // Draw cocktail name prominently
  myGLCD.setTextSize(4);
  myGLCD.setTextColor(0xFFE0, 0x0000);  // Yellow text
  myGLCD.setCursor(50, 80);
  myGLCD.print("Making: ");
  myGLCD.setTextColor(0xFFFF, 0x0000);  // White text
  myGLCD.print(cocktailsName[cocktailValue]);

  // Draw progress area title
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(0x07FF, 0x0000);  // Cyan text
  myGLCD.setCursor(50, 140);
  myGLCD.print("Pouring Progress:");

  int yPos = 180;
  int bottleIndex = 0;

  // Initialize arrays and start pouring
  for (int i = 0; i < RELAY_PIN_COUNT; i++) {
    if (drinksComposition[cocktailValue][i] != 0) { // check if we use bottle
      // Draw bottle info with modern styling
      myGLCD.fillRect(50, yPos - 5, 750, yPos + 35, 0x2104);  // Dark background
      
      myGLCD.setTextSize(2);
      myGLCD.setTextColor(0xFFFF, 0x2104);  // White text on dark background
      myGLCD.setCursor(60, yPos + 5);
      myGLCD.print(drinksName[i]);
      myGLCD.setCursor(600, yPos + 5);
      myGLCD.print(drinksComposition[cocktailValue][i]);
      myGLCD.print(" ml");

      // Draw progress bar background
      myGLCD.drawRect(350, yPos + 5, 580, yPos + 25, 0xFFFF);  // White border
      myGLCD.fillRect(351, yPos + 6, 579, yPos + 24, 0x0000);  // Black fill

      // Start pouring for this bottle
      pouring[i] = true;
      startTimes[i] = millis();
      digitalWrite(relayPins[i], HIGH);
      
      yPos += 45;
      bottleIndex++;
    } else {
      pouring[i] = false; // No pouring needed for this bottle
    }
  }

  // Continue until all bottles are done pouring
  bool allDone = false;
  while (!allDone) {
    allDone = true;
    yPos = 180;
    bottleIndex = 0;
    
    for (int i = 0; i < RELAY_PIN_COUNT; i++) {
      if (drinksComposition[cocktailValue][i] != 0) {
        if (pouring[i]) {
          // Calculate progress
          unsigned long elapsed = millis() - startTimes[i];
          unsigned long totalTime = drinksComposition[cocktailValue][i] * TIME_BY_ML;
          int progressWidth = (elapsed * 228) / totalTime;  // 228 is max progress bar width
          if (progressWidth > 228) progressWidth = 228;
          
          // Update progress bar
          myGLCD.fillRect(351, yPos + 6, 351 + progressWidth, yPos + 24, 0x07E0);  // Green progress
          
          if (elapsed >= totalTime) {
            // Stop pouring for this bottle
            digitalWrite(relayPins[i], LOW);
            pouring[i] = false;
            
            // Complete progress bar
            myGLCD.fillRect(351, yPos + 6, 579, yPos + 24, 0x07E0);  // Full green
            
            // Show completion indicator
            myGLCD.setTextSize(2);
            myGLCD.setTextColor(0x07E0, 0x2104);  // Green text
            myGLCD.setCursor(680, yPos + 5);
            myGLCD.print("DONE");

            // Reduce quantity of the current drink in EEPROM
            if (EEPROM.read(i) < 15) {
              EEPROM.write(i, 0);
            } else {
              EEPROM.write(i, EEPROM.read(i) - (int(drinksComposition[cocktailValue][i]) / 10));
            }
          } else {
            allDone = false; // Not all done yet
          }
        }
        yPos += 45;
        bottleIndex++;
      }
    }
    delay(100);  // Small delay for smooth progress updates
  }

  // Show completion message
  myGLCD.fillScreen(0x0000);
  myGLCD.setTextSize(4);
  myGLCD.setTextColor(0x07E0, 0x0000);  // Green text
  myGLCD.setCursor(200, 150);
  myGLCD.print("COMPLETED!");
  
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(0xFFFF, 0x0000);  // White text
  myGLCD.setCursor(150, 220);
  myGLCD.print("Your cocktail is ready!");
  
  delay(2000);

  // Check for low quantity warnings
  int lowBottles = 0;
  for (int i = 0; i < RELAY_PIN_COUNT; i++) {
    if (EEPROM.read(i) <= 5) {
      lowBottles++;
    }
  }

  if (lowBottles > 0) {
    myGLCD.fillScreen(0x0000);
    drawTopText("LOW BOTTLE WARNING");
    drawBottomText("Please refill the following bottles");
    
    myGLCD.setTextSize(3);
    myGLCD.setTextColor(0xF800, 0x0000);  // Red text
    myGLCD.setCursor(50, 80);
    myGLCD.print("Low Level Bottles:");
    
    int yPos = 130;
    for (int i = 0; i < RELAY_PIN_COUNT; i++) {
      if (EEPROM.read(i) <= 5) {
        myGLCD.fillRect(50, yPos - 5, 750, yPos + 30, 0xF800);  // Red background
        myGLCD.setTextSize(2);
        myGLCD.setTextColor(0xFFFF, 0xF800);  // White text on red
        myGLCD.setCursor(60, yPos + 5);
        myGLCD.print(drinksName[i]);
        myGLCD.setCursor(400, yPos + 5);
        myGLCD.print("Level: ");
        myGLCD.print(EEPROM.read(i) * 10);
        myGLCD.print(" ml");
        myGLCD.setCursor(580, yPos + 5);
        myGLCD.print("REFILL NEEDED!");
        yPos += 40;
      }
    }
    
    // Continue button
    myGLCD.fillRoundRect(300, 380, 500, 430, 15, 0x001F);  // Blue button
    myGLCD.drawRoundRect(300, 380, 500, 430, 15, 0xFFFF);  // White border
    myGLCD.setTextSize(3);
    myGLCD.setTextColor(0xFFFF, 0x001F);  // White text on blue
    myGLCD.setCursor(340, 395);
    myGLCD.print("CONTINUE");
    
    waitForTouch();
    param();
  } else {
    // Continue button
    myGLCD.fillRoundRect(300, 300, 500, 350, 15, 0x001F);  // Blue button
    myGLCD.drawRoundRect(300, 300, 500, 350, 15, 0xFFFF);  // White border
    myGLCD.setTextSize(3);
    myGLCD.setTextColor(0xFFFF, 0x001F);  // White text on blue
    myGLCD.setCursor(340, 315);
    myGLCD.print("CONTINUE");
    
    waitForTouch();
    drink(0);
  }
}
