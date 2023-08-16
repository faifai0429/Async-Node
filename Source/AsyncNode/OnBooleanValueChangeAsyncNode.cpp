#include "OnBooleanValueChangeAsyncNode.h"

#include "ListeningActor.h"
#include "TargetActor.h"

UOnBooleanValueChangeAsyncNode* UOnBooleanValueChangeAsyncNode::OnBooleanValueChange(AListeningActor* InListeningActor, ATargetActor* InTargetActor)
{
	UOnBooleanValueChangeAsyncNode* OnBooleanValueChangeAsyncNode = NewObject<UOnBooleanValueChangeAsyncNode>(InListeningActor);
	OnBooleanValueChangeAsyncNode->ListeningActor = InListeningActor;
	OnBooleanValueChangeAsyncNode->TargetActor = InTargetActor;
	OnBooleanValueChangeAsyncNode->RegisterWithGameInstance(InListeningActor);

	return OnBooleanValueChangeAsyncNode;
}

void UOnBooleanValueChangeAsyncNode::Activate()
{
	if (TargetActor != nullptr && ListeningActor != nullptr)
	{
		TargetActor->OnDestroyed.AddDynamic(this, &UOnBooleanValueChangeAsyncNode::OnTargetActorOrListeningActorDestroyed);
		ListeningActor->OnDestroyed.AddDynamic(this, &UOnBooleanValueChangeAsyncNode::OnTargetActorOrListeningActorDestroyed);

		TargetActor->GetOnTargetBooleanValueChanged().AddUObject(this, &UOnBooleanValueChangeAsyncNode::OnValueChanged);

		OnSuccessDelegate.Broadcast();
	}
	else
	{
		OnFailDelegate.Broadcast();
	}
}

void UOnBooleanValueChangeAsyncNode::OnValueChanged()
{
	OnValueChangedDelegate.Broadcast();

	SetReadyToDestroy();
}

void UOnBooleanValueChangeAsyncNode::OnTargetActorOrListeningActorDestroyed(AActor* destroyedActor)
{
	if (destroyedActor == ListeningActor)
	{
		TargetActor->GetOnTargetBooleanValueChanged().RemoveAll(this);
	}

	SetReadyToDestroy();
}
