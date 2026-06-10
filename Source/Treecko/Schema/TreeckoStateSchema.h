// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeSchema.h"
#include "Components/StateTreeComponent.h"
#include "Components/StateTreeComponentSchema.h"
#include "GameFramework/Controller.h"
#include "TreeckoStateSchema.generated.h"

class UStateTreeComponent;

namespace Treecko
{
    struct FStateTreeContextDataNames
    {
        const static FName ContextOwner,
                           ContextAvatar,
                           ContextStateTreeComponent,
                           ContextMeshComponent,
                           ContextAbilitySystemComponent,
                           ContextController;
    };
}

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew, meta=(CommonSchema), DisplayName = "Treecko StateTree")
class TREECKO_API UTreeckoStateSchema : public UStateTreeComponentSchema
{
    GENERATED_BODY()

public:
    UTreeckoStateSchema();

protected:
    virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const override;
    virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;
    virtual bool IsClassAllowed(const UClass* InScriptStruct) const override;
    virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;

    virtual void PostLoad() override;
    //

    // UPROPERTY()
    // TArray<FStateTreeExternalDataDesc> ContextDataDescs;
    //

public:
    UPROPERTY(EditAnywhere, NoClear)
    TSubclassOf<AActor> OwnerType = AActor::StaticClass();

    UPROPERTY(EditAnywhere, NoClear)
    TSubclassOf<AActor> AvatarType = AActor::StaticClass();

    UPROPERTY(EditAnywhere, NoClear)
    TSubclassOf<UStateTreeComponent> StateTreeComponentType;

    UPROPERTY(EditAnywhere, NoClear)
    TSubclassOf<AController> ControllerType = AController::StaticClass();

protected:
#if WITH_EDITOR
    virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
};
