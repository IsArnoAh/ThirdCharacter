// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionwarpingComponent.h"
#include "MyTPCCharacter.generated.h"


//C:\Program Files\Epic Games\UE_5.0\Engine\Plugins\Experimental\Animation\MotionWarping
UCLASS(config=Game)
class AMyTPCCharacter : public ACharacter
{
	GENERATED_BODY()
	

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	
public:
	AMyTPCCharacter();

	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;
	
	//奔跑状态，蹲伏状态
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsRun;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsCrouch;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool Standing=true;
	//默认参数设置，跳跃高度，和移动速度，
	UPROPERTY(EditAnywhere, Category = "Jump")
	float DefaultJumpZVelocity = 300.f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float RunJumpZVelocity = 400.f;
	
	UPROPERTY(EditAnywhere, Category = "Move")
	float WalkSpeed=220.0f;
	
	
	UPROPERTY(EditAnywhere, Category = "Move")
	float RunSpeed=600.0f;

	UPROPERTY(EditAnywhere, Category = "Move")
	float CrouchSpeed=200.0f;

	//攀爬的参数配置
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ClimbStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ClimbMid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ClimbEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanClimb;


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
	//奔跑函数声明
	void Run();
	//蹲伏函数声明
	UFUNCTION(BlueprintCallable, Category = "Move")
	void MyCrouch();

	//攀爬函数声明
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void MyClimb();

	//重写跳函数
	virtual  void Jump() override;

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	// Motion Warping Component
	UPROPERTY(BlueprintReadWrite,Category="Animation")
	UMotionWarpingComponent* MotionWarpingComponent;
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
};

