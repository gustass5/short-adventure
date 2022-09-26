#pragma once

#include "../ui/UIManager.hpp"
#include <string>

class QuestManager {
  private:
	QuestManager();
	~QuestManager();

  private:
	// [SUMMARY]: Current quest data
	static std::string currentQuestText;
	static std::string currentQuestCompletedText;
	static bool hasQuestBeenStarted;
	static bool hasQuestBeenCompleted;
	static bool hasQuestBeenRewarded;
	static int shellCount;

  public:
	static void
	SetCurrentQuestText(std::string text);
	static void SetCurrentQuestCompletedText(std::string text);
	static void SetHasQuestBeenStarted(bool started);
	static void SetHasQuestBeenCompleted(bool completed);
	static void SetHasQuestBeenRewarded(bool rewarded);
	static void SetShellCount(int count);

	static std::string GetCurrentQuestText();
	static std::string GetCurrentQuestCompletedText();
	static bool GetHasQuestBeenStarted();
	static bool GetHasQuestBeenCompleted();
	static bool GetHasQuestBeenRewarded();
	static int GetShellCount();

  private:
	// [SUMMARY]: Conditions
	static int elderStepIndex;
	static int elderLineIndex;
	static bool hasElderBeenMet;
	static bool hasForestBeenCleared;
	static bool hasPassBeenCleared;
	static bool hasFishermanBeenMet;
	static bool hasSeashoreBeenCleared;
	static bool hasDungeonBeenCleared;

  public:
	static void SetElderStepIndex(int index);
	static void SetElderLineIndex(int index);
	static void SetHasElderBeenMet();
	static void SetHasForestBeenCleared();
	static void SetHasPassBeenCleared();
	static void SetHasFishermanBeenMet();
	static void SetHasSeashoreBeenCleared();
	static void SetHasDungeonBeenCleared();

	static int GetElderStepIndex();
	static int GetElderLineIndex();
	static bool GetHasElderBeenMet();
	static bool GetHasForestBeenCleared();
	static bool GetHasPassBeenCleared();
	static bool GetHasFishermanBeenMet();
	static bool GetHasSeashoreBeenCleared();
	static bool GetHasDungeonBeenCleared();

  public:
	static void StartQuest(std::string questText, std::string questCompletedText);
	static void RenderQuest(SDL_Renderer* renderer);
};
