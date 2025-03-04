#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestInstance.generated.h"

class UQuestData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestCompleted, UQuestInstance*, QuestInstance, TSoftObjectPtr<UQuestData>, QuestData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestFailed, UQuestInstance*, QuestInstance, TSoftObjectPtr<UQuestData>, QuestData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStarted, UQuestInstance*, QuestInstance, TSoftObjectPtr<UQuestData>, QuestData);

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class GOBLIN25D_API UQuestInstance : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    TSoftObjectPtr<UQuestData> CurrentQuestData = nullptr;

public:
    UPROPERTY(BlueprintAssignable)
    FOnQuestCompleted OnQuestCompleted;

    UPROPERTY(BlueprintAssignable)
    FOnQuestFailed OnQuestFailed;

    UPROPERTY(BlueprintAssignable)
    FOnQuestStarted OnQuestStarted;

    UFUNCTION(BlueprintNativeEvent, Category = "QuestInstance")
    void StartQuest(APlayerController* InPlayerController, const TSoftObjectPtr<UQuestData>& InQuestData);
    virtual void StartQuest_Implementation(APlayerController* InPlayerController, const TSoftObjectPtr<UQuestData>& InQuestData);

    UFUNCTION(BlueprintCallable, Category = "QuestInstance")
    virtual void ActivateQuest(APlayerController* InPlayerController, TSoftObjectPtr<UQuestData> InQuestData) {
        CurrentQuestData = InQuestData;
        StartQuest(InPlayerController, CurrentQuestData);
        OnQuestStarted.Broadcast(this, CurrentQuestData);
    }

    UFUNCTION(BlueprintCallable, Category = "QuestInstance")
    virtual void CompleteQuest() {
        OnQuestCompleted.Broadcast(this, CurrentQuestData);
    }

    UFUNCTION(BlueprintCallable, Category = "QuestInstance")
    virtual void FailQuest() {
        OnQuestFailed.Broadcast(this, CurrentQuestData);
    }
};