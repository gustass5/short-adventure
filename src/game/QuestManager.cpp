#include "QuestManager.hpp"

QuestManager::QuestManager() {
	QuestManager::elderStepIndex = 0;
	QuestManager::elderLineIndex = 0;
}
QuestManager::~QuestManager() {}

void QuestManager::StartQuest(std::string questText, std::string questCompletedText) {
	QuestManager::SetCurrentQuestText(questText);
	QuestManager::SetCurrentQuestCompletedText(questCompletedText);
	QuestManager::SetHasQuestBeenStarted(true);
	QuestManager::SetHasQuestBeenCompleted(false);
	QuestManager::SetHasQuestBeenRewarded(false);
};

void QuestManager::RenderQuest(SDL_Renderer* renderer) {
	std::string textToRender = QuestManager::GetHasQuestBeenCompleted() || !QuestManager::GetHasQuestBeenStarted() ? QuestManager::GetCurrentQuestCompletedText() : QuestManager::GetCurrentQuestText();
	UIManager::RenderQuest(renderer, textToRender);
};

void QuestManager::SetCurrentQuestText(std::string text) {
	AudioManager::playQuest();
	QuestManager::currentQuestText = text;
};

void QuestManager::SetCurrentQuestCompletedText(std::string text) {
	QuestManager::currentQuestCompletedText = text;
};

void QuestManager::SetHasQuestBeenStarted(bool started) {
	QuestManager::hasQuestBeenStarted = started;
};

void QuestManager::SetHasQuestBeenCompleted(bool completed) {
	QuestManager::hasQuestBeenCompleted = completed;
};

void QuestManager::SetHasQuestBeenRewarded(bool rewarded) {
	QuestManager::hasQuestBeenRewarded = rewarded;
};

void QuestManager::SetShellCount(int count) {
	QuestManager::shellCount = count;
};

std::string QuestManager::GetCurrentQuestText() {
	return QuestManager::currentQuestText;
};

std::string QuestManager::GetCurrentQuestCompletedText() {
	return QuestManager::currentQuestCompletedText;
};

bool QuestManager::GetHasQuestBeenStarted() {
	return QuestManager::hasQuestBeenStarted;
};

bool QuestManager::GetHasQuestBeenCompleted() {
	return QuestManager::hasQuestBeenCompleted;
};

bool QuestManager::GetHasQuestBeenRewarded() {
	return QuestManager::hasQuestBeenRewarded;
};

int QuestManager::GetShellCount() {
	return QuestManager::shellCount;
};

void QuestManager::SetElderStepIndex(int index) {
	QuestManager::elderStepIndex = index;
};

void QuestManager::SetElderLineIndex(int index) {
	QuestManager::elderLineIndex = index;
};

void QuestManager::SetHasElderBeenMet() {
	QuestManager::hasElderBeenMet = true;
};

void QuestManager::SetHasForestBeenCleared() {
	QuestManager::hasForestBeenCleared = true;
};

void QuestManager::SetHasPassBeenCleared() {
	QuestManager::hasPassBeenCleared = true;
};

void QuestManager::SetHasFishermanBeenMet() {
	QuestManager::hasFishermanBeenMet = true;
};

void QuestManager::SetHasSeashoreBeenCleared() {
	QuestManager::hasSeashoreBeenCleared = true;
};

void QuestManager::SetHasDungeonBeenCleared() {
	QuestManager::hasDungeonBeenCleared = true;
};

void QuestManager::SetHasGuardianBeenSummoned(bool summoned) {
	if (summoned) {
		AudioManager::startBossMusic();
	}

	QuestManager::hasGuardianBeenSummoned = summoned;
};

void QuestManager::SetHasGatesBeenClosed(bool closed) {
	QuestManager::hasGatesBeenClosed = closed;
};

int QuestManager::GetElderStepIndex() {
	return QuestManager::elderStepIndex;
};

int QuestManager::GetElderLineIndex() {
	return QuestManager::elderLineIndex;
};

bool QuestManager::GetHasElderBeenMet() {
	return QuestManager::hasElderBeenMet;
};
bool QuestManager::GetHasForestBeenCleared() {
	return QuestManager::hasForestBeenCleared;
};
bool QuestManager::GetHasPassBeenCleared() {
	return QuestManager::hasPassBeenCleared;
};
bool QuestManager::GetHasFishermanBeenMet() {
	return QuestManager::hasFishermanBeenMet;
};
bool QuestManager::GetHasSeashoreBeenCleared() {
	return QuestManager::hasSeashoreBeenCleared;
};
bool QuestManager::GetHasDungeonBeenCleared() {
	return QuestManager::hasDungeonBeenCleared;
};
bool QuestManager::GetHasGuardianBeenSummoned() {
	return QuestManager::hasGuardianBeenSummoned;
};
bool QuestManager::GetHasGatesBeenClosed() {
	return QuestManager::hasGatesBeenClosed;
};

std::string QuestManager::currentQuestText = "";
// [Note]: This is a quick hack for beggining of the game when I want to show Find the elder quest, but no actual quest has not been started.
std::string QuestManager::currentQuestCompletedText = "Find the Elder       ";
bool QuestManager::hasQuestBeenStarted = false;
bool QuestManager::hasQuestBeenCompleted = false;
bool QuestManager::hasQuestBeenRewarded = false;

int QuestManager::shellCount = 0;
int QuestManager::elderStepIndex = 0;
int QuestManager::elderLineIndex = 0;
bool QuestManager::hasElderBeenMet = false;
bool QuestManager::hasForestBeenCleared = false;
bool QuestManager::hasPassBeenCleared = false;
bool QuestManager::hasFishermanBeenMet = false;
bool QuestManager::hasSeashoreBeenCleared = false;
bool QuestManager::hasDungeonBeenCleared = false;
bool QuestManager::hasGuardianBeenSummoned = false;
bool QuestManager::hasGatesBeenClosed = false;