#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
private:
    int level; 
    int healthBar; 

public:
    Player(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, int playerLevel, int playerHealth);

  
    int getLevel() const;
    void setLevel(int playerLevel);

    int getHealthBar() const;
    void setHealthBar(int playerHealth);

    
    void moveHealthBar(int dx);
    void moveLevelBar(int dx);
};

#endif // PLAYER_H
