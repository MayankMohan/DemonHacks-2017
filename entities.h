class Entity{
	private:
		glm::vec3 position;
		glm::vec3 direction;
		int hp
		int damage;
		double size;
	public:
		virtual Entity(): hp(5), damage;
}

class Player: public Entity{
	private:
		int lives;
		int score;
}

class Enemy: public Entity{
	
}

class Position(x,y,z){//needs attention 
	Player player = new Player();
	player.move()
	player.rotate()
	ene.move()
	Enemies ene = new Enemies();
	// ? player.rotate = true;
	if player.rotate == true;{
		player.x = for i in range(0, x);
		player.y = for i in range(0, y);
	}
	//assert certain positions to other entities; think using random	
}

class Collision{
	Player player = new Player()
	Enemies ene = new Enemies()
	std::vector<enemies> objects; //making an array of entities 
	for (int i = 0; i < objects.size(); i++){ //player colliding to enemies
		if (objects.get(i).collides(player)) {
				if (lives == 0)
					player.delete();
				player.lives --;
		}
	}
	for (int i  = 0; i < objects.size(); i++){//enemies colliding to playerBullet
		if (player.shootBullet.collides(objects.get(i)))
			objects.get(i).delete();
			player.lives ++;
	}
	for (int i = 0; i < objects.size(); i++){//player colliding to enemyFire
		if (objects.get(i).shootFire.collides(player))
			if (lives == 0)
				player.delete()
			player.lives --;
	}
}

class Size{
	int max_size;
	int min_size;
	
}
class tart{
}

class End{
	
}