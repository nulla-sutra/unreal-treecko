// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "TreeckoStateSchema.h"

#include "AbilitySystemComponent.h"
#include "StateTreeConditionBase.h"
#include "StateTreeConsiderationBase.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreePropertyFunctionBase.h"
#include "StateTreeTaskBase.h"

namespace Treecko
{
    const FName FStateTreeContextDataNames::ContextOwner = TEXT("Owner");
    const FName FStateTreeContextDataNames::ContextAvatar = TEXT("Avatar");
    const FName FStateTreeContextDataNames::ContextStateTreeComponent = TEXT("State Tree Component");
    const FName FStateTreeContextDataNames::ContextMeshComponent = TEXT("Mesh Component");
    const FName FStateTreeContextDataNames::ContextAbilitySystemComponent = TEXT("Ability System Component");
    const FName FStateTreeContextDataNames::ContextController = TEXT("Controller");
}


UTreeckoStateSchema::UTreeckoStateSchema(): StateTreeComponentType(UStateTreeComponent::StaticClass())
{
    ContextDataDescs.Empty();
    ContextDataDescs.Append({
        {
            Treecko::FStateTreeContextDataNames::ContextOwner,
            AActor::StaticClass(),
            FGuid("D98379D5C1B14EA8B81B766E04661E75")
        },
        {
            Treecko::FStateTreeContextDataNames::ContextAvatar,
            AActor::StaticClass(),
            FGuid("FF4251599EC7443080EE3C4CDEC11CCF")
        },
        {
            Treecko::FStateTreeContextDataNames::ContextStateTreeComponent,
            UStateTreeComponent::StaticClass(),
            FGuid("3DABE82CEB204BEF9111AE0800B1647E")
        },
        {
            Treecko::FStateTreeContextDataNames::ContextMeshComponent,
            USkeletalMeshComponent::StaticClass(),
            FGuid("C151B3D68FFE4318B6C0383A102D4B97")
        },
        {
            Treecko::FStateTreeContextDataNames::ContextAbilitySystemComponent,
            UAbilitySystemComponent::StaticClass(),
            FGuid("8D6D1CC1D0B943378837DC8F7ED2C765")
        },
        {
            Treecko::FStateTreeContextDataNames::ContextController,
            AController::StaticClass(),
            FGuid("49B973A456E24692856D630F523AC8C8")
        }

    });
}

TConstArrayView<FStateTreeExternalDataDesc> UTreeckoStateSchema::GetContextDataDescs() const
{
    return ContextDataDescs;
}

bool UTreeckoStateSchema::IsStructAllowed(const UScriptStruct* InScriptStruct) const
{
    return InScriptStruct->IsChildOf(FStateTreeConditionCommonBase::StaticStruct())
        || InScriptStruct->IsChildOf(FStateTreeEvaluatorCommonBase::StaticStruct())
        || InScriptStruct->IsChildOf(FStateTreeTaskCommonBase::StaticStruct())
        || InScriptStruct->IsChildOf(FStateTreeConsiderationCommonBase::StaticStruct())
        || InScriptStruct->IsChildOf(FStateTreePropertyFunctionCommonBase::StaticStruct());
}

bool UTreeckoStateSchema::IsClassAllowed(const UClass* InScriptStruct) const
{
    return IsChildOfBlueprintBase(InScriptStruct);
}

bool UTreeckoStateSchema::IsExternalItemAllowed(const UStruct& InStruct) const
{
    return true;
}

void UTreeckoStateSchema::PostLoad()
{
    Super::PostLoad();
    ContextDataDescs[0].Struct = OwnerType.Get();
    ContextDataDescs[1].Struct = AvatarType.Get();
    ContextDataDescs[2].Struct = StateTreeComponentType.Get();
    ContextDataDescs[5].Struct = ControllerType.Get();
}

#if WITH_EDITOR
void UTreeckoStateSchema::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
    Super::PostEditChangeChainProperty(PropertyChangedEvent);

    const FProperty* Property = PropertyChangedEvent.Property;

    if (Property)
    {
        if (Property->GetOwnerClass() == StaticClass()
            && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTreeckoStateSchema, OwnerType))
        {
            ContextDataDescs[0].Struct = OwnerType.Get();
        }
        if (Property->GetOwnerClass() == StaticClass()
            && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTreeckoStateSchema, AvatarType))
        {
            ContextDataDescs[1].Struct = AvatarType.Get();
        }
        if (Property->GetOwnerClass() == StaticClass()
            && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTreeckoStateSchema, StateTreeComponentType))
        {
            ContextDataDescs[2].Struct = StateTreeComponentType.Get();
        }
        if (Property->GetOwnerClass() == StaticClass()
            && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTreeckoStateSchema, ControllerType))
        {
            ContextDataDescs[5].Struct = ControllerType.Get();
        }
    }
}

#endif
