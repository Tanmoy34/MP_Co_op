// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class COOPADVENTURE_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:


	//variable
	IOnlineSessionPtr SessionInterface;

	bool CreateServerAfterDestroy;

	FString DestroyServerName;

	TSharedPtr<FOnlineSessionSearch>  SessionSearch;

	FString ServerNameToFind;


	UMultiplayerSessionsSubsystem();
	//Fuction
	 void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	void CreateSession(FString ServerName);

	UFUNCTION(BlueprintCallable)
	void FindSession(FString ServerName);

	

	void OnCreatSessionComplete(FName SessionName,bool WasSucssessFull );
	
	void OnDestroySessionComplete(FName SessionName,bool WasSucssessFull );

	void FindSessionComplete(bool WasSucssessFull);

	

	

	
};
