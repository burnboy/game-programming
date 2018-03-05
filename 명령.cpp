void InputHandler::handleInput(){
	if(isPressed(BUTTON_X)) jump();
	else if(isPressed(BUTTON_Y))fireGun();
	
	
}