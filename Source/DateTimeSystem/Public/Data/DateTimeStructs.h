
#pragma once

#include "CoreMinimal.h"
#include "Data/DateTimeEnums.h"
#include "UObject/NoExportTypes.h"
#include "DateTimeStructs.generated.h"

USTRUCT(BlueprintType)
struct DATETIMESYSTEM_API FWeekTime
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
		EDayOfTheWeek DayOfTheWeek = EDayOfTheWeek::Monday;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0, ClampMax = 23, UIMax = 23))
		int32 Hour = 0;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0, ClampMax = 59, UIMax = 59))
		int32 Minute = 0;

    FWeekTime() : FWeekTime(EDayOfTheWeek::Monday,0,0)
    {}

    FWeekTime(EDayOfTheWeek DayOfTheWeek, int32 Hour, int32 Minute) : DayOfTheWeek(DayOfTheWeek), Hour(Hour), Minute(Minute)
    {}

    FWeekTime(const FWeekTime& Other) : FWeekTime(Other.DayOfTheWeek,Other.Hour,Other.Minute)
    {}

    bool operator==(const FWeekTime& Other) const
    {
        return Equals(Other);
    }

    bool Equals(const FWeekTime& Other) const
    {
        return DayOfTheWeek == Other.DayOfTheWeek && Hour == Other.Hour && Minute == Other.Minute;
    }
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FWeekTime& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FWeekTime& Thing)
{
    uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FWeekTime));
    return Hash;
}
#endif


USTRUCT(BlueprintType)
struct DATETIMESYSTEM_API FMonthTime
{
    GENERATED_BODY()

public:

    UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1, UIMin = 1, ClampMax = 31, UIMax = 31))
        int32 Day = 1;

    UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0, ClampMax = 23, UIMax = 23))
        int32 Hour = 0;

    UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0, ClampMax = 59, UIMax = 59))
        int32 Minute = 0;

    FMonthTime() : FMonthTime(1, 0, 0)
    {}

    FMonthTime(int32 Day, int32 Hour, int32 Minute) : Day(Day), Hour(Hour), Minute(Minute)
    {}

    FMonthTime(const FMonthTime& Other) : FMonthTime(Other.Day, Other.Hour, Other.Minute)
    {}

    bool operator==(const FMonthTime& Other) const
    {
        return Equals(Other);
    }

    bool Equals(const FMonthTime& Other) const
    {
        return Day == Other.Day && Hour == Other.Hour && Minute == Other.Minute;
    }
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FMonthTime& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FMonthTime& Thing)
{
    uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FMonthTime));
    return Hash;
}
#endif
