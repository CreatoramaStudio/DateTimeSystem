#include "LogDateTimeSystem.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogDateTimeSystem);

void FLogDateTimeSystem::ConsoleInfo(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogDateTimeSystem, Display, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::White, Description);
	}
}

void FLogDateTimeSystem::ConsoleWarning(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogDateTimeSystem, Warning, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, Description);
	}
}

void FLogDateTimeSystem::ConsoleError(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogDateTimeSystem, Error, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Red, Description);
	}
}

void FLogDateTimeSystem::VisLogString(const AActor* Actor, const FString& Description, const FColor Color)
{
	UE_VLOG(Actor, LogDateTimeSystem, Log, TEXT("%s"), *Description);
}

void FLogDateTimeSystem::VisLogLocation(const AActor* Actor, const FVector Location, const float Radius, const FString& Description, const FColor Color)
{
	UE_VLOG_LOCATION(Actor, LogDateTimeSystem, Log, Location, Radius, Color, TEXT("%s"), *Description);
}

void FLogDateTimeSystem::VisLogSegment(const AActor* Actor, const FVector Start, const FVector End, const float Thickness, const FString& Description, const FColor Color)
{
	UE_VLOG_SEGMENT_THICK(Actor, LogDateTimeSystem, Log, Start, End, Color, Thickness, TEXT("%s"), *Description);
}

void FLogDateTimeSystem::VisLogArrow(const AActor* Actor, const FVector Start, const FVector End, const FString& Description, const FColor Color)
{
	UE_VLOG_ARROW(Actor, LogDateTimeSystem, Log, Start, End, Color, TEXT("%s"), *Description);
}
