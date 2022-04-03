// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDateTimeSystem, Log, All);

class FLogDateTimeSystem
{
public:

#pragma region Console

	static void ConsoleInfo(const FString& Description, const bool bShowOnScreen = false, const float Time = 1);

	static void ConsoleWarning(const FString& Description, const bool bShowOnScreen = false, const float Time = 1);

	static void ConsoleError(const FString& Description, const bool bShowOnScreen = false, const float Time = 1);

#pragma endregion

#pragma region VisualLogger

	static void VisLogString(const AActor* Actor, const FString& Description, const FColor Color = FColor::White);

	static void VisLogLocation(const AActor* Actor, const FVector Location, const float Radius = 5, const FString& Description = "", const FColor Color = FColor::White);

	static void VisLogSegment(const AActor* Actor, const FVector Start, const FVector End, const float Thickness = 2, const FString& Description = "", const FColor Color = FColor::White);

	static void VisLogArrow(const AActor* Actor, const FVector Start, const FVector End, const FString& Description, const FColor Color = FColor::White);

#pragma endregion
};