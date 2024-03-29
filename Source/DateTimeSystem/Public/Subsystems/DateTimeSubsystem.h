// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data/DateTimeEnums.h"
#include "Data/DateTimeStructs.h"
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

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Time Subsystem|Events")
	FOnUpdateTime OnUpdateTime;

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Time Subsystem|Events")
	FOnChangeHour OnChangeHour;

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Time Subsystem|Events")
	FOnChangeDay OnChangeDay;

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Time Subsystem|Events")
	FOnChangeMouth OnChangeMouth;

	UPROPERTY(SaveGame,BlueprintAssignable, Category = "Time Subsystem|Events")
	FOnChangeYear OnChangeYear;

protected:

	UPROPERTY(SaveGame)
	FDateTime CurrentDate;

	UPROPERTY(SaveGame)
	FTimespan TimeUpdateSpeed;

	UPROPERTY(SaveGame)
	FTimerHandle TimerHandle;

	UPROPERTY(SaveGame)
	TMap<FDateTime, FOnTimeEventMulticast> DateTimeEvents;

	UPROPERTY(SaveGame)
	TMap<FWeekTime, FOnTimeEventMulticast> WeeklyEvents;

	UPROPERTY(SaveGame)
	TMap<FMonthTime, FOnTimeEventMulticast> MonthlyEvents;

private:

public:

	UDateTimeSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
	void SetDefaultDateTime(FDateTime Value);

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	FDateTime GetDateTime() const;

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	FString GetStringDateTime() const;

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	ETimeOfTheDay GetTimeOfTheDay() const;

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	EDayOfTheWeek GetDayOfTheWeek() const;

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	EMonthOfTheYear GetMonthOfTheYear() const;

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
	void StartTime(FTimespan InTimeUpdateSpeed, float UpdateRate = 1);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
	void PauseTime();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
	void UnPauseTime();

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem")
	void StopTime();

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	bool IsTimePaused() const;

	UFUNCTION(BlueprintPure, Category = "Time Subsystem")
	bool IsTimeActive() const;

	//Date time

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void BindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindAllDateTimeEvents(FDateTime DateTime);

	//Week

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void BindWeeklyEvent(FWeekTime WeekTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindWeeklyEvent(FWeekTime WeekTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindAllWeeklyEvents(FWeekTime WeekTime);

	//Month

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void BindMonthlyEvent(FMonthTime MonthTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindMonthlyEvent(FMonthTime MonthTime, const FOnTimeEvent& Value);

	UFUNCTION(BlueprintCallable, Category = "Time Subsystem|Date Time Events")
	void UnbindAllMonthlyEvents(FMonthTime MonthTime);

protected:

	void CallDateTimeEvents(FDateTime DateTime);

	void CallWeeklyEvents(FWeekTime WeekTime);

	void CallMonthlyEvents(FMonthTime MonthTime);

	void UpdateTime();

private:
};
