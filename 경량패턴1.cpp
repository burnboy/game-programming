
//경량 패턴
//줄기 가지 잎의 형태를 나타내는 폴리곤 매시
//나무껍질과 입사귀 텍스쳐
//숲에서의 위치와 방향
//각각의 나무가 다르게 보이도록 크기와 음영같은 값을 조절할 수 있는 매개변수

class Tree
{
	private:
	Mesh mesh_;
	Texture bark_;
	Texture leaves_;
	Vector position_;
	double height_;
	double thickness_;
	Color barkTint_;
	Color leafTint_;
};

// 59p
class TreeModel{
	private:
	Mesh mesh_;
	Texture bark_;
	Texture leaves_;
};

class Tree{
	private:
	TreeModel* model_;
	
	Vector position_;
	double height_;
	double thickness_;
	Color barkTint_;
	Color leafTint_;
}

//지형 정보
enum Terrain{
	TERRAIN_GRASS,
	TERRAIN_HILL,
	TERRAIN_RIVER,
	//............
	
};

//월드는 지형을 거대한 격자로 관리,2차원 배열에 저장
class World{
	public:
	World()
	:grassTerrain_(1,false,GRASS_TEXTURE),
	hillTerrain_(3,false,HILL_TEXTURE),
	riverTerrain_(2,true,RIVER_TEXTURE){
		
	}
	
	private:
	Terrain grassTerrain_;
	Terrain tiles_[WIDTH][HEIGHT];
	
}

int World::getMovementCost(int x,int y){
	switch(tiles_[x][y]){
		case TERRAIN_GRASS: return 1;
		case TERRAIN_HILL: return 3;
		case TERRAIN_RIVER return 2;
	//그 외의 다른 지형들......
	}
	
}
//지저분한 코드 (하드코딩)
bool World::isWater(int x,int y){
	switch(tiles_[x][y]){
		case TERRAIN_GRASS:return false;
		case TERRAIN_HILL:return false;
		case TERRAIN_RIVER return true;
		//그 외의 다른 지형들......
		
	}
	
}

//클래스를 따로 만드는게 훨씬 낫다
class Terrain{
	public:
	Terrain(int movementCost,bool isWater,Texture texture)
	: movementCost_(movementCost),
	isWater_(isWater),
	texture_(texture){
	}
	
	int getMovementCost() const {return movementCost_;}
	bool isWater() const{return isWater_;}
	const texture& getTexture()const{return texture_;}
	
	private:
	int movementCost_;
	bool isWater_;
	Texture texture_;
	 
}

//64p
class World{
	public:
	World()
	:grassTerrain_(1,false,GRASS_TEXTURE),
	hillTerrain_(3,false,HILL_TEXTURE),
	riverTerrain_(2,true,RIVER_TEXTURE){
		
	}
	
	private:
	Terrain grassTerrain_;
	Terrain hillTerrain_;
	Terrain riverTerrain_;
	Terrain tiles_[WIDTH][HEIGHT];
	
}

void World::generateTerrain(){
	//땅에 풀을 채운다.
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			//언덕을 몇 개 놓는다.
			if(random(10)==0){
				tiles_[x][y]=&hillTerrain_;
			}else{
				tiles_[x][y]=&grassTerrain_;		
			}
		}
	}
//강을 하나 놓는다
	int x=random(WIDTH);
	for(int y=0;y<HEIGHT;y++){
		tiles_[x][y]=&riverTerrain_;
	}
}
//지형 속성값을 world의 메서드 대신 terrain객체에서 바로 얻을 수 있다.
const Terrain& World::getTile(int x,int y)const{
	return *tiles_[x][y];
}

//world 클래스는 더 이상 지형의 세부정보와 커플링 되지 않는다. 타일 속성은 terrain 객체에서 바로
//얻을 수 있다.
int cost=world.getTile(2,3,).getMovementCost();









