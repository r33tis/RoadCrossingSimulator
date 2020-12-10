#include "CharacterHandler.h"

void CharacterHandler::init(SceneManager* sceneMgr) {
	this->sceneMgr = sceneMgr;
	this->deleteQueue = std::queue<Character*>();
	std::cout << "characterhandler singleton init\n";
}

void CharacterHandler::deleteCharacter(Character* character)
{
	deleteQueue.push(character);
}

std::vector<Character*> CharacterHandler::listCharacters()
{
	return characters;
}

void CharacterHandler::update(Real elapsedTime, OIS::Keyboard* input) {
	for (Character* character : characters) {
		character->update(elapsedTime, input);
	}

	while (!deleteQueue.empty()) {
		Character* c = deleteQueue.front();
		if (std::find(characters.begin(), characters.end(), c) != characters.end()) {
			characters.erase(std::remove(characters.begin(), characters.end(), c), characters.end());
			delete c;
		}
		deleteQueue.pop();
	}
}
