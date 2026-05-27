// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"



#define EasyPrint(X) GEngine->AddOnScreenDebugMessage(-1,15,FColor::Red,X)

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		FString SubsystemName   =  OnlineSubsystem->GetSubsystemName().ToString();
		EasyPrint(SubsystemName);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			EasyPrint("session interface IS Valid");
			
		}
	}
		
}

void UMultiplayerSessionsSubsystem::CreateSession(FString ServerName)
{
	EasyPrint("Create session Called");
}

void UMultiplayerSessionsSubsystem::FindSession(FString ServerName)
{
	EasyPrint("Find session Called");
}
