
//명령 커맨드 클래스
class Command{
	public:
		virtual ~Command(){}
		// virtual void execute(GameActor& actor)=0;//게임 객체 클래스
			//순수 가상함수 undo 작성
		virtual void execute()=0;
		virtual void undo()=0	
};

//점프 클래스
class JumpCommand:public Command{
	public:
	visual void execute(GameActor& actor){
		actor.jump();
	}
};


Command* InputHandler::handleInput(){
	if(isPressed(BUTTON_X)) return buttonX_;	
	if(isPressed(BUTTON_Y)) return buttonY_;
	if(isPressed(BUTTON_A)) return buttonA_;
	if(isPressed(BUTTON_B)) return buttonB_;
	
	//아무것도 누르지 않고 있다면 
	return NULL;
}

//실행취소와 재실행
class MoveUnitCommand:public Command{
	public:
	MoveUnitCommand(Unit* unit,int x,int y)
	//: unit_(unit),
	: unit_(unit),x_(x),y_(y)
	xBefore_(0),yBefore_(0),
	x_(x),y_(y)
	{

	}
	
	virtual void execute(){
		//나중에 이동을 취소할수 있도록 원래 유닛 위치를 저장한다
		xBefore_=unit_->x();
		yBefore_=unit_->y();
		unit_->moveTo(x_,y_);
	}
	
	virtual void undo(){
		unit_->moveTo(xBefore_,yBefore_);
	}
	
	private:
	Unit* unit_;
	int x_,int y_;
	int xBefore_,yBefore_;
}

Command* handleInput(){
	Unit* unit=getSelectedUnit();
	if(isPressed(BUTTON_UP)){
		//유닛을 한칸 위로 이동한다.
		int destY=unit->y()-1;
		return new MoveUnitCommand(unit,unit->x(),destY);
	}
	if(isPressed(BUTTON_DOWN)){
		//유닛을 한칸 아래로 이동한다.
		int destY=unit->y()+1;
		return new MoveUnitCommand(unit,unit->x(),destY);
	}
	
	return NULL;
	
}
/////////////////////////////////////////////////
//53p
//자바 스크립트

function makeMoveUnitCommand(unit,x,y){
	//아래 function이 명령 객체에 해당
	return function(){
		unit.moveTo(x,y);
	}
	
}
//클로저를 여러개 이용한 실행취소
function makeMoveUnitCommand(unit,x,y){
	var xBefore,yBefore;
	//아래 function이 명령 객체에 해당
	return{
	execute function(){
	xBefore=unit.x();
	yBefore=unit.y();
	unit.moveTo(x,y);
	}
	
	undo:function(){
		unit.moveTo(xBefore,yBefore);
	 }
	};	
}












