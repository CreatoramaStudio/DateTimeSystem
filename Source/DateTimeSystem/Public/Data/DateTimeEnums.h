
#pragma once

#include "CoreMinimal.h"
#include "DateTimeEnums.generated.h"


UENUM(BlueprintType)
enum class ETimeOfTheDay : uint8
{
	Morning,
	Afternoon
};

/**
 * Enumerates the days of the week in 7-day calendars.
 */
UENUM(BlueprintType)
enum class EDayOfTheWeek : uint8
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};


/**
 * Enumerates the months of the year in 12-month calendars.
 */
UENUM(BlueprintType)
enum class EMonthOfTheYear : uint8
{
	None UMETA(Hidden),
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};
