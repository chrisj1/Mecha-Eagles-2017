const int L_BUTTON = 1;
const int C_BUTTON = 2;
const int R_BUTTON = 4;
const int NONE_BUTTONS = 0;

int askPos() {
	string opt[] = {
		"left",
		"right"
	};
	string str = "Side?";
	int option = displayLCDMenu(opt, 2, str);
	return option;
}

int askRoutine() {
	string options[] = {
		"Full length",
		"Forwards",
		"Fence Drive",
		"Back wall",
		"Stars"
	};
	string str = "Which Routine?";
	int opt = displayLCDMenu(options, 5, str);
	return opt;
}

int displayLCDMenu(string* optionsP, int length, string prompt) {
	clearScreen();
	VERIFY(strlen(prompt) <= 16);
	displayLCDCenteredString(0, prompt);

	int currentSelected = 0;
	while(true) {
		int index = currentSelected % length;
		//mod function is broken with negatives? another robotc bug
		if(index < 0) {
			index = (length + index)%length;
		}
		string str = *(optionsP + index);
		displayLCDCenteredString(1, str);
		waitForPress();
		int btn = nLCDButtons;
		if(btn == R_BUTTON) {
			currentSelected++;
		} else if(btn == L_BUTTON) {
			currentSelected--;
		} else if(btn == C_BUTTON) {
			return index;
		}
		waitForRelease();
	}
	return 0;
}

int promptInt(int maxInt, int minInt, int startInt, int increment,string prompt) {
	clearScreen();
	displayLCDCenteredString(0, prompt);
	int currentInt = startInt;
	while(true) {
		string str;
		sprintf(str, "%d", currentInt);
		displayLCDCenteredString(1, str);
		waitForPress();
		int btn = nLCDButtons;
		int previous = currentInt;
		if(btn == R_BUTTON) {
			currentInt = min(maxInt, currentInt + increment);
		} else if(btn == L_BUTTON) {
			currentInt = max(minInt, currentInt - increment);
		} else if(btn == C_BUTTON) {
			return currentInt;
		}
		waitForRelease();
	}
}


void clearScreen() {
	clearLCDLine(0);
	clearLCDLine(1);

}

void checkBattery() {
    bLCDBacklight = true;
    string mainBattery, expanderBattery;
    int mainBatteryLevel, expanderBatteryLevel;
    clearScreen();

    while(nLCDButtons != R_BUTTON) {
        mainBatteryLevel = getBatteryLevelVoltage();
        expanderBatteryLevel = getExpanderBatteryVoltage();
        //Display the Primary Robot battery voltage
        displayLCDString(0, 0, "Primary: ");
        sprintf(mainBattery, "%1.2f%c", mainBatteryLevel,'V'); //Build the value to be displayed
        displayNextLCDString(mainBattery);

        //Display the Backup battery voltage
        displayLCDString(1, 0, "Expander: ");
        sprintf(expanderBattery, "%1.2f%c", getExpanderBatteryVoltage(), 'V');    //Build the value to be displayed
        displayNextLCDString(expanderBattery);

        if(mainBatteryLevel < MIN_BATT_VOLT || expanderBatteryLevel < MIN_BATT_VOLT) {
            startTask(flashScreen);
        }
        wait1Msec(100);
    }
    stopTask(flashScreen);
}

bool askPole() {
		string options[] = {
		"True",
		"False"
	};
	string str = "Pole?";
	int opt = displayLCDMenu(options, 2, str);
	return opt == true;
}

task flashScreen() {
    while(true) {
        bLCDBacklight = false;
        wait1Msec(500);
        bLCDBacklight = true;
        wait1Msec(500);
    }
}

bool confirmChoiceWithUser(string prompt, string choice) {
	string opt[] = {"yes", "no"};
	stringConcatenate(prompt, " ");
	stringConcatenate(prompt, choice);
	stringConcatenate(prompt, "?");
	return true;
}

void waitForRelease() {
	while(nLCDButtons != NONE_BUTTONS){
		wait1Msec(100);
	}
}

void waitForPress() {
	while(nLCDButtons == NONE_BUTTONS) {
		wait1Msec(100);
	}
}
