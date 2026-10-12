void param()
{
  myGLCD.setTextSize(2);

  //*******************************************************Draw Settings Menu
  drawTopText("Settings - Autoholik v2");
  drawBottomText(funnySentence[random(0,FUNNY_SENTENCE_SIZE)]);
  
  // Draw larger buttons for 800x480 display
  myGLCD.fillRoundRect(100, 60, 700, 120, 15, TFT_RED);   // Reset bottles button
  myGLCD.fillRoundRect(100, 140, 700, 200, 15, TFT_RED);  // Information button
  myGLCD.fillRoundRect(100, 220, 700, 280, 15, TFT_RED);  // Clean system button
  myGLCD.fillRoundRect(100, 300, 700, 360, 15, TFT_RED);  // Calibration button
  myGLCD.fillRoundRect(100, 380, 700, 440, 15, TFT_BLUE);  // Back button (blue)
  
  // Draw button borders
  myGLCD.drawRoundRect(100, 60, 700, 120, 15, TFT_WHITE);
  myGLCD.drawRoundRect(100, 140, 700, 200, 15, TFT_WHITE);
  myGLCD.drawRoundRect(100, 220, 700, 280, 15, TFT_WHITE);
  myGLCD.drawRoundRect(100, 300, 700, 360, 15, TFT_WHITE);
  myGLCD.drawRoundRect(100, 380, 700, 440, 15, TFT_WHITE);
  
  // Draw button text
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(TFT_WHITE, TFT_RED);  // White text on red background
  myGLCD.setCursor(280, 80);
  myGLCD.print("Reset Bottles");
  
  myGLCD.setCursor(310, 160);
  myGLCD.print("Information");
  
  myGLCD.setCursor(290, 240);
  myGLCD.print("Clean System");
  
  myGLCD.setCursor(320, 320);
  myGLCD.print("Calibration");
  
  myGLCD.setTextColor(TFT_WHITE, TFT_BLUE);  // White text on blue background
  myGLCD.setCursor(360, 400);
  myGLCD.print("BACK");

  //*******************************************************Wait for touch
  TSPoint p = ts.getPoint();
  while (p.z < ts.pressureThreshhold) p = ts.getPoint();
  
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
  
  int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
  int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);

  //*******************************************************Handle Reset Bottles
  if (x >= 100 && x <= 700 && y >= 60 && y <= 120) {
    
    myGLCD.fillScreen(TFT_BLACK);  // Clear screen
    drawTopText("Reset Bottle Levels");
    drawBottomText("Touch bottles to reset to 500ml");
    
    myGLCD.setTextSize(2);
    
    // Draw back button
    myGLCD.fillRoundRect(100, 400, 700, 450, 15, TFT_BLUE);  // Blue back button
    myGLCD.drawRoundRect(100, 400, 700, 450, 15, TFT_WHITE);
    myGLCD.setTextColor(TFT_WHITE, TFT_BLUE);
    myGLCD.setCursor(360, 415);
    myGLCD.print("BACK");
    
    while (1) {
      // Draw bottle status grid (2x3 layout)
      for (int i = 0; i < 6; i++) {
        int col = i % 2;
        int row = i / 2;
        int btnX = 150 + col * 300;
        int btnY = 70 + row * 100;
        
        // Choose color based on bottle level
        int level = EEPROM.read(i) * 10;
        uint16_t btnColor;
        if (level > 200) btnColor = TFT_GREEN;      // Green
        else if (level > 100) btnColor = TFT_YELLOW;  // Yellow  
        else btnColor = TFT_RED;                   // Red
        
        myGLCD.fillRoundRect(btnX, btnY, btnX + 200, btnY + 80, 10, btnColor);
        myGLCD.drawRoundRect(btnX, btnY, btnX + 200, btnY + 80, 10, TFT_WHITE);
        
        // Draw bottle info
        myGLCD.setTextColor(TFT_BLACK, btnColor);  // Black text on colored background
        myGLCD.setCursor(btnX + 10, btnY + 10);
        myGLCD.print(drinksName[i]);
        myGLCD.setCursor(btnX + 10, btnY + 35);
        myGLCD.print(level);
        myGLCD.print(" ml");
        myGLCD.setCursor(btnX + 10, btnY + 55);
        myGLCD.print("Tap to reset");
      }

      TSPoint p = ts.getPoint();
      if (p.z > ts.pressureThreshhold) {
        pinMode(A2, OUTPUT);
        pinMode(A3, OUTPUT);
        digitalWrite(A3, HIGH);
        digitalWrite(A2, HIGH);
        
        int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
        int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);
        
        // Check bottle buttons
        for (int i = 0; i < 6; i++) {
          int col = i % 2;
          int row = i / 2;
          int btnX = 150 + col * 300;
          int btnY = 70 + row * 100;
          
          if (x >= btnX && x <= btnX + 200 && y >= btnY && y <= btnY + 80) {
            EEPROM.write(i, 50);  // Reset to 500ml (50 * 10)
            delay(500);  // Visual feedback delay
            break;
          }
        }
        
        // Check back button
        if (x >= 100 && x <= 700 && y >= 400 && y <= 450) {
          param();
          return;
        }
      }
    }
  }

  //*******************************************************Handle Information
  else if (x >= 100 && x <= 700 && y >= 140 && y <= 200) {
    myGLCD.fillScreen(TFT_BLACK);
    drawTopText("System Information");
    drawBottomText("Autoholik v2 - Your premium cocktail assistant");
    
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(TFT_YELLOW, TFT_BLACK);  // Yellow
    myGLCD.setCursor(50, 70);
    myGLCD.print("System: Autoholik v2 - 800x480 Edition");
    
    myGLCD.setTextColor(TFT_CYAN, TFT_BLACK);  // Cyan
    myGLCD.setCursor(50, 100);
    myGLCD.print("Author: nazgut@gmail.com");
    
    myGLCD.setTextColor(TFT_MAGENTA, TFT_BLACK);  // Magenta
    myGLCD.setCursor(50, 130);
    myGLCD.print("Display: 5'' 800x480 MCUFRIEND TFT");
    
    myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);  // White
    myGLCD.setCursor(50, 160);
    myGLCD.print("Available Cocktails: ");
    myGLCD.print(SIZE_OF_COCKTAILS);
    
    myGLCD.setCursor(50, 190);
    myGLCD.print("Total Drinks Available: ");
    myGLCD.print(RELAY_PIN_COUNT);
    
    // Show current bottle levels
    myGLCD.setTextColor(TFT_GREEN, TFT_BLACK);  // Green
    myGLCD.setCursor(50, 230);
    myGLCD.print("Current Bottle Levels:");
    
    for (int i = 0; i < 6; i++) {
      myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);  // White
      myGLCD.setCursor(50, 260 + i * 25);
      myGLCD.print(drinksName[i]);
      myGLCD.print(": ");
      myGLCD.print(EEPROM.read(i) * 10);
      myGLCD.print(" ml");
    }
    
    // Back button
    myGLCD.fillRoundRect(300, 410, 500, 460, 15, TFT_BLUE);
    myGLCD.drawRoundRect(300, 410, 500, 460, 15, TFT_WHITE);
    myGLCD.setTextColor(TFT_WHITE, TFT_BLUE);
    myGLCD.setCursor(360, 430);
    myGLCD.print("BACK");
    
    waitForTouch();
    param();
  }

  //*******************************************************Handle Clean System
  else if (x >= 100 && x <= 700 && y >= 220 && y <= 280) {
    cleanSystem();
  }

  //*******************************************************Handle Calibration
  else if (x >= 100 && x <= 700 && y >= 300 && y <= 360) {
    myGLCD.fillScreen(TFT_BLACK);
    drawTopText("Touch Calibration");
    drawBottomText("Touch the corners as instructed");
    
    myGLCD.setTextSize(3);
    myGLCD.setTextColor(TFT_YELLOW, TFT_BLACK);  // Yellow
    myGLCD.setCursor(200, 200);
    myGLCD.print("Calibration Mode");
    
    myGLCD.setTextSize(2);
    myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);  // White
    myGLCD.setCursor(250, 250);
    myGLCD.print("Feature Coming Soon...");
    
    delay(2000);
    param();
  }

  //*******************************************************Handle Back
  else if (x >= 100 && x <= 700 && y >= 380 && y <= 440) {
    drink(0);
  }
}

