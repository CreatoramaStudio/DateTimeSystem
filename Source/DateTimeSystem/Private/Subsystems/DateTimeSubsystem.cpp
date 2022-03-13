// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DateTimeSubsystem.h"

UDateTimeSubsystem::UDateTimeSubsystem()
{

}

void UDateTimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UDateTimeSubsystem::Deinitialize()
{
	Super::Deinitialize();

}

void UDateTimeSubsystem::SetDefaultDateTime(FDateTime Value)
{
	CurrentDate = Value;
}

FDateTime UDateTimeSubsystem::GetDateTime()
{
	return CurrentDate;
}

FString UDateTimeSubsystem::GetStringDateTime()
{
	return CurrentDate.ToString();
}

ETimeOfTheDay UDateTimeSubsystem::GetTimeOfTheDay()
{
	return CurrentDate.IsMorning() ? ETimeOfTheDay::Morning : ETimeOfTheDay::Afternoon;
}

EDayOfTheWeek UDateTimeSubsystem::GetDayOfTheWeek()
{
	return (EDayOfTheWeek)CurrentDate.GetDayOfWeek();
}

EMonthOfTheYear UDateTimeSubsystem::GetMonthOfTheYear()
{
	return (EMonthOfTheYear)CurrentDate.GetMonthOfYear();
}

void UDateTimeSubsystem::StartTime(FTimespan timeUpdateSpeed, float UpdateRate)
{
	TimeUpdateSpeed = timeUpdateSpeed;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDateTimeSubsystem::UpdateTime, UpdateRate, true, 0);
}

void UDateTimeSubsystem::PauseTime()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
}

void UDateTimeSubsystem::UnPauseTime()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
}

void UDateTimeSubsystem::StopTime()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

bool UDateTimeSubsystem::IsTimePaused()
{
	return GetWorld()->GetTimerManager().IsTimerPaused(TimerHandle);
}

bool UDateTimeSubsystem::IsTimeActive()
{
	return GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);
}


void UDateTimeSubsystem::BindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value)
{
	FOnTimeEventMulticast& MulticastDelegate = DateTimeEvents.FindOrAdd(DateTime);
	MulticastDelegate.Add(Value);
}

void UDateTimeSubsystem::UnbindDateTimeEvent(FDateTime DateTime, const FOnTimeEvent& Value)
{
	FOnTimeEventMulticast* MulticastDelegate = DateTimeEvents.Find(DateTime);
	if (MulticastDelegate)
	{
		MulticastDelegate->Remove(Value);
	}
}

void UDateTimeSubsystem::UnbindAllDateTimeEvents(FDateTime DateTime)
{
	FOnTimeEventMulticast* MulticastDelegate = DateTimeEvents.Find(DateTime);
	if (MulticastDelegate)
	{
		MulticastDelegate->Clear();
	}
}

void UDateTimeSubsystem::CallDateTimeEvents(FDateTime DateTime)
{
	FOnTimeEventMulticast* MulticastDelegate = DateTimeEvents.Find(DateTime);
	if (MulticastDelegate && MulticastDelegate->IsBound())
	{
		MulticastDelegate->Broadcast();
	}
}

void UDateTimeSubsystem::UpdateTime()
{
	FDateTime OldValue = CurrentDate;

	CurrentDate += TimeUpdateSpeed;

	OnUpdateTime.Broadcast(CurrentDate);

	if (OldValue.GetHour() != CurrentDate.GetHour())
	{
		OnChangeHour.Broadcast(CurrentDate, GetTimeOfTheDay());
	}

	if (OldValue.GetDay() != CurrentDate.GetDay())
	{
		OnChangeDay.Broadcast(CurrentDate, GetDayOfTheWeek());
	}

	if (OldValue.GetMonth() != CurrentDate.GetMonth())
	{
		OnChangeMouth.Broadcast(CurrentDate, GetMonthOfTheYear());
	}

	if (OldValue.GetYear() != CurrentDate.GetYear())
	{
		OnChangeYear.Broadcast(CurrentDate);
	}

	CallDateTimeEvents(CurrentDate);

}
