#pragma once
#include "CharacterHandler.h"
#include "Character.h"

class CollidableCharacter : public Character
{
public:
    template <class T>
    bool placeMeeting(float x, float z);
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


