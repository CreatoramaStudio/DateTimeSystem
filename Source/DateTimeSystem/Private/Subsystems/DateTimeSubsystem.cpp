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

void UDateTimeSubsystem::SetDefaultDateTime(const FDateTime Value)
{
	CurrentDate = Value;
}

FDateTime UDateTimeSubsystem::GetDateTime() const
{
	return CurrentDate;
}

FString UDateTimeSubsystem::GetStringDateTime() const
{
	return CurrentDate.ToString();
}

ETimeOfTheDay UDateTimeSubsystem::GetTimeOfTheDay() const
{
	return CurrentDate.IsMorning() ? ETimeOfTheDay::Morning : ETimeOfTheDay::Afternoon;
}

EDayOfTheWeek UDateTimeSubsystem::GetDayOfTheWeek() const
{
	return (EDayOfTheWeek)CurrentDate.GetDayOfWeek();
}

EMonthOfTheYear UDateTimeSubsystem::GetMonthOfTheYear() const
{
	return (EMonthOfTheYear)CurrentDate.GetMonthOfYear();
}

void UDateTimeSubsystem::StartTime(const FTimespan InTimeUpdateSpeed, const float UpdateRate)
{
	TimeUpdateSpeed = InTimeUpdateSpeed;
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

bool UDateTimeSubsystem::IsTimePaused() const
{
	return GetWorld()->GetTimerManager().IsTimerPaused(TimerHandle);
}

bool UDateTimeSubsystem::IsTimeActive() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);
}


void UDateTimeSubsystem::BindDateTimeEvent(const FDateTime DateTime, const FOnTimeEvent& Value)
{
	FOnTimeEventMulticast& MulticastDelegate = DateTimeEvents.FindOrAdd(DateTime);
	MulticastDelegate.Add(Value);
}

void UDateTimeSubsystem::UnbindDateTimeEvent(const FDateTime DateTime, const FOnTimeEvent& Value)
{
	if (const TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = DateTimeEvents.Find(DateTime))
	{
		MulticastDelegate->Remove(Value);
	}
}

void UDateTimeSubsystem::UnbindAllDateTimeEvents(const FDateTime DateTime)
{
	if (TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = DateTimeEvents.Find(DateTime))
	{
		MulticastDelegate->Clear();
	}
}

void UDateTimeSubsystem::BindWeeklyEvent(const FWeekTime WeekTime, const FOnTimeEvent& Value)
{
	FOnTimeEventMulticast& MulticastDelegate = WeeklyEvents.FindOrAdd(WeekTime);
	MulticastDelegate.Add(Value);
}

void UDateTimeSubsystem::UnbindWeeklyEvent(const FWeekTime WeekTime, const FOnTimeEvent& Value)
{
	if (TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = WeeklyEvents.Find(WeekTime))
	{
		MulticastDelegate->Remove(Value);
	}
}

void UDateTimeSubsystem::UnbindAllWeeklyEvents(const FWeekTime WeekTime)
{
	if (TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = WeeklyEvents.Find(WeekTime))
	{
		MulticastDelegate->Clear();
	}
}

void UDateTimeSubsystem::BindMonthlyEvent(const FMonthTime MonthTime, const FOnTimeEvent& Value)
{
	FOnTimeEventMulticast& MulticastDelegate = MonthlyEvents.FindOrAdd(MonthTime);
	MulticastDelegate.Add(Value);
}

void UDateTimeSubsystem::UnbindMonthlyEvent(const FMonthTime MonthTime, const FOnTimeEvent& Value)
{
	if (TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = MonthlyEvents.Find(MonthTime))
	{
		MulticastDelegate->Remove(Value);
	}
}

void UDateTimeSubsystem::UnbindAllMonthlyEvents(const FMonthTime MonthTime)
{
	if (TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = MonthlyEvents.Find(MonthTime))
	{
		MulticastDelegate->Clear();
	}
}

void UDateTimeSubsystem::CallDateTimeEvents(const FDateTime DateTime)
{
	const TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = DateTimeEvents.Find(DateTime);
	if (MulticastDelegate && MulticastDelegate->IsBound())
	{
		MulticastDelegate->Broadcast();
	}
}

void UDateTimeSubsystem::CallWeeklyEvents(const FWeekTime WeekTime)
{
	const TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = WeeklyEvents.Find(WeekTime);
	if (MulticastDelegate && MulticastDelegate->IsBound())
	{
		MulticastDelegate->Broadcast();
	}
}

void UDateTimeSubsystem::CallMonthlyEvents(const FMonthTime MonthTime)
{
	const TObjectPtr<FOnTimeEventMulticast> MulticastDelegate = MonthlyEvents.Find(MonthTime);
	if (MulticastDelegate && MulticastDelegate->IsBound())
	{
		MulticastDelegate->Broadcast();
	}
}

void UDateTimeSubsystem::UpdateTime()
{
	const FDateTime OldValue = CurrentDate;

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

	CallWeeklyEvents(FWeekTime(GetDayOfTheWeek(), CurrentDate.GetHour(), CurrentDate.GetMinute()));

	CallMonthlyEvents(FMonthTime(CurrentDate.GetDay(), CurrentDate.GetHour(), CurrentDate.GetMinute()));

}
