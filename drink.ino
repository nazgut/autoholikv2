void drink(int currentPage)
{
  drawTopText("Autoholik v2 - Premium Cocktail Machine");
  drawBottomText(funnySentence[random(0,FUNNY_SENTENCE_SIZE)]);
  
  // With 800x480, we can show 4 cocktails per page in a 2x2 grid
  // Calculate available space: 800x480 - top(35) - bottom(40) = 800x405
  
  //*******************************************************Draw 4 Cocktail Buttons in 2x2 Grid
  int buttonWidth = 360;   // Wider buttons for better readability
  int buttonHeight = 120;  // Taller buttons for better touch
  int spacing = 20;
  
  // Top row buttons
  myGLCD.fillRoundRect(40, 60, 40 + buttonWidth, 60 + buttonHeight, 10, TFT_RED);  // Red button 1
  myGLCD.fillRoundRect(420, 60, 420 + buttonWidth, 60 + buttonHeight, 10, TFT_RED); // Red button 2
  
  // Bottom row buttons  
  myGLCD.fillRoundRect(40, 200, 40 + buttonWidth, 200 + buttonHeight, 10, TFT_RED);  // Red button 3
  myGLCD.fillRoundRect(420, 200, 420 + buttonWidth, 200 + buttonHeight, 10, TFT_RED); // Red button 4
  
  // Draw white borders
  myGLCD.drawRoundRect(40, 60, 40 + buttonWidth, 60 + buttonHeight, 10, TFT_WHITE);
  myGLCD.drawRoundRect(420, 60, 420 + buttonWidth, 60 + buttonHeight, 10, TFT_WHITE);
  myGLCD.drawRoundRect(40, 200, 40 + buttonWidth, 200 + buttonHeight, 10, TFT_WHITE);
  myGLCD.drawRoundRect(420, 200, 420 + buttonWidth, 200 + buttonHeight, 10, TFT_WHITE);
  
  //*******************************************************Draw Control Buttons
  myGLCD.fillRoundRect(40, 340, 200, 400, 10, TFT_BLUE);   // Blue settings button
  myGLCD.fillRoundRect(220, 340, 380, 400, 10, TFT_BLUE);  // Blue prev page button
  myGLCD.fillRoundRect(400, 340, 560, 400, 10, TFT_BLUE);  // Blue next page button
  myGLCD.fillRoundRect(580, 340, 740, 400, 10, TFT_BLUE);  // Blue info button
  
  // Draw borders for control buttons
  myGLCD.drawRoundRect(40, 340, 200, 400, 10, TFT_WHITE);
  myGLCD.drawRoundRect(220, 340, 380, 400, 10, TFT_WHITE);
  myGLCD.drawRoundRect(400, 340, 560, 400, 10, TFT_WHITE);
  myGLCD.drawRoundRect(580, 340, 740, 400, 10, TFT_WHITE);

  //*******************************************************Draw Cocktail Names
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(TFT_WHITE, TFT_RED);  // White text on red background
  
  // Cocktail 1
  if (0 + (currentPage * 4) < SIZE_OF_COCKTAILS) {
    myGLCD.setCursor(60, 105);
    myGLCD.print(cocktailsName[0 + (currentPage * 4)]);
  }
  
  // Cocktail 2
  if (1 + (currentPage * 4) < SIZE_OF_COCKTAILS) {
    myGLCD.setCursor(440, 105);
    myGLCD.print(cocktailsName[1 + (currentPage * 4)]);
  }
  
  // Cocktail 3
  if (2 + (currentPage * 4) < SIZE_OF_COCKTAILS) {
    myGLCD.setCursor(60, 245);
    myGLCD.print(cocktailsName[2 + (currentPage * 4)]);
  } else {
    myGLCD.setCursor(60, 245);
    myGLCD.print("--- Empty ---");
  }
  
  // Cocktail 4
  if (3 + (currentPage * 4) < SIZE_OF_COCKTAILS) {
    myGLCD.setCursor(440, 245);
    myGLCD.print(cocktailsName[3 + (currentPage * 4)]);
  } else {
    myGLCD.setCursor(440, 245);
    myGLCD.print("--- Empty ---");
  }

  //*******************************************************Draw Control Button Text
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLUE);  // White text on blue background
  
  myGLCD.setCursor(70, 362);
  myGLCD.print("Settings");
  
  myGLCD.setCursor(240, 362);
  myGLCD.print("< Prev");
  
  myGLCD.setCursor(420, 362);
  myGLCD.print("Next >");
  
  myGLCD.setCursor(610, 362);
  myGLCD.print("Info");

  //*******************************************************Draw Page Information
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(TFT_YELLOW, TFT_BLACK);  // Yellow text on black background
  myGLCD.setCursor(350, 420);
  myGLCD.print("Page ");
  myGLCD.print(currentPage + 1);
  myGLCD.print("/");
  myGLCD.print((SIZE_OF_COCKTAILS + 3) / 4);  // Round up division

  //*******************************************************Wait for touch
  while (1) {
    TSPoint p = ts.getPoint();
    
    if (p.z > ts.pressureThreshhold) {
      // Map touch coordinates for 800x480 display
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      
      int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
      int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);

      // Check cocktail buttons
      if (x >= 40 && x <= 400 && y >= 60 && y <= 180) {  // Button 1
        if (0 + (currentPage * 4) < SIZE_OF_COCKTAILS) 
          drinkConfirmation(0 + (currentPage * 4));
      }
      else if (x >= 420 && x <= 780 && y >= 60 && y <= 180) {  // Button 2
        if (1 + (currentPage * 4) < SIZE_OF_COCKTAILS) 
          drinkConfirmation(1 + (currentPage * 4));
      }
      else if (x >= 40 && x <= 400 && y >= 200 && y <= 320) {  // Button 3
        if (2 + (currentPage * 4) < SIZE_OF_COCKTAILS) 
          drinkConfirmation(2 + (currentPage * 4));
      }
      else if (x >= 420 && x <= 780 && y >= 200 && y <= 320) {  // Button 4
        if (3 + (currentPage * 4) < SIZE_OF_COCKTAILS) 
          drinkConfirmation(3 + (currentPage * 4));
      }
      // Check control buttons
      else if (x >= 40 && x <= 200 && y >= 340 && y <= 400) {  // Settings
        param();
      }
      else if (x >= 220 && x <= 380 && y >= 340 && y <= 400) {  // Previous page
        if (currentPage > 0) drink(currentPage - 1);
        else drink((SIZE_OF_COCKTAILS + 3) / 4 - 1);  // Go to last page
      }
      else if (x >= 400 && x <= 560 && y >= 340 && y <= 400) {  // Next page
        if ((currentPage + 1) * 4 < SIZE_OF_COCKTAILS) drink(currentPage + 1);
        else drink(0);  // Go to first page
      }
      else if (x >= 580 && x <= 740 && y >= 340 && y <= 400) {  // Info
        showInfo();
      }
    }
  }
}

