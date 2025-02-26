// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestTask.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EQuestTaskStatus : uint8 {
    INACTIVE = 0 UMETA(DisplayName = "Inactive"),
    ACTIVE = 1 UMETA(DisplayName = "Active"),
    COMPLETED = 2 UMETA(DisplayName = "Completed"),
    FAILED = 3 UMETA(DisplayName = "Failed")
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskCompleted, UQuestTask*, Task);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskFailed, UQuestTask*, Task);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskStarted, UQuestTask*, Task);

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class GOBLIN25D_API UQuestTask : public UObject
{
	GENERATED_BODY()


public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
    FText TaskName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
    FText TaskDescription;


public:

    UPROPERTY(BlueprintAssignable)
    FOnTaskCompleted OnTaskCompleted;

    UPROPERTY(BlueprintAssignable)
    FOnTaskFailed OnTaskFailed;

    UPROPERTY(BlueprintAssignable)
    FOnTaskStarted OnTaskStarted;

    UFUNCTION(BlueprintNativeEvent, Category = "Quest Task")
    void StartTask(APlayerController* PlayerController);
    virtual void StartTask_Implementation(APlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Category = "Quest Task")
    virtual void ActivateTask(APlayerController* PlayerController) {
        OnTaskStarted.Broadcast(this);
        StartTask(PlayerController);
    }

    UFUNCTION(BlueprintCallable, Category = "Quest Task")
    virtual void CompleteTask() {
        OnTaskCompleted.Broadcast(this);
    }

    UFUNCTION(BlueprintCallable, Category = "Quest Task")
    virtual void FailTask() {
        OnTaskFailed.Broadcast(this);
    }
	
};
