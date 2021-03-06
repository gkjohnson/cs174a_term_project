#ifndef _TURRETENTITY
#define _TURRETENTITY

#include "MobileEntity.h"
#include "BulletEntity.h"
#include "Scene.h"

/** @brief A turretEntity is one of the enemies.
  * It points at the player (if there is one) and shoots
  * straight bullets when the player enters a certain radius.
  * This same class is used as the "boss" entity by setting
  * a variable to determine the kind of turret that it is
  */
class TurretEntity:public MobileEntity{
private:
	int _bulletDelay;
	bool _isBoss;
public:
	/*@brief Initializes the turret entity by adding the models
	* and setting the position of it
	*/
	TurretEntity(vec3 pos=vec3(0,0,0))
		:MobileEntity(ID_ENEMY_TURRET),_bulletDelay(5),_isBoss(false)
	{
		//creates the models
		translate(pos);
		setModel(DrawableEntity("resources/turretTexture.png","resources/turretBase.obj"));	
		setModel(DrawableEntity("resources/turretTexture.png","resources/turretTop.obj"),1);
		getModel(1).setTranslate(0,.75,0);
		setModel(DrawableEntity("resources/turretTexture.png","resources/turretBarrel.obj"),2);
		getModel(2).setTranslate(.5,0,0);
		getModel(2).setParent(&getModel(1));

		CollisionBox b;
		b.setDim(1,2,1);

		scale(3.5,3.5,3.5);

		this->setHitbox(b);

	}
	/** @brief Updates the entity to look at the player and shoot if
	 * it is within range
	 */
	void update(){
	
		const GameEntity* const p=Globals::getPlayer();

		//if the entity is dead, create and explosion
		if(getHealth()<0){
			if(_isBoss)Globals::setCurrLevelWon();
			setDelete();
			Explosion* e= new Explosion(3*getScale().x,50);
			e->translate(getTranslate());
			Globals::addSoftEntity(e);
		}

		resetHightlight();

		//find the direction to the player and if the player is in range
		vec3 dir=p->getTranslate()-getModel(1).getTranslate();
		if(dot(dir,dir)>pow(80.0,2)&&!_isBoss)return;
		else if(dot(dir,dir)>pow(130.0,2)&&_isBoss)return;
		vec3 dirNorm=normalize(dir);

		float yRotate=-(atan2(0.0,1.0)-atan2(dir.x,dir.z))-M_PI/2;

		getModel(1).setRotate(0,yRotate*(360/(2*M_PI))-getRotate().y,0);

		//count down to the next bullet firing
		_bulletDelay--;

		//fire the bullet at the appropriate interval - varies if it is a "boss" type
		if(_bulletDelay==0){
			Globals::addBullet(ID_BULLET_STRAIGHT,0,3.5, normalize(p->getTranslate()-(getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z))),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));
			_bulletDelay=10;
			if(_isBoss){
				if(getHealth()<75)Globals::addBullet(ID_BULLET_GRENADE,0,3.5, normalize(p->getTranslate()-(getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z))),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));
				_bulletDelay=14;
			}
		}else if(_isBoss&&_bulletDelay==7&&getHealth()<50){
			
			vec4 angle=normalize(p->getTranslate()-(getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z)));
			vec4 angleLeft=RotateY(5)*angle;
			vec4 angleRight=RotateY(-5)*angle;

			Globals::addBullet(ID_BULLET_CURVY,0,3.5, vec3(angleLeft.x,angleLeft.y,angleLeft.z),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));
			Globals::addBullet(ID_BULLET_CURVY,0,3.5, vec3(angleRight.x,angleRight.y,angleRight.z),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));

			/*if(getHealth()<25){
			
			angleLeft=RotateY(10)*angle;
			angleRight=RotateY(-10)*angle;

			Globals::addBullet(ID_BULLET_CURVY,0,3.5, vec3(angleLeft.x,angleLeft.y,angleLeft.z),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));
			Globals::addBullet(ID_BULLET_CURVY,0,3.5, vec3(angleRight.x,angleRight.y,angleRight.z),getModel(1).getTranslate()+2*vec3(dirNorm.x*getScale().x,0,dirNorm.z*getScale().z));
			}*/
		}
	}

	/** @brief If the entity collides with a bullet, apply damage
	*/
	void onCollide(const GameEntity& g){
		float damageMult=1;
		if(_isBoss)damageMult=.1;

		switch(g.getId()){
		case ID_BULLET_STRAIGHT:
			decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage()*damageMult);
			break;
		case ID_BULLET_GRENADE:
			decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage()*damageMult);
			break;
		case ID_BULLET_CURVY:
			decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage()*damageMult);
			break;
		case ID_EXPLOSION:
			decHealth(1);
			break;
		}
	}
	/** @brief sets whether or not the entity is a boss */
	void setBoss(bool t){
	_isBoss=t;
	}
};




#endif //_TURRETENTITY