//*******************************************************validate a cocktail
void drinkConfirmation(int cocktailValue) {
  myGLCD.setTextSize(3);
  myGLCD.fillScreen(0x0000);  // Clear screen with black

  //*******************************************************draw title box
  myGLCD.fillRoundRect(50, 20, 750, 80, 15, 0x0000);  // Black background
  myGLCD.drawRoundRect(50, 20, 750, 80, 15, 0xFFFF);  // White border
  
  //*******************************************************draw cocktail name
  myGLCD.setTextColor(0xFFE0, 0x0000);  // Yellow text on black background
  myGLCD.setCursor(70, 40);
  myGLCD.print("Cocktail: ");
  myGLCD.setTextColor(0xFFFF, 0x0000);  // White text
  myGLCD.print(cocktailsName[cocktailValue]);

  //*******************************************************draw ingredients list
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(0x07FF, 0x0000);  // Cyan color for "Ingredients:"
  myGLCD.setCursor(50, 100);
  myGLCD.print("Ingredients:");
  
  int yPos = 130;
  for (int i = 0; i < 6; i++) {
    if (drinksComposition[cocktailValue][i] != 0) {
      // Draw ingredient background
      myGLCD.fillRect(50, yPos - 5, 700, yPos + 20, 0x2104);  // Dark gray background
      
      // Draw ingredient name
      myGLCD.setTextColor(0xFFFF, 0x2104);  // White text on gray background
      myGLCD.setCursor(60, yPos);
      myGLCD.print(drinksName[i]);
      
      // Draw amount
      myGLCD.setCursor(500, yPos);
      myGLCD.print(drinksComposition[cocktailValue][i]);
      myGLCD.print(" ml");
      
      // Draw visual bar for amount
      int barWidth = drinksComposition[cocktailValue][i] * 2;  // 2px per ml
      if (barWidth > 150) barWidth = 150;  // Maximum bar width
      myGLCD.fillRect(550, yPos + 2, 550 + barWidth, yPos + 15, 0x001F);  // Blue bar
      
      yPos += 35;
    }
  }

  //*******************************************************draw confirmation buttons
  // YES button (larger and green)
  myGLCD.fillRoundRect(150, 350, 350, 420, 20, 0x07E0);  // Green button
  myGLCD.drawRoundRect(150, 350, 350, 420, 20, 0xFFFF);  // White border
  myGLCD.setTextSize(4);
  myGLCD.setTextColor(0x0000, 0x07E0);  // Black text on green background
  myGLCD.setCursor(210, 375);
  myGLCD.print("YES");
  
  // NO button (larger and red)
  myGLCD.fillRoundRect(450, 350, 650, 420, 20, 0xF800);  // Red button
  myGLCD.drawRoundRect(450, 350, 650, 420, 20, 0xFFFF);  // White border
  myGLCD.setTextColor(0xFFFF, 0xF800);  // White text on red background
  myGLCD.setCursor(520, 375);
  myGLCD.print("NO");

  //*******************************************************wait for touch
  while (1) {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      
      int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
      int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);
      
      if (x >= 150 && x <= 350 && y >= 350 && y <= 420) {  // YES button
        motor(cocktailValue);
      }
      else if (x >= 450 && x <= 650 && y >= 350 && y <= 420) {  // NO button
        drink(0);
      }
    }
  }
}

