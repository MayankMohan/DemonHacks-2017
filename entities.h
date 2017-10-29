class Entity{
	protected:
		glm::vec3 position;
		glm::vec3 direction;
		int damage;
		double size;
    double min_size;
    double max_size;
	public:
    bool hit();
    virtual void damage();
}

class Player:public Entity{
	private:
		int lives;
		int score;
  public:
    Player();
    void addScore(int i);
}

class Enemy: public Entity{
  private:
    int hp;
    int spawn_count;
  public:
    bool alive();
}
	//assert certain positions to other entities; think using random


bool enemy_limit(Enemy spawn_count)
bool player_die(Player lives)