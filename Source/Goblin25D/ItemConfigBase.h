// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "GameplayTagContainer.h"
#include "ItemConfigBase.generated.h"

/**
 * 
 */
UCLASS()
class GOBLIN25D_API UItemConfigBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	//CONFIG

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable, Category = "Config")
	FName AssetRegistrySearchableTag = "";

	//BASE

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Base")
	FText Name = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Base")
	FText Description = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Base")
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Base")
	FGameplayTag ItemType;

	//INVENTORY

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Inventory")
	bool IsStackable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Inventory", meta = (EditCondition = "IsStackable", EditConditionHides, ClampMin = 0))
	int64 StackCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Inventory", meta = (EditCondition = "IsStackable", EditConditionHides, ClampMin = 0))
	int64 MaxStackCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config|Inventory")
	int32 Value = 0;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("Item"), AssetRegistrySearchableTag);
	}
	
};
