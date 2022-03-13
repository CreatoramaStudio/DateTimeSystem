// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data/Enums.h"
#include "DateTimeSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnTimeEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeEventMulticast);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateTime, FDateTime, CurrentDateTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeHour, FDateTime, CurrentDateTime, ETimeOfTheDay, TimeOfTheDay);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeDay, FDateTime, CurrentDateTime, EDayOfTheWeek, DayOfTheWeek);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeMouth, FDateTime, CurrentDateTime, EMonthOfTheYear, MonthOfTheYear);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeYear, FDateTime, CurrentDateTime);


/**
 *
 */
UCLASS()
class DATETIMESYSTEM_API UDateTimeSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

protected:

	FDateTime CurrentDate;

	FTimespan TimeUpdateSpeed;

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "Time Subsystem|Events")
		FOnUpdateTime OnUpdateTime;

	UPROPERTY(BlueprintAssignable, Category = "Time Subsystem|Events")
		FOnChangeHour OnChangeHour;

	UPROPERTY(BlueprintAssignable, Category = "Time Subsystem|Events")
		FOnChangeDay OnChangeDay;

	UPROPERTY(BlueprintAssignable, Category = "Time Subsystem|Events")
		FOnChangeMouth OnChangeMouth;

	UPROPERTY(BlueprintAssignable, Category = "Time Subsystem|Events")
		FOnChangeYear OnChangeYear;


	TMap<FDateTime, FOnTimeEventMulticast> DateTimeEvents;

	//UPROPERTY(BlueprintReadWrite, Category = "Time Subsystem")

private:

public:

	UDateTimeSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
		void SetDefaultDateTime(FDateTime Value);

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		FDateTime GetDateTime();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		FString GetStringDateTime();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		ETimeOfTheDay GetTimeOfTheDay();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		EDayOfTheWeek GetDayOfTheWeek();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		EMonthOfTheYear GetMonthOfTheYear();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
		void StartTime(FTimespan timeUpdateSpeed, float UpdateRate = 1);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
		void PauseTime();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
		void UnPauseTime();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
		void StopTime();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		bool IsTimePaused();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
		bool IsTimeActive();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
		void BindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
		void UnbindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
		void UnbindAllDateTimeEvents(FDateTime DateTime);

protected:

	void CallDateTimeEvents(FDateTime DateTime);

	void UpdateTime();

private:

};
