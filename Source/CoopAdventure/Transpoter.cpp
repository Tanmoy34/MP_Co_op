// Fill out your copyright notice in the Description page of Project Settings.


#include "Transpoter.h"

#include "PressurePlate.h"

// Sets default values for this component's properties
UTranspoter::UTranspoter()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	MovePoint = 3.0f;
	ActivatedTriggerCount = 0;

	ArePointsSet = false;
	StartPoint =FVector::Zero();
	EndPoint =FVector::Zero();
}



void UTranspoter::BeginPlay()
{
	Super::BeginPlay();
	for (AActor* TA : TriggerActors)
	{
		APressurePlate* PressurePlateActor = Cast<APressurePlate>(TA);
		if (PressurePlateActor)
		{
			PressurePlateActor->OnActivate.AddDynamic(this,&UTranspoter::OnPressurePlateActivated);
			PressurePlateActor->OnDeactivate.AddDynamic(this,&UTranspoter::OnPressurePlateDeactivated);
		}
	}
	
	
}



void UTranspoter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TriggerActors.Num()>0)
	{
		AllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
		if (AllTriggerActorsTriggered)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("All Trigger Actors Triggered!!!"));
		}
	}
	
}

void UTranspoter::Setpoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2))
	{
		return;
	}
	StartPoint = Point1;
	EndPoint = Point2;
	ArePointsSet = true;
		
}

void UTranspoter::OnPressurePlateActivated()
{
	ActivatedTriggerCount++;
	FString Msg = FString::Printf(TEXT("Active Trigger Count: %d"), ActivatedTriggerCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Msg);
}

void UTranspoter::OnPressurePlateDeactivated()
{
	ActivatedTriggerCount--;
	FString Msg = FString::Printf(TEXT("Active Trigger Count: %d"), ActivatedTriggerCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, Msg);
}

