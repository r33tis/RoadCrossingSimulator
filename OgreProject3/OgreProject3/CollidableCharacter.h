#pragma once
#include "CharacterHandler.h"
#include "Character.h"

class CollidableCharacter : public Character
{
public:
    template <class T>
    bool placeMeeting(float x, float z);
    template <class T>
    Ogre::Real distance(Ogre::Vector3 position);
};

template <class T>
inline bool CollidableCharacter::placeMeeting(float x, float z)
{
    CharacterHandler* handler = CharacterHandler::getInstance();
    std::vector<Character*> characters = handler->listClassCharacters<T>();

    AxisAlignedBox bbox = this->getBbox();
    for (Character* c : characters) {
        AxisAlignedBox obbox = c->getBbox();
        if (bbox.intersects(obbox)) {
            return true;
        }
    }

    return false;
}

template <class T>
inline Ogre::Real CollidableCharacter::distance(Ogre::Vector3 position)
{
    CharacterHandler* handler = CharacterHandler::getInstance();
    std::vector<Character*> characters = handler->listClassCharacters<T>();

    float min = Ogre::Math::POS_INFINITY;
    
    for (Character* c : characters) {
        Ogre::Vector3 positionOther = c->getWorldPosition();
        Ogre::Real distance = positionOther.squaredDistance(position);

        if (distance < min) {
            min = distance;
        }
    }

    return Ogre::Math::Sqrt(min);
}