//*******************************************************info screen function
void showInfo() {
  myGLCD.fillScreen(0x0000);  // Clear screen with black
  
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(0xFFE0, 0x0000);  // Yellow color
  myGLCD.setCursor(250, 30);
  myGLCD.print("AUTOHOLIK v2");
  
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(0x07FF, 0x0000);  // Cyan color
  myGLCD.setCursor(300, 70);
  myGLCD.print("800x480 Edition");
  
  myGLCD.setTextSize(2);
  myGLCD.setTextColor(0xFFFF, 0x0000);  // White color
  myGLCD.setCursor(280, 110);
  myGLCD.print("nazgut@gmail.com");
  
  // Show bottle levels
  myGLCD.setTextColor(0xF81F, 0x0000);  // Magenta color
  myGLCD.setCursor(50, 150);
  myGLCD.print("Bottle Levels:");
  
  for (int i = 0; i < 6; i++) {
    myGLCD.setTextColor(0xFFFF, 0x0000);  // White text
    myGLCD.setCursor(50, 180 + i * 30);
    myGLCD.print(drinksName[i]);
    
    int level = EEPROM.read(i) * 10;
    myGLCD.setCursor(300, 180 + i * 30);
    myGLCD.print(level);
    myGLCD.print(" ml");
    
    // Draw level bar
    int barWidth = level / 2;  // Scale to fit display
    if (barWidth > 200) barWidth = 200;
    
    // Choose color based on level
    uint16_t barColor;
    if (level > 200) barColor = 0x07E0;      // Green
    else if (level > 100) barColor = 0xFFE0;  // Yellow
    else barColor = 0xF800;                   // Red
    
    myGLCD.fillRect(400, 185 + i * 30, 400 + barWidth, 200 + i * 30, barColor);
    myGLCD.drawRect(400, 185 + i * 30, 600, 200 + i * 30, 0xFFFF);  // White border
  }
  
  // Back button
  myGLCD.fillRoundRect(300, 400, 500, 450, 15, 0x001F);  // Blue button
  myGLCD.drawRoundRect(300, 400, 500, 450, 15, 0xFFFF);  // White border
  myGLCD.setTextSize(3);
  myGLCD.setTextColor(0xFFFF, 0x001F);  // White text on blue background
  myGLCD.setCursor(360, 415);
  myGLCD.print("BACK");
  
  // Wait for back button press
  while (1) {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, HIGH);
      
      int x = map(p.y, TS_MAXX, TS_MINX, 0, 800);
      int y = map(p.x, TS_MAXY, TS_MINY, 0, 480);
      
      if (x >= 300 && x <= 500 && y >= 400 && y <= 450) {  // Back button
        drink(0);
        break;
      }
    }
  }
}
