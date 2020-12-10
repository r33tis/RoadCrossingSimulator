#include "CharacterHandler.h"

void CharacterHandler::init(SceneManager* sceneMgr) {
	this->sceneMgr = sceneMgr;
}

void CharacterHandler::deleteCharacter(Character* character)
{
	// TO+DO
}

std::vector<Character*> CharacterHandler::listCharacters()
{
	return characters;
}

void CharacterHandler::update(Real elapsedTime, OIS::Keyboard* input) {
	for (auto character : characters) {
		character->update(elapsedTime, input);
	}
}