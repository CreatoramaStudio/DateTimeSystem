
#pragma once

#include "CoreMinimal.h"
#include "Data/Enums.h"
#include "UObject/NoExportTypes.h"
#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct DATETIMESYSTEM_API FSchedule
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
		EDayOfTheWeek DayOfTheWeek = EDayOfTheWeek::Monday;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
		int32 Hour;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
		int32 Minute;

    FSchedule() : FSchedule(EDayOfTheWeek::Monday,0,0)
    {}

    FSchedule(EDayOfTheWeek DayOfTheWeek, int32 Hour, int32 Minute) : DayOfTheWeek(DayOfTheWeek), Hour(Hour), Minute(Minute)
    {}

    FSchedule(const FSchedule& Other) : FSchedule(Other.DayOfTheWeek,Other.Hour,Other.Minute)
    {}

    bool operator==(const FSchedule& Other) const
    {
        return Equals(Other);
    }

    bool Equals(const FSchedule& Other) const
    {
        return DayOfTheWeek == Other.DayOfTheWeek && Hour == Other.Hour && Minute == Other.Minute;
    }
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FSchedule& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FSchedule& Thing)
{
    uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FSchedule));
    return Hash;
}
#endif
