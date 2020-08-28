
#include "CoreMinimal.h"
#include "Inventory/ItemActor.h"
#include "ConsumingItem.generated.h"


UCLASS(abstract)
class AConsumingItem : public AItemActor {

	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
		float CalculateHealth;

	UPROPERTY(EditDefaultsOnly)
		float CalculateHunger;

	UPROPERTY(EditDefaultsOnly)
		float CalculateEndurance;

	UPROPERTY(EditDefaultsOnly)
		float CalculateThirst;
};