// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestData.generated.h"

class UQuestTask;

/**
 * 
 */
UCLASS()
class GOBLIN25D_API UQuestData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	// CONFIG

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable, Category = "Config")
	FName QuestID = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	TSoftObjectPtr<UTexture2D> QuestThumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	FText QuestName = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	FText Description = FText::GetEmpty();

	// TASKS

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Tasks")
	TArray<UQuestTask*> QuestTasks;


	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("Quest"), QuestID);
	}
	
};
