// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"



#define EasyPrint(X) GEngine->AddOnScreenDebugMessage(-1,15,FColor::Green,X)

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		EasyPrint(SubsystemName);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UMultiplayerSessionsSubsystem::OnCreatSessionComplete);
			
		}
	}
		
}

void UMultiplayerSessionsSubsystem::CreateSession(FString ServerName)
{
	EasyPrint("Create session Called");
	
	//Checking Servername Should not be Empty
	if (ServerName.IsEmpty())
	{
		EasyPrint("server name is empty");
		return;
	}

	//Session Setting and Properties
	FOnlineSessionSettings SessionSettings;
	
	SessionSettings.bAllowJoinInProgress = true; //Can Other player Can Join after Session Inisiated
	SessionSettings.bIsDedicated = false; //says Server didiacted or not
	SessionSettings.bShouldAdvertise = true; // Allow Other Player To vissualize My session
	SessionSettings.NumPublicConnections = 2; //How many Player Can maximum join

	//Steam sestting
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowJoinViaPresence = true;
	bool IsLan = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLan = true;
	}
	
	SessionSettings.bIsLANMatch = IsLan;


	

	//Give Session A Name 
	FName SessionName = FName("Co-op Advencher Session");

	
	SessionInterface->CreateSession(0,SessionName,SessionSettings);
	
	




	
	
}

void UMultiplayerSessionsSubsystem::FindSession(FString ServerName)
{
	EasyPrint("Find session Called");
}

void UMultiplayerSessionsSubsystem::OnCreatSessionComplete(FName SessionName, bool WasSucssessFull)
{
	EasyPrint(FString::Printf(TEXT("ON session Creation completed: %d"),WasSucssessFull));
}

