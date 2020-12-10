#pragma once
#include <vector>
#include "Character.h"
#include <type_traits>

class CharacterHandler
{
private:
	std::vector<Character*> characters;
	std::queue<Character*> deleteQueue;
	SceneManager* sceneMgr;
	CharacterHandler() {};
public:
	// creation and singleton pattern
	static CharacterHandler* getInstance() {
		static CharacterHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr);
	void update(Real elapsedTime, OIS::Keyboard* input);

public:

	template<class T>
	Character* createCharacter(float x, float y, float z);

	void deleteCharacter(Character* character);

	std::vector<Character*> listCharacters();

	template<class T>
	std::vector<Character*> listClassCharacters();
};


template<class T>
inline Character* CharacterHandler::createCharacter(float x, float y, float z)
{
	Character* object = new T();
	object->create(sceneMgr, x, y, z);
	characters.push_back(object);
	return object;
}

template<class T>
inline std::vector<Character*> CharacterHandler::listClassCharacters()
{
	std::vector<Character*> filtered = std::vector<Character*>();
	for (Character* c : characters) {
		if (dynamic_cast<const T*>(c) != nullptr) {
			filtered.push_back(c);
		}
	}

	return filtered;
}