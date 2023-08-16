#pragma once

#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

UCLASS()
class ASYNCNODE_API ATargetActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	bool bBooleanValue = false;

	DECLARE_MULTICAST_DELEGATE(FOnTargetBooleanValueChanged);
	FOnTargetBooleanValueChanged OnTargetBooleanValueChanged;

public:
	FOnTargetBooleanValueChanged& GetOnTargetBooleanValueChanged()
	{
		return OnTargetBooleanValueChanged;
	}

	UFUNCTION(BlueprintCallable)
	void SetBooleanValue(const bool bValue)
	{
		if (bValue != bBooleanValue)
		{
			bBooleanValue = bValue;
			OnTargetBooleanValueChanged.Broadcast();
		}
	}

	UFUNCTION(BlueprintPure)
	bool GetBooleanValue() const
	{
		return bBooleanValue;
	}
};
