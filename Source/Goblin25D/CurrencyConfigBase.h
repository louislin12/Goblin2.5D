// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "CurrencyConfigBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECurrencyType : uint8 {
	COIN = 0 UMETA(DisplayName = "Coin"),
	CRYSTAL = 1 UMETA(DisplayName = "Crystal")
};

UCLASS()
class GOBLIN25D_API UCoinConfigBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	//CONFIG

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable, Category = "Config")
	FName AssetRegistrySearchableTag = "";

	//BASE

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	FText Name = FText::GetEmpty();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flipbook")
	UPaperFlipbook* Flipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	ECurrencyType CurrencyType = ECurrencyType::COIN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	int32 Value = 0;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("Item"), AssetRegistrySearchableTag);
	}
	
};