//*******************************************************CLEAN SYSTEM FUNCTION
void cleanSystem() {
  myGLCD.fillScreen(TFT_BLACK);
  drawTopText("SYSTEM CLEANING");
  drawBottomText("WARNING: All pumps will run for cleaning!");
  
  // Warning screen
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(TFT_RED, TFT_BLACK);  
  myGLCD.setCursor(200, 100);
  myGLCD.print("CLEANING MODE");
  
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
  myGLCD.setCursor(50, 150);
  myGLCD.print("This will run all pumps for 200ml to clean the");
  myGLCD.setCursor(50, 180);
  myGLCD.print("system. Make sure cleaning solution is in all");
  myGLCD.setCursor(50, 210);
  myGLCD.print("bottles and waste container is ready.");
  
  myGLCD.setTextColor(TFT_YELLOW, TFT_BLACK);
  myGLCD.setCursor(50, 250);
  myGLCD.print("This process will take about 2-3 minutes.");
  
  // Confirmation buttons
  myGLCD.fillRoundRect(150, 320, 350, 380, 15, TFT_GREEN);  // YES button
  myGLCD.drawRoundRect(150, 320, 350, 380, 15, TFT_WHITE);
  myGLCD.fillRoundRect(450, 320, 650, 380, 15, TFT_RED);    // NO button
  myGLCD.drawRoundRect(450, 320, 650, 380, 15, TFT_WHITE);
  
  myGLCD.setTextSize(4);
  myGLCD.setTextColor(TFT_BLACK, TFT_GREEN);
  myGLCD.setCursor(210, 340);
  myGLCD.print("YES");
  
  myGLCD.setTextColor(TFT_WHITE, TFT_RED);
  myGLCD.setCursor(520, 340);
  myGLCD.print("NO");
  
  // Wait for confirmation
  while (1) {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      
      int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
      int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);
      
      if (x >= 150 && x <= 350 && y >= 320 && y <= 380) {  // YES button
        // Start cleaning process
        myGLCD.fillScreen(TFT_BLACK);
        drawTopText("CLEANING IN PROGRESS");
        drawBottomText("Please wait... Do not interrupt the process!");
        
        myGLCD.setTextSize(3);
        myGLCD.setTextColor(TFT_GREEN, TFT_BLACK);
        myGLCD.setCursor(250, 120);
        myGLCD.print("CLEANING");
        
        myGLCD.setTextSize(2);
        myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
        myGLCD.setCursor(50, 170);
        myGLCD.print("All pumps are now running for 200ml each...");
        
        // Calculate cleaning time (200ml per pump)
        unsigned long cleaningTime = 200 * TIME_BY_ML;  // Time for 200ml
        
        // Show pump status
        for (int i = 0; i < RELAY_PIN_COUNT; i++) {
          myGLCD.setCursor(50, 210 + i * 25);
          myGLCD.print("Pump ");
          myGLCD.print(i + 1);
          myGLCD.print(" (");
          myGLCD.print(drinksName[i]);
          myGLCD.print("): RUNNING");
        }
        
        // Start all pumps
        for (int i = 0; i < RELAY_PIN_COUNT; i++) {
          digitalWrite(relayPins[i], HIGH);
        }
        
        unsigned long startTime = millis();
        
        // Show progress
        while (millis() - startTime < cleaningTime) {
          unsigned long elapsed = millis() - startTime;
          int progress = (elapsed * 100) / cleaningTime;
          
          // Draw progress bar
          myGLCD.fillRect(100, 380, 600, 400, TFT_BLACK);  // Clear previous
          myGLCD.drawRect(100, 380, 600, 400, TFT_WHITE);   // Border
          myGLCD.fillRect(102, 382, 102 + (progress * 596) / 100, 398, TFT_GREEN);  // Progress
          
          myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
          myGLCD.setCursor(350, 410);
          myGLCD.print(progress);
          myGLCD.print("%");
          
          delay(500);
        }
        
        // Stop all pumps
        for (int i = 0; i < RELAY_PIN_COUNT; i++) {
          digitalWrite(relayPins[i], LOW);
        }
        
        // Show completion
        myGLCD.fillScreen(TFT_BLACK);
        drawTopText("CLEANING COMPLETED");
        drawBottomText("System cleaning is finished!");
        
        myGLCD.setTextSize(4);
        myGLCD.setTextColor(TFT_GREEN, TFT_BLACK);
        myGLCD.setCursor(200, 180);
        myGLCD.print("COMPLETE!");
        
        myGLCD.setTextSize(2);
        myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
        myGLCD.setCursor(50, 240);
        myGLCD.print("Cleaning process finished successfully.");
        myGLCD.setCursor(50, 270);
        myGLCD.print("Remember to flush with clean water if needed.");
        
        // Continue button
        myGLCD.fillRoundRect(300, 350, 500, 400, 15, TFT_BLUE);
        myGLCD.drawRoundRect(300, 350, 500, 400, 15, TFT_WHITE);
        myGLCD.setTextSize(3);
        myGLCD.setTextColor(TFT_WHITE, TFT_BLUE);
        myGLCD.setCursor(340, 365);
        myGLCD.print("CONTINUE");
        
        waitForTouch();
        param();
        return;
      }
      else if (x >= 450 && x <= 650 && y >= 320 && y <= 380) {  // NO button
        param();
        return;
      }
    }
  }
}
