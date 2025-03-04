// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemConfigBase.h"
#include "QuestData.generated.h"

class UQuestTask;

/**
 * 
 */

UENUM(BlueprintType)
enum class EQuestType : uint8 {
	MAIN = 0 UMETA(DisplayName = "Main Mission"),
	SIDE = 1 UMETA(DisplayName = "Side Mission"),
	RETRIGGERABLE = 2 UMETA(DisplayName = "Retriggerable Mission"),
};


USTRUCT(BlueprintType)
struct FItemLoot
{
	GENERATED_BODY()

UPROPERTY(EditAnywhere, BlueprintReadWrite)
TSoftObjectPtr<class UItemConfigBase> ItemReward = nullptr;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
int32 Amount = 1;

};

USTRUCT(BlueprintType)
struct FItemRandomAmount
{
	GENERATED_BODY()

	FItemRandomAmount()
	{
		RangeProbability = FRuntimeFloatCurve();
		RangeProbability.GetRichCurve()->AddKey(0.f, 1.f);
		RangeProbability.GetRichCurve()->AddKey(1.f, 0.f);
	}
	FItemRandomAmount(const TSoftObjectPtr<class UItemConfigBase>& InItem, FInt32Range InAmountRange) : Item(InItem), AmountRange(InAmountRange)
	{
		RangeProbability = FRuntimeFloatCurve();
		RangeProbability.GetRichCurve()->AddKey(0.f, 1.f);
		RangeProbability.GetRichCurve()->AddKey(1.f, 0.f);
	}

UPROPERTY(EditAnywhere, BlueprintReadWrite)
TSoftObjectPtr<class UItemConfigBase> Item = nullptr;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceInlineRow))
FInt32Range AmountRange = FInt32Range(0, 1);

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (XAxisName = "Normalized Amount Range", YAxisName = "Probability"))
FRuntimeFloatCurve RangeProbability;

int GetRandomizedAmount() const
{
	const FRichCurve* RichCurve = RangeProbability.GetRichCurveConst();

	TArray<float> Distribution;

	const int Min = AmountRange.GetLowerBoundValue();
	const int Max = AmountRange.GetUpperBoundValue();
	const int Range = Max - Min + 1;

	for (int i = Min; i <= Max; ++i)
	{
		const float NormalizedValue = static_cast<float>(i - Min) / Range;
		float Probability = RichCurve->Eval(NormalizedValue, 0.0f);
		Distribution.Add(Probability);
	}

	float TotalProbability = 0.0f;
	for (const auto& Prob : Distribution)
	{
		TotalProbability += Prob;
	}

	float RandomProbability = FMath::RandRange(0.f, TotalProbability);

	for (int i = 0; i < Distribution.Num(); ++i)
	{
		if (RandomProbability < Distribution[i])
		{
			return i + Min;
		}
		RandomProbability -= Distribution[i];
	}
	return Max;
}
};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	EQuestType QuestType = EQuestType::MAIN;

	// TASKS

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Tasks")
	TArray<UQuestTask*> QuestTasks;

	// REWARDS

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rewards")
	int32 Experience;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rewards")
	int32 Coins;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rewards")
	int32 Crystals;

	UPROPERTY(EditDefaultsOnly, Category = "Rewards")
	TArray<FItemRandomAmount> ItemLoot;

	UFUNCTION(BlueprintCallable)
	TArray<FItemLoot> GetLoot()
	{
		TArray<FItemLoot> Result;

		for (const auto& ItemRandomAmount : ItemLoot)
		{
			const int32 Amount = ItemRandomAmount.GetRandomizedAmount();
			if (Amount <= 0) continue;

			UItemConfigBase* ItemConfig = ItemRandomAmount.Item.LoadSynchronous();
			if (!ItemConfig) continue;

			FItemLoot Loot;
			Loot.ItemReward = ItemRandomAmount.Item;
			Loot.Amount = Amount;

			Result.Add(Loot);
		}

		return Result;
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("Quest"), QuestID);
	}
	
};
