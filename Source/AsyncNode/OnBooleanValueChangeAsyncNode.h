#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "OnBooleanValueChangeAsyncNode.generated.h"

class AListeningActor;
class ATargetActor;

UCLASS()
class ASYNCNODE_API UOnBooleanValueChangeAsyncNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	ATargetActor* TargetActor;

	UPROPERTY(Transient)
	AActor* ListeningActor;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyOnValueChangeAsyncNodeExecutionPinDelegate);

public:
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Success"))
	FDestroyOnValueChangeAsyncNodeExecutionPinDelegate OnSuccessDelegate;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Fail"))
	FDestroyOnValueChangeAsyncNodeExecutionPinDelegate OnFailDelegate;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Value Change"))
	FDestroyOnValueChangeAsyncNodeExecutionPinDelegate OnValueChangedDelegate;

	UFUNCTION
	(
		BlueprintCallable,
		meta =
		(
			DisplayName = "On Boolean Value Change",
			BlueprintInternalUseOnly = "true",
			DefaultToSelf = "InListeningActor"
		)
	)
	static UOnBooleanValueChangeAsyncNode* OnBooleanValueChange(AListeningActor* InListeningActor, ATargetActor* InTargetActor);

	virtual void Activate() override;

private:
	void OnValueChanged();

	UFUNCTION()
	void OnTargetActorOrListeningActorDestroyed(AActor* destroyedActor);
};
