﻿// Copyright (c) Jared Taylor. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AlphaInterp.h"
#include "GameplayTagContainer.h"
#include "HitReact.h"
#include "HitReactImpulseParams.h"
#include "HitReactTypes.h"
#include "Components/ActorComponent.h"
#include "HitReactComponent.generated.h"

class UPhysicalAnimationComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitReactToggleStateChanged, EHitReactToggleState, NewState);

/**
 * Component for applying hit reactions to a skeletal mesh
 */
UCLASS(Config=Game, ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class PHYSICSHITREACT_API UHitReactComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Hit react profiles to use when applying hit reacts */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=HitReact, meta=(Categories="HitReact.Profile"))
	TMap<FGameplayTag, FHitReactProfile> Profiles;

	/** Whether to apply hit reacts on dedicated servers */
	UPROPERTY(Config)
	bool bApplyHitReactOnDedicatedServer = false;

	/** Global interp toggle properties for enabling/disabling the hit react system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HitReact)
	FInterpProperties GlobalToggleProperties;
	
protected:
	/** Bones currently being simulated */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=HitReact)
	TMap<FName, FHitReact> PhysicsBlends;

	/** Mesh to simulate hit reactions on */
	UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, Category=HitReact)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, Category=HitReact)
	TObjectPtr<UPhysicalAnimationComponent> PhysicalAnimation;

	/** Global physics interpolation for toggling the system on and off */
	UPROPERTY(Transient, BlueprintReadOnly, Category=HitReact)
	FAlphaInterp GlobalAlphaInterp;

	/** Current toggle state of the hit react system */
	UPROPERTY(Transient, BlueprintReadOnly, Category=HitReact)
	EHitReactToggleState HitReactToggleState = EHitReactToggleState::Enabled;

public:
	/** Called when the hit react system is toggled on or off */
	UPROPERTY(BlueprintAssignable, Category=HitReact)
	FOnHitReactToggleStateChanged OnHitReactToggleStateChanged;
	
public:
	UHitReactComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	 * Trigger a hit reaction on the specified bone
	 * @param ProfileToUse - Profile to use when applying the hit react
	 * @param BoneName - Name of the bone to hit react
	 * @param bIncludeSelf - If false, exclude the BoneName and only simulate bones below it
	 * @param ImpulseParams - Impulse parameters to use when applying the hit react
	 * @return True if the hit react was applied
	 */
	UFUNCTION(BlueprintCallable, Category=HitReact, meta=(Categories="HitReact.Profile"))
	bool HitReact(FGameplayTag ProfileToUse, FName BoneName, bool bIncludeSelf = true,
		FHitReactImpulseParams ImpulseParams = FHitReactImpulseParams());

	/**
	 * Toggle the hit react system on or off
	 * @param bEnabled - Whether to enable or disable the hit react system
	 * @param bInterpolateState - Whether to interpolate the state change
	 * @param InterpProperties - Interpolation properties to use - will not be applied if bInterpolateState is false
	 */
	UFUNCTION(BlueprintCallable, Category=HitReact)
	void ToggleHitReactSystem(bool bEnabled, bool bInterpolateState = true, const FInterpProperties& InterpProperties = FInterpProperties());

	/**
	 * Instantly disables the system entirely if currently running, clearing all active hit reacts, if false
	 * To disable the system smoothly use ToggleHitReactSystem instead
	 * Consider using IsAnyHitReactInProgress to check if the system is currently running
	 * @return False if no hit reacts can be applied
	 */
	UFUNCTION(BlueprintNativeEvent, Category=HitReact)
	bool CanHitReact() const;

	/**
	 * Check if the hit react system should be paused
	 * @note This is probably not what you want - once resumed the hit reacts will continue from where they left off, consider using ToggleHitReactSystem instead
	 * @return True if the hit react system should be paused
	 */
	UFUNCTION(BlueprintNativeEvent, Category=HitReact)
	bool ShouldPauseHitReactSystem() const;

	/** @return Number of hit reacts currently in progress */
	UFUNCTION(BlueprintPure, Category=HitReact)
	int32 GetNumHitReactsInProgress() const;

	/** @return True if any hit reacts are currently in progress */
	UFUNCTION(BlueprintPure, Category=HitReact)
	bool IsAnyHitReactInProgress() const;
	
protected:
	UFUNCTION()
	virtual void OnMeshPoseInitialized();

	virtual void ResetHitReactSystem();

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;
	
	/** Get the mesh to simulate from the owner */
	UFUNCTION(BlueprintNativeEvent, Category=HitReact)
	USkeletalMeshComponent* GetMeshFromOwner() const;
	
	UFUNCTION(BlueprintPure, Category=HitReact)
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	/** Get the PhysicalAnimationComponent from the owner */
	UFUNCTION(BlueprintNativeEvent, Category=HitReact)
	UPhysicalAnimationComponent* GetPhysicalAnimationComponentFromOwner() const;

	/**
	 * Get the PhysicalAnimationComponent
	 * Can be null if the owner does not have a PhysicalAnimationComponent
	 * Used to set animation profiles and apply physical animation settings
	 */
	UFUNCTION(BlueprintPure, Category=HitReact)
	UPhysicalAnimationComponent* GetPhysicalAnimationComponent() const { return PhysicalAnimation; }
	
private:
	void DebugHitReactResult(const FString& Result, bool bFailed) const;
};
